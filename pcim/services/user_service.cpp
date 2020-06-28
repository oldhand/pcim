﻿#include "stdafx.h"
#include "user_service.h"
#include "photo_service.h"
//#include "module/local/local_helper.h"
//#include "module/login/login_manager.h"
#include "gui/subscribe_event/subscribe_event_manager.h"
#include "plugins/contact/nim_cpp_friend.h"
#include "plugins/contact/nim_cpp_user.h"
#include "utils/xml_util.h"

std::string GetConfigValue(const std::string& key)
{
	//return app_sdk::AppSDKInterface::GetConfigValue(key);	
	return "";
}

namespace nim_comp
{

UserService::UserService()
{
	//向SDK注册监听好友列表变化
	//nim::Friend::RegChangeCb(nbase::Bind(&UserService::OnFriendListChangeBySDK, this, std::placeholders::_1));

	////向SDK注册监听用户名片变化
	//nim::User::RegUserNameCardChangedCb(nbase::Bind(&UserService::OnUserInfoChangeBySDK, this, std::placeholders::_1));
}

void UserService::InvokeGetAllUserInfo(const OnGetUserInfoCallback& cb)
{
	nim::Friend::GetList(ToWeakCallback([this, cb](nim::NIMResCode res_code, const std::list<Db::Contact>& user_profile_list)
	{
		std::list<std::string> account_list;
		for (auto& it : user_profile_list)
		{
			friend_list_[it.contactid] = it; //插入friend_list_（类的成员变量）好友列表
			account_list.push_back(it.contactid);
		}

		std::list<Db::Profile> uinfos;
		GetUserInfos(account_list, uinfos); // 从db和服务器查询用户信息
		if (cb)
			cb(uinfos);
	}));
}

void UserService::InvokeGetAllUserInfo(const std::list<std::string>& accids, const OnGetUserInfoCallback& cb)
{
	/*nim::User::GetUserNameCardOnline(accids, [this, cb](const std::list<Db::Profile>& uinfos)
	{
		std::list<std::string> accids;
		for (auto& it : uinfos)
		{
			nim::FriendProfile pro;
			pro.SetAccId(it.id);
			pro.SetRelationship(nim::kNIMFriendFlagNormal);
			friend_list_[it.id].Update(pro);
			accids.push_back(it.id);
		}
		if (cb)
			cb(uinfos);
	});*/
}

void UserService::InvokeUpdateMyInfo(const Db::Profile &new_info, const OnUpdateUserInfoCallback& cb)
{
	/*Db::Profile info = new_info;

	auto update_uinfo_cb = ToWeakCallback([this, info, cb](nim::NIMResCode res) {
		if (res == nim::kNIMResSuccess)
		{
			assert(nbase::MessageLoop::current()->ToUIMessageLoop());
			std::list<Db::Profile> lst;
			lst.push_back(info);
			OnUserInfoChangeBySDK(lst);
		}
		if (cb != nullptr)
			cb(res);
	});

	nim::User::UpdateMyUserNameCard(info, update_uinfo_cb);*/
}

void UserService::InvokeUpdateMyPhoto(const std::string &url, const OnUpdateUserInfoCallback& cb)
{
	/*Db::Profile my_info;
	my_info.SetAccId(LoginManager::GetInstance()->GetAccount());
	my_info.SetIconUrl(url);
	InvokeUpdateMyInfo(my_info, cb);*/
}

const std::map<std::string, Db::Profile>& UserService::GetAllUserInfos()
{
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	return all_user_;
}

const std::map<std::string, Db::Contact>& UserService::GetAllFriendInfos()
{
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	return friend_list_;
}

bool UserService::GetUserInfo(const std::string &id, Db::Profile &info)
{
	auto iter = all_user_.find(id);
	if (iter != all_user_.cend())
	{
		info = iter->second;
		return true;
	}
	else
	{
		info.profileid = id; 
		if(on_query_list_.find(id) == on_query_list_.cend())
			InvokeGetUserInfo(std::list<std::string>(1, id));
		return false;
	}
}

bool UserService::IsRobotAccount(const std::string &accid)
{
	//return robot_list_.find(accid) != robot_list_.end();
	return false;
}

void UserService::GetUserInfos(const std::list<std::string>& ids, std::list<Db::Profile>& uinfos)
{
	uinfos.clear();
	std::list<std::string> not_get_list;

	for (const auto &id : ids)
	{
		auto iter = all_user_.find(id);
		if (iter != all_user_.cend())
			uinfos.push_back(iter->second);
		else
		{
			Db::Profile info;
			info.profileid = id;
			uinfos.push_back(info);
			if(on_query_list_.find(id) == on_query_list_.end()) //不在all_user_里面，也不在查询途中
				not_get_list.push_back(id);
		}
	}

	if (!not_get_list.empty())
		InvokeGetUserInfo(not_get_list);
}

void UserService::DoQueryUserInfos(const std::list<std::string>& ids)
{
	if (ids.empty())
		return;
	
	std::list<std::string> not_get_list;

	for (const auto &id : ids)
	{
		if (id.empty())
			continue;

		if (all_user_.find(id) == all_user_.end())
		{
			if (on_query_list_.find(id) == on_query_list_.end()) //不在all_user_里面，也不在查询途中
				not_get_list.push_back(id);
		}
	}

	if (!not_get_list.empty())
		InvokeGetUserInfo(not_get_list);
}

void UserService::DoQueryUserInfos(const std::set<std::string>& ids)
{
	if (ids.empty())
		return;

	std::list<std::string> not_get_list;

	for (const auto &id : ids)
	{
		if (id.empty())
			continue;

		if (all_user_.find(id) == all_user_.end())
		{
			if (on_query_list_.find(id) == on_query_list_.end()) //不在all_user_里面，也不在查询途中
				not_get_list.push_back(id);
		}
	}

	if (!not_get_list.empty())
		InvokeGetUserInfo(not_get_list);
}

nim::NIMFriendFlag UserService::GetUserType(const std::string &id)
{
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	return (friend_list_.find(id) != friend_list_.end() ? nim::kNIMFriendFlagNormal : nim::kNIMFriendFlagNotFriend);
}

std::wstring UserService::GetUserName(const std::string &id, bool alias_prior/* = true */)
{
	//if(alias_prior && GetUserType(id) == nim::kNIMFriendFlagNormal && !friend_list_.at(id).GetAlias().empty()) //优先使用备注名
	//	return nbase::UTF8ToUTF16(friend_list_.at(id).GetAlias());

	Db::Profile info;
	GetUserInfo(id, info);
	return nbase::UTF8ToUTF16(info.givenname);
}

Json::Value UserService::GetUserCustom(const std::string &id)
{
	Json::Value ret;
	Db::Profile info;
	GetUserInfo(id, info);	
	//Json::Reader().parse(nim_cpp_wrapper_util::Json::FastWriter().write(info.GetExpand()), ret);
	return ret;
}

std::wstring UserService::GetFriendAlias(const std::string & id)
{
	auto iter = friend_list_.find(id);
	if (iter == friend_list_.cend())
		return L"";
	return nbase::UTF8ToUTF16(iter->second.remarks);
}

UnregisterCallback UserService::RegFriendListChange(const OnFriendListChangeCallback& callback)
{
	OnFriendListChangeCallback* new_callback = new OnFriendListChangeCallback(callback);
	int cb_id = (int)new_callback;
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	friend_list_change_cb_list_[cb_id].reset(new_callback);
	auto cb = ToWeakCallback([this, cb_id]() {
		friend_list_change_cb_list_.erase(cb_id);
	});
	return cb;
}

UnregisterCallback UserService::RegUserInfoChange(const OnUserInfoChangeCallback& callback)
{
	OnUserInfoChangeCallback* new_callback = new OnUserInfoChangeCallback(callback);
	int cb_id = (int)new_callback;
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	uinfo_change_cb_list_[cb_id].reset(new_callback);
	auto cb = ToWeakCallback([this, cb_id]() {
		uinfo_change_cb_list_.erase(cb_id);
	});
	return cb;
}

UnregisterCallback nim_comp::UserService::RegMiscUInfoChange(const OnUserInfoChangeCallback & callback)
{
	OnUserInfoChangeCallback* new_callback = new OnUserInfoChangeCallback(callback);
	int cb_id = (int)new_callback;
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	misc_uinfo_change_cb_list_[cb_id].reset(new_callback);
	auto cb = ToWeakCallback([this, cb_id]() {
		misc_uinfo_change_cb_list_.erase(cb_id);
	});
	return cb;
}

void UserService::OnFriendListChangeBySDK(const nim::FriendChangeEvent& change_event)
{
	std::list<std::string> add_list;
	std::list<std::string> delete_list;
	std::list<std::string> update_list; // 需要更换备注名的用户列表

	//switch (change_event.type_)
	//{
	//case nim::kNIMFriendChangeTypeDel:
	//{
	//	nim::FriendDelEvent del_event;
	//	nim::Friend::ParseFriendDelEvent(change_event, del_event);
	//	delete_list.push_back(del_event.accid_);
	//	update_list.push_back(del_event.accid_); // 删除好友之后，其原来的备注名改为其昵称
	//	friend_list_.erase(del_event.accid_); // 从friend_list_删除
	//	break;
	//}
	//case nim::kNIMFriendChangeTypeRequest:
	//{
	//	nim::FriendAddEvent add_event;
	//	nim::Friend::ParseFriendAddEvent(change_event, add_event);
	//	if (add_event.add_type_ == nim::kNIMVerifyTypeAdd || add_event.add_type_ == nim::kNIMVerifyTypeAgree)
	//	{
	//		// 此处根据accid获取该好友的FriendProfile，添加到friend_list_中。
	//		nim::Friend::GetFriendProfileCallback cb = ToWeakCallback([this](const std::string& accid, const nim::FriendProfile& user_profile)
	//		{
	//			if (accid.empty() || user_profile.id.empty())
	//			{
	//				QLOG_ERR(L"UserService::OnFriendListChangeBySDK kNIMFriendChangeTypeRequest error, accid:{0}, profile_accid:{1}") << accid.c_str() << user_profile.id.c_str();
	//				return;
	//			}
	//				
	//			friend_list_[user_profile.id] = user_profile;
	//			SubscribeEventManager::GetInstance()->SubscribeFriendEvent(user_profile.id);
	//			InvokeFriendListChangeCallback(kChangeTypeAdd, user_profile.id);
	//		});
	//		nim::Friend::GetFriendProfile(add_event.accid_, cb);
	//	}
	//	break;
	//}
	//case nim::kNIMFriendChangeTypeSyncList:
	//{
	//	// 单独处理好友同步消息
	//	OnSyncFriendList(change_event);
	//	return;
	//}
	//case nim::kNIMFriendChangeTypeUpdate:
	//{
	//	nim::FriendProfileUpdateEvent update_event;
	//	nim::Friend::ParseFriendProfileUpdateEvent(change_event, update_event);

	//	std::string accid = update_event.profile_.id;
	//	if (friend_list_.find(accid) != friend_list_.end())
	//	{
	//		update_list.push_back(accid);
	//		friend_list_.at(accid).Update(update_event.profile_);
	//	}		
	//	break;
	//}
	//default:
	//	break;
	//}

	//SubscribeEventManager::GetInstance()->SubscribeFriendEvent(add_list);
	//SubscribeEventManager::GetInstance()->UnSubscribeFriendEvent(delete_list);

	//for each (const auto& id in add_list)
	//	InvokeFriendListChangeCallback(kChangeTypeAdd, id);

	//for each (const auto& id in delete_list)
	//	InvokeFriendListChangeCallback(kChangeTypeDelete, id);

	//if (!update_list.empty())
	//{
	//	std::list<Db::Profile> uinfos;
	//	GetUserInfos(update_list, uinfos);
	//	for (auto& it : uinfo_change_cb_list_) //通知上层修改用户的备注名
	//		(*(it.second))(uinfos);
	//}
}

void UserService::OnSyncFriendList(const nim::FriendChangeEvent& change_event)
{
	std::list<std::string> add_list;
	std::list<std::string> delete_list;
	std::list<std::string> update_list; // 需要更换备注名的用户列表

	//nim::FriendProfileSyncEvent sync_event;
	//nim::Friend::ParseFriendProfileSyncEvent(change_event, sync_event);
	//for (auto& info : sync_event.profiles_)
	//{
	//	std::string accid = info.id;
	//	if (info.GetRelationship() == nim::kNIMFriendFlagNormal)
	//	{
	//		if (GetUserType(accid) == nim::kNIMFriendFlagNotFriend) //不在friend_list_里面，就添加进去
	//		{
	//			add_list.push_back(accid);
	//			friend_list_.insert(decltype(friend_list_)::value_type(accid, info));
	//		}
	//		else //在friend_list_里面，则更新之
	//		{
	//			update_list.push_back(accid);
	//			friend_list_.at(accid).Update(info);
	//		}
	//	}
	//	else
	//	{
	//		delete_list.push_back(accid);
	//		update_list.push_back(accid); // 删除好友之后，其原来的备注名改为其昵称
	//		friend_list_.erase(accid); // 从friend_list_删除
	//	}
	//}

	// 好友同步消息会在登录后较早的收到，这时批量的拉取用户信息把这些好友添加到查询队列里
	// 避免创建好友列表项时，列表项控件查询用户信息而导致频繁调用用户信息获取接口
	DoQueryUserInfos(add_list);
	DoQueryUserInfos(update_list);

	/*SubscribeEventManager::GetInstance()->SubscribeFriendEvent(add_list);
	SubscribeEventManager::GetInstance()->UnSubscribeFriendEvent(delete_list);*/

	for each (const auto& id in add_list)
		InvokeFriendListChangeCallback(kChangeTypeAdd, id);

	for each (const auto& id in delete_list)
		InvokeFriendListChangeCallback(kChangeTypeDelete, id);

	for each (const auto& id in update_list)
		InvokeFriendListChangeCallback(kChangeTypeUpdate, id);
}

void UserService::OnUserInfoChangeBySDK(const std::list<Db::Profile> &uinfo_list)
{
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());

