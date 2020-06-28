#pragma once

namespace nim_comp
{
	class AsyncManager
	{
	public:
		/** ͬ���û���Ϣ*/
		static void async_profile_info(std::string profileid);
		/** ͬ���û�����*/
		static void async_profile_setting_info(std::string profileid);
		/** ͬ��ͨѶ¼*/
		static void async_contacts(std::string profileid);
		static void async_contacts(std::string profileid, std::string contactid);
		/** ͬ�������ڵ�����*/
		static void async_pulledblocks(std::string profileid);
		/** ͬ��Ⱥ*/
		static std::list<std::string> async_groups(std::string profileid);
		static void async_groups(std::string profileid, std::string groupchatid);
		/** ͬ��Ⱥ��Ա��Ϣ*/
		static void async_group_members(std::string profileid, std::list<std::string> ids);
		/** ͬ��Ⱥ���*/
		static void async_group_alias(std::string profileid);
		/** ͬ����֤��Ϣ*/
		static void async_validates(std::string profileid);
		/** ͬ������*/
		static void async_todos(std::string profileid);
		/** ͬ���ղ�*/
		static void async_favorites(std::string profileid);

	};
}

