﻿#include "stdafx.h"
#include "session_box.h"
#include "session_form.h"
//#include "custom_msg_form.h"
//#include "gui/link/link_form.h"
//#include "gui/contact_select_form/contact_select_form.h"
//#include "gui/team_info/team_info.h"
//#include "gui/broad/broad_form.h"
//#include "gui/session/msg_record.h"
#include "gui/profile_form/profile_form.h"
//#include "gui/session/control/audio_capture.h"

//#include "callback/session/session_callback.h"
//#include "callback/http/http_callback.h"
//#include "callback/team/team_callback.h"
//#include "capture_image/src/capture_manager.h"

//#include "module/session/session_manager.h"
//#include "av_kit/module/video/video_manager.h"
//#include "module/rts/rts_manager.h"
//#include "module/service/user_service.h"

#include "ui_components/modal_wnd/file_dialog_ex.h"
//#include "gui/session/unread_form.h"
//#include "av_kit/gui/video/multi_video_form.h"
#include "ui_components/toast/toast.h"

using namespace ui;


namespace nim_comp
{

LRESULT SessionBox::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandle)
{
	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == 'V')
		{
			if (::GetKeyState(VK_CONTROL) < 0 && input_edit_->IsFocused())
			{
				if (!PasteClipboard())
					input_edit_->PasteSpecial(CF_TEXT);
				bHandle = true;
				return 1;
			}
		}
		else if (wParam == VK_DOWN || wParam == VK_UP || wParam == VK_RETURN || wParam == VK_BACK)
		{
			if (HandleAtMsg(wParam, lParam))
			{
				bHandle = true;
				return 0;
			}	
		}
	}
	if (uMsg == WM_CHAR)
	{
		if (wParam != VK_BACK)
		{
			//先让RichEdit处理完，然后再处理@消息
			LRESULT res = session_form_->HostWindowHandleMessage(uMsg, wParam, lParam);
			HandleAtMsg(wParam, lParam);
			bHandle = true;
			return res;
		}
	}
	else if (uMsg == WM_MOUSEWHEEL)
	{
		//处理@列表的滚动
		if (HandleAtMouseWheel(wParam, lParam))
		{
			bHandle = true;
			return 0;
		}		
	}
	else if (uMsg == WM_LBUTTONDOWN || uMsg == WM_NCLBUTTONDOWN || uMsg == WM_RBUTTONDOWN || uMsg == WM_KILLFOCUS)
	{
		HideAtListForm();
	}
	if (uMsg == WM_SIZE)
	{
		if (wParam == SIZE_RESTORED)
			OnWndSizeMax(false);
		else if (wParam == SIZE_MAXIMIZED)
			OnWndSizeMax(true);
	}
	if (uMsg == WM_SETFOCUS)
	{
		if (input_edit_)
			input_edit_->SetFocus();
	}
	if (uMsg == WM_ACTIVATE)
	{
		if (wParam != WA_INACTIVE)
		{
			OnActivate();
		}
	}

	return 0;
}

void SessionBox::OnEsc(BOOL &bHandled)
{
	std::wstring wstr = GetRichText(input_edit_);
	StringHelper::Trim(wstr);
	if (!wstr.empty())
	{
		bHandled = TRUE;

		/*MsgboxCallback cb = nbase::Bind(&SessionBox::OnCloseInputMsgBoxCallback, this, std::placeholders::_1);
		ShowMsgBox(this->GetWindow()->GetHWND(), cb, L"STRID_SESSION_CONTENT_NOT_SENT");*/
	}
}

