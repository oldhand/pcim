#include "UploadTaskGroupImpl.h"
#include "UploadTask.h"
#include "UploadTaskImpl.h"

UPLOAD_MANAGER_START

void UploadTaskGroupImpl::OnTaskFinished(UploadTask* pTask)
{
	//call in main thread
	UploadTaskImpl* pImpl = UPLOAD_TASK_IMPL(pTask->_pImpl);
	_taskIdFinishedMap[pImpl->_iTaskId] = true;
	_taskPercentMap[UPLOAD_TASK_IMPL(pTask->_pImpl)->_iTaskId] = 100;
	_outputPathes.push_back(pImpl->_fileCacheName);
}

void UploadTaskGroupImpl::AddTask(TaskPtr pTask)
{
	_taskIdFinishedMap[UPLOAD_TASK_IMPL(pTask->_pImpl)->_iTaskId] = false;
	_taskPercentMap[UPLOAD_TASK_IMPL(pTask->_pImpl)->_iTaskId] = 0;
	UPLOAD_TASK_IMPL(pTask->_pImpl)->_pGroup = _pOwner;
	_tasks.push_back(pTask);
}

void UploadTaskGroupImpl::OnTaskProcessed(UploadTask* pTask)
{
	UploadTaskImpl* pImpl = UPLOAD_TASK_IMPL(pTask->_pImpl);
	_taskPercentMap[pImpl->_iTaskId] = pImpl->GetUploadPercent();
}

UPLOAD_MANAGER_END
