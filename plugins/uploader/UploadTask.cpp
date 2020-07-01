#include "UploadTask.h"
#include "UploadTaskImpl.h"
#include "curl/curl.h"

#include "sqlite3.h"
#include <sstream>
#include <string>
#include <algorithm>

UPLOAD_MANAGER_START

//-----------------------------------------------------------------
UploadTask::UploadTask()
{
	_pImpl = new ((char*)this + sizeof(UploadTask)) UploadTaskImpl(this);
}

UploadTask::~UploadTask()
{
	UPLOAD_TASK_IMPL(_pImpl)->~UploadTaskImpl();
}

void *UploadTask::operator new(size_t size)
{
	return ::operator new(size + sizeof(UploadTaskImpl));
}

void UploadTask::SetValidTime(time_t iValidTime)
{
	UPLOAD_TASK_IMPL(_pImpl)->_iFileValidTime = iValidTime;
}

int UploadTask::GetHttpCode() const
{
	return UPLOAD_TASK_IMPL(_pImpl)->_iHttpCode;
}

const std::string& UploadTask::GetOutputPath() const
{
	return UPLOAD_TASK_IMPL(_pImpl)->_fileCacheName;
}

void UploadTask::SetUploadOKCallBack(const std::function<void(UploadTask* pTask)>& pUploadOK)
{
	UPLOAD_TASK_IMPL(_pImpl)->_pUploadOK = pUploadOK;
}

void UploadTask::SetUploadFailedCallBack(const std::function<void()>& pUploadFailed)
{
	UPLOAD_TASK_IMPL(_pImpl)->_pUploadFailed = pUploadFailed;
}

void UploadTask::SetUploadPercentCallBack(const std::function<void(double)>& pUploadPercent)
{
	UPLOAD_TASK_IMPL(_pImpl)->_pUploadPercent = pUploadPercent;
}
//-----------------------------------------------------------------

UPLOAD_MANAGER_END