bool SessionBox::Notify(ui::EventArgs* param)
{
//	std::wstring name = param->pSender->GetName();
//	if (param->Type == kEventCustomLinkClick)
//	{
//		RichEdit* text_edit = dynamic_cast<RichEdit*>(param->pSender);
//		std::wstring link_info;
//		if (text_edit->HittestCustomLink(param->ptMouse, link_info))
//		{
//			Json::Value values;
//			Json::Reader reader;
//			if (reader.parse(nbase::UTF16ToUTF8((std::wstring)link_info), values) && values.isObject())
//			{
//				std::string type = values["type"].asString();
//				if (type == "url")
//				{
//					std::string url = values["target"].asString();
//					//Post2GlobalMisc(nbase::Bind(&shared::tools::SafeOpenUrl, nbase::UTF8ToUTF16(url), SW_SHOW));
//				}
//				else if (type == "block")
//				{
//					std::string robot_id = values[nim::kNIMBotRobotMsgKeyRobotID].asString();
//					std::string content = values["link_text"].asString();
//					nim::IMMessage msg;
//					PackageMsg(msg);
//					nim::MessageSetting setting;
//					msg.type_ = nim::kNIMMessageTypeRobot;
//					msg.content_ = content;
//					nim::IMBotRobot bot;
//					bot.robot_accid_ = robot_id;
//					bot.sent_param_["target"] = values["target"].asString();
//					bot.sent_param_["type"] = "03";
//					bot.sent_param_["params"] = values["params"].asString();
//					msg.attach_ = bot.ToJsonString();
//					//std::string json_msg = nim::Talk::CreateBotRobotMessage(msg.receiver_accid_, msg.session_type_, msg.client_msg_id_, content, bot, setting, msg.timetag_);
//					//AddSendingMsg(msg);
//					//nim::Talk::SendMsg(json_msg);
//
//				}
//				else
//				{
//					assert(0);
//					QLOG_ERR(L"\r\nError custom click: {0}") << (std::wstring)link_info;
//				}
//			}
//		}
//
//	}
//	else if (param->Type == kEventScrollChange)
//	{
//		if (name == L"msg_list")
//		{
//			if (receipt_need_send_)
//			{
//				SendReceiptIfNeeded(true);
//			}
//			SendTeamReceiptIfNeeded(true);
//		}
//	}
//	else if (param->Type == ui::kEventNotify)
//	{
//		//MsgBubbleItem* item = dynamic_cast<MsgBubbleItem*>(param->pSender);
//		//assert(item);
//		//nim::IMMessage md = item->GetMsg();
//
//		//if (param->wParam == BET_RESEND)
//		//{
//		//	RemoveMsgItem(md.client_msg_id_);
//		//	ReSendMsg(md);
//		//}
//		//else if (param->wParam == BET_UNREAD_COUNT)
//		//{
//		//	UnreadForm *window = (UnreadForm*)(WindowsManager::GetInstance()->GetWindow(UnreadForm::kClassName, UnreadForm::kClassName));
//		//	if (!window)
//		//	{
//		//		window = new UnreadForm;
//		//		window->Create(session_form_->GetHWND(), UnreadForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
//		//		window->CenterWindow();
//		//		window->ShowWindow();
//		//	}
//		//	else
//		//	{
//		//		window->ActiveWindow();
//		//	}
//		//	if (window)
//		//		window->LoadList(md, team_member_info_list_);
//		//}
//		//else if (param->wParam == BET_RELOAD)
//		//{
//		//	item->SetLoadStatus(RS_LOADING);
//		//	nim::NOS::FetchMedia(md, nim::NOS::DownloadMediaCallback(), nim::NOS::ProgressCallback());
//		//}
//		//else if (param->wParam == BET_DELETE)
//		//{
//		//	RemoveMsgItem(md.client_msg_id_);
//		//	//if (session_type_ == nim::kNIMSessionTypeTeam)
//		//	//	nim::Session::DeleteRecentSession(nim::kNIMSessionTypeTeam, session_id_, nim::Session::DeleteRecentSessionCallabck());
//		//	nim::MsgLog::DeleteAsync(session_id_, session_type_, md.client_msg_id_, nim::MsgLog::DeleteCallback());
//		//}
//		//else if (param->wParam == BET_RETWEET)
//		//{
//		//	nim::MsgLog::QueryMsgByIDAysnc(md.client_msg_id_, ToWeakCallback(
//		//		[this](nim::NIMResCode res_code, const std::string& msg_id, const nim::IMMessage& msg){
//		//		if (res_code == nim::kNIMResSuccess)
//		//			OnMenuRetweetMessage(msg);
//		//	}));			
//		//}
//		//else if (param->wParam == BET_RECALL)
//		//{
//		//	nim::Talk::RecallMsg(md, "test notify when recall", nbase::Bind(&nim_comp::TalkCallback::OnReceiveRecallMsgCallback, std::placeholders::_1, std::placeholders::_2));
//		//}
//		//else if (param->wParam == BET_TRANSFORM)
//		//{
//		//	nim::IMMessage msg_data = ((MsgBubbleAudio*)param->pSender)->GetMsg();
//		//	nim::IMAudio audio;
//		//	nim::Talk::ParseAudioMessageAttach(msg_data, audio);
//		//	nim::AudioInfo audio_info;
//		//	audio_info.samplerate_ = "16000";
//		//	audio_info.url_ = audio.url_;
//		//	audio_info.duration_ = audio.duration_;
//		//	audio_info.mime_type_ = audio.file_extension_;
//
//		//	nim::Tool::GetAudioTextAsync(audio_info, ToWeakCallback([this](int rescode, const std::string& text) {
//		//		if (rescode == nim::kNIMResSuccess) {
//		//			ShowMsgBox(this->GetWindow()->GetHWND(), MsgboxCallback(), nbase::UTF8ToUTF16(text), false, L"STRID_SESSION_TRANSCODE_TIP_TITLE");
//		//		}
//		//		else {
//		//			ShowMsgBox(this->GetWindow()->GetHWND(), MsgboxCallback(), L"STRID_SESSION_TRANSCODE_FAIL", true, L"STRID_SESSION_TRANSCODE_TIP_TITLE");
//		//			QLOG_ERR(L"audio convert to text failed errorcode={0}") << rescode;
//		//		}
//		//	}));
//		//}
//		//else if (param->wParam == BET_SHOWPROFILE)
//		//{
//		//	bool is_robot_id = false;
//		//	std::string robot_id;
//		//	if (md.type_ == nim::kNIMMessageTypeRobot)
//		//	{
//		//		nim::IMBotRobot robot;
//		//		nim::Talk::ParseBotRobotMessageAttach(md, robot);
//		//		is_robot_id = robot.out_msg_;
//		//		robot_id = robot.robot_accid_;
//		//	}
//
//		//	if (session_type_ == nim::kNIMSessionTypeTeam)
//		//	{
//		//		if (is_robot_id)
//		//		{
//		//			ProfileForm::ShowProfileForm(robot_id, is_robot_id);
//		//		}
//		//		else
//		//		{
//		//			nim::NIMTeamUserType type = team_member_info_list_[LoginManager::GetInstance()->GetAccount()].GetUserType();
//		//			ProfileForm::ShowProfileForm(session_id_, md.sender_accid_, type);
//		//		}
//		//	}
//		//	else
//		//	{
//		//		ProfileForm::ShowProfileForm(is_robot_id ? robot_id : md.sender_accid_, is_robot_id);
//		//	}
//		//}
//		else if (param->wParam == BET_MENUATTA)
//		{
//			AtSomeone at;
//			at.is_robot_ = md.type_ == nim::kNIMMessageTypeRobot;
//			at.uid_ = item->GetSenderId();
//			std::string show_name;
//			if (!at.is_robot_)
//			{
//				auto i = team_member_info_list_.find(at.uid_);
//				if (i != team_member_info_list_.end())
//				{
//					show_name = i->second.GetNick();
//				}
//				if (show_name.empty())
//				{
//					show_name = nbase::UTF16ToUTF8(UserService::GetInstance()->GetUserName(at.uid_, false));
//				}
//			}
//			else
//			{
//				show_name = "";
//			}
//			uid_at_someone_[show_name] = at;
//
//			std::wstring show_text = L"@";
//			show_text.append(nbase::UTF8ToUTF16(show_name));
//			show_text.append(L" ");
//
//			input_edit_->ReplaceSel(show_text, false);
//		}
//	}
//	else if (param->Type == ui::kEventTextChange)
//	{
//		if (name == L"input_edit")
//		{
//			//当用户正在输入框内输入文字时，发送给对方“对方正在输入”的消息
//			if (session_type_ == nim::kNIMSessionTypeP2P && !IsFileTransPhone())
//			{
//				std::wstring wstr = GetRichText(input_edit_);
//				if (wstr.empty())
//				{
//
//				}
//				else
//				{
//					long long now = nbase::Time::Now().ToTimeT();
//					if (writing_time_ == 0 || now - writing_time_ > kCellWritingTime)
//					{
//						writing_time_ = now;
//
//						Json::Value json;
//						Json::FastWriter writer;
//						json["id"] = "1";
//
//						nim::SysMessage msg;
//						msg.receiver_accid_ = session_id_;
//						msg.sender_accid_ = LoginManager::GetInstance()->GetAccount();
//						msg.client_msg_id_ = QString::GetGUID();
//						msg.attach_ = writer.write(json);
//						msg.type_ = nim::kNIMSysMsgTypeCustomP2PMsg;
//
//						nim::SystemMsg::SendCustomNotificationMsg(msg.ToJsonString());
//					}
//				}
//			}
//		}
//	}
	return true;
}

