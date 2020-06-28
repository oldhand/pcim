﻿#include "stdafx.h"
#include "session_callback.h"
#include "session_manager.h"
#include "plugins/session//nim_ui_session_list_manager.h"
#include "pages/ui_window_manager.h"
#include "gui/session/session_util.h"
namespace nim_comp
{
//void TalkCallback::OnSendMsgCallback(const nim::SendMessageArc& arc)
//{
//	QLOG_APP(L"OnSendMsgCallback: id={0} msg_id={1} code={2}") << arc.talk_id_ << arc.msg_id_ << arc.rescode_;
//
//	//测试用代码
//	// 	nim::MsgLog::UpdateLocalExtAsync(arc.msg_id_, arc.msg_id_, [arc](nim::NIMResCode res_code, const std::string& msg_id){
//	// 		QLOG_APP(L"UpdateLocalExtAsync: id={0} msg_id={1} code={2} local={3}") << arc.talk_id_ << msg_id << res_code << arc.msg_id_;
//	// 		nim::MsgLog::QueryMsgByIDAysnc(arc.msg_id_, [arc](nim::NIMResCode res_code, const std::string& msg_id, const nim::IMMessage& msg){
//	// 			QLOG_APP(L"QueryMsgByIDAysnc: id={0} msg_id={1} code={2}, local:{3}") << arc.talk_id_ << msg_id << res_code << msg.local_ext_;
//	// 		});
//	// 	});
//
//	SessionBox* session_form = SessionManager::GetInstance()->FindSessionBox(arc.talk_id_);
//	if (session_form)
//		session_form->OnSendMsgCallback(arc.msg_id_, arc.rescode_, arc.msg_timetag_);
//}

void TalkCallback::OnReceiveMsgCallback(const nim::IMMessage& message)
{
	QLOG_PRO(L"OnReceiveMsgCallback: {0} from client:{1}") << message.client_msg_id_ << message.readonly_sender_client_type_;
	std::string id = GetSessionId(message);

	if (message.feature_ == nim::kNIMMessageFeatureDefault)
	{
		if (message.type_ == nim::kNIMMessageTypeNotification/* && !nim::Client::GetSDKConfig().team_notification_unread_count_*/)
		{
			SessionBox* session = SessionManager::GetInstance()->FindSessionBox(id);
			if (session)
			{
				session->AddNewMsg(message, false);
			}
		}
		else
		{
			SessionManager::GetInstance()->AddNewMsg(message);
		}
	}
	else if (message.feature_ == nim::kNIMMessageFeatureSyncMsg ||
		message.feature_ == nim::kNIMMessageFeatureRoamMsg ||
		message.feature_ == nim::kNIMMessageFeatureCustomizedMsg ||
		message.feature_ == nim::kNIMMessageFeatureLeaveMsg)
	{
		SessionBox* session = SessionManager::GetInstance()->FindSessionBox(id);
		if (session)
		{
			session->AddNewMsg(message, false);
		}
	}
	
	// 如果目标会话盒子不在激活状态
	if (!SessionManager::GetInstance()->IsSessionBoxActive(id))
	{
		// 更新对应会话中的@me消息为未读
		/*if (ForcePushManager::GetInstance()->IsAtMeMsg(message))
			ForcePushManager::GetInstance()->AddAtMeMsg(id, message);*/
	}
}

void TalkCallback::OnReceiveMsgsCallback(const std::list<nim::IMMessage>& messages)
{
	//例子 开发者可以根据需求实现(比如为了减少UI刷新频率，只在最后一条消息收到后刷新UI等)
	for (auto msg : messages)
	{
		OnReceiveMsgCallback(msg);
	}
}

void TalkCallback::OnReceiveBroadcastMsgCallback(const nim::BroadcastMessage& message)
{
	std::wstring toast = nbase::StringPrintf(L"Receive broadcast:\r\n%s(%s):\r\n%s"
		, nbase::UTF8ToUTF16(message.from_id_).c_str()
		, nim_comp::GetMessageTime(message.time_, false).c_str()
		, nbase::UTF8ToUTF16(message.body_).c_str());
	nim_ui::ShowToast(toast, 30000);
}

void TalkCallback::OnReceiveBroadcastMsgsCallback(const std::list<nim::BroadcastMessage>& messages)
{
	std::wstring toast = nbase::StringPrintf(L"Receive %d broadcasts\r\n", messages.size());
	for (auto &msg : messages)
	{
		std::wstring tt = nbase::StringPrintf(L"%s(%s):\r\n%s\r\n"
			, nbase::UTF8ToUTF16(msg.from_id_).c_str()
			, nim_comp::GetMessageTime(msg.time_, false).c_str()
			, nbase::UTF8ToUTF16(msg.body_).c_str());
		toast += tt;
	}
	nim_ui::ShowToast(toast, 30000);
}

//void TalkCallback::OnReceiveRecallMsgCallback(nim::NIMResCode code, const std::list<nim::RecallMsgNotify>& message)
//{
//	for (auto notify : message)
//	{
//		QLOG_APP(L"TalkCallback::OnReceiveRecallMsgCallback: code:{0} from_id:{1} to_id:{2} msg_time:{3} msglog_createtime:{4} msg_id:{5}")
//			<< code << notify.from_id_ << notify.to_id_ << notify.notify_timetag_ << notify.msglog_timetag_ << notify.msg_id_;
//
//		UTF8String talk_id;
//		if (notify.session_type_ == nim::kNIMSessionTypeTeam)
//			talk_id = notify.to_id_;
//		else
//			talk_id = notify.from_id_ == LoginManager::GetInstance()->GetAccount() ? notify.to_id_ : notify.from_id_;
//
//		SessionBox* session = SessionManager::GetInstance()->FindSessionBox(talk_id);
//		if (session)
//		{
//			session->OnRecallMsgCallback(code, notify);
//		}
//		else
//		{
//			if (code != nim::kNIMResSuccess)
//			{
//				std::wstring toast = nbase::StringPrintf(L"recall msg error, code:%d, id:%s", code, nbase::UTF8ToUTF16(notify.msg_id_).c_str());
//				nim_ui::ShowToast(toast, 5000);
//				return;
//			}
//
//			std::wstring notify_text = GetRecallNotifyTextEx(talk_id, notify.session_type_, notify.from_id_, notify.operator_id_,notify.from_nick_);
//			nim::IMMessage msg;
//			msg.timetag_ = notify.msglog_timetag_;
//			msg.feature_ = notify.notify_feature_;
//			msg.client_msg_id_ = QString::GetGUID();
//			msg.receiver_accid_ = talk_id;
//			msg.session_type_ = notify.session_type_;
//			msg.sender_accid_ = notify.from_id_;
//			msg.status_ = nim::kNIMMsgLogStatusSent;
//			msg.type_ = nim::kNIMMessageTypeText;
//			Json::Value values;
//			values["comment"] = "is_recall_notification";
//			values["notify_from"] = notify.from_id_;
//			values["operator_id"] = notify.operator_id_;
//			values["from_nick"] = notify.from_nick_;
//			values["feature"] = msg.feature_;
//			msg.attach_ = values.toStyledString();
//			msg.content_ = nbase::UTF16ToUTF8(notify_text);
//			msg.msg_setting_.push_need_badge_ = BS_FALSE; //设置会话列表不需要计入未读数
//			nim::MsgLog::WriteMsglogToLocalAsync(talk_id, msg, true, nim::MsgLog::WriteMsglogCallback());
//		}
//	}
//}

void TalkCallback::OnMsgStatusChangedCallback(const nim::MessageStatusChangedResult& res)
{
	QLOG_APP(L"TalkCallback: OnMsgStatusChangedCallback");
	for (auto res : res.results_)
	{
		SessionBox *form = SessionManager::GetInstance()->FindSessionBox(res.talk_id_);
		if (form)
			form->OnMsgStatusChangedCallback(res.talk_id_, res.msg_timetag_, res.status_);
	}
}

//void TalkCallback::OnSendCustomSysmsgCallback(const nim::SendMessageArc& arc)
//{
//	if (arc.rescode_ != nim::kNIMResSuccess)
//	{
//		QLOG_ERR(L"OnSendCustomSysmsgCallback: id={0} msg_id={1} code={2}") << arc.talk_id_ << arc.msg_id_ << arc.rescode_;
//	}
//}

void TalkCallback::OnQueryMsgCallback(nim::NIMResCode code, const std::string& query_id, nim::NIMSessionType query_type, const nim::QueryMsglogResult& result)
{
	QLOG_APP(L"query end: id={0} type={1} code={2} source={3}") <<query_id <<query_type <<code<< result.source_;

	std::vector<nim::IMMessage> vec;
	for each (auto msg in result.msglogs_)
	{
		vec.push_back(msg);
	}

	SessionBox* session_form = SessionManager::GetInstance()->FindSessionBox(query_id);
	if (session_form)
		session_form->ShowMsgs(vec);
}

void TalkCallback::OnQuerySessionListCallback(int unread_count, const nim::SessionDataList& session_list)
{
	QLOG_PRO(L"local session list: count :{0} - unread :{1}") << session_list.count_ << session_list.unread_count_;
	nim_ui::SessionListManager::GetInstance()->OnQuerySessionListCallback(session_list.sessions_);
}

}