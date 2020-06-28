#include "stdafx.h"
#include "profile_box.h"
//#include "callback/multiport/multiport_push_callback.h"
//#include "module/session/session_manager.h"
//#include "module/service/mute_black_service.h"
//#include "av_kit/module/video/video_manager.h"
//#include "head_modify_form.h"
//#include "callback/team/team_callback.h"
namespace nim_comp
{
	ProfileBox::ProfileBox() : taskbar_title_function_(nullptr), close_function_(nullptr)
	{
	
	};
	ProfileBox::ProfileBox(UTF8String tid, UTF8String uid, nim::NIMTeamUserType my_type) :
		taskbar_title_function_(nullptr), close_function_(nullptr), tid_(tid), my_team_user_type_(my_type)
	{
		
	}
	ProfileBox::~ProfileBox()
	{
	};
	void ProfileBox::DoInit()
	{
		AttachBubbledEvent(ui::kEventTab, nbase::Bind(&ProfileBox::Notify, this, std::placeholders::_1));

		head_image_btn = static_cast<ui::Button*>(FindSubControl(L"head_image"));
		show_name_label = static_cast<ui::Label*>(FindSubControl(L"show_name"));
		user_id_label = static_cast<ui::Label*>(FindSubControl(L"userid"));
		nickname_label = static_cast<ui::Label*>(FindSubControl(L"nickname"));
		sex_icon = static_cast<ui::CheckBox*>(FindSubControl(L"sex_icon"));

		multi_push_switch = static_cast<ui::CheckBox*>(FindSubControl(L"multi_push_switch"));
		webrtc_setting_ = static_cast<ui::CheckBox*>(FindSubControl(L"webrtc_setting"));
		notify_switch = static_cast<ui::CheckBox*>(FindSubControl(L"notify_switch"));
		black_switch = static_cast<ui::CheckBox*>(FindSubControl(L"black_switch"));
		mute_switch = static_cast<ui::CheckBox*>(FindSubControl(L"mute_switch"));
		start_chat = static_cast<ui::Button*>(FindSubControl(L"start_chat"));
		add_or_del = static_cast<ui::TabBox*>(FindSubControl(L"add_or_del"));
		delete_friend = static_cast<ui::Button*>(FindSubControl(L"delete_friend"));
		add_friend = static_cast<ui::Button*>(FindSubControl(L"add_friend"));

		btn_modify_info = static_cast<ui::Button*>(FindSubControl(L"modify_info"));
		btn_cancel_modify = static_cast<ui::Button*>(FindSubControl(L"cancel_modify"));
		btn_save_modify = static_cast<ui::Button*>(FindSubControl(L"save_modify"));

		alias_box = static_cast<ui::HBox*>(FindSubControl(L"alias_box"));
		alias_edit = static_cast<ui::RichEdit*>(FindSubControl(L"alias_edit"));

		nickname_box = static_cast<ui::HBox*>(FindSubControl(L"nickname_box"));
		nickname_edit = static_cast<ui::RichEdit*>(FindSubControl(L"nickname_edit"));
		nickname_error_tip = static_cast<ui::Label*>(FindSubControl(L"nickname_error_tip"));

		sex_box = static_cast<ui::HBox*>(FindSubControl(L"sex_box"));
		sex_option = static_cast<ui::Combo*>(FindSubControl(L"sex_option"));

		birthday_label = static_cast<ui::Label*>(FindSubControl(L"birthday"));
		birthday_combo_box = static_cast<ui::HBox*>(FindSubControl(L"birthday_combobox"));
		birth_year_combo = static_cast<ui::Combo*>(birthday_combo_box->FindSubControl(L"year"));
		birth_month_combo = static_cast<ui::Combo*>(birthday_combo_box->FindSubControl(L"month"));
		birth_day_combo = static_cast<ui::Combo*>(birthday_combo_box->FindSubControl(L"day"));

		phone_label = static_cast<ui::Label*>(FindSubControl(L"phone"));
		phone_edit = static_cast<ui::RichEdit*>(FindSubControl(L"phone_edit"));

		email_label = static_cast<ui::Label*>(FindSubControl(L"email"));
		email_edit = static_cast<ui::RichEdit*>(FindSubControl(L"email_edit"));

		signature_label = static_cast<ui::Label*>(FindSubControl(L"signature"));
		signature_edit = static_cast<ui::RichEdit*>(FindSubControl(L"signature_edit"));

		common_info_ = static_cast<ui::VBox*>(FindSubControl(L"common_info"));
		robot_info_ = static_cast<ui::VBox*>(FindSubControl(L"robot_info"));
		common_other_ = static_cast<ui::VBox*>(FindSubControl(L"common_other"));
		robot_intro_ = static_cast<ui::RichEdit*>(FindSubControl(L"robot_intro"));

		if (tid_.empty())
		{
			ui::Box* panel = static_cast<ui::Box*>(FindSubControl(L"mute_switch_box"));
			panel->SetVisible(false);
		}
		else
		{
			if (my_team_user_type_ != nim::kNIMTeamUserTypeCreator && my_team_user_type_ != nim::kNIMTeamUserTypeManager)
				mute_switch->SetEnabled(false);
			else
				have_mute_right_ = true;
		}

		auto user_info_change_cb = nbase::Bind(&ProfileBox::OnUserInfoChange, this, std::placeholders::_1);
		unregister_cb.Add(UserService::GetInstance()->RegUserInfoChange(user_info_change_cb));

		auto user_photo_ready_cb = nbase::Bind(&ProfileBox::OnUserPhotoReady, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		unregister_cb.Add(PhotoService::GetInstance()->RegPhotoReady(user_photo_ready_cb));

		auto misc_uinfo_change_cb = nbase::Bind(&ProfileBox::OnMiscUInfoChange, this, std::placeholders::_1);
		unregister_cb.Add(UserService::GetInstance()->RegMiscUInfoChange(misc_uinfo_change_cb));

		auto friend_list_change_cb = nbase::Bind(&ProfileBox::OnFriendListChange, this, std::placeholders::_1, std::placeholders::_2);
		unregister_cb.Add(UserService::GetInstance()->RegFriendListChange(friend_list_change_cb));
	}

	void ProfileBox::InitUserInfo(const Db::Profile &info)
	{
		m_uinfo = info;

		//if (m_uinfo.id == LoginManager::GetInstance()->GetAccount())
		//	user_type = -1;
		//else
		//	user_type = UserService::GetInstance()->GetUserType(m_uinfo.id);
		user_type = -1;
		if (user_type == -1) // �Լ�����Ƭ
		{
			// ��ȡ������Ϳ���
			//nim::Client::GetMultiportPushConfigAsync(&MultiportPushCallback::OnMultiportPushConfigChange);

			head_image_btn->SetMouseEnabled(true); // �ɵ��ͷ����и���
			btn_modify_info->SetVisible(true); // ��ʾ���༭����ť
			head_image_btn->SetMouseEnabled(true); // �ɵ��ͷ����и���

			FindSubControl(L"only_other")->SetVisible(false);	// ����Ƭ���Լ���ʱ��������������
			FindSubControl(L"only_me")->SetVisible(true);		// ����Ƭ���Լ���ʱ����ʾ������Ϳ���

			nickname_edit->SetLimitText(10);
			phone_edit->SetLimitText(13);
			email_edit->SetLimitText(30);
			signature_edit->SetLimitText(30);

			head_image_btn->AttachClick(nbase::Bind(&ProfileBox::OnHeadImageClicked, this, std::placeholders::_1));

			birth_year_combo->AttachSelect(nbase::Bind(&ProfileBox::OnBirthdayComboSelect, this, std::placeholders::_1));
			birth_month_combo->AttachSelect(nbase::Bind(&ProfileBox::OnBirthdayComboSelect, this, std::placeholders::_1));

			btn_modify_info->AttachClick(nbase::Bind(&ProfileBox::OnModifyOrCancelBtnClicked, this, std::placeholders::_1, true));
			btn_cancel_modify->AttachClick(nbase::Bind(&ProfileBox::OnModifyOrCancelBtnClicked, this, std::placeholders::_1, false));
			btn_save_modify->AttachClick(nbase::Bind(&ProfileBox::OnSaveInfoBtnClicked, this, std::placeholders::_1));

			multi_push_switch->AttachSelect(nbase::Bind(&ProfileBox::OnMultiPushSwitchSelected, this, std::placeholders::_1));
			multi_push_switch->AttachUnSelect(nbase::Bind(&ProfileBox::OnMultiPushSwitchUnSelected, this, std::placeholders::_1));
//			webrtc_setting_->Selected(nim_comp::VideoManager::GetInstance()->GetWebrtc(), false);
			webrtc_setting_->AttachSelect(nbase::Bind(&ProfileBox::OnWebRtcSelected, this, std::placeholders::_1));
			webrtc_setting_->AttachUnSelect(nbase::Bind(&ProfileBox::OnWebRtcUnSelected, this, std::placeholders::_1));
		}
		else
		{
			FindSubControl(L"only_other")->SetVisible(true);	// ����Ƭ���Լ���ʱ����ʾ��������
			FindSubControl(L"only_me")->SetVisible(false);		// ����Ƭ���Լ���ʱ�����ض�����Ϳ���

			CheckInMuteBlack();
			add_or_del->SelectItem(user_type == nim::kNIMFriendFlagNormal ? 0 : 1);

			alias_edit->SetLimitText(16);
			alias_edit->SetSelAllOnFocus(true);
			alias_edit->AttachSetFocus(nbase::Bind(&ProfileBox::OnAliasEditGetFocus, this, std::placeholders::_1));
			alias_edit->AttachKillFocus(nbase::Bind(&ProfileBox::OnAliasEditLoseFocus, this, std::placeholders::_1));
			alias_edit->AttachMouseEnter(nbase::Bind(&ProfileBox::OnAliasEditMouseEnter, this, std::placeholders::_1));
			alias_edit->AttachMouseLeave(nbase::Bind(&ProfileBox::OnAliasEditMouseLeave, this, std::placeholders::_1));
			alias_edit->AttachReturn(nbase::Bind(&ProfileBox::OnReturnOnAliasEdit, this, std::placeholders::_1));

			notify_switch->AttachSelect(nbase::Bind(&ProfileBox::OnNotifySwitchSelected, this, std::placeholders::_1));
			notify_switch->AttachUnSelect(nbase::Bind(&ProfileBox::OnNotifySwitchUnSelected, this, std::placeholders::_1));
			black_switch->AttachSelect(nbase::Bind(&ProfileBox::OnBlackSwitchSelected, this, std::placeholders::_1));
			black_switch->AttachUnSelect(nbase::Bind(&ProfileBox::OnBlackSwitchUnSelected, this, std::placeholders::_1));
			mute_switch->AttachSelect(nbase::Bind(&ProfileBox::OnMuteSwitchSelected, this, std::placeholders::_1));
			mute_switch->AttachUnSelect(nbase::Bind(&ProfileBox::OnMuteSwitchUnSelected, this, std::placeholders::_1));

			//unregister_cb.Add(MuteBlackService::GetInstance()->RegSyncSetMuteCallback(nbase::Bind(&ProfileBox::OnNotifyChangeCallback, this, std::placeholders::_1, std::placeholders::_2)));
//			unregister_cb.Add(MuteBlackService::GetInstance()->RegSyncSetBlackCallback(nbase::Bind(&ProfileBox::OnBlackChangeCallback, this, std::placeholders::_1, std::placeholders::_2)));

			start_chat->AttachClick(nbase::Bind(&ProfileBox::OnStartChatBtnClicked, this, std::placeholders::_1));
			delete_friend->AttachClick(nbase::Bind(&ProfileBox::OnDeleteFriendBtnClicked, this, std::placeholders::_1));
			add_friend->AttachClick(nbase::Bind(&ProfileBox::OnAddFriendBtnClicked, this, std::placeholders::_1));

			if (have_mute_right_)
			{
				//TODO(litianyi) ͬ�������ӿڲ���
				//nim::TeamMemberProperty prop = nim::Team::QueryTeamMemberBlock(tid_, m_uinfo.id);
				//mute_switch->Selected(prop.IsMute());

				/*nim::Team::QueryTeamMemberAsync(tid_, m_uinfo.id, ToWeakCallback([this](const nim::TeamMemberProperty& team_member_info) {
					mute_switch->Selected(team_member_info.IsMute());
				}));*/
			}

			std::list<std::string> list;
			list.push_back(m_uinfo.id);
			//nim::User::GetUserNameCardOnline(list, nim::User::GetUserNameCardCallback());
		}

		InitLabels();
	}
	Db::Profile	ProfileBox::GetNameCard() const
	{
		return m_uinfo;
	}
	void ProfileBox::CheckInMuteBlack()
	{
		/*auto service = MuteBlackService::GetInstance();*/
	/*	auto mute_list = service->GetMuteList();
		auto black_list = service->GetBlackList();
		notify_switch->Selected(!service->IsInMuteList(m_uinfo.id));
		if (service->IsInBlackList(m_uinfo.id))
		{
			black_switch->Selected(true);
			notify_switch->SetEnabled(false);
		}
		else
			black_switch->Selected(false);*/
	}

	bool ProfileBox::Notify(ui::EventArgs * msg)
	{
		std::wstring name = msg->pSender->GetName();

		if (msg->Type == ui::kEventTab)
		{
			if (btn_modify_info->IsVisible()) // ��ǰ���Ǳ༭ҳ��
				return false;

			if (name == L"nickname_edit")
			{
				phone_edit->SetFocus();
			}
			else if (name == L"phone_edit")
			{
				email_edit->SetFocus();
			}
			else if (name == L"email_edit")
			{
				signature_edit->SetFocus();
			}
			else if (name == L"signature_edit")
			{
				nickname_edit->SetFocus();
			}
		}
		return true;
	}

	bool ProfileBox::OnMultiPushSwitchSelected(ui::EventArgs* args)
	{
		//nim::Client::SetMultiportPushConfigAsync(true, &MultiportPushCallback::OnMultiportPushConfigChange);
		return true;
	}

	bool ProfileBox::OnMultiPushSwitchUnSelected(ui::EventArgs* args)
	{
		//nim::Client::SetMultiportPushConfigAsync(false, &MultiportPushCallback::OnMultiportPushConfigChange);
		return true;
	}
	bool ProfileBox::OnWebRtcSelected(ui::EventArgs* args)
	{
		//nim_comp::VideoManager::GetInstance()->SetWebrtc(true);
		return true;
	}

	bool ProfileBox::OnWebRtcUnSelected(ui::EventArgs* args)
	{
		//nim_comp::VideoManager::GetInstance()->SetWebrtc(false);
		return true;
	}

	bool ProfileBox::OnNotifySwitchSelected(ui::EventArgs* args)
	{
		//MuteBlackService::GetInstance()->InvokeSetMute(m_uinfo.id, false);
		return true;
	}

	bool ProfileBox::OnNotifySwitchUnSelected(ui::EventArgs* args)
	{
		//MuteBlackService::GetInstance()->InvokeSetMute(m_uinfo.id, true);
		return true;
	}

	bool ProfileBox::OnBlackSwitchSelected(ui::EventArgs* args)
	{
		//MuteBlackService::GetInstance()->InvokeSetBlack(m_uinfo.id, true);
		return true;
	}

	bool ProfileBox::OnBlackSwitchUnSelected(ui::EventArgs* args)
	{
		//MuteBlackService::GetInstance()->InvokeSetBlack(m_uinfo.id, false);
		return true;
	}

	bool ProfileBox::OnMuteSwitchSelected(ui::EventArgs* args)
	{
		//nim::Team::MuteMemberAsync(tid_, m_uinfo.id, true, nbase::Bind(&TeamCallback::OnTeamEventCallback, std::placeholders::_1));
		return true;
	}

	bool ProfileBox::OnMuteSwitchUnSelected(ui::EventArgs* args)
	{
		//nim::Team::MuteMemberAsync(tid_, m_uinfo.id, false, nbase::Bind(&TeamCallback::OnTeamEventCallback, std::placeholders::_1));
		return true;
	}

	void ProfileBox::OnNotifyChangeCallback(std::string id, bool mute)
	{
		if (id == m_uinfo.id)
			notify_switch->Selected(!mute);
	}

	void ProfileBox::OnBlackChangeCallback(std::string id, bool black)
	{
		if (id == m_uinfo.id)
		{
			if (black)
			{
				black_switch->Selected(true);
				notify_switch->SetEnabled(false);
			}
			else
			{
				black_switch->Selected(false);
				notify_switch->SetEnabled(true);
			}
		}
	}

	bool ProfileBox::OnStartChatBtnClicked(ui::EventArgs* args)
	{
		/*if (!m_uinfo.id.empty())
			SessionManager::GetInstance()->OpenSessionBox(m_uinfo.id, nim::kNIMSessionTypeP2P);
		else
			SessionManager::GetInstance()->OpenSessionBox(m_robot.id, nim::kNIMSessionTypeP2P);*/
		return true;
	}

	bool ProfileBox::OnDeleteFriendBtnClicked(ui::EventArgs* args)
	{
		MsgboxCallback cb = nbase::Bind(&ProfileBox::OnDeleteFriendMsgBox, this, std::placeholders::_1);
		ShowMsgBox(GetWindow()->GetHWND(), cb, L"STRID_PROFILE_FORM_DELETE_FRIEND_TIP", true, L"STRING_TIPS", true, L"STRING_OK", true, L"STRING_NO", true);
		return true;
	}

	void ProfileBox::OnDeleteFriendMsgBox(MsgBoxRet ret)
	{
		if (ret == MB_YES)
		{
		/*	nim::DeleteFriendOption option;
			option.delete_alias_ = dynamic_cast<ui::CheckBox*>(FindSubControl(L"chkbox_delete_with_alias"))->IsSelected();
			nim::Friend::DeleteEx(m_uinfo.id, option, ToWeakCallback([this](nim::NIMResCode res_code) {
				if (res_code == 200)
					Close();
				}));*/
		}
	}

	bool ProfileBox::OnAddFriendBtnClicked(ui::EventArgs* args)
	{
		/*nim::Friend::Request(m_uinfo.id, nim::kNIMVerifyTypeAdd, "", ToWeakCallback([this](int res_code) {
			if (res_code == 200)
				Close();
		}));*/

		return true;
	}

	void ProfileBox::OnModifyHeaderComplete(const std::string& id, const std::string &url)
	{
		// ͷ���ϴ��ɹ�����ʼ�����û���Ϣ
		auto update_cb = nbase::Bind(&ProfileBox::UpdateUInfoHeaderCallback, this, std::placeholders::_1);
		UserService::GetInstance()->InvokeUpdateMyPhoto(url, update_cb);
	}

	void ProfileBox::UpdateUInfoHeaderCallback(int res)
	{
		QLOG_ERR(L"updateUInfoHeaderCallback error code: {0}.") << res;
	}

	bool ProfileBox::OnHeadImageClicked(ui::EventArgs * args)
	{
		std::string uid = m_uinfo.id;
	/*	HeadModifyForm* form = (HeadModifyForm*)WindowsManager::GetInstance()->GetWindow(HeadModifyForm::kClassName, nbase::UTF8ToUTF16(uid));
		if (form == NULL)
		{
			form = new HeadModifyForm(uid, L"");
			form->Create(NULL, NULL, WS_OVERLAPPED, 0L);
			form->ShowWindow(true);
			form->CenterWindow();
		}
		else
		{
			::SetForegroundWindow(form->GetHWND());
		}
		form->RegCompleteCallback(nbase::Bind(&ProfileBox::OnModifyHeaderComplete, this, std::placeholders::_1, std::placeholders::_2));*/

		return true;
	}

	bool ProfileBox::OnModifyOrCancelBtnClicked(ui::EventArgs* args, bool to_modify)
	{
		/*if (LoginManager::GetInstance()->IsEqual(m_uinfo.id))
		{
			btn_modify_info->SetVisible(!to_modify);
			btn_save_modify->SetVisible(to_modify);
			btn_cancel_modify->SetVisible(to_modify);
		}*/
		nickname_box->SetVisible(to_modify);
		sex_box->SetVisible(to_modify);
		birthday_label->SetVisible(!to_modify);
		birthday_combo_box->SetVisible(to_modify);
		phone_label->SetVisible(!to_modify);
		phone_edit->SetVisible(to_modify);
		email_label->SetVisible(!to_modify);
		email_edit->SetVisible(to_modify);
		signature_label->SetVisible(!to_modify);
		signature_edit->SetVisible(to_modify);
		if (to_modify)
		{
			InitBirthdayCombo(); //��ʼ���������������������ó�ʼֵ
			InitEdits();
			nickname_error_tip->SetVisible(false);
		}
		return true;
	}

	bool ProfileBox::OnSaveInfoBtnClicked(ui::EventArgs * args)
	{
		/*std::wstring nick = nbase::StringTrim(nickname_edit->GetText());
		if (nick.empty())
		{
			nickname_error_tip->SetText(ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_PROFILE_FORM_NICKNAME_NON_EMPTY"));
			nickname_error_tip->SetVisible(true);
			return false;
		}
		else
			nickname_error_tip->SetVisible(false);

		Db::Profile new_info;
		new_info.SetAccId(m_uinfo.id);

		if (!m_uinfo.ExistValue(nim::kUserNameCardKeyName) || nbase::UTF16ToUTF8(nick) != m_uinfo.GetName())
		{
			new_info.SetName(nbase::UTF16ToUTF8(nick));
		}

		switch (sex_option->GetCurSel())
		{
		case 0:
			if (!m_uinfo.ExistValue(nim::kUserNameCardKeyGender) || m_uinfo.GetGender() != UG_MALE)
			{
				new_info.SetGender(UG_MALE);
			}
			break;
		case 1:
			if (!m_uinfo.ExistValue(nim::kUserNameCardKeyGender) || m_uinfo.GetGender() != UG_FEMALE)
			{
				new_info.SetGender(UG_FEMALE);
			}
			break;
		default:
			break;
		}

		if (birth_year_combo->GetCurSel() != -1 && birth_month_combo->GetCurSel() != -1 && birth_day_combo->GetCurSel() != -1)
		{
			int this_year = nbase::Time::Now().ToTimeStruct(true).year();
			int birth_year = this_year - birth_year_combo->GetCurSel() - 1;
			int birth_month = birth_month_combo->GetCurSel() + 1;
			int birth_day = birth_day_combo->GetCurSel() + 1;
			std::string new_birthday = nbase::StringPrintf("%04d-%02d-%02d", birth_year, birth_month, birth_day);
			if (!m_uinfo.ExistValue(nim::kUserNameCardKeyBirthday) || new_birthday != m_uinfo.GetBirth())
			{
				new_info.SetBirth(nbase::StringPrintf("%04d-%02d-%02d", birth_year, birth_month, birth_day));
			}
		}

		if (!m_uinfo.ExistValue(nim::kUserNameCardKeyMobile) && !phone_edit->GetUTF8Text().empty()
			|| (m_uinfo.ExistValue(nim::kUserNameCardKeyMobile) && phone_edit->GetUTF8Text() != m_uinfo.GetMobile()))
		{
			new_info.SetMobile(nbase::UTF16ToUTF8(phone_edit->GetText()));
		}
		if (!m_uinfo.ExistValue(nim::kUserNameCardKeyEmail) && !email_edit->GetUTF8Text().empty()
			|| (m_uinfo.ExistValue(nim::kUserNameCardKeyEmail) && email_edit->GetUTF8Text() != m_uinfo.GetEmail()))
		{
			new_info.SetEmail(nbase::UTF16ToUTF8(email_edit->GetText()));
		}
		if (!m_uinfo.ExistValue(nim::kUserNameCardKeySignature) && !signature_edit->GetUTF8Text().empty()
			|| (m_uinfo.ExistValue(nim::kUserNameCardKeySignature) && signature_edit->GetUTF8Text() != m_uinfo.GetSignature()))
		{
			new_info.SetSignature(nbase::UTF16ToUTF8(signature_edit->GetText()));
		}

		if (new_info.ExistValue(nim::kUserNameCardKeyAll))
			UserService::GetInstance()->InvokeUpdateMyInfo(new_info, nullptr);
		else
			OnModifyOrCancelBtnClicked(nullptr, false);*/

		return true;
	}

	bool nim_comp::ProfileBox::OnAliasEditGetFocus(ui::EventArgs * args)
	{
		alias_edit->SetBorderSize(1);
		return false;
	}

	bool ProfileBox::OnAliasEditLoseFocus(ui::EventArgs * args)
	{
		alias_edit->SetBorderSize(0);

		if (alias_edit->GetText() == UserService::GetInstance()->GetFriendAlias(m_uinfo.id))
			return false;

		nim::FriendProfile profile;
		//Json::Value values;
		//Json::Reader reader;
		//std::string test_string = "{\"remote\":{\"mapmap\":{\"int\":1,\"boolean\":false,\"list\":[1,2,3],\"string\":\"string, lalala\"}}}";
		//if (reader.parse(test_string, values))
		//	profile.SetEx(values);
		profile.SetAccId(m_uinfo.id);
		profile.SetAlias(alias_edit->GetUTF8Text());
		//nim::Friend::Update(profile, nullptr);

		return true;
	}

	bool ProfileBox::OnAliasEditMouseEnter(ui::EventArgs * args)
	{
		if (!alias_edit->IsFocused())
			alias_edit->SetBorderSize(1);
		return false;
	}

	bool ProfileBox::OnAliasEditMouseLeave(ui::EventArgs * args)
	{
		if (!alias_edit->IsFocused())
			alias_edit->SetBorderSize(0);
		return false;
	}

	bool nim_comp::ProfileBox::OnReturnOnAliasEdit(ui::EventArgs * args)
	{
		alias_edit->GetParent()->SetFocus();
		return false;
	}

	void ProfileBox::InitBirthdayCombo()
	{
		birth_year_combo->RemoveAll();
		birth_month_combo->RemoveAll();
		birth_day_combo->RemoveAll();

		auto create_elem = [](int i)
		{
			ui::ListContainerElement* elem = new ui::ListContainerElement;
			elem->SetClass(L"listitem");
			elem->SetFixedHeight(30);
			elem->SetTextPadding(ui::UiRect(10, 1, 1, 1));
			elem->SetText(nbase::IntToString16(i));
			//elem->SetFont(2);
			elem->SetStateTextColor(ui::kControlStateNormal, L"profile_account");
			return elem;
		};

		int this_year = nbase::Time::Now().ToTimeStruct(true).year();
		for (int i = this_year - 1; i >= 1900; i--)
			birth_year_combo->Add(create_elem(i));
		for (int i = 1; i <= 12; i++)
			birth_month_combo->Add(create_elem(i));
		for (int i = 1; i <= 31; i++)
			birth_day_combo->Add(create_elem(i));
	}

	bool ProfileBox::OnBirthdayComboSelect(ui::EventArgs * args)
	{
		ui::ListContainerElement* cur_year = (ui::ListContainerElement*)birth_year_combo->GetItemAt(birth_year_combo->GetCurSel());
		ui::ListContainerElement* cur_month = (ui::ListContainerElement*)birth_month_combo->GetItemAt(birth_month_combo->GetCurSel());
		if (cur_year == NULL || cur_month == NULL)
			return false;

		int year = std::stoi(cur_year->GetText());
		int month = std::stoi(cur_month->GetText());

		std::set<int> big_months({ 1, 3, 5, 7, 8, 10, 12 });
		std::set<int> small_months({ 4, 6, 9, 11 });
		if (big_months.find(month) != big_months.cend()) //����
		{
			for (int i = 28; i < 31; i++)
			{
				auto item = birth_day_combo->GetItemAt(i);
				if (item) item->SetVisible(true);
			}
		}
		else if (small_months.find(month) != small_months.cend()) //С��
		{
			for (int i = 28; i < 30; i++)
			{
				auto item = birth_day_combo->GetItemAt(i);
				if (item) item->SetVisible(true);
			}
			auto item = birth_day_combo->GetItemAt(30);
			if (item)
				item->SetVisible(false);

			if (birth_day_combo->GetCurSel() > 29)
				birth_day_combo->SelectItem(29);
		}
		else //����
		{
			for (int i = 29; i < 31; i++)
			{
				auto item = birth_day_combo->GetItemAt(i);
				if (item) item->SetVisible(false);
			}

			auto item = birth_day_combo->GetItemAt(28);
			if (item)
			{
				bool bissextile = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
				birth_day_combo->GetItemAt(28)->SetVisible(bissextile);

				if (birth_day_combo->GetCurSel() > 27 + bissextile)
					birth_day_combo->SelectItem(27 + bissextile);
			}
		}

		return true;
	}

	void ProfileBox::OnFriendListChange(FriendChangeType change_type, const std::string& accid)
	{
		if (accid == m_uinfo.id)
		{
			if (change_type == kChangeTypeAdd)
				user_type = nim::kNIMFriendFlagNormal;
			else if (change_type == kChangeTypeDelete)
				user_type = nim::kNIMFriendFlagNotFriend;

			add_or_del->SelectItem(user_type == nim::kNIMFriendFlagNormal ? 0 : 1);
			SetShowName();
		}
	}

	void ProfileBox::OnUserInfoChange(const std::list<Db::Profile>& uinfos)
	{
		for (auto info : uinfos)
		{
			/*if (m_uinfo.id == info.id)
			{
				m_uinfo.Update(info);
				if (info.ExistValue(nim::kUserNameCardKeyIconUrl))
					head_image_btn->SetBkImage(PhotoService::GetInstance()->GetUserPhoto(m_uinfo.id));
				if (info.ExistValue(nim::kUserNameCardKeyName))
				{
					SetShowName();
					OnModifyOrCancelBtnClicked(nullptr, false);
				}
				break;
			}*/
		}
	}

	void nim_comp::ProfileBox::OnUserPhotoReady(PhotoType type, const std::string & account, const std::wstring & photo_path)
	{
		if (type == kUser && m_uinfo.id== account)
			head_image_btn->SetBkImage(photo_path);
	}

	void nim_comp::ProfileBox::OnMiscUInfoChange(const std::list<Db::Profile>& uinfos)
	{
		for (auto info : uinfos)
		{
			/*if (m_uinfo.id == info.id)
			{
				m_uinfo.Update(info);
				InitLabels();
				OnModifyOrCancelBtnClicked(nullptr, false);
				break;
			}*/
		}
	}

	void ProfileBox::OnMultiportPushConfigChange(bool switch_on)
	{
		if (-1 != user_type)
			return;

		multi_push_switch->Selected(switch_on, false);
	}

	void ProfileBox::InitLabels()
	{
		SetShowName();

		head_image_btn->SetBkImage(PhotoService::GetInstance()->GetUserPhoto(m_uinfo.id)); //ͷ��

		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyGender))
		//{
		//	switch (m_uinfo.GetGender()) // �ǳ��ұߵ��Ա�ͼ��
		//	{
		//	case UG_MALE:
		//		sex_icon->Selected(false);
		//		sex_icon->SetVisible(true);
		//		break;
		//	case UG_FEMALE:
		//		sex_icon->Selected(true);
		//		sex_icon->SetVisible(true);
		//		break;
		//	case UG_UNKNOWN:
		//	default:
		//		sex_icon->SetVisible(false);
		//	}
		//}

