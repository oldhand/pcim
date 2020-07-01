#include "stdafx.h"
#include "services/photo_service.h"
#include "services/user_service.h"
#include "pages/login_manager.h"

#include "downloader/Defines.h"
#include "downloader/DownloadManager.h"
#include "downloader/DownloadTask.h"
#include "downloader/DownloadTaskGroup.h"

namespace nim_comp
{

std::wstring PhotoService::UrlToFile(PhotoType type, const std::string& link){
	int index = link.rfind('.');
	std::string ext = link.substr(index, link.length() - index);
	std::wstring photo_path = GetPhotoDir(kUser) + nbase::UTF8ToUTF16(QString::GetMd5(link) + ext);
	return photo_path;
}

std::wstring PhotoService::GetUserPhoto(const std::string &accid)
{
	std::wstring default_photo = QPath::GetAppPath() + L"res\\faces\\default\\default.png";
	if (!nbase::FilePathIsExist(default_photo, false))
		default_photo = L"";

	std::wstring photo_path;

	Db::Profile info;
	UserService::GetInstance()->GetUserInfo(accid, info);
	if (info.link.empty())
		return default_photo;
	photo_path = UrlToFile(kUser,info.link);

	// 检查图片是否存在
	if (!CheckPhotoOK(photo_path))
		return default_photo;

	return photo_path;
}

bool PhotoService::CheckPhotoOK(std::wstring photo_path)
{
	if (!nbase::FilePathIsExist(photo_path, false))
		return false;

	// 检查图片是否损坏
	return (Gdiplus::Image(photo_path.c_str()).GetLastStatus() == Gdiplus::Status::Ok);
}

std::wstring PhotoService::GetPhotoDir(PhotoType type)
{
	std::wstring photo_dir = QPath::GetUserAppDataDir(LoginManager::GetInstance()->GetProfileId());
	if (type == kUser || type == kRobot)
		photo_dir = photo_dir.append(L"photo\\");
	else if (type == kTeam)
		photo_dir = photo_dir.append(L"team_photo\\");
	else if (type == kOther)
		photo_dir = photo_dir.append(L"other\\");

	if (!nbase::FilePathIsExist(photo_dir, true))
		nbase::win32::CreateDirectoryRecursively(photo_dir.c_str());
	return photo_dir;
}

UnregisterCallback PhotoService::RegPhotoReady(const OnPhotoReadyCallback & callback)
{
	OnPhotoReadyCallback* new_callback = new OnPhotoReadyCallback(callback);
	int cb_id = (int)new_callback;
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	photo_ready_cb_list_[cb_id].reset(new_callback);
	auto cb = ToWeakCallback([this, cb_id]() {
		photo_ready_cb_list_.erase(cb_id);
	});
	return cb;
}

int PhotoService::CheckForDownload(PhotoType type, const std::string& url)
{
	std::wstring photo_path = UrlToFile(kUser, url);
	if (CheckPhotoOK(photo_path)) // 如果头像已经存在且完好，就不下载
		return 1;

	std::string url_md5 = QString::GetMd5(url);
	if (download_tasks_[type].find(url_md5) != download_tasks_[type].end())
		return 2;

	download_tasks_[type][url_md5] = "";
	return 0;
}

void PhotoService::DownloadUserPhoto(const Db::Profile &info)
{
	std::string url = info.link; 
	std::wstring photo_path = UrlToFile(kUser, info.link);
	std::string fullurl = Env::imgBaseUrl + url;
	int valid = CheckForDownload(kUser, url);
	if (valid != 0)
	{
		if (valid == 1)
		{
			for (auto &it : photo_ready_cb_list_) // 执行监听头像下载的回调
				(*it.second)(kUser, info.profileid, photo_path);
		}
		return;
	}


	nbase::ThreadManager::PostTask(kThreadDownLoader, ToWeakCallback([this,info,fullurl, photo_path]() {
		//std::string url1 = "http://api.mclouds.org.cn/storage/mp4/xiangyaAffidavit.mp4"; 
		libdlmgr::TaskPtr task = libdlmgr::DownloadManager::GetSingleton().CreateDownLoadTask(fullurl);
		bool isfinished = false;
		task->SetDownloadOKCallBack([this, info, fullurl, photo_path, &isfinished](libdlmgr::DownloadTask* pTask)
		{
			download_tasks_[kUser].erase(QString::GetMd5(info.link));
			std::wstring ws_file_path = nbase::UTF8ToUTF16(pTask->GetOutputPath());
			if (nbase::FilePathIsExist(ws_file_path, false))
			{
				nbase::CopyFileW(ws_file_path, photo_path);
				nbase::DeleteFile(ws_file_path); 
				Post2UI([=](){
					for (auto &it : photo_ready_cb_list_) // 执行监听头像下载的回调
						(*it.second)(kUser, info.profileid, photo_path);
				});
				
			}
			isfinished = true;
		});
		task->SetDownloadPercentCallBack([fullurl](double percent)
		{
			printf_s("_______SetDownloadPercentCallBack_______%s_____%lf%%__________\n", fullurl.c_str(), percent);
		});
		libdlmgr::DownloadManager::GetSingleton().AddDownLoadTask(task);
		while (true)
		{
			if (isfinished)  break;
			libdlmgr::DownloadManager::GetSingleton().Update();
#ifdef _MSC_VER
			Sleep(10);
#else
			usleep(100 * 1000);
#endif
		}
	}));
	 

	//nim::NOS::DownloadMediaCallback cb = ToWeakCallback([this, info, photo_path](int res_code, const std::string& file_path, const std::string& call_id, const std::string& res_id) {
	//	download_tasks_[kUser].erase(nim::Tool::GetMd5(info.GetIconUrl()));
	//	if (res_code == nim::kNIMResSuccess)
	//	{
	//		std::wstring ws_file_path = nbase::UTF8ToUTF16(file_path);
	//		if (nbase::FilePathIsExist(ws_file_path, false))
	//		{
	//			nbase::CopyFileW(ws_file_path, photo_path);
	//			nbase::DeleteFile(ws_file_path);

	//			for (auto &it : photo_ready_cb_list_) // 执行监听头像下载的回调
	//				(*it.second)(kUser, info.id, photo_path);
	//		}
	//	}
	//});
	//nim::NOS::DownloadResource(url, cb);
}

//void PhotoService::DownloadRobotPhoto(const nim::RobotInfo &info)
//{
//	std::string url = info.GetIcon();
//	std::wstring photo_path = GetPhotoDir(kRobot) + nbase::UTF8ToUTF16(QString::GetMd5(url));
//	int valid = CheckForDownload(kRobot, url);
//	if (valid != 0)
//	{
//		if (valid == 1)
//		{
//			for (auto &it : photo_ready_cb_list_) // 执行监听头像下载的回调
//				(*it.second)(kRobot, info.id, photo_path);
//		}
//		return;
//	}
//
//	nim::NOS::DownloadMediaExCallback cb = ToWeakCallback([this, info, photo_path](nim::NIMResCode res_code, const nim::DownloadMediaResult& result) {
//		download_tasks_[kRobot].erase(nim::Tool::GetMd5(info.GetIcon()));
//		if (res_code == nim::kNIMResSuccess)
//		{
//			std::wstring ws_file_path = nbase::UTF8ToUTF16(result.file_path_);
//			if (nbase::FilePathIsExist(ws_file_path, false))
//			{
//				nbase::CopyFileW(ws_file_path, photo_path);
//				nbase::DeleteFile(ws_file_path);
//
//				for (auto &it : photo_ready_cb_list_) // 执行监听头像下载的回调
//					(*it.second)(kRobot, info.id, photo_path);
//			}
//		}
//	});
//	Json::Value values;
//	std::wstring temp = GetPhotoDir(kRobot) + nbase::UTF8ToUTF16(info.id);
//	values[nim::kNIMNosSaveAsFilePath] = nbase::UTF16ToUTF8(temp);
//	nim::NOS::DownloadResourceEx(url, values.toStyledString(), cb);
//}
//
void PhotoService::DownloadTeamIcon(const nim::TeamInfo &info)
{
	std::string url = info.GetIcon();
	std::wstring photo_path = GetPhotoDir(kTeam) + nbase::UTF8ToUTF16(QString::GetMd5(url));
	int valid = CheckForDownload(kTeam, url);
	if (valid != 0)
	{
		if (valid == 1)
		{
			for (auto &it : photo_ready_cb_list_) // 执行监听头像下载的回调
			(*it.second)(kTeam, info.GetTeamID(), photo_path);
		}
		return;
	}

	//nim::NOS::DownloadMediaCallback cb = ToWeakCallback([this, info, photo_path](int res_code, const std::string& file_path, const std::string& call_id, const std::string& res_id) {
	//	download_tasks_[kTeam].erase(nim::Tool::GetMd5(info.GetIcon()));
	//	if (res_code == nim::kNIMResSuccess)
	//	{
	//		std::wstring ws_file_path = nbase::UTF8ToUTF16(file_path);
	//		if (nbase::FilePathIsExist(ws_file_path, false))
	//		{
	//			nbase::CopyFileW(ws_file_path, photo_path);
	//			nbase::DeleteFile(ws_file_path);

	//			for (auto &it : photo_ready_cb_list_) // 执行监听头像下载的回调
	//				(*it.second)(kTeam, info.GetTeamID(), photo_path);
	//		}
	//	}
	//});
	//nim::NOS::DownloadResource(url, cb);
}

std::wstring PhotoService::GetTeamPhoto(const std::string &tid, bool full_path/* = true*/)
{
	std::wstring default_photo = QPath::GetAppPath();
	if (full_path)
		default_photo.append(L"resources\\themes\\default\\public\\header\\head_team.png");
	else
		default_photo = L"../public/header/head_team.png";

	if (full_path && !nbase::FilePathIsExist(default_photo, false))
		default_photo = L"";

	//std::string icon;
	//if (!TeamService::GetInstance()->GetTeamIcon(tid, icon) || icon.empty())
	//	return default_photo;

	//std::wstring photo_path = GetPhotoDir(kTeam) + nbase::UTF8ToUTF16(QString::GetMd5(icon));
	//if (!CheckPhotoOK(photo_path))
	//	return default_photo;

	//return photo_path;
	return default_photo;
}


}