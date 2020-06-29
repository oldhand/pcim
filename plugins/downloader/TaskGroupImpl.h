#ifndef _DOWNLOAD_TASKGROUP_IMPL_H__
#define _DOWNLOAD_TASKGROUP_IMPL_H__

#include "Defines.h"

DOWNLOAD_MANAGER_START

class TaskGroup;
class TaskGroupImpl
{
public:
	TaskGroupImpl(TaskGroup* pOwner) 
		: _pOwner(pOwner)
		, _pDownLoadGroupOk(nullptr)
		, _pDownloadPercent(nullptr){};
	~TaskGroupImpl() {};

	friend class DownloadManagerImpl;
	friend class DownloadTask;
	friend class ThreadTaskQueue;
	friend class TaskGroup;

	void AddTask(TaskPtr pTask);
	void OnTaskFinished(DownloadTask* pTask);
	void OnTaskProcessed(DownloadTask* pTask);
public:
	std::function<void(const std::vector<std::string>& rDownloadedFiles)> _pDownLoadGroupOk;
	std::function<void(double)> _pDownloadPercent;
private:
	std::vector<TaskPtr> _tasks;

	std::map<uint64_t, bool> _taskIdFinishedMap;
	std::map<uint64_t, double> _taskPercentMap;

	std::vector<std::string> _outputPathes;

	TaskGroup* _pOwner;
};

DOWNLOAD_MANAGER_END

#endif
