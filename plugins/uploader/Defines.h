//author: linyuanxuan
#ifndef _UPLOADDEFINES_H
#define _UPLOADDEFINES_H

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

#define UPLOAD_MANAGER_START namespace libdlmgr {
#define UPLOAD_MANAGER_END }

UPLOAD_MANAGER_START

enum CURL_STATUS { CURL_STARTED = 1, CURL_RECEIVING = 2, CURL_TERMINATED = 3 };

class UploadTaskGroup;
class UploadTask;
typedef std::shared_ptr<UploadTaskGroup> TaskGroupPtr;
typedef std::shared_ptr<UploadTask> TaskPtr;

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

UPLOAD_MANAGER_END

#define UPLOAD_TASK_IMPL(impl) static_cast<libdlmgr::UploadTaskImpl*>(impl)
#define UPLOAD_TASKGROUP_IMPL(impl) static_cast<libdlmgr::UploadTaskGroupImpl*>(impl)
#define UPLOAD_MANAGER_IMPL(impl) static_cast<libdlmgr::UploadManagerImpl*>(impl)

#endif
