﻿#include "member_manager.h"
#include "util/windows_manager.h"
#include "shared/pin_yin_helper.h"
#include "callback/team/team_callback.h"
#include "shared/tool.h"
#include "shared/ui/msgbox.h"
#include "module/login/login_manager.h"
#include "module/service/user_service.h"
#include "module/service/team_service.h"

using namespace ui;
using namespace std;

namespace nim_comp
{
const LPCTSTR MemberManagerForm::kClassName			= _T("MemberManagerForm");

MemberManagerForm::MemberManagerForm(const std::string& team_id, const nim::TeamMemberProperty& member_info, bool show_privilege_panel)
{
	tid_ = team_id;
	member_info_ = member_info;
	show_privilege_panel_ = show_privilege_panel;
}

MemberManagerForm::~MemberManagerForm()
{

}

std::wstring MemberManagerForm::GetSkinFolder()
{
	return L"team_info";
}

std::wstring MemberManagerForm::GetSkinFile()
{
	return L"member_manager.xml";
}

std::wstring MemberManagerForm::GetWindowClassName() const
{
	return kClassName;
}

std::wstring MemberManagerForm::GetWindowId() const
{
	std::wstring ws_user_id_ = nbase::UTF8ToUTF16(member_info_.GetAccountID());
	return ws_user_id_;
}

UINT MemberManagerForm::GetClassStyle() const
{
	return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

void MemberManagerForm::InitWindow()
{
	std::string user_id = member_info_.GetAccountID();
	std::string team_card = member_info_.GetNick();

	Button* head_image_button = (Button*)FindControl(L"head_image");
	head_image_button->SetBkImage(PhotoService::GetInstance()->GetUserPhoto(user_id));
	Label* show_name_label = (Label*)FindControl(L"show_name");
	show_name_label->SetText(UserService::GetInstance()->GetUserName(user_id));
	re_team_card_ = (ui::RichEdit*)FindControl(L"team_card");
	re_team_card_->SetUTF8Text(team_card);
	re_team_card_->SetLimitText(10);
	ui::Button* btn_confirm = (ui::Button*)FindControl(L"confirm");
	btn_confirm->AttachClick(nbase::Bind(&MemberManagerForm::OnBtnConfirmClick, this, std::placeholders::_1));
	ui::Button* btn_cancel = (ui::Button*)FindControl(L"cancel");
	btn_cancel->AttachClick(nbase::Bind(&MemberManagerForm::OnBtnCancelClick, this, std::placeholders::_1));

	FindControl(L"privilege_panel")->SetVisible(show_privilege_panel_);
	if (show_privilege_panel_)
	{
		switch (member_info_.GetUserType())
		{
		case nim::kNIMTeamUserTypeCreator:
			((Option*)FindControl(L"owner"))->Selected(true);
			break;
		case nim::kNIMTeamUserTypeManager:
			((Option*)FindControl(L"manager"))->Selected(true);
			break;
		case nim::kNIMTeamUserTypeNomal:
			((Option*)FindControl(L"member"))->Selected(true);
			break;
		default:
			break;
		}
	}
}

static void OnTeamEventCallback(const std::string& uid, const std::string& team_card, const nim::TeamEvent& team_event)
{
	if (team_event.res_code_ == nim::kNIMResSuccess)
	{
		if (team_event.notification_id_ == nim::kNIMNotificationIdLocalUpdateOtherNick || team_event.notification_id_ == nim::kNIMNotificationIdLocalUpdateMemberProperty)
		{
			TeamService::GetInstance()->InvokeChangeTeamMember(team_event.team_id_, uid, team_card);
		}
	}
}

bool MemberManagerForm::OnBtnConfirmClick(ui::EventArgs* param)
{
	std::string user_id = member_info_.GetAccountID();
	std::string team_card = member_info_.GetNick();
	nim::NIMTeamUserType user_type = member_info_.GetUserType();
	std::string tid = tid_;	
	auto task_member_type = ToWeakCallback([this,user_id,tid, user_type]() {
		auto task_team_event_cb = ToWeakCallback([this](const nim::TeamEvent& result) {
			TeamCallback::OnTeamEventCallback(result);
			Close();
		});

		if (((Option*)FindControl(L"owner"))->IsSelected())
		{
			if (member_info_.IsMute())
			{
				nim::Team::MuteMemberAsync(tid_, user_id, false, ToWeakCallback([this, tid, user_id, task_team_event_cb](const nim::TeamEvent& result) {
					if (result.res_code_ == nim::kNIMResSuccess)
					{
						nim::Team::TransferTeamAsync(tid, user_id, false, task_team_event_cb);
					}
				}));
			}
			else
			{
				nim::Team::TransferTeamAsync(tid_, user_id, false, task_team_event_cb);
			}				
		}
		else if (((Option*)FindControl(L"manager"))->IsSelected() && user_type != nim::kNIMTeamUserTypeManager)
		{
			std::list<std::string> uids_list;
			uids_list.push_back(user_id);
			nim::Team::AddManagersAsync(tid_, uids_list, task_team_event_cb);
		}
		else if (((Option*)FindControl(L"member"))->IsSelected() && user_type != nim::kNIMTeamUserTypeNomal)
		{
			std::list<std::string> uids_list;
			uids_list.push_back(user_id);
			nim::Team::RemoveManagersAsync(tid_, uids_list, task_team_event_cb);
		}
		else
		{
			Close();
		}
	});	
	std::string new_team_card = nbase::StringTrim(re_team_card_->GetUTF8Text());
	if (new_team_card != team_card)
	{
		auto task = [new_team_card, user_id, task_member_type,this]() {
			auto team_event_callback = ToWeakCallback([this, user_id, new_team_card,task_member_type](const nim::TeamEvent& team_event) {
				OnTeamEventCallback(user_id, new_team_card, team_event);
				task_member_type();
			});
			nim::TeamMemberProperty values(tid_, user_id, member_info_.GetUserType());
			values.SetNick(new_team_card);
			if (user_id != LoginManager::GetInstance()->GetAccount())
				nim::Team::UpdateOtherNickAsync(values, team_event_callback);
			else
				nim::Team::UpdateMyPropertyAsync(values, team_event_callback);
		};
		nbase::ThreadManager::PostTask(task);
	}
	else
	{
		task_member_type();
	}	
	return true; 
}

bool MemberManagerForm::OnBtnCancelClick(ui::EventArgs* param)
{
	Close();
	return true;
}
}