#include "UploadTaskImpl.h"
#include "UploadTask.h"
#include "UploadManager.h"
#include "UploadManagerImpl.h"
#include "MultipartByteRangesParser.h"
#include "ScopedMutex.h"
#include "curl/curl.h"
#include "sqlite3.h"
#include <sstream>
#include <string>
#include <algorithm>

#ifdef __ANDROID__
#include <android/log.h>
#define LOG(fmt, args...) __android_log_print(ANDROID_LOG_INFO, "hotpatch", fmt, ##args);
#elif defined(__APPLE__)
#define LOG printf
#else
#define LOG printf
#endif

UPLOAD_MANAGER_START

#define MGR_IMPL static_cast<UploadManagerImpl*>(_pMgr->_pImpl)
#define RETRY_TIMES 10

//-----------------------------------------------

UploadTaskImpl::UploadTaskImpl(UploadTask* pOwner)
	: _pOwner(pOwner)
	, _iUploadedSize(0)
	, _iContentLength(0)
	, _iHttpCode(0)
	, _eStatus(CURL_TERMINATED)
	, _pFile(nullptr)
	, _pMgr(nullptr)
	, _pGroup(nullptr)
	, _iRetryTimes(0)
	, _pUploadFailed(nullptr)
	, _pUploadOK(nullptr)
	, _pUploadBufferOK(nullptr)
	, _pUploadPercent(nullptr)
{
	_pRangeBufferParser = new MultipartByteRangesParser();
	pthread_mutex_init(&_userdataLock, 0);
}

UploadTaskImpl::~UploadTaskImpl()
{
	_memory.clear();
	if (_pFile)
	{
		fclose(_pFile);
		_pFile = nullptr;
	}
	if (_pRangeBufferParser)
	{
		delete _pRangeBufferParser;
	}
	pthread_mutex_destroy(&_userdataLock);
}

void UploadTaskImpl::AddRange(uint64_t iForm, uint64_t iTo)
{
	UpLoadRange range;
	range._iFromByte = iForm;
	range._iToByte = iTo;
	_uploadRanges.push_back(range);
};

void UploadTaskImpl::AddByteSize(int iSize)
{
	_iUploadedSize += iSize;
}

void UploadTaskImpl::Init(const std::string& rUrl, const std::string& rCacheDir)
{
	_memory.clear();
	memset(&_boolMarks, 0, sizeof(BoolFileds));
	_boolMarks._bUseCache = true;
	_iUploadedSize = 0;
	_iContentLength = 0;
	_url = rUrl;
	_iHttpCode = 0;
	_eStatus = CURL_TERMINATED;
	_fileName = rCacheDir;
	_fileCacheName = _fileName;
}

void UploadTaskImpl::ReInit()
{
	_memory.clear();
	memset(&_boolMarks, 0, sizeof(BoolFileds));
	_boolMarks._bUseCache = true;
	_iUploadedSize = 0;
	_iContentLength = 0;
	_iHttpCode = 0;
	_eStatus = CURL_TERMINATED;
}

void UploadTaskImpl::Start()
{
	_eStatus = CURL_STARTED;
	CheckResume();
	if (_eStatus == CURL_TERMINATED)
	{
		return;
	}

	UpLoad(false);
}

void UploadTaskImpl::SetBoundary(const std::string& rBoundary)
{
	_boundary = rBoundary;
}

const std::string& UploadTaskImpl::GetBoundary()
{
	return _boundary;
}

