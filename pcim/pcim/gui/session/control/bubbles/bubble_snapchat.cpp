﻿#include "stdafx.h"
#include "bubble_snapchat.h"
//#include "image_view/src/image_view_manager.h"
//#include "module/session/session_manager.h"
//#include "util/user.h"

namespace nim_comp
{
void MsgBubbleSnapChat::InitInfo(const nim::IMMessage &msg)
{
	MsgBubbleItem::InitInfo(msg);

	path_ = nbase::UTF8ToUTF16(msg.local_res_path_);
	thumb_ = QPath::GetAppPath();
	if (my_msg_)
		thumb_ += L"resources\\themes\\default\\session\\snapchat_send.png";
	else
		thumb_ += L"resources\\themes\\default\\session\\snapchat_receive.png";

	bubble_box_->SetBkImage(L"");
	image_->SetForeStateImage(ui::kControlStateNormal, L"");
	image_->SetMargin(ui::UiRect(0, 0, 0, 0));
	image_->SetBkImage(thumb_);
	msg_image_->SetMargin(ui::UiRect(0,0,0,20));
	ui::Label* label = new ui::Label;
	bubble_box_->Add(label);
	label->SetText(ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_SESSION_SNAPCHAT_CLICK"));
	label->SetVerAlignType(ui::kVerAlignBottom);
	label->SetStateTextColor(ui::kControlStateNormal, L"lightcolor");
	if (!my_msg_)
		label->SetHorAlignType(ui::kHorAlignRight);
	else
		label->SetHorAlignType(ui::kHorAlignLeft);
}

bool MsgBubbleSnapChat::OnClicked(ui::EventArgs* arg)
{
	//如果是阅后即焚，则需要先下载好图片
	if (path_.empty() || !nbase::FilePathIsExist(path_, false))
	{
		Json::Value json;
		if (StringToJson(msg_.attach_, json) && json.isObject())
		{
			std::string url = json["data"]["url"].asString();
			//nim::NOS::DownloadMediaCallback download_cb = nbase::Bind(&MsgBubbleSnapChat::OnDownloadCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
			//nim::NOS::DownloadResource(url, download_cb);
		}
	}
	else
		ViewSnapchatImage();

	return true;
}

void MsgBubbleSnapChat::OnDownloadCallback(int res_code, const std::string& file_path, const std::string& call_id, const std::string& res_id)
{
	if (res_code == nim::kNIMResSuccess)
	{
		path_ = nbase::UTF8ToUTF16(file_path);
		ViewSnapchatImage();
	}
}

void MsgBubbleSnapChat::ViewSnapchatImage()
{
	struct DeleteFileTask
	{
		DeleteFileTask(const std::wstring& path) : path_(path){};
		virtual void operator()() const{
			/*if (!nbase::DeleteFile(path_) && 32 == GetLastError())
				nbase::ThreadManager::PostDelayedTask(ThreadId::kThreadGlobalMisc, DeleteFileTask(path_), nbase::TimeDelta::FromSeconds(2));*/
		}
	private:
		std::wstring path_;
	};
	if (nbase::FilePathIsExist(path_, false))
	{	/*	
		auto no_topmost_cb = ImageViewManager::GetInstance()->StartViewPicEx(path_, L"", true, true,true);
		nim::MsgLog::DeleteAsync(sid_, type_, msg_.client_msg_id_, ToWeakCallback([this, no_topmost_cb](nim::NIMResCode res_code, const std::string& msg_id){
			SessionBox* session_form = dynamic_cast<SessionBox*>(SessionManager::GetInstance()->FindSessionBox(sid_));
			if (session_form)
			{
				auto temp_path = path_;
				session_form->OnSnapchatReadCallback(msg_.client_msg_id_);
				nbase::ThreadManager::PostTask(ThreadId::kThreadGlobalMisc, DeleteFileTask(temp_path));
				if (no_topmost_cb != nullptr)
					nbase::ThreadManager::PostDelayedTask(no_topmost_cb,nbase::TimeDelta::FromMilliseconds(200));
			}				
		}));*/
	}
}

}