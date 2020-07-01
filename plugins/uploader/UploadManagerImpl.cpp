#include "UploadManagerImpl.h"
#include "UploadTaskImpl.h"
#include "UploadTaskGroupImpl.h"
#include "curl/curl.h"
#include "UploadTask.h"
#include "UploadTaskGroup.h"

#include "ScopedMutex.h"
#include "sqlite3.h"
#include <sstream>

#ifdef _MSC_VER
#include <WinSock2.h>
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define LOG(fmt, args...) __android_log_print(ANDROID_LOG_INFO, "hotpatch", fmt, ##args);
#elif defined(__APPLE__)
#define LOG printf
#else
#define LOG printf
#endif

UPLOAD_MANAGER_START

//-----------------------------------------------------------------
class ThreadTaskQueue
{
public:
	ThreadTaskQueue();
	~ThreadTaskQueue();
	void FetchTask(TaskPtr& rTask);
	void AddTask(TaskPtr pTask);
	//put finished task to rQueue
	void FetchFinisedTasks(ThreadTaskQueue& rQueue);
	//emit events, must be call in main thread
	void EmitFinishedEvents();
private:
	pthread_mutex_t _queueLock;
	std::vector<TaskPtr> _taskQueue;
};

ThreadTaskQueue::ThreadTaskQueue()
{
	pthread_mutex_init(&_queueLock, 0);
}

ThreadTaskQueue::~ThreadTaskQueue()
{
	pthread_mutex_destroy(&_queueLock);
}

void ThreadTaskQueue::FetchTask(TaskPtr& rTask)
{
	ScopedMutex lock(&_queueLock);
	if (_taskQueue.size() > 0)
	{
		rTask = _taskQueue.back();
		_taskQueue.pop_back();
		LOG("FetchTask ,task queue size: %d\n", _taskQueue.size());
	}
	else
	{
		rTask = nullptr;
	}
}

void ThreadTaskQueue::AddTask(TaskPtr pTask)
{
	ScopedMutex lock(&_queueLock);
	_taskQueue.push_back(pTask);
	LOG("AddTask, task queue size: %d\n", _taskQueue.size());
}

void ThreadTaskQueue::FetchFinisedTasks(ThreadTaskQueue& rQueue)
{
	ScopedMutex lock(&_queueLock);
	if (_taskQueue.size() > 0)
	{
		for (std::vector<TaskPtr>::iterator it = _taskQueue.begin(); it != _taskQueue.end(); )
		{
			TaskPtr task = *it;
			UploadTaskImpl* pTaskImpl = UPLOAD_TASK_IMPL(task->_pImpl);
			if (pTaskImpl->_eStatus == CURL_TERMINATED)
			{
				rQueue.AddTask(task);
				it = _taskQueue.erase(it);
				continue;
			}
			else
			{
				//emit percent call back
				if (pTaskImpl->_pUploadPercent)
					pTaskImpl->_pUploadPercent(pTaskImpl->GetUploadPercent());
				if (pTaskImpl->_pGroup)
					pTaskImpl->_pGroup->OnTaskProcessed(task.get());
			}
			++it;
		}
		//printf("FetchFinisedTasks, task queue size: %d\n", _taskQueue.size());
	}
}

void ThreadTaskQueue::EmitFinishedEvents()
{
	ScopedMutex lock(&_queueLock);
	if (_taskQueue.size() > 0)
	{
		for (std::vector<TaskPtr>::iterator it = _taskQueue.begin(); it != _taskQueue.end(); )
		{
			TaskPtr task = *it;
			UploadTaskImpl* pTaskImpl = UPLOAD_TASK_IMPL(task->_pImpl);
			if (pTaskImpl->_boolMarks._bUpLoadOk)
			{
				//emit events
				if (pTaskImpl->_pUploadBufferOK)
				{
					pTaskImpl->_pUploadBufferOK(pTaskImpl->_memory.c_str(), (int)pTaskImpl->_memory.size());
				}

				if (pTaskImpl->_pUploadOK)
				{
					pTaskImpl->_pUploadOK(task.get());
				}

				if (pTaskImpl->_pGroup)
				{
					pTaskImpl->_pGroup->OnTaskFinished(task.get());
				}
			}
			else
			{
				//the failed task
				if (pTaskImpl->_pUploadFailed)
				{
					pTaskImpl->_pUploadFailed();
				}
			}
			it = _taskQueue.erase(it);
		}
	}
}

//------------------------------------------------------------------------------------

UploadManagerImpl::UploadManagerImpl(UploadManager* pOwner)
	: _pOwner(pOwner)
	, _bInited(false)
{
	_taskQueue = new ThreadTaskQueue;
	_runningQueue = new ThreadTaskQueue;
	_finishedQueue = new ThreadTaskQueue;
}

UploadManagerImpl::~UploadManagerImpl()
{
	delete _taskQueue;
	delete _runningQueue;
	delete _finishedQueue;
}

void UploadManagerImpl::Init(const std::string& rCacheDatabaseDir)
{
	if (!_bInited)
	{
		_bInited = true;

		curl_global_init(CURL_GLOBAL_ALL);

		_pCurlMulti = curl_multi_init();

		pthread_mutex_init(&_cacheLock, 0);
		sem_init(&_semaphore, 0, 0);
		sem_init(&_deinitSemaphore, 0, 0);

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, 1);
		pthread_create(&_taskQueueThread, &attr, UploadManagerImpl::_NetThread, this);
		pthread_attr_destroy(&attr);

		_cacheDatabaseDir = rCacheDatabaseDir;
		char &rBack = _cacheDatabaseDir.back();
		if (rBack == '\\' || rBack == '/')
		{
			_cacheDatabaseDir.pop_back();
		}

		srand((int)time(NULL));
	}
}

