//author: linyuanxuan
//multipart byte ranges parser
#include "MultipartByteRangesParser.h"

#include <fcntl.h>

#ifndef _MSC_VER
#include <unistd.h>
#include <alloca.h>
#include <sys/mman.h>
#include <cinttypes>
#else

#if _MSC_VER > 1600
#include <cinttypes>
#endif

#include <windows.h>
#include <io.h>
#include <malloc.h>
#define S_IRUSR S_IREAD
#define S_IWUSR S_IWRITE
#pragma warning (disable : 4996)
#endif

DOWNLOAD_MANAGER_START

#define LF 10
#define CR 13 

void MultipartByteRangesParser::Reset()
{
	std::set<int> closed;
	for (std::map<std::string, RangeDescribe>::iterator iter = _multiRangeDataMap.begin(); iter != _multiRangeDataMap.end(); ++iter)
	{
		if (closed.find(iter->second._fd) == closed.end())
		{
			closed.insert(iter->second._fd);
			close(iter->second._fd);
		}
	}

	_multiRangeDataMap.clear();
	_eState = START;
	_iDounaryIndex = 0;
	_iPrevToByte = 0;
	_iDataSize = 0;
};

void MultipartByteRangesParser::AnalyzeRangeBuffers(const std::string& rFileName)
{
	int rangeFd = open(rFileName.c_str(),
#if defined(_MSC_VER) 
		O_RDONLY | O_BINARY, S_IREAD);
#else
		O_RDONLY);
#endif

	if (rangeFd > 0)
	{
		struct stat _st;
		stat(rFileName.c_str(), &_st);
		uint64_t iFrom, iTo;
		uint64_t iFileOffset = 0;
		size_t iDataSize = sizeof(uint64_t);
		while (iFileOffset < _st.st_size)
		{
			lseek(rangeFd, iFileOffset, SEEK_SET);
			read(rangeFd, &iFrom, iDataSize);
			read(rangeFd, &iTo, iDataSize);

			RangeDescribe desc;
			desc._fd = rangeFd;
			desc._iOffset = iFileOffset + iDataSize * 2;
			std::string range = to_string(iFrom) + "-" + to_string(iTo);
			_multiRangeDataMap[range] = desc;

			iFileOffset += (iDataSize * 2 + iTo - iFrom + 1);
		}
	}
	else
	{
		printf("AnalyzeRangeBuffers, file %s error!\n", rFileName.c_str());
	}
}

std::string MultipartByteRangesParser::MakeUndownloadRanges(std::vector<DownLoadRange>& rExceptRanges, const std::string& rFileName)
{
	std::string result = "";
	FILE *pFile = fopen(rFileName.c_str(), "rb");
	if (pFile)
	{
		struct stat _st;
		stat(rFileName.c_str(), &_st);

		uint64_t iFileSize = 0;
		uint64_t iFrom = 0;
		uint64_t iTo = 0;
		std::string range = "";
		bool bNeedRead = (_st.st_size != 0);

		for (int i = 0, iLen = rExceptRanges.size(); i < iLen; ++i)
		{
			if (bNeedRead)
			{
				fread(&iFrom, sizeof(uint64_t), 1, pFile);
				fread(&iTo, sizeof(uint64_t), 1, pFile);
				iFileSize += 16;
			}

			uint64_t iReadSize = iTo - iFrom + 1;
			if (iReadSize + iFileSize > _st.st_size && bNeedRead)
			{
				//download uncompleted
				range = to_string(_st.st_size - iFileSize + iFrom) + "-" + to_string(iTo);
				if (result.size() > 0)
				{
					result += ",";
				}
				result += range;
				_iPrevToByte = iTo;
				bNeedRead = false;
			}
			else
			{			
				if (bNeedRead)
				{
					fseek(pFile, iTo - iFrom + 1, SEEK_CUR);
					iFileSize += iTo - iFrom + 1;
				}
				else
				{
					range = to_string(rExceptRanges[i]._iFromByte) + "-" + to_string(rExceptRanges[i]._iToByte);
					if (result.size() > 0)
					{
						result += ",";
					}
					result += range;
				}
			}
		}
		fclose(pFile);
	}
	return result;
}

