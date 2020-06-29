#include "DownloadManager.h"
#include "DownloadTaskImpl.h"
#include "TaskGroupImpl.h"
#include "DownloadManagerImpl.h"
#include "DownloadTask.h"
#include "TaskGroup.h"
#include "curl/curl.h"

#include "sqlite3.h"
#include <sstream>

#ifdef _MSC_VER
#include <WinSock2.h>
#endif

struct sqlite3;
typedef void CURLM;
typedef void CURL;

DOWNLOAD_MANAGER_START

//---------------------------------------------------------------------------------------
DownloadManager* DownloadManager::_pInstance = new DownloadManager();

DownloadManager::DownloadManager()
{
	_pImpl = new ((char*)this + sizeof(DownloadManager)) DownloadManagerImpl(this);
}

DownloadManager::~DownloadManager()
{
	MANAGER_IMPL(_pImpl)->~DownloadManagerImpl();
}

void *DownloadManager::operator new(size_t size)
{
	return ::operator new(size + sizeof(DownloadManagerImpl));
}

DownloadManager& DownloadManager::GetSingleton()
{
	return *_pInstance;
}

void DownloadManager::Init(const std::string& rCacheDatabaseDir)
{
	MANAGER_IMPL(_pImpl)->Init(rCacheDatabaseDir);
}

void DownloadManager::DeInit()
{
	MANAGER_IMPL(_pImpl)->DeInit();
}

TaskPtr DownloadManager::CreateDownLoadTask(const std::string& rUrl)
{
	return MANAGER_IMPL(_pImpl)->CreateDownLoadTask(rUrl);
}

//add task to download queue
void DownloadManager::AddDownLoadTask(TaskPtr pTask)
{
	MANAGER_IMPL(_pImpl)->AddDownLoadTask(pTask);
}

void DownloadManager::AddTaskGroup(TaskGroupPtr pTaskGroup)
{
	MANAGER_IMPL(_pImpl)->AddTaskGroup(pTaskGroup);
}

// application call this api per-frame to to informed of download events
void DownloadManager::Update()
{
	MANAGER_IMPL(_pImpl)->Update();
}

const std::string& DownloadManager::GetCachePath() const
{
	return MANAGER_IMPL(_pImpl)->GetCachePath();
}

void DownloadManager::ClearCache(const std::string& rUrl)
{
	MANAGER_IMPL(_pImpl)->ClearCache(rUrl);
}

DOWNLOAD_MANAGER_END