#ifndef _UPLOAD_TASKGROUP_IMPL_H__
#define _UPLOAD_TASKGROUP_IMPL_H__

#include "Defines.h"

UPLOAD_MANAGER_START

class UploadTaskGroup;
class UploadTaskGroupImpl
{
public:
	UploadTaskGroupImpl(UploadTaskGroup* pOwner)
		: _pOwner(pOwner)
		, _pUpLoadGroupOk(nullptr)
		, _pUploadPercent(nullptr){};
	~UploadTaskGroupImpl() {};

	friend class UploadManagerImpl;
	friend class UploadTask;
	friend class ThreadTaskQueue;
	friend class UploadTaskGroup;

	void AddTask(TaskPtr pTask);
	void OnTaskFinished(UploadTask* pTask);
	void OnTaskProcessed(UploadTask* pTask);
public:
	std::function<void(const std::vector<std::string>& rUploadedFiles)> _pUpLoadGroupOk;
	std::function<void(double)> _pUploadPercent;
private:
	std::vector<TaskPtr> _tasks;

	std::map<uint64_t, bool> _taskIdFinishedMap;
	std::map<uint64_t, double> _taskPercentMap;

	std::vector<std::string> _outputPathes;

	UploadTaskGroup* _pOwner;
};

UPLOAD_MANAGER_END

#endif