void UploadManagerImpl::InitCache()
{
	//check cache database
	CacheBegin([](sqlite3* db)->bool
	{
		//check table
		int iRet;
		char *zErrMsg = 0;
		std::string sql = "CREATE TABLE upload_cache(ID INTEGER PRIMARY KEY,URL VARCHAR(512), FILENAME VARCHAR(512),";
		sql +=  "RANGE VARCHAR(4096), DONE BOOLEAN, SHA1 VARCHAR(30), BOUNARY VARCHAR(100), VALIDE_TIME VARCHAR(50));";

		iRet = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

		//delete invalid cache
		sql = "select * from upload_cache;";
		int iRow = 0;
		int iColumn = 0;
		char **pResult;

		iRet = sqlite3_get_table(db, sql.c_str(), &pResult, &iRow, &iColumn, &zErrMsg);
		if (iRow)
		{
			std::stringstream sstream;
			for (int i = 1; i <= iRow; i++)
			{
				int fileIndex = i * iColumn + 2;
				struct stat _st;
				int res = stat(pResult[fileIndex], &_st);

				time_t iMTime = 0, iNowTime;
				time(&iNowTime);
				sstream.clear();
				sstream << pResult[i * iColumn + 7];
				sstream >> iMTime;
				if (iNowTime - _st.st_mtime > iMTime || res != 0)
				{
					//delete data
					remove(pResult[fileIndex]);
					sql = "delete from upload_cache where URL = '" 
						+ std::string(pResult[i * iColumn + 1]) + "' and RANGE = '" + std::string(pResult[i * iColumn + 3]) + "';";
					iRet = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
				}
			}
		}

		return iRet == 0;
	});
}

