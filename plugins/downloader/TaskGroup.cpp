#include "TaskGroup.h"
#include "TaskGroupImpl.h"

DOWNLOAD_MANAGER_START

TaskGroup::TaskGroup()
{
	_pImpl = new ((char*)this + sizeof(TaskGroup)) TaskGroupImpl(this);
}

TaskGroup::~TaskGroup()
{
	TASKGROUP_IMPL(_pImpl)->~TaskGroupImpl();
}

void *TaskGroup::operator new(size_t size)
{
	return ::operator new(size + sizeof(TaskGroupImpl));
}

void TaskGroup::AddTask(TaskPtr pTask)
{
	TASKGROUP_IMPL(_pImpl)->AddTask(pTask);
}

void TaskGroup::OnTaskFinished(DownloadTask* pTask)
{
	TASKGROUP_IMPL(_pImpl)->OnTaskFinished(pTask);
}

void TaskGroup::OnTaskProcessed(DownloadTask* pTask)
{
	TASKGROUP_IMPL(_pImpl)->OnTaskProcessed(pTask);
}

void TaskGroup::SetDownLoadGroupOkCallBack(std::function<void(const std::vector<std::string> & rDownloadedFiles)> pDownLoadGroupOk)
{
	TASKGROUP_IMPL(_pImpl)->_pDownLoadGroupOk = pDownLoadGroupOk;
}

void TaskGroup::SetDownloadPercentCallBack(const std::function<void(double)>& pDownloadPercent)
{
	TASKGROUP_IMPL(_pImpl)->_pDownloadPercent = pDownloadPercent;
}

DOWNLOAD_MANAGER_END