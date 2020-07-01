#ifndef _DOWNLOAD_TASK_IMPL_H__
#define _DOWNLOAD_TASK_IMPL_H__

#include "Defines.h" 
extern "C" {
#include <pthread.h> 
}


typedef void CURL;

namespace hotpatch
{
	class HotPatchInternal;
}
//-----------------------------------------------------------------

DOWNLOAD_MANAGER_START

//-----------------------------------------------------------------
struct DownLoadRange
{
	uint64_t _iFromByte;
	uint64_t _iToByte;
	DownLoadRange() : _iFromByte(0), _iToByte(0) {}
};

class DownloadTask;
class DownloadTaskGroup;
class DownloadManager;
class MultipartByteRangesParser;

class DownloadTaskImpl
{
public:
	DownloadTaskImpl(DownloadTask* pOwner);
	~DownloadTaskImpl();

	friend class DownloadManagerImpl;
	friend class ThreadTaskQueue;
	friend class DownloadTaskGroupImpl;
	friend class DownloadTask;
	friend class MultipartByteRangesParser;
	friend class hotpatch::HotPatchInternal;

	void Init(const std::string& rUrl, const std::string& rCacheDir);
	//init for retry
	void ReInit();
	void Start();
	void WriteMemory(char* pBuffer, int iSize);
	void AddRange(uint64_t iForm, uint64_t iTo);
	void AddByteSize(int iSize);

	FILE * PrepareForWrite();
	void SetBoundary(const std::string& rBoundary);
	const std::string& GetBoundary();
	MultipartByteRangesParser& GetRangeBufferParser() { return *_pRangeBufferParser; }

	inline const std::string& GetOutputPath() const { return _fileCacheName; };
	inline size_t GetDownLoadedSize() const { return _iDownloadedSize; };
	inline bool GetDownLoadBuffered() const { return _boolMarks._bDownLoadBuffer; };
	inline void SetRetryedTimes(int iRetryedTimes) { _iRetryTimes = iRetryedTimes; }
	void SetDownloadPercent(double fPercent);
	double GetDownloadPercent();
protected:
	void DownLoad(bool bHeadOnly);
	bool CheckResume();
	std::string MakeRangeString();
	void Done(bool bOk);
private:
	struct BoolFileds
	{
		uint8_t _bAutoStart :		1, 
				_bUseCache :		1,
				_bDownLoadOk :		1,
				_bDownLoadBuffer :	1,
				_bNeedResume :		1;
		BoolFileds() 
			: _bAutoStart(0)
			, _bUseCache(0)
			, _bDownLoadOk(0)
			, _bDownLoadBuffer(0)
			, _bNeedResume(0) 
		{}
	}_boolMarks;
	std::string _memory;
	size_t _iDownloadedSize;
	uint64_t _iContentLength;
	std::string _url;
	std::string _unescaped;
	CURL_STATUS _eStatus;
	int _iHttpCode;
	std::vector<DownLoadRange> _downloadRanges;
	std::string _boundary;
	std::string _fileName;
	std::string _fileCacheName;
	int _iCacheId;
	int _iRetryTimes;
	double _fDownloadPercent;

	pthread_mutex_t _userdataLock;

	//for file cache
	FILE * _pFile;

	//to compare with local cache file modify time
	time_t _iFileValidTime;

	CURL *_pCurlHandle;

	DownloadManager* _pMgr;
	DownloadTaskGroup *_pGroup;

	uint64_t _iTaskId;

	std::string _sha1;
	std::function<void(const char * pBuffer, int iSize)> _pDownloadBufferOK;
	std::function<void(DownloadTask* pTask)> _pDownloadOK;
	std::function<void()> _pDownloadFailed;
	std::function<void(double percent)> _pDownloadPercent;

	MultipartByteRangesParser *_pRangeBufferParser;

	DownloadTask* _pOwner;
};

DOWNLOAD_MANAGER_END

#endif