void UploadManagerImpl::CacheBegin(std::function<bool(sqlite3 * db)> pExcute)
{
	ScopedMutex lock(&_cacheLock);

	sqlite3 *pCacheDB = NULL;
	int rc;
	std::string dbName = _cacheDatabaseDir + "/upload_cache.db";
	rc = sqlite3_open(dbName.c_str(), &pCacheDB);
	if (rc)
	{
		LOG("Can¡¯t open database: %s\n", sqlite3_errmsg(pCacheDB));
		sqlite3_close(pCacheDB);
		return;
	}

	if (pExcute)
	{
		char *zErrMsg = 0;
		sqlite3_exec(pCacheDB, "begin transaction", 0, 0, &zErrMsg);
		LOG("begin transaction\n");
		if (pExcute(pCacheDB))
		{
			sqlite3_exec(pCacheDB, "commit transaction", 0, 0, &zErrMsg);
			LOG("committed transaction\n");
		}
		else
		{
			sqlite3_exec(pCacheDB, "rollback transaction", 0, 0, &zErrMsg);
			LOG("sql error, rollback transaction\n");
		}
	}

	sqlite3_close(pCacheDB);
}

void UploadManagerImpl::ClearCache(const std::string& rUrl)
{
	CacheBegin([rUrl](sqlite3* db)->bool
	{
		//check table
		int iRet;
		char *zErrMsg = 0;
		std::string sql = "select * from upload_cache where URL = '" + rUrl + "';";

		int iRow = 0;
		int iColumn = 0;
		char **pResult;
		iRet = sqlite3_get_table(db, sql.c_str(), &pResult, &iRow, &iColumn, &zErrMsg);
		if (iRow)
		{
			for (int i = 1; i <= iRow; i++)
			{
				int fileIndex = i * iColumn + 2;
				remove(pResult[fileIndex]);
			}

			//delete data
			sql = "delete from upload_cache where URL = '" + rUrl + "';";
			iRet = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
		}

		return iRet == 0;
	});
}

int UploadManagerImpl::CurlMultiSelect(CURLM* pCurlMulti)
{
	struct timeval timeout_tv;
	fd_set fd_read;
	fd_set fd_write;
	fd_set fd_except;
	int max_fd = -1;

	FD_ZERO(&fd_read);
	FD_ZERO(&fd_write);
	FD_ZERO(&fd_except);

	timeout_tv.tv_sec = 1;
	timeout_tv.tv_usec = 0;

	curl_multi_fdset(_pCurlMulti, &fd_read, &fd_write, &fd_except, &max_fd);

	int res = select(max_fd + 1, &fd_read, &fd_write, &fd_except, &timeout_tv);

	return res;
}

void UploadManagerImpl::WaitDeInit()
{
	sem_wait(&_deinitSemaphore);
}

void UploadManagerImpl::ThreadDeInitFinished()
{
	sem_post(&_deinitSemaphore);
}

void UploadManagerImpl::Resume()
{
	sem_post(&_semaphore);
}

void UploadManagerImpl::Wait()
{
	sem_wait(&_semaphore);
}

void* UploadManagerImpl::_NetThread(void * mgr)
{
	((UploadManagerImpl*)mgr)->_ThreadExcute();

	return 0;
}

void UploadManagerImpl::_ThreadExcute()
{
	InitCache();

	while (_bInited)
	{

		TaskPtr pTask = nullptr;
		_taskQueue->FetchTask(pTask);
		while (pTask != nullptr)
		{
			_runningQueue->AddTask(pTask);
			UPLOAD_TASK_IMPL(pTask->_pImpl)->Start();
			_taskQueue->FetchTask(pTask);
		}

		int iRunningHandles = 0;
		while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(_pCurlMulti, &iRunningHandles));
		if (iRunningHandles)
		{
			int loopTimes = 100;
			while (iRunningHandles && (loopTimes--))
			{
				if (CurlMultiSelect(_pCurlMulti) != -1)
				{
					while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(_pCurlMulti, &iRunningHandles));
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			Wait();
		}

		if (!_bInited)
		{
			break;
		}

		//process result
		int iMsgs;
		CURLMsg* pMsg;
		while (pMsg = curl_multi_info_read(_pCurlMulti, &iMsgs))
		{
			if (CURLMSG_DONE == pMsg->msg)
			{
				UploadTask* task = _httpHandlerMap[pMsg->easy_handle];
				UploadTaskImpl* pImpl = UPLOAD_TASK_IMPL(task->_pImpl);
				if (pMsg->data.result == CURLE_OK)
				{
					pImpl->Done(true);
				}
				else
				{
					pImpl->Done(false);
					LOG("curl_multi_info_read curl error, prepare to retry. error code: %d\n", pMsg->data.result);
				}
				_httpHandlerMap.erase(pMsg->easy_handle);
				curl_multi_remove_handle(_pCurlMulti, pMsg->easy_handle);
				curl_easy_cleanup(pMsg->easy_handle);
			}
		}
	}

	//signal main thread to resume
	ThreadDeInitFinished();
}

