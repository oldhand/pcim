#include "DownloadTask.h"
#include "DownloadTaskImpl.h"
#include "curl/curl.h"

#include "sqlite3.h"
#include <sstream>
#include <string>
#include <algorithm>

DOWNLOAD_MANAGER_START

//-----------------------------------------------------------------
DownloadTask::DownloadTask()
{
	_pImpl = new ((char*)this + sizeof(DownloadTask)) DownloadTaskImpl(this);
}

DownloadTask::~DownloadTask()
{
	DOWNLOAD_TASK_IMPL(_pImpl)->~DownloadTaskImpl();
}

void *DownloadTask::operator new(size_t size)
{
	return ::operator new(size + sizeof(DownloadTaskImpl));
}

void DownloadTask::SetValidTime(time_t iValidTime)
{
	DOWNLOAD_TASK_IMPL(_pImpl)->_iFileValidTime = iValidTime;
}

int DownloadTask::GetHttpCode() const
{
	return DOWNLOAD_TASK_IMPL(_pImpl)->_iHttpCode;
}

const std::string& DownloadTask::GetOutputPath() const
{
	return DOWNLOAD_TASK_IMPL(_pImpl)->_fileCacheName;
}

void DownloadTask::SetDownloadOKCallBack(const std::function<void(DownloadTask* pTask)>& pDownloadOK)
{
	DOWNLOAD_TASK_IMPL(_pImpl)->_pDownloadOK = pDownloadOK;
}

void DownloadTask::SetDownloadFailedCallBack(const std::function<void()>& pDownloadFailed)
{
	DOWNLOAD_TASK_IMPL(_pImpl)->_pDownloadFailed = pDownloadFailed;
}

void DownloadTask::SetDownloadPercentCallBack(const std::function<void(double)>& pDownloadPercent)
{
	DOWNLOAD_TASK_IMPL(_pImpl)->_pDownloadPercent = pDownloadPercent;
}
//-----------------------------------------------------------------

DOWNLOAD_MANAGER_END