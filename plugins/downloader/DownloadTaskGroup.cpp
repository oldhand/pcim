#include "DownloadTaskGroup.h"
#include "DownloadTaskGroupImpl.h"

DOWNLOAD_MANAGER_START

DownloadTaskGroup::DownloadTaskGroup()
{
	_pImpl = new ((char*)this + sizeof(DownloadTaskGroup)) DownloadTaskGroupImpl(this);
}

DownloadTaskGroup::~DownloadTaskGroup()
{
	DOWNLOAD_TASKGROUP_IMPL(_pImpl)->~DownloadTaskGroupImpl();
}

void *DownloadTaskGroup::operator new(size_t size)
{
	return ::operator new(size + sizeof(DownloadTaskGroupImpl));
}

void DownloadTaskGroup::AddTask(TaskPtr pTask)
{
	DOWNLOAD_TASKGROUP_IMPL(_pImpl)->AddTask(pTask);
}

void DownloadTaskGroup::OnTaskFinished(DownloadTask* pTask)
{
	DOWNLOAD_TASKGROUP_IMPL(_pImpl)->OnTaskFinished(pTask);
}

void DownloadTaskGroup::OnTaskProcessed(DownloadTask* pTask)
{
	DOWNLOAD_TASKGROUP_IMPL(_pImpl)->OnTaskProcessed(pTask);
}

void DownloadTaskGroup::SetDownLoadGroupOkCallBack(std::function<void(const std::vector<std::string> & rDownloadedFiles)> pDownLoadGroupOk)
{
	DOWNLOAD_TASKGROUP_IMPL(_pImpl)->_pDownLoadGroupOk = pDownLoadGroupOk;
}

void DownloadTaskGroup::SetDownloadPercentCallBack(const std::function<void(double)>& pDownloadPercent)
{
	DOWNLOAD_TASKGROUP_IMPL(_pImpl)->_pDownloadPercent = pDownloadPercent;
}

DOWNLOAD_MANAGER_END