bool UploadTaskImpl::CheckResume()
{
	//load cached info from database
	if (_boolMarks._bUseCache && !_boolMarks._bUpLoadBuffer)
	{
		MGR_IMPL->CacheBegin([this](sqlite3* db)->bool
		{
			_boolMarks._bNeedResume = false;
			std::string rangeString = MakeRangeString();
			std::string fileValidTime = to_string(_iFileValidTime);
			std::string sql = "SELECT * FROM upload_cache WHERE URL = '"
				+ _url + "' AND RANGE = '" + rangeString + "';";

			char *zErrMsg = 0;
			int iRow = 0;
			int iColumn = 0;
			char **pResult;
			int iRet = 0;
			iRet = sqlite3_get_table(db, sql.c_str(), &pResult, &iRow, &iColumn, &zErrMsg);

			if (iRow == 0)
			{
				//insert new record
				sql = "INSERT INTO upload_cache VALUES(NULL ,'" + _url + "', '"
					+ _fileCacheName + "','" + rangeString + "', 0,'" + _sha1 + "', '','" + fileValidTime + "');";
				iRet = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

				_iCacheId = sqlite3_last_insert_rowid(db);

				_fileCacheName = _pMgr->GetCachePath() + "/"
					+ (_uploadRanges.size() > 0 ? ("range_" + to_string(_iCacheId)) + "_" : "") +_fileName;
				LOG("_fileCacheName1 %s\n", _fileCacheName.c_str());

				sql = "UPDATE upload_cache SET FILENAME = '"+ _fileCacheName +"' WHERE URL = '"
					+ _url + "' AND RANGE = '" + rangeString + "'";
				iRet = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
			}
			else
			{
				std::stringstream sstream;
				sstream << pResult[iColumn];
				sstream >> _iCacheId;

				_fileCacheName = _pMgr->GetCachePath() + "/"
					+ (_uploadRanges.size() > 0 ? ("range_" + to_string(_iCacheId)) + "_" : "") + _fileName;
				LOG("_fileCacheName2 %s\n", _fileCacheName.c_str());
				//check sha1 and if file is exist
				//delete invalid cache
				struct stat _st;
				int res = stat(_fileCacheName.c_str(), &_st);

				time_t iNowTime;
				time(&iNowTime);
				if (iNowTime - _st.st_mtime > _iFileValidTime)
				{
					remove(_fileCacheName.c_str());
					res = stat(_fileCacheName.c_str(), &_st);
				}

				bool bSha1 = _sha1.length() > 0;
				bool bSha1Checked = false;
				if (bSha1)
				{
					bSha1Checked = memcmp(_sha1.c_str(), pResult[iColumn + 5], 20) == 0;
				}

				if ((res == 0 && !bSha1) || (res == 0 && bSha1 && bSha1Checked))
				{
					//check if upload ok
					int isDone;
					sstream.clear();
					sstream << pResult[iColumn + 4];
					sstream >> isDone;
					if (isDone)
					{
						//terminal task
						_boundary = pResult[iColumn + 6];
						_boolMarks._bUpLoadOk = true;
						_eStatus = CURL_TERMINATED;
					}
					else
					{
						_boolMarks._bNeedResume = true;
					}
				}
				else
				{
					sql = "UPDATE upload_cache SET DONE = '0', SHA1 = '" + _sha1 + "', VALIDE_TIME = '" + fileValidTime + "' WHERE URL = '"
						+ _url + "' AND RANGE = '" + rangeString + "'";
					iRet = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
				}
			}

			return iRet == 0;
		});
	}

	return true;
}

static size_t curl_header_parse(char *pBuffer, size_t size, size_t nmemb, void *pUserdata)
{
	UploadTaskImpl * pTaskImpl = (UploadTaskImpl*)pUserdata;
	std::string buffer(pBuffer);
	size_t iHeadLen = size * nmemb;
	size_t iIndex = buffer.find("boundary=");
	if (iIndex != std::string::npos)
	{
		std::string boundary = buffer.substr(iIndex + 9, iHeadLen - iIndex - 11);
		pTaskImpl->SetBoundary(boundary);
	}

	LOG("%s\n", pBuffer);

	return size * nmemb;
}

static size_t curl_write_data(char * ptr, size_t size, size_t nmemb, void * userdata)
{
	UploadTaskImpl * pTaskImpl = (UploadTaskImpl *)userdata;
	pTaskImpl->SetRetryedTimes(0);
	if (pTaskImpl->GetUpLoadBuffered())
	{
		pTaskImpl->WriteMemory(ptr, size * nmemb);
		pTaskImpl->AddByteSize(size * nmemb);
	}
	else
	{
		FILE * f = pTaskImpl->PrepareForWrite();
		if (f)
		{
			pTaskImpl->GetRangeBufferParser().MultipartParserExecute(ptr, size * nmemb, "--" + pTaskImpl->GetBoundary(), f, pTaskImpl);
			size_t written = size * nmemb;
			pTaskImpl->AddByteSize(written);
			return written;
		}
		else
		{
			LOG("PrepareForWrite error, open file faild!\n");
		}
	}

	return size * nmemb;
}

static int curl_progress_info(void *clientp,
							  double dltotal,
							  double dlnow,
							  double ultotal,
							  double ulnow)
{
	if (dltotal <= 0)
		return 0;
	UploadTaskImpl * pTaskImp = (UploadTaskImpl *)clientp;

	size_t iUploadedSize = pTaskImp->GetUpLoadedSize();
	dlnow += iUploadedSize;
	dltotal += iUploadedSize;

	//LOG("curl_progress:%s, %.2lf %%\n", pTaskImp->GetOutputPath().c_str(), dlnow / dltotal * 100);
	pTaskImp->SetUploadPercent(dlnow / dltotal * 100);

	return 0;
}

double UploadTaskImpl::GetUploadPercent()
{
	ScopedMutex lock(&_userdataLock);
	return _fUploadPercent;
}

void UploadTaskImpl::SetUploadPercent(double fPercent)
{
	ScopedMutex lock(&_userdataLock);
	_fUploadPercent = fPercent;
}

//resize buffered datas when upload some small datas, like vfs head
void UploadTaskImpl::WriteMemory(char* pBuffer, int iSize)
{
	if (iSize > 0)
	{
		_memory.append(pBuffer, iSize);
	}
}