void MultipartByteRangesParser::MultipartParserExecute(const char *pBuffer, size_t iSize, const std::string& rBoundary, FILE *f, DownloadTaskImpl* pTaskImpl)
{
	if (rBoundary == "--")
	{
		if (pTaskImpl->_downloadRanges.size() == 1)
		{
			if (_iPrevToByte != pTaskImpl->_downloadRanges[0]._iToByte)
			{
				fwrite(&pTaskImpl->_downloadRanges[0]._iFromByte, sizeof(uint64_t), 1, f);
				fwrite(&pTaskImpl->_downloadRanges[0]._iToByte, sizeof(uint64_t), 1, f);
				_iPrevToByte = pTaskImpl->_downloadRanges[0]._iToByte;
			}
			fwrite(pBuffer, iSize, 1, f);
		}
		else
		{
			fwrite(pBuffer, iSize, 1, f);
		}
		return;
	}

	size_t i = 0;
	size_t iBoundarySize = rBoundary.size();
	std::string field = "";
	std::string value = "";
	std::string curRange = "";
	char c;
	while (i < iSize)
	{
		c = pBuffer[i];
		switch (_eState)
		{
		case START:
		{
			_iDounaryIndex = 0;
			_eState = START_BOUNARY;
		}
		case START_BOUNARY:
		{
			if (_iDounaryIndex == iBoundarySize)
			{
				if (c != CR && c != '-')
				{
					return;
				}
				_iDounaryIndex++;
				break;
			}
			else if (_iDounaryIndex == (iBoundarySize + 1))
			{
				if (c != LF && c != '-')
				{
					return;
				}
				_iDounaryIndex = 0;
				if (c == '-')
				{
					_eState = END;
				}
				else
				{
					_eState = HEADERS_FIELD_START;
				}
				break;
			}
			if (c != rBoundary[_iDounaryIndex])
			{
				if (c != CR && c != LF)
				{
					return;
				}
			}
			else
			{
				_iDounaryIndex++;
			}
			break;
		}
		case HEADERS_FIELD_START:
		{
			_eState = HEADERS_FIELD;
			field = "";
		}
		case HEADERS_FIELD:
		{
			if (c == CR)
			{
				_eState = HEADERS_ALMOST_DONE;
				break;
			}
			if (c == ':')
			{
				_eState = HEADER_VALUE_START;
				break;
			}
			field += c;
			break;
		}
		case HEADERS_ALMOST_DONE:
		{
			if (c != LF)
			{
				return;
			}
			_eState = PART_DATA_START;
			break;
		}
		case HEADER_VALUE_START:
		{
			value = "";
			if (c == ' ')
			{
				break;
			}
			_eState = HEADER_VALUE;
		}
		case HEADER_VALUE:
		{
			if (c == CR)
			{
				_eState = HEADER_VALUE_ALMOST_DONE;
				if (field == "Content-Range")
				{
					uint64_t iFrom, iTo, iAllSize;
#ifdef _MSC_VER 

#if _MSC_VER > 1600
					sscanf(value.c_str(), "bytes %" PRIu64 "-%" PRIu64 "/%" PRIu64 "", &iFrom, &iTo, &iAllSize);
#else
					sscanf(value.c_str(), "bytes %I64u-%I64u/%I64u", &iFrom, &iTo, &iAllSize);
#endif

#else
					sscanf(value.c_str(), "bytes %" PRIu64 "-%" PRIu64 "/%" PRIu64 "", &iFrom, &iTo, &iAllSize);
#endif // _MSC_VER
					_iDataSize = iTo - iFrom + 1;
					if (iTo != _iPrevToByte)
					{
						fwrite(&iFrom, sizeof(uint64_t), 1, f);//from
						fwrite(&iTo, sizeof(uint64_t), 1, f);//to
						fflush(f);
					}
				}

				break;
			}
			value += c;
			break;
		}
		case HEADER_VALUE_ALMOST_DONE:
		{
			if (c != LF)
			{
				return;
			}
			_eState = HEADERS_FIELD_START;
			break;
		}
		case PART_DATA_START:
		{
			_eState = PART_DATA;
		}
		case PART_DATA:
		{
			uint64_t iReadSize = min(uint64_t(iSize - i), _iDataSize);
			fwrite(pBuffer + i, iReadSize, 1, f);
			i += iReadSize;
			_iDataSize = max(uint64_t(0), _iDataSize - iReadSize);		
			if (0 == _iDataSize)
			{
				_eState = START;
			}		
			break;
		}
		case END:
		default:break;
		}

		++i;
	}
}

MultipartByteRangesParser::MultipartByteRangesParser()
	: _eState(START)
{
	Reset();
}

MultipartByteRangesParser::~MultipartByteRangesParser()
{
	
}

DOWNLOAD_MANAGER_END