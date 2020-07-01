#include "UploadManager.h"
#include "UploadTaskImpl.h"
#include "UploadTaskGroupImpl.h"
#include "UploadManagerImpl.h"
#include "UploadTask.h"
#include "UploadTaskGroup.h"
#include "curl/curl.h"

#include "sqlite3.h"
#include <sstream>

#ifdef _MSC_VER
#include <WinSock2.h>
#endif

struct sqlite3;
typedef void CURLM;
typedef void CURL;

UPLOAD_MANAGER_START

//---------------------------------------------------------------------------------------
UploadManager* UploadManager::_pInstance = new UploadManager();

UploadManager::UploadManager()
{
	_pImpl = new ((char*)this + sizeof(UploadManager)) UploadManagerImpl(this);
}

UploadManager::~UploadManager()
{
	UPLOAD_MANAGER_IMPL(_pImpl)->~UploadManagerImpl();
}

void *UploadManager::operator new(size_t size)
{
	return ::operator new(size + sizeof(UploadManagerImpl));
}

UploadManager& UploadManager::GetSingleton()
{
	return *_pInstance;
}

void UploadManager::Init(const std::string& rCacheDatabaseDir)
{
	UPLOAD_MANAGER_IMPL(_pImpl)->Init(rCacheDatabaseDir);
}

void UploadManager::DeInit()
{
	UPLOAD_MANAGER_IMPL(_pImpl)->DeInit();
}

TaskPtr UploadManager::CreateUpLoadTask(const std::string& rUrl)
{
	return UPLOAD_MANAGER_IMPL(_pImpl)->CreateUpLoadTask(rUrl);
}

//add task to upload queue
void UploadManager::AddUpLoadTask(TaskPtr pTask)
{
	UPLOAD_MANAGER_IMPL(_pImpl)->AddUpLoadTask(pTask);
}

void UploadManager::AddTaskGroup(TaskGroupPtr pTaskGroup)
{
	UPLOAD_MANAGER_IMPL(_pImpl)->AddTaskGroup(pTaskGroup);
}

// application call this api per-frame to to informed of upload events
void UploadManager::Update()
{
	UPLOAD_MANAGER_IMPL(_pImpl)->Update();
}

const std::string& UploadManager::GetCachePath() const
{
	return UPLOAD_MANAGER_IMPL(_pImpl)->GetCachePath();
}

void UploadManager::ClearCache(const std::string& rUrl)
{
	UPLOAD_MANAGER_IMPL(_pImpl)->ClearCache(rUrl);
}

UPLOAD_MANAGER_END
