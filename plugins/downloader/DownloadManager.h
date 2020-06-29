#ifndef _DOWNLOAD_MANAGER_H__
#define _DOWNLOAD_MANAGER_H__

#include "Defines.h"

DOWNLOAD_MANAGER_START

//-----------------------------------------------------------------
class DownloadManager
{
public:
	friend class DownloadTaskImpl;

	static DownloadManager& GetSingleton();

	//Init and DeInit Manager, should be called only once
	//pass application writable path
	void Init(const std::string& rCacheDatabaseDir);
	void DeInit();
	//create a task
	TaskPtr CreateDownLoadTask(const std::string& rUrl);

	//add task to download queue
	void AddDownLoadTask(TaskPtr pTask);

	void AddTaskGroup(TaskGroupPtr pTaskGroup);

	// application call this api per-frame to to informed of download events
	void Update();

	const std::string& GetCachePath() const;

	void ClearCache(const std::string& rUrl);
private:
	DownloadManager();
	~DownloadManager();
	static DownloadManager* _pInstance;

	void* operator new(size_t);
	void* _pImpl;
};

DOWNLOAD_MANAGER_END

#endif
