#include "stdafx.h"
#include "services/session_service.h"
#include "services/user_service.h"
#include "gui/subscribe_event/subscribe_event_manager.h"
#include "include/callback_proxy.h"
#include "plugins/session/nim_cpp_session.h"

namespace nim_comp
{
	void SessionService::InvokeLoadSessionList()
	{
		nim::Session::QueryAllRecentSessionAsync(nbase::Bind(&nim_comp::SessionService::OnQuerySessionListCallback, std::placeholders::_1, std::placeholders::_2));
	}


	nim::SessionData SessionService::GetSessionItem(const std::string &session_id)
	{
		auto iter = sessions_.find(session_id);
		if (iter != sessions_.end())
			return iter->second;
		else
			return nim::SessionData();
	}

	void SessionService::OnQuerySessionList(const std::list<nim::SessionData>& sessions)
	{
		if (sessions.empty())
			return;

		// ����Ự�б���ڵ�¼�������յ�����ʱ��������ȡ�漰�����û���Ϣ����Щ�û���ӵ���ѯ������
		// ���ⴴ���Ự�б���ʱ���б���ؼ���ѯ�û���Ϣ������Ƶ�������û���Ϣ��ȡ�ӿ�
		std::list<std::string> user_ids;
		for each (auto& session in sessions)
		{
			if (session.type_ == nim::kNIMSessionTypeP2P)
			{
				user_ids.push_back(session.id_);
			}
			else
			{
				user_ids.push_back(session.msg_sender_accid_);
			}
		}
		nim_comp::UserService::GetInstance()->DoQueryUserInfos(user_ids);
		//nim_comp::SubscribeEventManager::GetInstance()->SubscribeAllSessionEvent(sessions);

		for each (auto& session in sessions)
		{
			auto iter = sessions_.find(session.id_);
			if (iter != sessions_.end())
			{
				if (nim::kNIMSessionCommandMsgDeleted != session.command_ && iter->second.msg_timetag_ > session.msg_timetag_)
				{
					sessions_[session.id_] = session;
				}
				break;
			}
			else
			{
				sessions_[session.id_] = session;
			}
		}

		(*session_data_changed_callback_)(sessions);
	}

	void SessionService::OnQuerySessionListCallback(int unread_count, const nim::SessionDataList& session_list)
	{
		QLOG_PRO(L"local session list: count :{0} - unread :{1}") << session_list.count_ << session_list.unread_count_;
		SessionService::GetInstance()->OnQuerySessionList(session_list.sessions_);
	}
}