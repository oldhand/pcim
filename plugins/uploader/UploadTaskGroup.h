#ifndef _UPLOAD_TASKGROUP_H__
#define _UPLOAD_TASKGROUP_H__

#include "Defines.h"

UPLOAD_MANAGER_START

//-----------------------------------------------------------------
class UploadTaskGroup
{
public:
	UploadTaskGroup();
	~UploadTaskGroup();

	friend class UploadManagerImpl;

	void AddTask(TaskPtr pTask);
	void OnTaskFinished(UploadTask* pTask);
	void OnTaskProcessed(UploadTask* pTask);
	void SetUpLoadGroupOkCallBack(std::function<void(const std::vector<std::string>& rUploadedFiles)> pUpLoadGroupOk);
	void SetUploadPercentCallBack(const std::function<void(double)>& pUploadPercent);
	void* operator new(size_t);
private:
	void* _pImpl;
};

UPLOAD_MANAGER_END

#endif
