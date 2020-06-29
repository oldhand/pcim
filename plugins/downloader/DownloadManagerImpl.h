#ifndef _DOWNLOAD_MANAGER_IMPL_H__
#define _DOWNLOAD_MANAGER_IMPL_H__

#include "Defines.h"


extern "C" {
	#include <pthread.h>
	#include <semaphore.h>
}




struct sqlite3;
typedef void CURLM;
typedef void CURL;

DOWNLOAD_MANAGER_START

//-----------------------------------------------------------------
class DownloadManager;
class ThreadTaskQueue;
class DownloadManagerImpl
{
public:
	DownloadManagerImpl(DownloadManager* pOwner);
	~DownloadManagerImpl();

	friend class DownloadTaskImpl;

	//Init and DeInit Manager, should be called only once
	//pass application writable path
	void Init(const std::string& rCacheDatabaseDir);
	void DeInit();
	//create a task
	TaskPtr CreateDownLoadTask(const std::string& rUrl);

	//add task to download queue
	void AddDownLoadTask(TaskPtr pTask);

	void AddTaskGroup(TaskGroupPtr pTaskGroup);

	// application call this api per-frame to to informed of download events
	void Update();

	const std::string& GetCachePath() const { return _cacheDatabaseDir; };

	void ClearCache(const std::string& rUrl);
protected:
	static void * _NetThread(void *);
	void _ThreadExcute();
	int CurlMultiSelect(CURLM* pCurlMulti);
	void InitCache();
	void CacheBegin(std::function<bool(sqlite3* db)> pExcute);
	void UpdateTaskGroup();

	void WaitDeInit();
	void ThreadDeInitFinished();

	//wait for semaphore
	void Wait();
	//post a semaphore
	void Resume();
private:

	pthread_t _taskQueueThread;
	ThreadTaskQueue* _taskQueue;
	ThreadTaskQueue* _runningQueue;
	ThreadTaskQueue* _finishedQueue;

	CURLM * _pCurlMulti;

	/*
		_cacheLock: lock when access cache database
		_semaphore: resume network thread when a new task added
		_deinitSemaphore: wait for deinit finished
	*/
	pthread_mutex_t _cacheLock;
	sem_t _semaphore;
	sem_t _deinitSemaphore;

	std::string _cacheDatabaseDir;

	std::vector<TaskGroupPtr> _taskGroups;

	//only read and write by network thread 
	std::map<CURL*, DownloadTask*> _httpHandlerMap;

	uint64_t _iNextTaskId;

	bool _bInited;

	DownloadManager* _pOwner;
};

DOWNLOAD_MANAGER_END

#endif
