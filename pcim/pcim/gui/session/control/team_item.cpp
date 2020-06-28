﻿#include "stdafx.h"
#include "team_item.h"
#include "ui_components/menu/ui_menu.h"
//#include "callback/team/team_callback.h"
#include "gui/session/session_manager.h"
#include "gui/profile_form/profile_form.h"

using namespace ui;

namespace nim_comp
{
	void TeamItem::InitControl()
	{
		this->AttachMenu(nbase::Bind(&TeamItem::OnItemMenu, this, std::placeholders::_1));
		this->AttachDoubleClick(nbase::Bind(&TeamItem::OnDbClicked, this, std::placeholders::_1));

		member_icon_ = (Button*) this->FindSubControl(L"member_icon");
		member_name_ = (Label*) this->FindSubControl(L"member_name");

		icon_admin_ = this->FindSubControl(L"icon_admin");
		icon_mute_ = this->FindSubControl(L"icon_mute");
	}

	void TeamItem::InitInfo(const nim::TeamMemberProperty &info)
	{
		member_info_ = info;
		this->SetUTF8Name(info.GetAccountID());
		SetMemberName(member_info_.GetNick());
		member_icon_->SetBkImage(PhotoService::GetInstance()->GetUserPhoto(info.GetAccountID()));

		nim::NIMTeamUserType team_user_type = member_info_.GetUserType();
		if (team_user_type == nim::kNIMTeamUserTypeCreator || team_user_type == nim::kNIMTeamUserTypeManager)
		{
			icon_admin_->SetBkImage(team_user_type == nim::kNIMTeamUserTypeCreator ? L"..\\public\\icon\\team_creator.png" : L"..\\public\\icon\\team_manager.png");
			icon_admin_->SetVisible(true);
		}
		else
			icon_admin_->SetVisible(false);

		is_mute_ = info.IsMute();
		if (info.IsMute())
		{
			icon_mute_->SetBkImage(L"..\\public\\icon\\mute.png");
			icon_mute_->SetVisible(true);
		}

		member_icon_->AttachClick(nbase::Bind(&TeamItem::OnHeadImageClick, this, member_info_.GetAccountID(), std::placeholders::_1));
	}

	bool TeamItem::OnHeadImageClick(const std::string& uid, ui::EventArgs*)
	{
		ProfileForm::ShowProfileForm(uid);
		return true;
	}

	void TeamItem::SetAdmin(bool admin)
	{
		icon_admin_->SetBkImage(L"..\\public\\icon\\team_manager.png");
		icon_admin_->SetVisible(admin);
		if (admin)
		{
			member_info_.SetUserType(nim::kNIMTeamUserTypeManager);
		}
		else
		{
			member_info_.SetUserType(nim::kNIMTeamUserTypeNomal);
		}
	}

	void TeamItem::SetMute(bool mute)
	{
		is_mute_ = mute;
		icon_mute_->SetBkImage(L"..\\public\\icon\\mute.png");
		icon_mute_->SetVisible(mute);
	}

	void TeamItem::SetOwner(bool is_owner)
	{
		icon_admin_->SetBkImage(L"..\\public\\icon\\team_creator.png");
		icon_admin_->SetVisible(is_owner);
		if (is_owner)
		{
			member_info_.SetUserType(nim::kNIMTeamUserTypeCreator);
		}
		else
		{
			member_info_.SetUserType(nim::kNIMTeamUserTypeNomal);
		}
	}

	nim::NIMTeamUserType TeamItem::GetTeamUserType()
	{
		return member_info_.GetUserType();
	}

	void TeamItem::SetMemberName(const std::string& team_card)
	{
		if (NULL == member_name_)
			return;

		if (!team_card.empty())
		{
			member_name_->SetUTF8Text(team_card);
			member_info_.SetNick(team_card);
		}
		else
			member_name_->SetText(UserService::GetInstance()->GetUserName(GetUTF8Name()));
	}

	std::string TeamItem::GetTeamCard() const
	{
		return member_info_.GetNick();
	}

	bool TeamItem::OnItemMenu(ui::EventArgs* arg)
	{
		POINT point;
		::GetCursorPos(&point);
		PopupItemMenu(point);
		return true;
	}

	void TeamItem::PopupItemMenu(POINT point)
	{
		CMenuWnd* pMenu = new CMenuWnd(NULL);
		STRINGorID xml(L"team_item_menu.xml");
		pMenu->Init(xml, _T("xml"), point);

		nim::NIMTeamUserType my_team_user_type = nim::kNIMTeamUserTypeNomal;
		SessionBox* session_box = dynamic_cast<SessionBox*>(SessionManager::GetInstance()->FindSessionBox(member_info_.GetTeamID()));
		if (session_box)
		{
		/*	auto my_pro = session_box->GetTeamMemberInfo(LoginManager::GetInstance()->GetAccount());
			my_team_user_type = my_pro.GetUserType();*/
		}
		nim::NIMTeamUserType team_user_type = member_info_.GetUserType();

		CMenuElementUI* mute_item = (CMenuElementUI*)pMenu->FindControl(L"mute");
		if (my_team_user_type == nim::kNIMTeamUserTypeNomal
			|| my_team_user_type == team_user_type
			|| team_user_type == nim::kNIMTeamUserTypeCreator
			|| team_user_type == nim::kNIMTeamUserTypeApply
			|| team_user_type == nim::kNIMTeamUserTypeLocalWaitAccept)
			mute_item->SetEnabled(false);
		else
			mute_item->SetEnabled(true);

		if (is_mute_)
		{
			((Label*)(mute_item->FindSubControl(L"mute_text")))->SetText(MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_SESSION_TEAM_ITEM_MENU_UNMUTE"));
		}
		else
		{
			((Label*)(mute_item->FindSubControl(L"mute_text")))->SetText(MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_SESSION_TEAM_ITEM_MENU_MUTE"));
		}
		mute_item->AttachSelect(nbase::Bind(&TeamItem::TeamItemMenuItemClick, this, std::placeholders::_1));
		((CMenuElementUI*)pMenu->FindControl(L"info"))->AttachSelect(nbase::Bind(&TeamItem::TeamItemMenuItemClick, this, std::placeholders::_1));
		((CMenuElementUI*)pMenu->FindControl(L"talk"))->AttachSelect(nbase::Bind(&TeamItem::TeamItemMenuItemClick, this, std::placeholders::_1));
		pMenu->Show();
	}

	bool TeamItem::TeamItemMenuItemClick(ui::EventArgs* param)
	{
		std::wstring name = param->pSender->GetName();
		if (name == L"mute")
		{
			//nim::Team::MuteMemberAsync(member_info_.GetTeamID(), member_info_.GetAccountID(), !is_mute_, nbase::Bind(&TeamCallback::OnTeamEventCallback, std::placeholders::_1));
		}
		else if (name == L"info")
		{
			ProfileForm::ShowProfileForm(member_info_.GetAccountID());
		}
		else if (name == L"talk")
		{
			std::string id = member_info_.GetAccountID();

			nim_comp::SessionManager::GetInstance()->OpenSessionBox(id, nim::kNIMSessionTypeP2P);
		}
		return true;
	}

	bool TeamItem::OnDbClicked(ui::EventArgs* arg)
	{
		std::string id = member_info_.GetAccountID();

		nim_comp::SessionManager::GetInstance()->OpenSessionBox(id, nim::kNIMSessionTypeP2P);

		return true;
	}
}