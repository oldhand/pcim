#include "UploadTaskGroup.h"
#include "UploadTaskGroupImpl.h"

UPLOAD_MANAGER_START

UploadTaskGroup::UploadTaskGroup()
{
	_pImpl = new ((char*)this + sizeof(UploadTaskGroup)) UploadTaskGroupImpl(this);
}

UploadTaskGroup::~UploadTaskGroup()
{
	UPLOAD_TASKGROUP_IMPL(_pImpl)->~UploadTaskGroupImpl();
}

void *UploadTaskGroup::operator new(size_t size)
{
	return ::operator new(size + sizeof(UploadTaskGroupImpl));
}

void UploadTaskGroup::AddTask(TaskPtr pTask)
{
	UPLOAD_TASKGROUP_IMPL(_pImpl)->AddTask(pTask);
}

void UploadTaskGroup::OnTaskFinished(UploadTask* pTask)
{
	UPLOAD_TASKGROUP_IMPL(_pImpl)->OnTaskFinished(pTask);
}

void UploadTaskGroup::OnTaskProcessed(UploadTask* pTask)
{
	UPLOAD_TASKGROUP_IMPL(_pImpl)->OnTaskProcessed(pTask);
}

void UploadTaskGroup::SetUpLoadGroupOkCallBack(std::function<void(const std::vector<std::string> & rUploadedFiles)> pUpLoadGroupOk)
{
	UPLOAD_TASKGROUP_IMPL(_pImpl)->_pUpLoadGroupOk = pUpLoadGroupOk;
}

void UploadTaskGroup::SetUploadPercentCallBack(const std::function<void(double)>& pUploadPercent)
{
	UPLOAD_TASKGROUP_IMPL(_pImpl)->_pUploadPercent = pUploadPercent;
}

UPLOAD_MANAGER_END
