#include "TaskGroupImpl.h"
#include "DownloadTask.h"
#include "DownloadTaskImpl.h"

DOWNLOAD_MANAGER_START

void TaskGroupImpl::OnTaskFinished(DownloadTask* pTask)
{
	//call in main thread
	DownloadTaskImpl* pImpl = TASK_IMPL(pTask->_pImpl);
	_taskIdFinishedMap[pImpl->_iTaskId] = true;
	_taskPercentMap[TASK_IMPL(pTask->_pImpl)->_iTaskId] = 100;
	_outputPathes.push_back(pImpl->_fileCacheName);
}

void TaskGroupImpl::AddTask(TaskPtr pTask)
{
	_taskIdFinishedMap[TASK_IMPL(pTask->_pImpl)->_iTaskId] = false;
	_taskPercentMap[TASK_IMPL(pTask->_pImpl)->_iTaskId] = 0;
	TASK_IMPL(pTask->_pImpl)->_pGroup = _pOwner;
	_tasks.push_back(pTask);
}

void TaskGroupImpl::OnTaskProcessed(DownloadTask* pTask)
{
	DownloadTaskImpl* pImpl = TASK_IMPL(pTask->_pImpl);
	_taskPercentMap[pImpl->_iTaskId] = pImpl->GetDownloadPercent();
}

DOWNLOAD_MANAGER_END