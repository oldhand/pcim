#ifndef _DOWNLOAD_TASKGROUP_H__
#define _DOWNLOAD_TASKGROUP_H__

#include "Defines.h"

DOWNLOAD_MANAGER_START

//-----------------------------------------------------------------
class TaskGroup
{
public:
	TaskGroup();
	~TaskGroup();

	friend class DownloadManagerImpl;

	void AddTask(TaskPtr pTask);
	void OnTaskFinished(DownloadTask* pTask);
	void OnTaskProcessed(DownloadTask* pTask);
	void SetDownLoadGroupOkCallBack(std::function<void(const std::vector<std::string>& rDownloadedFiles)> pDownLoadGroupOk);
	void SetDownloadPercentCallBack(const std::function<void(double)>& pDownloadPercent);
	void* operator new(size_t);
private:
	void* _pImpl;
};

DOWNLOAD_MANAGER_END

#endif
