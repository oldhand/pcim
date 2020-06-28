﻿#include "stdafx.h"
#include "session_manager.h"
#include "plugins/session/nim_ui_session_list_manager.h"
//#include "gui/session/force_push_manager.h"
//#include "module/service/mute_black_service.h"
//#include "module/runtime_data/runtime_data_manager.h"
//#include "module/video/video_manager.h"
#include "gui/session/session_form.h"
#include "gui/session/session_box.h"
#include "gui/session/session_dock_def.h"
namespace nim_comp
{
SessionManager::SessionManager()
{
	enable_merge_ = true;
	use_custom_drag_image_ = true;
	ring_.Init(NULL);
}

SessionManager::~SessionManager()
{

}

SessionBox* SessionManager::OpenSessionBox(std::string session_id, nim::NIMSessionType type, bool reopen)
{
	if (session_id.empty())
	{
		ASSERT(0);
		return NULL;
	}

	// 在当前列表中查找是否有要打开的会话
	auto it_box = session_box_map_.find(session_id);
	if (it_box != session_box_map_.end())
	{
		// 如果需要重新打开则删除原来的 session box 再重新创建一个，否则就激活当前查找到的 session box
		ISessionDock *parent_form = it_box->second->GetSessionForm();
		if (!reopen)
		{
			parent_form->SetActiveSessionBox(session_id);
			return it_box->second;
		}
		else
		{
			parent_form->CloseSessionBox(session_id);
			RemoveSessionBox(session_id);
		}
	}
	/*std::vector<ForcePushManager::ForcePushInfo> infos;
	ForcePushManager::GetInstance()->GetAtMeMsgs(session_id, infos);*/

	SessionBox *session_box = CreateSessionBox(session_id, type);
	if (NULL == session_box)
		return NULL;

	session_box->InvokeShowMsgs(true);
	//session_box->InitAtMeView(infos);
	if (session_box->GetSessionForm() != nullptr)
		session_box->GetSessionForm()->ActiveWindow();
	return session_box;
}

void SessionManager::AddNewMsg(const nim::IMMessage &msg)
{
	std::string id = GetSessionId(msg);
	SessionBox *session_box = FindSessionBox(id);

	if (session_box && !session_box->IsTeamValid())
	{
		ISessionDock *parent_form = session_box->GetSessionForm();
		parent_form->CloseSessionBox(id);
		session_box = NULL;
	}

	bool create = false;
	bool msg_notify = true;
	if (nim_comp::RunTimeDataManager::GetInstance()->GetUIStyle() == UIStyle::join)
	{
		msg_notify = false;
	}
	else
	{
		if (msg.session_type_ == nim::kNIMSessionTypeTeam)
		{
			if (!IsTeamMsgNotify(id, msg.sender_accid_))
				msg_notify = false;
		}
		/*else
			msg_notify = !MuteBlackService::GetInstance()->IsInMuteList(id);*/
	}
	

	if (NULL == session_box)
	{
		if (msg_notify)
		{
			create = true;
			// 如果使用了合并会话功能并且已经有了会话窗体，则取消create标志
			if (enable_merge_ && !session_box_map_.empty())
				create = false;
			if(create)
				session_box = CreateSessionBox(id, msg.session_type_);
			if (NULL == session_box)
				return;
		}
	}

	Json::Reader reader;
	Json::Value values;
	reader.parse(msg.attach_, values);
	if (msg.type_ == nim::kNIMMessageTypeCustom)
	{
		if (values.isMember(kJsonKeyCommand))
		{
			// 不播放 P2P 传送文件时自定义协商消息
			msg_notify = values[kJsonKeyCommand].asString() == kJsonKeyTransferFileRequest;
		}
	}

	if (msg.type_ == nim::kNIMMessageTypeTips && msg.session_type_ == nim::kNIMSessionTypeTeam)
	{
		//// 群组视频邀请 tips 消息
		//if (values.isMember("id") && values["id"].asInt() == 100)
		//{
		//	bool add_new_msg = false;
		//	auto account = nim_comp::LoginManager::GetInstance()->GetAccount();
		//	for (auto member : values["content"]["members"])
		//	{
		//		if (account == member.asString())
		//			add_new_msg = true;

		//		QLOG_APP(L"member = {0}") << member.asString();
		//	}

		//	if (add_new_msg)
		//		VideoManager::GetInstance()->InvokeReceiveCustomP2PMessage(values["content"], msg.sender_accid_);
		//	else
		//		return;
		//}
	}

	if (session_box)
	{
		session_box->AddNewMsg(msg, create);

		if (msg_notify)
			ring_.Play(RING_NEW_MESSAGE);
	}
}

bool SessionManager::IsSessionBoxActive(const std::string& id)
{
	SessionBox *session_box = FindSessionBox(id);
	if (NULL != session_box)
	{
		ISessionDock *parent_form = session_box->GetSessionForm();
		return parent_form->IsActiveSessionBox(session_box);
	}

	return false;
}
SessionBox* SessionManager::GetFirstActiveSession()
{
	for (auto &it_box : session_box_map_)
	{
		ISessionDock *parent_form = it_box.second->GetSessionForm();
		if (parent_form && parent_form->IsActiveSessionBox(it_box.second))
		{
			return it_box.second;
		}
	}
	return nullptr;
}

SessionBox* SessionManager::FindSessionBox( const std::string &id )
{
	std::map<std::string, SessionBox*>::const_iterator i = session_box_map_.find(id);
	if (i == session_box_map_.end())
		return NULL;
	else
		return i->second;
}

void SessionManager::RemoveSessionBox( std::string id, const SessionBox* box /*=NULL*/)
{
	auto it_box = session_box_map_.find(id);
	if (it_box != session_box_map_.end())
	{
		if (NULL == box || box == it_box->second)
		{
			session_box_map_.erase(it_box);
		}
		else
		{
			assert(0);
		}
	}
}

nim_comp::SessionBox* SessionManager::CreateSessionBox(const std::string &session_id, nim::NIMSessionType type)
{
	SessionBox *session_box = NULL;
	ISessionDock *session_form = NULL;

	// 如果启用了窗口合并功能，就把新会话盒子都集中创建到某一个会话窗体里
	// 否则每个会话盒子都创建一个会话窗体
	if (enable_merge_)
	{
		if (session_box_map_.size() >= 1)
		{
			session_form = session_box_map_.begin()->second->GetSessionForm();
		}
		else
		{
			session_form = ISessionDock::InstantDock();
			HWND hwnd = session_form->Create();
			if (hwnd == NULL)
			{
				session_form = NULL;
				return NULL;
			}
			session_form->CenterWindow();
		}

		session_box = session_form->CreateSessionBox(session_id, type);
		if (NULL == session_box)
			return NULL;
	}
	else
	{
		session_form = ISessionDock::InstantDock();
		HWND hwnd = session_form->Create();
		if (hwnd == NULL)
			return NULL;

		session_box = session_form->CreateSessionBox(session_id, type);
		if (NULL == session_box)
			return NULL;

		session_form->CenterWindow();
	}
	session_box_map_[session_id] = session_box;
	return session_box;
}

void SessionManager::ResetUnread(const std::string &id)
{
	// 重置对应会话中的@me消息为已读
	//ForcePushManager::GetInstance()->ResetAtMeMsg(id);

	// 重置会话列表未读消息数
	nim_ui::SessionListManager::GetInstance()->InvokeResetSessionUnread(id);
}

void SessionManager::QueryMyTeamMemberInfo(const std::string& tid)
{
	//nim::Team::QueryTeamMemberAsync(tid, LoginManager::GetInstance()->GetAccount(), nbase::Bind(&SessionManager::OnQueryMyTeamMemberInfo, this, tid, std::placeholders::_1));
}

void SessionManager::QueryMyAllTeamMemberInfos()
{
	//nim::Team::QueryMyAllMemberInfosAsync(nbase::Bind(&SessionManager::OnQueryMyAllTeamMemberInfos, this, std::placeholders::_1, std::placeholders::_2));
}

void SessionManager::OnQueryMyTeamMemberInfo(const std::string& tid, const nim::TeamMemberProperty& team_member_info)
{
	if (team_list_bits_[tid] != team_member_info.GetBits())
	{
		TeamService::GetInstance()->InvokeChangeNotificationMode(tid, team_member_info.GetBits());
	}
	team_list_bits_[tid] = team_member_info.GetBits();
}

void SessionManager::OnQueryMyAllTeamMemberInfos(int count, const std::list<nim::TeamMemberProperty>& all_my_member_info_list)
{
	for (auto it : all_my_member_info_list)
	{		
		if (team_list_bits_[it.GetTeamID()] != it.GetBits())
		{
			TeamService::GetInstance()->InvokeChangeNotificationMode(it.GetTeamID(), it.GetBits());
		}
		team_list_bits_[it.GetTeamID()] = it.GetBits();
	}
}

bool SessionManager::IsTeamMsgNotify(const std::string& tid, const std::string& sender_id)
{
	auto it = team_list_bits_.find(tid);
	if (it != team_list_bits_.end())
	{
		if ((it->second & nim::kNIMTeamBitsConfigMaskMuteNotify) == nim::kNIMTeamBitsConfigMaskMuteNotify)
		{
			return false;
		}
		else if ((it->second & nim::kNIMTeamBitsConfigMaskOnlyAdmin) == nim::kNIMTeamBitsConfigMaskOnlyAdmin)
		{
			if (!sender_id.empty())
			{
				/*auto prop = nim::Team::QueryTeamMemberBlock(tid, sender_id);
				return prop.GetUserType() > nim::kNIMTeamUserTypeNomal;*/
			}
			return false;
		}
	}
	return true;
}

bool SessionManager::IsTeamMsgMuteShown(const std::string& tid, int64_t bits)
{
	if (bits < 0)
	{
		auto it = team_list_bits_.find(tid);
		if (it == team_list_bits_.end())
			return false;
		bits = it->second;
	}
	if ((bits & nim::kNIMTeamBitsConfigMaskMuteNotify) == nim::kNIMTeamBitsConfigMaskMuteNotify
		|| (bits & nim::kNIMTeamBitsConfigMaskOnlyAdmin) == nim::kNIMTeamBitsConfigMaskOnlyAdmin)
	{
		return true;
	}
	return false;
}
}