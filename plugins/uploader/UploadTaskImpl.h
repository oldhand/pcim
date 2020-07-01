#ifndef _UPLOAD_TASK_IMPL_H__
#define _UPLOAD_TASK_IMPL_H__

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

UPLOAD_MANAGER_START

//-----------------------------------------------------------------
struct UpLoadRange
{
	uint64_t _iFromByte;
	uint64_t _iToByte;
	UpLoadRange() : _iFromByte(0), _iToByte(0) {}
};

class UploadTask;
class UploadTaskGroup;
class UploadManager;
class MultipartByteRangesParser;

class UploadTaskImpl
{
public:
	UploadTaskImpl(UploadTask* pOwner);
	~UploadTaskImpl();

	friend class UploadManagerImpl;
	friend class ThreadTaskQueue;
	friend class UploadTaskGroupImpl;
	friend class UploadTask;
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
	inline size_t GetUpLoadedSize() const { return _iUploadedSize; };
	inline bool GetUpLoadBuffered() const { return _boolMarks._bUpLoadBuffer; };
	inline void SetRetryedTimes(int iRetryedTimes) { _iRetryTimes = iRetryedTimes; }
	void SetUploadPercent(double fPercent);
	double GetUploadPercent();
protected:
	void UpLoad(bool bHeadOnly);
	bool CheckResume();
	std::string MakeRangeString();
	void Done(bool bOk);
private:
	struct BoolFileds
	{
		uint8_t _bAutoStart :		1, 
				_bUseCache :		1,
				_bUpLoadOk :		1,
				_bUpLoadBuffer :	1,
				_bNeedResume :		1;
		BoolFileds() 
			: _bAutoStart(0)
			, _bUseCache(0)
			, _bUpLoadOk(0)
			, _bUpLoadBuffer(0)
			, _bNeedResume(0) 
		{}
	}_boolMarks;
	std::string _memory;
	size_t _iUploadedSize;
	uint64_t _iContentLength;
	std::string _url;
	std::string _unescaped;
	CURL_STATUS _eStatus;
	int _iHttpCode;
	std::vector<UpLoadRange> _uploadRanges;
	std::string _boundary;
	std::string _fileName;
	std::string _fileCacheName;
	int _iCacheId;
	int _iRetryTimes;
	double _fUploadPercent;

	pthread_mutex_t _userdataLock;

	//for file cache
	FILE * _pFile;

	//to compare with local cache file modify time
	time_t _iFileValidTime;

	CURL *_pCurlHandle;

	UploadManager* _pMgr;
	UploadTaskGroup *_pGroup;

	uint64_t _iTaskId;

	std::string _sha1;
	std::function<void(const char * pBuffer, int iSize)> _pUploadBufferOK;
	std::function<void(UploadTask* pTask)> _pUploadOK;
	std::function<void()> _pUploadFailed;
	std::function<void(double percent)> _pUploadPercent;

	MultipartByteRangesParser *_pRangeBufferParser;

	UploadTask* _pOwner;
};

UPLOAD_MANAGER_END

#endif
