//author: linyuanxuan
#ifndef _DOWNLOADDEFINES_H
#define _DOWNLOADDEFINES_H

#include <functional>
#include <map>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>
#include <algorithm>
#include <sstream>
#include <sys/stat.h>
#include <set>

#define DOWNLOAD_MANAGER_START namespace libdlmgr {
#define DOWNLOAD_MANAGER_END }

DOWNLOAD_MANAGER_START

enum CURL_STATUS { CURL_STARTED = 1, CURL_RECEIVING = 2, CURL_TERMINATED = 3 };

class DownloadTaskGroup;
class DownloadTask;
typedef std::shared_ptr<DownloadTaskGroup> TaskGroupPtr;
typedef std::shared_ptr<DownloadTask> TaskPtr;

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

//template <typename T>
//T max(T v1, T v2)
//{
//	return v1 > v2 ? v1 : v2;
//}
//
//template <typename T>
//T min(T v1, T v2)
//{
//	return v1 < v2 ? v1 : v2;
//}

DOWNLOAD_MANAGER_END

#define DOWNLOAD_TASK_IMPL(impl) static_cast<libdlmgr::DownloadTaskImpl*>(impl)
#define DOWNLOAD_TASKGROUP_IMPL(impl) static_cast<libdlmgr::DownloadTaskGroupImpl*>(impl)
#define DOWNLOAD_MANAGER_IMPL(impl) static_cast<libdlmgr::DownloadManagerImpl*>(impl)

#endif
