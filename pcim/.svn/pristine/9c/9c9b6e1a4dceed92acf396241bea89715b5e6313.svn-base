#pragma once

namespace nim_comp
{
	class AsyncManager
	{
	public:
		/** 同步用户信息*/
		static void async_profile_info(std::string profileid);
		/** 同步用户设置*/
		static void async_profile_setting_info(std::string profileid);
		/** 同步通讯录*/
		static void async_contacts(std::string profileid);
		static void async_contacts(std::string profileid, std::string contactid);
		/** 同步被拉黑的名单*/
		static void async_pulledblocks(std::string profileid);
		/** 同步群*/
		static std::list<std::string> async_groups(std::string profileid);
		static void async_groups(std::string profileid, std::string groupchatid);
		/** 同步群成员信息*/
		static void async_group_members(std::string profileid, std::list<std::string> ids);
		/** 同步群别称*/
		static void async_group_alias(std::string profileid);
		/** 同步认证信息*/
		static void async_validates(std::string profileid);
		/** 同步待办*/
		static void async_todos(std::string profileid);
		/** 同步收藏*/
		static void async_favorites(std::string profileid);

	};
}