bool SessionBox::OnClicked(ui::EventArgs* param)
{
	std::wstring name = param->pSender->GetName();
	if (name == L"btn_send")
	{
		OnBtnSend();
	}
	else if (name == L"btn_image")
	{
		OnBtnImage(false);
	}
	else if (name == L"btn_snapchat")
	{
		OnBtnImage(true);
	}
	else if (name == L"btn_file")
	{
		use_p2p_transfer_file_ = false;
		OnBtnFile();
	}
	else if (name == L"btn_transfer_file")
	{
		use_p2p_transfer_file_ = true;
		OnBtnFile();
	}
	else if (name == L"btn_jsb")
	{
		OnBtnJsb();
	}
	else if (name == L"btn_audio")
	{
		OnBtnAudio();
	}
	else if (name == L"btn_video")
	{
		OnBtnVideo();
	}
	else if (name == L"btn_rts")
	{
		OnBtnRts();
	}
	else if (name == L"btn_tip")
	{
		SendTip(MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_SESSION_THIS_IS_A_TIP_MSG"));
	}
	else if (name == CELL_BTN_LOAD_MORE_MSG)
	{
		Control* ctrl = msg_list_->FindSubControl(CELL_LOAD_MORE_MSG);
		assert(ctrl);
		ctrl->SetVisible(false);

		InvokeShowMsgs(false);
	}
	else if (name == L"btn_clip")
	{
		//if (CaptureManager::GetInstance()->IsCaptureTracking())
		//{
		//	return false;
		//}

		////::ShowWindow( m_hWnd, SW_SHOWMINIMIZED );
		//StdClosure callback = nbase::Bind(&SessionBox::DoClip, this);
		//nbase::ThreadManager::PostDelayedTask(kThreadUI, callback, nbase::TimeDelta::FromMilliseconds(500));
	}
	else if (name == L"btn_msg_record")
	{
		/*MsgRecordForm* f = WindowsManager::SingletonShow<MsgRecordForm>(MsgRecordForm::kClassName);
		f->RefreshRecord(session_id_, session_type_);*/
	}
	else if (name == L"btn_custom_msg")
	{
		ShowCustomMsgForm();
	}
	else if (name == L"btn_new_broad")
	{
		/*BroadForm* broad = WindowsManager::SingletonShow<BroadForm>(BroadForm::kClassName);
		broad->SetTid(session_id_);*/
	}
	else if (name == L"btn_refresh_member")
	{
		InvokeGetTeamMember();
	}
	else if (name == L"add_msglog")
	{
		std::wstring wstr = GetRichText(input_edit_);
		int num = 100;
		nbase::StringToInt(param->pSender->GetDataID(), &num);
		for (int i = 0; i < num; i++)
		{
			nim::IMMessage msg;
			PackageMsg(msg);
			//msg.status_ = nim::kNIMMsgLogStatusSent;
			msg.status_ = nim::kNIMMsgLogStatusRead;
			msg.sender_accid_ = session_id_;
			msg.type_ = nim::kNIMMessageTypeText;
			msg.content_ = nbase::StringPrintf("%d>>%s", i, nbase::UTF16ToUTF8(wstr).c_str());
			//发送消息不需要填写昵称
			//UserInfo user_info;
			//UserService::GetInstance()->GetUserInfo(msg.from_account, user_info);
			//msg.from_nick = user_info.name;
			//nim::MsgLog::WriteMsglogToLocalAsync(session_id_, msg, false, nim::MsgLog::WriteMsglogCallback());
		}
	}
	else if (name == L"btn_team_ack_msg")
	{
		//SendText(nim::Tool::GetUuid(), true);
	}
	return true;
}

bool SessionBox::OnSelChanged(ui::EventArgs* param)
{
	std::wstring name = param->pSender->GetName();
	if (name == L"btn_face")
	{
		if (param->Type == kEventSelect)
			OnBtnEmoji();
	}
	else if (name == L"btn_capture_audio")
	{
		if (param->Type == kEventSelect)
			OnBtnCaptureAudio();
	}
	return true;
}

bool SessionBox::OnInputEditEnter(ui::EventArgs* param)
{
	OnBtnSend();
	return true;
}

void SessionBox::SetWindow(Window* pManager, Box* pParent, bool bInit)
{	
	session_form_ = dynamic_cast<ISessionDock*>(pManager);
	if (session_form_ == nullptr)
	{
		ui::Control* temp = pParent;
		if (temp != nullptr)
		do 
		{
			session_form_ = dynamic_cast<ISessionDock*>(temp);
			if (session_form_ != nullptr)
				break;
			temp = temp->GetParent();
		} while (temp != pManager->GetRoot());
	}
	__super::SetWindow(pManager, pParent, bInit);
}

void SessionBox::DoClip()
{
	/*std::wstring send_info;
	CaptureManager::CaptureCallback callback = nbase::Bind(&SessionBox::OnClipCallback, this, std::placeholders::_1, std::placeholders::_2);
	std::string acc = LoginManager::GetInstance()->GetAccount();
	assert(!acc.empty());
	std::wstring app_data_audio_path = QPath::GetUserAppDataDir(acc);
	if (CaptureManager::GetInstance()->StartCapture(callback, app_data_audio_path, send_info) == false)
	{
		OnClipCallback(FALSE, L"");
	}*/
}

void SessionBox::OnClipCallback(bool ret, const std::wstring& file_path)
{
	if (ret)
	{
		InsertImageToEdit(input_edit_, file_path, false);
	}
};

void SessionBox::OnBtnSend()
{
	/*if (!LoginManager::GetInstance()->IsLinkActive())
	{
		AddTip(STT_LINK);

		ShowLinkForm((nim::NIMResCode)LoginManager::GetInstance()->GetErrorCode(), true);
		return;
	}*/

	ITextServices *text_service = input_edit_->GetTextServices();
	if (!text_service)
	{
		QLOG_ERR(L"DoBtnSend occur error. text service null.");
		return;
	}

	std::vector<RE_OLE_ITEM_CONTENT> content_list;
	Re_GetTextEx(text_service, content_list);
	text_service->Release();

	bool empty_msg = content_list.empty();
	for (UINT i = 0; i < content_list.size(); ++i)
	{
		RE_OLE_ITEM_CONTENT info = content_list.at(i);
		std::string msg_body = nbase::UTF16ToUTF8(info.content_);
		switch (info.type_)
		{
		case RE_OLE_TYPE_TEXT:
		{
			if (CheckMsgContent(info.content_).empty())
			{
				if (content_list.size() == 1)
				{
					empty_msg = true;
				}
			}
			else
			{
				SendText(msg_body);
			}
		}
		break;
		case RE_OLE_TYPE_IMAGE:
		{
			if (nbase::FilePathIsExist(info.image_src_, FALSE))
			{
				SendImage(info.image_src_);
			}		
		}			
		break;
		case RE_OLE_TYPE_FILE:
		{
			std::wstring file_path = info.content_;
			if (CheckFileSize(file_path))
			{
				if (use_p2p_transfer_file_)
					TryToTransferFile(file_path);
				else
					SendFile(file_path);
			}
			else
			{
				ShowMsgBox(this->GetWindow()->GetHWND(), MsgboxCallback(), L"STRID_SESSION_SUPPORT_15MB");
			}
		}
		break;
		}
	}

	if (empty_msg)
	{
		input_edit_->SetText(L"");
		ShowMsgBox(this->GetWindow()->GetHWND(), MsgboxCallback(), L"STRID_SESSION_EDIT_EMPTY");
		return;
	}

	input_edit_->SetText(L"");
	input_edit_->SetFocus();
}

void SessionBox::OnBtnImage(bool is_snapchat)
{
	std::wstring file_type = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_SESSION_PIC_FILE");
	LPCTSTR filter = L"*.jpg;*.jpeg;*.png;*.bmp";
	std::wstring text = nbase::StringPrintf(L"%s(%s)", file_type.c_str(), filter);
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[text.c_str()] = filter;

	CFileDialogEx::FileDialogCallback2 cb = nbase::Bind(&SessionBox::OnImageSelected, this, is_snapchat, std::placeholders::_1, std::placeholders::_2);

	CFileDialogEx* file_dlg = new CFileDialogEx();
	file_dlg->SetFilter(filters);
	file_dlg->SetMultiSel(TRUE);
	file_dlg->SetParentWnd(this->GetWindow()->GetHWND());
	file_dlg->AyncShowOpenFileDlg(cb);
}

void SessionBox::OnImageSelected(bool is_snapchat, BOOL ret, std::wstring file_path)
{
	if (ret)
	{
		if (!nbase::FilePathIsExist(file_path, FALSE) || 0 == nbase::GetFileSize(file_path))
			return;
		
		std::wstring file_ext;
		nbase::FilePathExtension(file_path, file_ext);
		nbase::LowerString(file_ext);
		if (file_ext != L".jpg" && file_ext != L".jpeg" && file_ext != L".png" && file_ext != L".bmp")
			return;

		if (!is_snapchat)
		{
			InsertImageToEdit(input_edit_, file_path, false);
		}
		else 
		{
			SendSnapChat(file_path);
		}
	}
}

void SessionBox::OnBtnFile()
{
	std::wstring file_type = MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_SESSION_FILE_FORMAT") + L"(*.*)";
	LPCTSTR filter = L"*.*";
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[file_type.c_str()] = filter;

	CFileDialogEx::FileDialogCallback2 cb = nbase::Bind(&SessionBox::OnFileSelected, this, std::placeholders::_1, std::placeholders::_2);

	CFileDialogEx* file_dlg = new CFileDialogEx();
	file_dlg->SetFilter(filters);
	file_dlg->SetMultiSel(TRUE);
	file_dlg->SetParentWnd(this->GetWindow()->GetHWND());
	file_dlg->AyncShowOpenFileDlg(cb);
}

void SessionBox::OnFileSelected(BOOL ret, std::wstring file_path)
{
	if (!ret)
	{
		return;
	}

	if (CheckFileSize(file_path))
	{
		InsertFileToEdit(input_edit_, file_path);
	}
	else
	{
		ShowMsgBox(this->GetWindow()->GetHWND(), MsgboxCallback(), use_p2p_transfer_file_ ? L"STRID_SESSION_SUPPORT_2GB" : L"STRID_SESSION_SUPPORT_15MB");
	}
}

void SessionBox::OnBtnJsb()
{
	int jsb = (rand() % 3 + rand() % 4 + rand() % 5) % 3 + 1;

	Json::Value json;
	Json::FastWriter writer;
	json["type"] = CustomMsgType_Jsb;
	json["data"]["value"] = jsb;

	SendJsb(writer.write(json));
}

void SessionBox::OnBtnCaptureAudio()
{
	//audio_capture_view_->ShowControl(true);
}

void SessionBox::OnAudioCaptureComplete(int rescode, const std::string& sid, const std::string& file_path, const std::string& file_ext, long file_size, int audio_duration)
{
	if (sid == session_id_)
		btn_capture_audio_->Selected(false, false);

	/*if (rescode == nim_audio::kSuccess)
	{
		SendAudio(file_path, file_ext, file_size, audio_duration);
	}*/
}

void SessionBox::OnBtnEmoji()
{
	RECT rc = btn_face_->GetPos(true);
	POINT pt_offset = { 150, 350 };
	DpiManager::GetInstance()->ScalePoint(pt_offset);
	POINT pt = { rc.left - pt_offset.x, rc.top - pt_offset.y };
	::ClientToScreen(this->GetWindow()->GetHWND(), &pt);

	//OnSelectEmotion sel = nbase::Bind(&SessionBox::OnEmotionSelected, this, std::placeholders::_1);
	//OnSelectSticker sel2 = nbase::Bind(&SessionBox::OnEmotionSelectedSticker, this, std::placeholders::_1, std::placeholders::_2);
	//OnEmotionClose  cls = nbase::Bind(&SessionBox::OnEmotionClosed, this);

	//EmojiForm* emoji_form = new EmojiForm;
	//emoji_form->ShowEmoj(pt, sel, sel2, cls);
}

void SessionBox::OnEmotionSelected(std::wstring emo)
{
	std::wstring file;
	if (emoji::GetEmojiFileByTag(emo, file))
	{
		InsertFaceToEdit(input_edit_, file, emo);
	}
}

void SessionBox::OnEmotionSelectedSticker(const std::wstring &catalog, const std::wstring &name)
{
	SendSticker(nbase::UTF16ToUTF8(catalog), nbase::UTF16ToUTF8(name));
}

void SessionBox::OnEmotionClosed()
{
	btn_face_->Selected(false, false);

	input_edit_->SetFocus();
}

void SessionBox::OnBtnAudio()
{
	if (session_type_ == nim::kNIMSessionTypeP2P)
	{/*
		if (!RtsManager::GetInstance()->IsRtsFormExist(nim::kNIMRtsChannelTypeVchat, true))
			VideoManager::GetInstance()->ShowVideoChatForm(session_id_, false);*/
	}
}

void SessionBox::OnBtnVideo()
{
	//if (RtsManager::GetInstance()->IsRtsFormExist(nim::kNIMRtsChannelTypeVchat, true))
	//	return;

	//switch (session_type_)
	//{
	//case nim::kNIMSessionTypeP2P:
	//	VideoManager::GetInstance()->ShowVideoChatForm(session_id_, true);
	//	break;
	//case nim::kNIMSessionTypeTeam:
	//{
	//	//群视频人员选择界面
	//	ContactSelectForm *contact_select_form = (ContactSelectForm *)WindowsManager::GetInstance()->GetWindow\
	//		(ContactSelectForm::kClassName, nbase::UTF8ToUTF16(session_id_));

	//	if (!contact_select_form)
	//	{
	//		std::list<UTF8String> exnclude_ids;
	//		contact_select_form = new ContactSelectForm(session_id_, exnclude_ids, nbase::Bind(&SessionBox::OnVChatSelectedCallback, this, std::placeholders::_1, std::placeholders::_2), false, true);
	//		contact_select_form->Create(NULL, L"", UI_WNDSTYLE_FRAME& ~WS_MAXIMIZEBOX, 0L);
	//		contact_select_form->CenterWindow();
	//	}

	//	contact_select_form->ActiveWindow();
	//}

	//break;
	//default:
	//	break;
	//}
}

void SessionBox::OnVChatSelectedCallback(const std::list<UTF8String>& selected_friends, const std::list<UTF8String>& selected_teams)
{
	auto cb = [=](int res)
	{
		if (res == 200)
		{
			//发送消息
			{
				/*Db::Profile user_info;
				UserService::GetInstance()->GetUserInfo(LoginManager::GetInstance()->GetAccount(), user_info);
				std::wstring tip = nbase::StringPrintf(L"%s发起了群视频", nbase::UTF8ToUTF16(user_info.GetName()).c_str());
				int64_t timetag_ = 1000 * nbase::Time::Now().ToTimeT();
				nim::IMMessage msg;
				msg.session_type_ = nim::kNIMSessionTypeTeam;
				msg.receiver_accid_ = session_id_;
				msg.sender_accid_ = LoginManager::GetInstance()->GetAccount();
				msg.client_msg_id_ = QString::GetGUID();
				msg.msg_setting_.resend_flag_ = BS_FALSE;
				msg.timetag_ = 1000 * nbase::Time::Now().ToTimeT();

				msg.status_ = nim::kNIMMsgLogStatusSending;
				msg.type_ = nim::kNIMMessageTypeTips;
				msg.content_ = nbase::UTF16ToUTF8(tip);
				msg.msg_setting_.need_push_ = BS_FALSE;
				msg.status_ = nim::kNIMMsgLogStatusSent;
				std::string msg_info = msg.ToJsonString(true);
				QLOG_APP(L"send msg:{0}") << msg_info;
				nim::Talk::SendMsg(msg.ToJsonString(true));
				StdClosure closure = [=]()
				{
					nim_comp::SessionBox* session_box = SessionManager::GetInstance()->FindSessionBox(session_id_);
					if (session_box)
						session_box->AddNewMsg(msg, false);
				};
				Post2UI(closure);*/
			}
		}
	};
	if (selected_friends.size() <= 0)
	{
		std::wstring toast = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRING_MULTIVIDEOCHATFORM_START_MEMBER_CHECK_LOW");
		nim_comp::Toast::ShowToast(toast, 2000);
		return;
	}
	//VideoManager::GetInstance()->ShowVideoChatForm(session_id_, true, 0, selected_friends, ToWeakCallback(cb));
}

void SessionBox::OnBtnRts()
{
	if (session_type_ == nim::kNIMSessionTypeP2P)
	{
		//RtsManager::GetInstance()->StartRtsForm(nim::kNIMRtsChannelTypeTcp | nim::kNIMRtsChannelTypeVchat, session_id_, "");
	}
}

void SessionBox::OnMenuRetweetMessage(const nim::IMMessage &msg)
{
	/*ContactSelectForm *contact_select_form = (ContactSelectForm *)WindowsManager::GetInstance()->GetWindow(ContactSelectForm::kClassName, nbase::UTF8ToUTF16(ContactSelectForm::kRetweetMessage));
	if (!contact_select_form)
	{
		contact_select_form = new ContactSelectForm(ContactSelectForm::kRetweetMessage, std::list<UTF8String>(), nbase::Bind(&SessionBox::OnSelectedRetweetList, this, msg, std::placeholders::_1, std::placeholders::_2), true);
		contact_select_form->Create(NULL, L"", UI_WNDSTYLE_FRAME& ~WS_MAXIMIZEBOX, 0L);
		contact_select_form->CenterWindow();
	}
	else
	{
		contact_select_form->ActiveWindow();
	}*/
}

void SessionBox::OnSelectedRetweetList(nim::IMMessage msg, const std::list<std::string>& friend_list, const std::list<std::string>& team_list)
{
	if (friend_list.empty() && team_list.empty())
		return;

	auto retweet_cb = [this](const std::string &msg, const std::string &receiver_accid, nim::NIMSessionType receiver_type)
	{
		/*nim::IMMessage sending_msg;
		nim::Talk::ParseIMMessage(msg, sending_msg);
		sending_msg.sender_accid_ = LoginManager::GetInstance()->GetAccount();
		sending_msg.msg_setting_.team_msg_ack_sent_ = BS_FALSE;

		SessionBox *form = SessionManager::GetInstance()->OpenSessionBox(receiver_accid, receiver_type);
		if (form)
		{
			form->AddRetweetMsg(sending_msg);
		}
		nim::Talk::SendMsg(msg);*/
	};

	for (auto &it : friend_list)
	{
		//std::string send_msg = nim::Talk::CreateRetweetMessage(msg.ToJsonString(false), QString::GetGUID(), nim::kNIMSessionTypeP2P, it, msg.msg_setting_, 1000 * nbase::Time::Now().ToTimeT());
		//retweet_cb(send_msg, it, nim::kNIMSessionTypeP2P);
	}

	for (auto &it : team_list)
	{
		//std::string send_msg = nim::Talk::CreateRetweetMessage(msg.ToJsonString(false), QString::GetGUID(), nim::kNIMSessionTypeTeam, it, msg.msg_setting_, 1000 * nbase::Time::Now().ToTimeT());
		//retweet_cb(send_msg, it, nim::kNIMSessionTypeTeam);
	}
}

bool SessionBox::OnBtnInvite(ui::EventArgs* param)
{
	/*std::wstring session_id = nbase::UTF8ToUTF16(session_id_);
	ContactSelectForm* contact_select_form = (ContactSelectForm*)WindowsManager::GetInstance()->GetWindow\
		(ContactSelectForm::kClassName, session_id);
	if (contact_select_form == NULL)
	{
		std::list<std::string> exnclud_ids;
		exnclud_ids.push_back(session_id_);
		contact_select_form = new ContactSelectForm(session_id_, exnclud_ids, nbase::Bind(&SessionBox::OnSelectedInvateList, this, std::placeholders::_1, std::placeholders::_2));
		contact_select_form->Create(NULL, L"", WS_OVERLAPPEDWINDOW& ~WS_MAXIMIZEBOX, 0L);
		contact_select_form->CenterWindow();
		contact_select_form->ShowWindow(true);
	}
	else
	{
		contact_select_form->ActiveWindow();
	}*/

	return true;
}

void SessionBox::OnSelectedInvateList(const std::list<std::string>& friend_list, const std::list<std::string>& team_list)
{
	/*std::list<std::string> id_list = friend_list;
	id_list.push_back(session_id_);
	
	UTF16String user_names;
	auto it = id_list.cbegin();
	for (int i = 0; it != id_list.cend() && i < 2; it++, i++)
		user_names += UserService::GetInstance()->GetUserName(*it, false) + L";";
	user_names += UserService::GetInstance()->GetUserName(it == id_list.end() ? LoginManager::GetInstance()->GetAccount() : *it, false);

	nim::TeamInfo tinfo;
	tinfo.SetName(nbase::UTF16ToUTF8(user_names));
	tinfo.SetType(nim::kNIMTeamTypeNormal);
	nim::Team::CreateTeamAsync(tinfo, id_list, "", nbase::Bind(&TeamCallback::OnTeamEventCallback, std::placeholders::_1));

	session_form_->CloseSessionBox(session_id_);*/
}

void SessionBox::OnCloseInputMsgBoxCallback(MsgBoxRet ret)
{
	if (ret == MB_YES)
		session_form_->CloseSessionBox(session_id_);
}

void SessionBox::AddTip(SessionTipType type)
{
	if (type == STT_LINK)
	{
		RemoveTip(STT_LINK);

		HBox* hbox = new HBox;
		GlobalManager::FillBoxWithCache(hbox, L"session/tip_link.xml");
		msg_content_->Add(hbox);

		hbox->SetName(SESSION_TIP_LINK);
	}
	else if (type == STT_LEAVE)
	{
		RemoveTip(STT_LEAVE);

		HBox* hbox = new HBox;
		GlobalManager::FillBoxWithCache(hbox, L"session/tip_leave.xml");
		msg_content_->Add(hbox);

		hbox->SetName(SESSION_TIP_LEAVE);
	}
	else if (type == STT_NOT_FRIEND)
	{
		RemoveTip(STT_NOT_FRIEND);

		HBox* hbox = new HBox;
		GlobalManager::FillBoxWithCache(hbox, L"session/tip_not_friend.xml");
		msg_content_->Add(hbox);

		hbox->SetName(SESSION_TIP_NOT_FRIEND);
	}
	else if (type == STT_LOAD_MORE_MSG)
	{
		RemoveTip(STT_LOAD_MORE_MSG);

		ui::ListContainerElement* cell = new ui::ListContainerElement();
		GlobalManager::FillBoxWithCache(cell, L"session/cell_more_msg.xml");
		msg_list_->AddAt(cell, 0);

		cell->SetName(CELL_LOAD_MORE_MSG);
	}
}

void SessionBox::RemoveTip(SessionTipType type)
{
	if (type == STT_LINK)
	{
		Control* ctrl = msg_content_->FindSubControl(SESSION_TIP_LINK);
		if (ctrl)
			msg_content_->Remove(ctrl);
	}
	else if (type == STT_LEAVE)
	{
		Control* ctrl = msg_content_->FindSubControl(SESSION_TIP_LEAVE);
		if (ctrl)
			msg_content_->Remove(ctrl);
	}
	else if (type == STT_NOT_FRIEND)
	{
		Control* ctrl = msg_content_->FindSubControl(SESSION_TIP_NOT_FRIEND);
		if (ctrl)
			msg_content_->Remove(ctrl);
	}
	else if (type == STT_LOAD_MORE_MSG)
	{
		Control* ctrl = msg_list_->FindSubControl(CELL_LOAD_MORE_MSG);
		if (ctrl)
			msg_list_->Remove(ctrl);
	}
	else if (type == STT_WRITING)
	{
		Control* ctrl = msg_list_->FindSubControl(CELL_WRITING);
		if (ctrl)
			msg_list_->Remove(ctrl);
		has_writing_cell_ = false;
	}
}

bool SessionBox::OnBtnHeaderClick(ui::EventArgs* param)
{
	if (!is_header_enable_)
		return true;

	if (session_type_ == nim::kNIMSessionTypeTeam)
	{
		TeamInfoForm::ShowTeamInfoForm(false, team_info_.GetType(), session_id_, team_info_);
	}
	else if (session_type_ == nim::kNIMSessionTypeP2P)
	{
		ProfileForm::ShowProfileForm(session_id_, false);
	}
	return true;
}

void SessionBox::OnWndSizeMax(bool max)
{
	if (btn_max_restore_)
		btn_max_restore_->SetClass(max ? L"btn_wnd_restore" : L"btn_wnd_max");
}

void SessionBox::OnActivate()
{
	if (session_form_->IsActiveSessionBox(this))
	{
		/*SessionManager::GetInstance()->ResetUnread(session_id_);

		SendReceiptIfNeeded();

		if (input_edit_)
			input_edit_->SetFocus();

		SendTeamReceiptIfNeeded();*/
	}

	UpdateTaskbarInfo();
}
void SessionBox::UpdateTaskbarInfo()
{
	SetTaskbarIcon(btn_header_->GetBkImage());
	SetTaskbarTitle(label_title_->GetText());
}
void SessionBox::ShowCustomMsgForm()
{
	//CustomMsgForm* f = WindowsManager::SingletonShow<CustomMsgForm>(CustomMsgForm::kClassName);
	//f->SetSession(session_id_, session_type_, label_title_->GetText());
}

bool SessionBox::PasteClipboard()
{
	bool ret = false;
	if (OpenClipboard(NULL))
	{
		try
		{
			HANDLE h = ::GetClipboardData(CF_HDROP);
			if (h != NULL && h != INVALID_HANDLE_VALUE)
			{
				HDROP file = (HDROP)::GlobalLock(h);
				if (file != NULL)
				{
					OnDropFile(file);
					::GlobalUnlock(h);
					throw(true);
				}
			}
			HBITMAP bmp = (HBITMAP)::GetClipboardData(CF_BITMAP);
			if (bmp != NULL)
			{
				//std::wstring image_path(QPath::GetUserAppDataDir(nim_comp::LoginManager::GetInstance()->GetAccount()));
				//image_path.append(nbase::UTF8ToUTF16(QString::GetGUID())).append(L".png");
				/*if (CaptureWindow::SaveBitmapToFile(bmp, image_path))
				{
					if (nbase::FilePathIsExist(image_path, false))
					{
						OnClipCallback(true, image_path);
						throw(true);
					}
				}*/
			}
			throw(false);
		}
		catch (bool /*ret*/)
		{
			CloseClipboard();
		}
	}
	return ret;
}


} // namespace nim_comp
