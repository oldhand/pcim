#ifndef _UPLOAD_MANAGER_IMPL_H__
#define _UPLOAD_MANAGER_IMPL_H__

#include "Defines.h"


extern "C" {
	#include <pthread.h>
	#include <semaphore.h>
}




struct sqlite3;
typedef void CURLM;
typedef void CURL;

UPLOAD_MANAGER_START

//-----------------------------------------------------------------
class UploadManager;
class ThreadTaskQueue;
class UploadManagerImpl
{
public:
	UploadManagerImpl(UploadManager* pOwner);
	~UploadManagerImpl();

	friend class UploadTaskImpl;

	//Init and DeInit Manager, should be called only once
	//pass application writable path
	void Init(const std::string& rCacheDatabaseDir);
	void DeInit();
	//create a task
	TaskPtr CreateUpLoadTask(const std::string& rUrl);

	//add task to upload queue
	void AddUpLoadTask(TaskPtr pTask);

	void AddTaskGroup(TaskGroupPtr pTaskGroup);

	// application call this api per-frame to to informed of upload events
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
	std::map<CURL*, UploadTask*> _httpHandlerMap;

	uint64_t _iNextTaskId;

	bool _bInited;

	UploadManager* _pOwner;
};

UPLOAD_MANAGER_END

#endif
