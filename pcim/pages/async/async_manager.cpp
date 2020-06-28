#include "stdafx.h"
#include "async_manager.h"
#include "async_form.h"
#include "apis/ProfileApi.h" 
#include "apis/ContactApi.h" 
#include "apis/GroupApi.h" 
#include "apis/models/profile.h" 
#include "apis/models/profilesetting.h" 
#include "apis/models/contact.h"
#include "apis/models/group.h"
#include "apis/models/groupprofile.h"
#include "pages/login_manager.h"
#include "base/util/string_util.h"
#include "utils/lists.h"

using namespace ui;

namespace nim_comp
{
	/*
	* 同步用户信息
	*/
	void AsyncManager::async_profile_info(std::string profileid){
		Rest::Profile profile_info = Api::ProfileApi::load(profileid);
		Db::Profile profile = Db::Profile(profile_info);
		profile.saveCache();
	}
	/*
	* 同步用户设置
	*/
	void AsyncManager::async_profile_setting_info(std::string profileid){
		Rest::Content setting_info = Api::ProfileApi::get_profilesetting_info(profileid);
		Db::ProfileSetting proflesetting = Db::ProfileSetting(setting_info);
		proflesetting.saveCache();
	}
	/** 同步通讯录*/
	void AsyncManager::async_contacts(std::string profileid){
		std::string supplierid = nim_comp::LoginManager::GetInstance()->GetSupplierId();
		std::list<Rest::Content> contacts = Api::ContactApi::getContacts(supplierid, profileid);
		for (Rest::Content &info : contacts) {
			Db::Contact contactinfo = Db::Contact(info);
			contactinfo.saveCache();
		}
	}
	/** 同步群*/
	std::list<std::string> AsyncManager::async_groups(std::string profileid) {
		std::string supplierid = nim_comp::LoginManager::GetInstance()->GetSupplierId();
		std::list<Rest::Content> groupprofiles = Api::GroupApi::getGroupchatProfiles(supplierid, profileid);
		std::list<std::string> ids;
		for (Rest::Content &info : groupprofiles) {
			Db::GroupProfile groupprofile_info = Db::GroupProfile(info);
			groupprofile_info.saveCache();
			ids.push_back(groupprofile_info.groupchatid);
		}
		std::list<Rest::Content> groups = Api::GroupApi::getGroupchats(ids);

		std::list<std::string> contactids; 
		for (Rest::Content &group : groups) {
			Db::Group group_info = Db::Group(group);
			group_info.saveCache(profileid);
			if (group_info.contactids.compare("") != 0) {
				std::list<std::string> ids = nbase::StringTokenize(group_info.contactids.c_str(), ",");
				ids.sort();
				contactids.merge(ids);
			} 
		}
		contactids.erase(unique(contactids.begin(), contactids.end()), contactids.end());
		return contactids;
	}
	/** 同步群成员信息*/
	void AsyncManager::async_group_members(std::string profileid, std::list<std::string> ids){
		Rest::Profile profile_info = Api::ProfileApi::load(profileid);
		std::list<std::list<std::string>> chunks = nbase::chunk(ids,10);
		for (std::list<std::string> &profiles : chunks) {
			std::list<Rest::Profile> lists = Api::ProfileApi::loadMany(profiles);
			for (Rest::Profile &profile_info : lists) {
				Db::Profile profile = Db::Profile(profile_info);
				profile.saveCache();
			} 
		}
		
	}

}
