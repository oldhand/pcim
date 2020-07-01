#ifndef _DOWNLOAD_TASK_H__
#define _DOWNLOAD_TASK_H__

#include "Defines.h"

namespace hotpatch
{
	class HotPatchInternal;
}
//-----------------------------------------------------------------

DOWNLOAD_MANAGER_START

//-----------------------------------------------------------------
class DownloadTaskGroup;
class DownloadTask
{
public:
	DownloadTask();
	~DownloadTask();

	friend class ThreadTaskQueue;
	friend class DownloadTaskGroupImpl;
	friend class DownloadManagerImpl;
	friend class hotpatch::HotPatchInternal;

	void SetValidTime(time_t iValidTime);

	int GetHttpCode() const;

	const std::string& GetOutputPath() const;

	//pDownloadOK will be called when download task is ok
	void SetDownloadOKCallBack(const std::function<void(DownloadTask* pTask)>& pDownloadOK);

	//pDownloadFailed will be called when download task is failed
	void SetDownloadFailedCallBack(const std::function<void()>& pDownloadFailed);

	void SetDownloadPercentCallBack(const std::function<void(double)>& pDownloadPercent);
private:
	void* operator new(size_t);
	void* _pImpl;
};

DOWNLOAD_MANAGER_END

#endif
