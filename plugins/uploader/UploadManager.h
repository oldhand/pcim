#ifndef _UPLOAD_MANAGER_H__
#define _UPLOAD_MANAGER_H__

#include "Defines.h"

UPLOAD_MANAGER_START

//-----------------------------------------------------------------
class UploadManager
{
public:
	friend class UploadTaskImpl;

	static UploadManager& GetSingleton();

	//Init and DeInit Manager, should be called only once
	//pass application writable path
	void Init(const std::string& rCacheDatabaseDir);
	void DeInit();
	//create a task
	TaskPtr CreateUpLoadTask(const std::string& rUrl);

	//add task to upload queue
	void AddUpLoadTask(TaskPtr pTask);

	void AddTaskGroup(TaskGroupPtr pTaskGroup);

	// application call this api per-frame to to informed of upload events
	void Update();

	const std::string& GetCachePath() const;

	void ClearCache(const std::string& rUrl);
private:
	UploadManager();
	~UploadManager();
	static UploadManager* _pInstance;

	void* operator new(size_t);
	void* _pImpl;
};

UPLOAD_MANAGER_END

#endif
