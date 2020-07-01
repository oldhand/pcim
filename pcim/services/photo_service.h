#pragma once
#include "utils/threads.h"
#include "utils/auto_unregister.h"
#include "plugins/contact/nim_user_helper.h"
#include "plugins/team/nim_team_helper.h"

enum PhotoType
{
	kUser,
	kRobot,
	kTeam,
	kOther,
};

typedef std::function<void(PhotoType type, const std::string& profileid, const std::wstring &photo_path)> OnPhotoReadyCallback;

namespace nim_comp
{
/** @class PhotoService
  * @brief ͷ���������ȡ����
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @date 2016/09/13
  */
class PhotoService : public nbase::SupportWeakCallback
{
public:
	SINGLETON_DEFINE(PhotoService);
	PhotoService() {}
	~PhotoService() {}

public:

	/**
	* ע��ͷ��������Ϻ�Ļص�����
	* @param[in] callback �ص�����
	* @return UnregisterCallback ��ע�����
	*/
	UnregisterCallback RegPhotoReady(const OnPhotoReadyCallback& callback);

	/**
	* ��ȡ�û�ͷ��
	* @param[in] accid �û�id
	* @param[in] is_robot ��id�ǲ��ǻ�����
	* @return wstring ͷ���·��
	*/
	std::wstring GetUserPhoto(const std::string &accid);

	/**
	* ��ȡȺ��ͷ��
	* @param[in] tid Ⱥid
	* @param[in] full_path �Ƿ���Ҫ����·��
	* @return wstring ͷ���·��
	*/
	std::wstring GetTeamPhoto(const std::string &tid, bool full_path = true);

public:
	/**
	* ��ȡ�û���Ϣ�󣬻����û���Ϣ�޸ĺ������û�ͷ��(�����⿪�ţ��ṩ������service����)
	* @param[in] info Ҫ����ͷ����û���Ƭ
	* @return void	�޷���ֵ
	*/
	void DownloadUserPhoto(const Db::Profile &info);

	/**
	* ��ȡ��������Ϣ�󣬻��߻�������Ϣ�޸ĺ����ػ�����ͷ��(�����⿪�ţ��ṩ������service����)
	* @param[in] info Ҫ����ͷ��Ļ�������Ϣ
	* @return void	�޷���ֵ
	*/
	//void DownloadRobotPhoto(const nim::RobotInfo &info);

	/**
	* ��ȡȺ��Ϣ�󣬻���Ⱥ��Ϣ�޸ĺ�����Ⱥͷ��(�����⿪�ţ��ṩ������service����)
	* @param[in] info Ҫ����ͷ���Ⱥ��Ϣ
	* @return void	�޷���ֵ
	*/
	void DownloadTeamIcon(const nim::TeamInfo &info);

	/**
	* ��ȡ�û���Ⱥͷ������Ŀ¼
	* @param[in] type ��ȡͷ�������
	* @return wstring ͷ��Ŀ¼����·��
	*/
	std::wstring GetPhotoDir(PhotoType type);

	/**
	* ���ĳ��ͷ��ͼƬ�Ƿ����
	* @param[in] photo_path ͷ���ļ�·��
	* @return bool true ��ã�false �����
	*/
	bool CheckPhotoOK(std::wstring photo_path);

private:


	/**
	* ���ĳ��url��Ӧ��ͷ��ͼƬ�ڱ����Ƿ����
	* @param[in] type ͷ�������
	* @param[in] url ͷ������ص�ַ
	* @return int -1 url����ȷ��0 ����ã�1 ���
	*/
	int CheckForDownload(PhotoType type, const std::string& url);

	/**
	* ���ĳ��url��Ӧ��ͼƬ
	* @param[in] type ͷ�������
	* @param[in] url ͷ������ص�ַ
	* @return ͼƬ��ַ
	*/
	std::wstring UrlToFile(PhotoType type, const std::string& link);

private:
	std::map<int, std::unique_ptr<OnPhotoReadyCallback>> photo_ready_cb_list_; //�û�ͷ��������ɻص��б�
	std::map<PhotoType, std::map<std::string, std::string>> download_tasks_;
};


}