	std::list<Db::Profile> name_photo_list;
	std::list<Db::Profile> misc_uinfo_list;

	for (auto& info : uinfo_list)
	{
		//auto iter = all_user_.find(info.id);
		//if (iter != all_user_.end()) //all_user_中存在，就更新
		//	iter->second.Update(info);
		//else
		//	all_user_[info.id] = info;

		///*if (!info.GetIconUrl().empty())
		//	PhotoService::GetInstance()->DownloadUserPhoto(info);*/

		//if (info.ExistValue(nim::kUserNameCardKeyName) || info.ExistValue(nim::kUserNameCardKeyIconUrl)) //用户名或头像变化了
		//	name_photo_list.push_back(info);
		//if (info.ExistValue((Db::ProfileValueKey)(nim::kUserNameCardKeyAll - nim::kUserNameCardKeyName - nim::kUserNameCardKeyIconUrl))) //用户其他信息变化了
		//	misc_uinfo_list.push_back(info);
	}

	// 执行回调列表中所有回调
	//for (auto& it : uinfo_change_cb_list_)
	//	(*(it.second))(name_photo_list);
	//for (auto& it : misc_uinfo_change_cb_list_)
	//	(*(it.second))(misc_uinfo_list);
}

void UserService::OnUserInfoChange(const std::list<Db::Profile> &uinfo_list)
{
	assert(nbase::MessageLoop::current()->ToUIMessageLoop());

	std::list<Db::Profile> name_photo_list;
	std::list<Db::Profile> misc_uinfo_list;

	for (auto& info : uinfo_list)
	{
		if (!info.link.empty())
			PhotoService::GetInstance()->DownloadUserPhoto(info);

		//if (info.ExistValue(nim::kUserNameCardKeyName) || info.ExistValue(nim::kUserNameCardKeyIconUrl)) //用户名或头像变化了
		//	name_photo_list.push_back(info);
		//if (info.ExistValue((Db::ProfileValueKey)(nim::kUserNameCardKeyAll - nim::kUserNameCardKeyName - nim::kUserNameCardKeyIconUrl))) //用户其他信息变化了
		//	misc_uinfo_list.push_back(info);
	}

	//// 执行回调列表中所有回调
	for (auto& it : uinfo_change_cb_list_)
		(*(it.second))(name_photo_list);
	for (auto& it : misc_uinfo_change_cb_list_)
		(*(it.second))(misc_uinfo_list);
}