		//std::wstring account = nbase::StringPrintf(ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_PROFILE_FORM_ACCOUNT_").c_str(), nbase::UTF8ToUTF16(m_uinfo.id).c_str());
		//user_id_label->SetText(account);//�ʺ�

		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyBirthday))
		//	birthday_label->SetText(nbase::UTF8ToUTF16(m_uinfo.GetBirth())); //����
		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyMobile))
		//	phone_label->SetText(nbase::UTF8ToUTF16(m_uinfo.GetMobile())); //�ֻ�
		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyEmail))
		//	email_label->SetText(nbase::UTF8ToUTF16(m_uinfo.GetEmail())); //����
		//if (m_uinfo.ExistValue(nim::kUserNameCardKeySignature))
		//	signature_label->SetText(nbase::UTF8ToUTF16(m_uinfo.GetSignature())); //ǩ��
	}

	void ProfileBox::SetShowName()
	{
		UserService* user_service = UserService::GetInstance();
		std::wstring show_name = user_service->GetUserName(m_uinfo.id);
		show_name_label->SetText(show_name);
		ui::MutiLanSupport* mls = ui::MutiLanSupport::GetInstance();
		std::wstring title = nbase::StringPrintf(mls->GetStringViaID(L"STRID_PROFILE_FORM_WHOSE_NAMECARD").c_str(), show_name.c_str());
		SetTaskbarTitle(title); //����������

		if (user_type == nim::kNIMFriendFlagNormal) //����
		{
			std::wstring alias = user_service->GetFriendAlias(m_uinfo.id);

			alias_box->SetVisible(true); //�������ñ�ע��
			if (!alias_edit->IsFocused())
				alias_edit->SetText(alias); //��ע���༭����ʾ��ע��

			if (!alias.empty())
			{
				nickname_label->SetVisible(true); //�˺�������ʾ�ǳ�
				std::wstring nickname = nbase::StringPrintf(mls->GetStringViaID(L"STRID_PROFILE_FORM_NICKNAME_").c_str(), user_service->GetUserName(m_uinfo.id, false).c_str());
				nickname_label->SetText(nickname);
			}
			else
				nickname_label->SetVisible(false);
		}
		else //���Ǻ��ѣ�����ʾ��ע��
		{
			nickname_label->SetVisible(false);
			alias_box->SetVisible(false);
		}
	}

	void ProfileBox::InitEdits()
	{
		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyName))
		//	nickname_edit->SetText(nbase::UTF8ToUTF16(m_uinfo.GetName())); //�ǳ�
		//if (sex_icon->IsVisible() && m_uinfo.ExistValue(nim::kUserNameCardKeyGender))//�Ա�
		//	sex_option->SelectItem(sex_icon->IsSelected());

		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyBirthday))
		//{
		//	int birth[3] = { 0, 0, 0 }; //����
		//	size_t pos = std::string::npos;
		//	int count = 0;
		//	do
		//	{
		//		size_t temp = pos + 1;
		//		pos = m_uinfo.GetBirth().find_first_of('-', temp);
		//		std::string num_str = m_uinfo.GetBirth().substr(temp, pos - temp);
		//		if (!num_str.empty())
		//			birth[count] = std::stoi(num_str);
		//		count++;
		//	} while (pos != std::string::npos && count < 3);

		//	int this_year = nbase::Time::Now().ToTimeStruct(true).year();
		//	if (birth[0] >= 1900 && birth[0] < this_year && birth_year_combo->GetItemAt(this_year - birth[0] - 1) != NULL)
		//		birth_year_combo->SelectItem(this_year - birth[0] - 1);
		//	if (birth[1] >= 1 && birth[1] <= 12 && birth_month_combo->GetItemAt(birth[1] - 1) != NULL)
		//		birth_month_combo->SelectItem(birth[1] - 1);
		//	if (birth[2] >= 1 && birth[2] <= 31 && birth_day_combo->GetItemAt(birth[2] - 1) != NULL)
		//		birth_day_combo->SelectItem(birth[2] - 1);

		//	OnBirthdayComboSelect(NULL);
		//}

		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyMobile))
		//	phone_edit->SetText(nbase::UTF8ToUTF16(m_uinfo.GetMobile()));//�ֻ�
		//if (m_uinfo.ExistValue(nim::kUserNameCardKeyEmail))
		//	email_edit->SetText(nbase::UTF8ToUTF16(m_uinfo.GetEmail()));//����
		//if (m_uinfo.ExistValue(nim::kUserNameCardKeySignature))
		//	signature_edit->SetText(nbase::UTF8ToUTF16(m_uinfo.GetSignature()));//ǩ��
	}
	void ProfileBox::SetTaskbarTitle(const std::wstring &title)
	{
		if (taskbar_title_function_ != nullptr)
			taskbar_title_function_(title);
	}
	void ProfileBox::Close(UINT nRet/* = 0*/)
	{
		if (close_function_ != nullptr)
			close_function_(nRet);
	}
	void ProfileBox::AttachSetTaskbarTitle(const std::function<void(const std::wstring&)>& cb)
	{
		taskbar_title_function_ = cb;
	}
	void ProfileBox::AttachClose(const std::function<void(UINT)>& cb)
	{
		close_function_ = cb;
	}
}