void UploadTaskImpl::UpLoad(bool bHeadOnly)
{
	_pCurlHandle = curl_easy_init();

	//pecify URL to get
	curl_easy_setopt(_pCurlHandle, CURLOPT_URL, _url.c_str());
	curl_easy_setopt(_pCurlHandle, CURLOPT_LOW_SPEED_LIMIT, 10L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_LOW_SPEED_TIME, 60L);

	int iLen;
	char *unescaped = curl_easy_unescape(_pCurlHandle, _url.c_str(), _url.length(), &iLen);
	_unescaped = std::string(unescaped);
	curl_free(unescaped);

	//setopts
	curl_easy_setopt(_pCurlHandle, CURLOPT_HEADERFUNCTION, curl_header_parse);
	curl_easy_setopt(_pCurlHandle, CURLOPT_HEADERDATA, (void*)this);
	curl_easy_setopt(_pCurlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_PROGRESSFUNCTION, curl_progress_info);
	curl_easy_setopt(_pCurlHandle, CURLOPT_PROGRESSDATA, (void*)this);
	curl_easy_setopt(_pCurlHandle, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_CONNECTTIMEOUT, 20L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_FORBID_REUSE, 1L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_DNS_USE_GLOBAL_CACHE, 1L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_FAILONERROR, 1L);
	curl_easy_setopt(_pCurlHandle, CURLOPT_WRITEDATA, (void*)this);
	curl_easy_setopt(_pCurlHandle, CURLOPT_WRITEFUNCTION, curl_write_data);

	int iRangeSize = _uploadRanges.size();
	if (iRangeSize > 0 && !_boolMarks._bNeedResume)
	{
		LOG("MakeRangeString\n");
		std::string sRange = MakeRangeString();
		LOG("%s\n", sRange.c_str());
		curl_easy_setopt(_pCurlHandle, CURLOPT_RANGE, sRange.c_str());
	}

	if (_boolMarks._bNeedResume)
	{
		// range upload, FROM-TO byte 
		if (iRangeSize > 0)
		{
			LOG("MakeUnuploadRanges\n");
			std::string sRange = _pRangeBufferParser->MakeUnuploadRanges(_uploadRanges, _fileCacheName);
			LOG("%s\n", sRange.c_str());
			curl_easy_setopt(_pCurlHandle, CURLOPT_RANGE, sRange.c_str());
		}
		else
		{
			struct stat _st;
			stat(_fileCacheName.c_str(), &_st);
			curl_easy_setopt(_pCurlHandle, CURLOPT_RESUME_FROM, (long)_st.st_size);
			_iUploadedSize = _st.st_size;
		}

	}

	if (bHeadOnly)
	{
		curl_easy_setopt(_pCurlHandle, CURLOPT_HEADER, 1);
		curl_easy_setopt(_pCurlHandle, CURLOPT_NOBODY, 1);
	}

	//task will unexpected finished without user-agent field sometimes
	//some servers don't like requests that are made without a user-agent field, so we provide one
	curl_easy_setopt(_pCurlHandle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.8) Gecko/20050511 Firefox/1.0.4");

	MGR_IMPL->_httpHandlerMap[_pCurlHandle] = _pOwner;
	curl_multi_add_handle(MGR_IMPL->_pCurlMulti, _pCurlHandle);
}

std::string UploadTaskImpl::MakeRangeString()
{
	int iRangeSize = _uploadRanges.size();
	if (iRangeSize > 0)
	{
		std::string sRange = "";
		for (int i = 0; i < iRangeSize; ++i)
		{
			if (i != 0)
			{
				sRange += ',';
			}
			const UpLoadRange& rRange = _uploadRanges[i];
			sRange += to_string(rRange._iFromByte) + "-" + to_string(rRange._iToByte);
		}
		return sRange;
	}
	return "Range_All";
}

FILE * UploadTaskImpl::PrepareForWrite()
{
	if (_fileCacheName == "")
	{
		return nullptr;
	}
	if (_pFile)
		return _pFile;


	if (_boolMarks._bNeedResume)
	{
		//_pFile = fopen(_fileCacheName.c_str(), "ab+");
		fopen_s(&_pFile,_fileCacheName.c_str(), "ab+");
	}
	else
	{
		//_pFile = fopen(_fileCacheName.c_str(), "wb+");
		fopen_s(&_pFile, _fileCacheName.c_str(), "wb+");
	}
	return _pFile;
}

void UploadTaskImpl::Done(bool bOk)
{
	if (_pFile)
	{
		LOG("%s done.\n", _fileName.c_str());
		fclose(_pFile);
		_pFile = nullptr;
	}

	if (bOk)
	{
		_boolMarks._bUpLoadOk = true;
		//update cache database
		MGR_IMPL->CacheBegin([this](sqlite3* db)->bool
		{
			char *zErrMsg = 0;
			int iRet = 0;

			std::string fileValidTime = to_string(_iFileValidTime);
			std::string sql = "UPDATE upload_cache SET DONE = '1',BOUNARY = '" + _boundary + "', VALIDE_TIME = '" + fileValidTime + "' WHERE URL = '"
				+ _url + "' AND RANGE = '" + MakeRangeString() + "'";

			return sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg) == 0;
		});

		_eStatus = CURL_TERMINATED;
	}
	else
	{
		//to retry
		if (_iRetryTimes <= RETRY_TIMES)
		{
			ReInit();
			Start();
			_iRetryTimes++;
		}
		else
		{
			_eStatus = CURL_TERMINATED;
		}
	}
}

UPLOAD_MANAGER_END
