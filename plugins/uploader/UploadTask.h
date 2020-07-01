#ifndef _UPLOAD_TASK_H__
#define _UPLOAD_TASK_H__

#include "Defines.h"

namespace hotpatch
{
	class HotPatchInternal;
}
//-----------------------------------------------------------------

UPLOAD_MANAGER_START

//-----------------------------------------------------------------
class UploadTaskGroup;
class UploadTask
{
public:
	UploadTask();
	~UploadTask();

	friend class ThreadTaskQueue;
	friend class UploadTaskGroupImpl;
	friend class UploadManagerImpl;
	friend class hotpatch::HotPatchInternal;

	void SetValidTime(time_t iValidTime);

	int GetHttpCode() const;

	const std::string& GetOutputPath() const;

	//pUploadOK will be called when upload task is ok
	void SetUploadOKCallBack(const std::function<void(UploadTask* pTask)>& pUploadOK);

	//pUploadFailed will be called when upload task is failed
	void SetUploadFailedCallBack(const std::function<void()>& pUploadFailed);

	void SetUploadPercentCallBack(const std::function<void(double)>& pUploadPercent);
private:
	void* operator new(size_t);
	void* _pImpl;
};

UPLOAD_MANAGER_END

#endif
