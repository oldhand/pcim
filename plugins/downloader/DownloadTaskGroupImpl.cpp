#include "DownloadTaskGroupImpl.h"
#include "DownloadTask.h"
#include "DownloadTaskImpl.h"

DOWNLOAD_MANAGER_START

void DownloadTaskGroupImpl::OnTaskFinished(DownloadTask* pTask)
{
	//call in main thread
	DownloadTaskImpl* pImpl = DOWNLOAD_TASK_IMPL(pTask->_pImpl);
	_taskIdFinishedMap[pImpl->_iTaskId] = true;
	_taskPercentMap[DOWNLOAD_TASK_IMPL(pTask->_pImpl)->_iTaskId] = 100;
	_outputPathes.push_back(pImpl->_fileCacheName);
}

void DownloadTaskGroupImpl::AddTask(TaskPtr pTask)
{
	_taskIdFinishedMap[DOWNLOAD_TASK_IMPL(pTask->_pImpl)->_iTaskId] = false;
	_taskPercentMap[DOWNLOAD_TASK_IMPL(pTask->_pImpl)->_iTaskId] = 0;
	DOWNLOAD_TASK_IMPL(pTask->_pImpl)->_pGroup = _pOwner;
	_tasks.push_back(pTask);
}

void DownloadTaskGroupImpl::OnTaskProcessed(DownloadTask* pTask)
{
	DownloadTaskImpl* pImpl = DOWNLOAD_TASK_IMPL(pTask->_pImpl);
	_taskPercentMap[pImpl->_iTaskId] = pImpl->GetDownloadPercent();
}

DOWNLOAD_MANAGER_END