void UserService::InvokeGetUserInfo(const std::list<std::string>& account_list)
{
	// 先在本地db中找
	std::list<Db::Profile> profiles = Api::ProfileApi::get_ProfilesFromDb(account_list);

	std::set<std::string> not_get_set(account_list.cbegin(), account_list.cend());
	for (auto& profile : profiles)
	{
		all_user_[profile.profileid] = profile; // 插入all_user
		on_query_list_.erase(profile.profileid); //已经查到，就从on_query_list_删除
		not_get_set.erase(profile.profileid);
	}

	OnUserInfoChange(profiles); //触发监听

	if (not_get_set.empty()) // 全部从本地db找到，直接返回
		return;

	std::list<std::string> ids;
	for (auto iter = not_get_set.begin(); iter != not_get_set.end(); ++iter)
	{
		ids.push_back(*iter);
	}
	std::list<Rest::Profile> lists = Api::ProfileApi::loadMany(ids);
	for (Rest::Profile &profile_info : lists) {
		Db::Profile profile = Db::Profile(profile_info);
		profile.saveCache();
		all_user_[profile.profileid] = profile; // 插入all_user
	} 
	//nim::User::GetUserNameCardCallback cb1 = ToWeakCallback([this, account_list](const std::list<Db::Profile> &json_result)
	//{
	//	std::set<std::string> not_get_set(account_list.cbegin(), account_list.cend());
	//	for (auto& card : json_result)
	//	{
	//		all_user_[card.id] = card; // 插入all_user
	//		on_query_list_.erase(card.id); //已经查到，就从on_query_list_删除
	//		not_get_set.erase(card.id);
	//	}

	//	OnUserInfoChange(json_result); //触发监听

	//	if (not_get_set.empty()) // 全部从本地db找到，直接返回
	//		return;

	//	// 有些信息本地db没有，再从服务器获取
	//	auto closure = [this](const std::list<std::string>& ids)
	//	{
	//		nim::User::GetUserNameCardOnline(ids,
	//			this->ToWeakCallback([this, ids](const std::list<Db::Profile> &json_result)
	//			{
	//				std::set<std::string> tmp_set(ids.cbegin(), ids.cend());
	//				for (auto& card : json_result)
	//				{
	//					all_user_[card.id] = card; // 插入all_user

	//					//if (card.ExistValue(nim::kUserNameCardKeyIconUrl))
	//					//	PhotoService::GetInstance()->DownloadUserPhoto(card); // 下载头像

	//					on_query_list_.erase(card.id); //已经查到，就从on_query_list_删除
	//					tmp_set.erase(card.id);
	//				}

	//				//OnUserInfoChangeBySdk(json_result); //sdk会自动触发此回调

	//				for (const auto& id : tmp_set) //从服务器也查不到的用户
	//				{
	//					QLOG_APP(L"Can't get user's name card from server. Account id: {0}.") << id;
	//					on_query_list_.erase(id); //从on_query_list_删除，以免积压
	//				}
	//		}));
	//	};
	//			
	//	//SDK限制一次服务器查询数量不超过150	
	//	std::list<std::string> ids;
	//	if (not_get_set.size() > 150)
	//	{			
	//		for (auto iter = not_get_set.begin(); iter != not_get_set.end(); ++iter)
	//		{
	//			ids.push_back(*iter);
	//			if (ids.size() == 150)
	//			{
	//				closure(ids);
	//				ids.clear();
	//			}
	//		}
	//		if (!ids.empty())
	//		{
	//			closure(ids);
	//			ids.clear();
	//		}
	//	}
	//	else
	//	{
	//		for (auto iter = not_get_set.begin(); iter != not_get_set.end(); ++iter)
	//		{
	//			ids.push_back(*iter);
	//		}
	//		closure(ids);
	//	}
	//});

	//for (const auto& id : account_list)
	//	on_query_list_.insert(id);

	//nim::User::GetUserNameCard(account_list, cb1);
}

void UserService::InvokeFriendListChangeCallback(FriendChangeType change_type, const std::string& accid)
{
	if (accid.empty())
		return;

	assert(nbase::MessageLoop::current()->ToUIMessageLoop());
	for (auto& it : friend_list_change_cb_list_)
	{
		(*(it.second))(change_type, accid);
	}
}

}