void UploadManagerImpl::DeInit()
{
	_bInited = false;

	//resume thread to finish and clean
	Resume();

	WaitDeInit();

	pthread_mutex_destroy(&_cacheLock);
	sem_destroy(&_semaphore);
	sem_destroy(&_deinitSemaphore);

	curl_multi_cleanup(_pCurlMulti);
	curl_global_cleanup();
}

void UploadManagerImpl::AddUpLoadTask(TaskPtr pTask)
{
	_taskQueue->AddTask(pTask);

	Resume();
}

void UploadManagerImpl::AddTaskGroup(TaskGroupPtr pTaskGroup)
{
	_taskGroups.push_back(pTaskGroup);
	UploadTaskGroupImpl* pTaskGroupImpl = UPLOAD_TASKGROUP_IMPL(pTaskGroup->_pImpl);
	for (int i = 0, n = (int)pTaskGroupImpl->_tasks.size(); i < n; ++i)
	{
		_taskQueue->AddTask(pTaskGroupImpl->_tasks[i]);
	}
	pTaskGroupImpl->_tasks.clear();

	Resume();
}

void UploadManagerImpl::Update()
{
	if (_bInited)
	{
		_runningQueue->FetchFinisedTasks(*_finishedQueue);
		_finishedQueue->EmitFinishedEvents();
		
		UpdateTaskGroup();
	}
}

void UploadManagerImpl::UpdateTaskGroup()
{
	for (std::vector<TaskGroupPtr>::iterator taskGroup = _taskGroups.begin(); taskGroup != _taskGroups.end(); )
	{
		bool bDone = true;
		double fAllPercent = 0;;
		UploadTaskGroupImpl* pTaskGroupImpl = UPLOAD_TASKGROUP_IMPL((*taskGroup)->_pImpl);
		for (std::map<uint64_t, bool>::iterator iter = pTaskGroupImpl->_taskIdFinishedMap.begin();
			 iter != pTaskGroupImpl->_taskIdFinishedMap.end(); ++iter)
		{
			if (iter->second == false)
				bDone = false;

			fAllPercent += pTaskGroupImpl->_taskPercentMap[iter->first];
		}

		if (pTaskGroupImpl->_pUploadPercent)
			pTaskGroupImpl->_pUploadPercent(fAllPercent / (pTaskGroupImpl->_taskPercentMap.size() * 100.0f));

		if (bDone)
		{
			if (pTaskGroupImpl->_pUpLoadGroupOk)
			{
				pTaskGroupImpl->_pUpLoadGroupOk(pTaskGroupImpl->_outputPathes);
			}
			taskGroup = _taskGroups.erase(taskGroup);
			continue;
		}
		++taskGroup;
	}
}

//this method called in main thread
TaskPtr UploadManagerImpl::CreateUpLoadTask(const std::string& rUrl)
{
	TaskPtr task = TaskPtr(new libdlmgr::UploadTask);
	UploadTaskImpl* pImpl = UPLOAD_TASK_IMPL(task->_pImpl);
	pImpl->_pMgr = _pOwner;
	pImpl->_iTaskId = _iNextTaskId++;
	pImpl->_pGroup = nullptr;

	pImpl->_iFileValidTime = rand() % (592001) + 2000000; //random time

	int index = (int)rUrl.rfind('/');
	std::string filename = rUrl.substr(index + 1, rUrl.length() - index);

	pImpl->Init(rUrl, filename);
	return task;
}

UPLOAD_MANAGER_END
