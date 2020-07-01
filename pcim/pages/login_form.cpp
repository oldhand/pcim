#include "stdafx.h"
#include "resource.h"
#include "login_form.h"
#include "common/db/public_db.h"
#include "main_form_ex.h"
#include "ui_window_manager.h"
#include "main_form_menu.h"
#include "ui_window_manager.h"
#include "login_callback.h"
#include "ui_login_manager.h"



using namespace ui;
const LPCTSTR LoginForm::kClassName = L"Login";

LoginForm::LoginForm()
{
	PublicDB::GetInstance()->ReadLoginData();
}


LoginForm::~LoginForm()
{
}

std::wstring LoginForm::GetSkinFolder()
{
	return L"Login";
}

std::wstring LoginForm::GetSkinFile()
{
	return L"Login.xml";
}

std::wstring LoginForm::GetWindowClassName() const
{
	return kClassName;
}

UINT LoginForm::GetClassStyle() const
{
	return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

void LoginForm::InitWindow()
{
	SetIcon(IDI_IM);
	m_pRoot->AttachBubbledEvent(ui::kEventAll, nbase::Bind(&LoginForm::Notify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, nbase::Bind(&LoginForm::OnClicked, this, std::placeholders::_1));

	usericon_ = FindControl(L"usericon");
	passwordicon_ = FindControl(L"passwordicon");

	user_name_edit_ = (RichEdit*)FindControl(L"username");
	password_edit_ = (RichEdit*)FindControl(L"password");
	user_name_edit_->SetSelAllOnFocus(true);
	password_edit_->SetSelAllOnFocus(true);

	login_ing_tip_ = FindControl(L"login_ing_tip");
	login_error_tip_ = (Label*)FindControl(L"login_error_tip"); 

	btn_login_ = (Button*)FindControl(L"btn_login"); 
	btn_cancel_ = (Button*)FindControl(L"btn_cancel");
	remember_pwd_ckb_ = (CheckBox *)FindControl(L"chkbox_remember_pwd");
	remember_user_ckb_ = (CheckBox *)FindControl(L"chkbox_remember_username");

	use_new_uistyle_ = (CheckBox *)FindControl(L"chkbox_use_new_uistyle");

	user_name_edit_->SetLimitText(32); 
	password_edit_->SetLimitText(128); 

	((ui::Button*)FindControl(L"scanqrcode_login"))->AttachClick([this](ui::EventArgs* msg) {
		return OnSwitchToScanQrcodeLoginPage();
	});

	((ui::Button*)FindControl(L"enter_login"))->AttachClick([this](ui::EventArgs* msg) {
		return OnSwitchToLoginPage();
	});

	InitLoginData();
	CheckAutoLogin();
}

LRESULT LoginForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

 
void LoginForm::InitLoginData()
{
	PublicDB* manager = PublicDB::GetInstance();
	UTF8String user_name = manager->GetLoginData()->user_name_;
	UTF8String user_password = manager->GetLoginData()->user_password_;
	bool remember_user = manager->GetLoginData()->remember_user_ == 1;
	bool remember_psw = manager->GetLoginData()->remember_psw_ == 1;

	if (!user_name.empty() && !user_password.empty())
	{
		if (remember_user)
		{
			user_name_edit_->SetUTF8Text(user_name);
		}

		if (remember_psw)
		{
			password_edit_->SetUTF8Text(user_password);
		}

		remember_pwd_ckb_->Selected(remember_psw);
		remember_user_ckb_->Selected(remember_user);
	}
	else
	{
		remember_pwd_ckb_->Selected(false);
		remember_user_ckb_->Selected(false);
	}
	UTF8String dirctory = nbase::UTF16ToUTF8(QPath::GetNimAppDataDir(L""));
}
void LoginForm::CheckAutoLogin()
{
	bool pwd_save = remember_pwd_ckb_->IsSelected();
	bool autorun_flag = QCommand::Get(L"autorun") == L"1";
	QLOG_APP(L"CheckAutoLogin: pwd:{0} autorun:{1}") << pwd_save << autorun_flag;
	if (pwd_save && autorun_flag)
	{
		//OnLogin();
	}
}
bool LoginForm::OnSwitchToScanQrcodeLoginPage()
{
	MutiLanSupport* multilan = MutiLanSupport::GetInstance();
	SetTaskbarTitle(multilan->GetStringViaID(L"STRID_LOGIN_FORM_SCAN_QRCODE_LOGIN"));
	FindControl(L"enter_panel")->SetVisible(false);
	FindControl(L"login_cache_conf")->SetVisible(false);
	FindControl(L"btn_panel")->SetVisible(false);
	FindControl(L"scanqrcode_login")->SetVisible(false);
	FindControl(L"enter_login")->SetVisible(true);
	FindControl(L"scanqrcode_login_panel")->SetVisible(true);
	login_ing_tip_->SetVisible(false);
	login_error_tip_->SetVisible(false);
	return true;
}
bool LoginForm::OnSwitchToLoginPage()
{
	MutiLanSupport* multilan = MutiLanSupport::GetInstance();
	SetTaskbarTitle(multilan->GetStringViaID(L"STRID_LOGIN_FORM_LOGIN"));
	FindControl(L"scanqrcode_login_panel")->SetVisible(false);
	FindControl(L"enter_login")->SetVisible(false);
	FindControl(L"enter_panel")->SetVisible(true);
	FindControl(L"login_cache_conf")->SetVisible(true);
	FindControl(L"btn_panel")->SetVisible(true);
	FindControl(L"enter_panel")->SetBkImage(L"user_password.png");
	FindControl(L"login_cache_conf")->SetVisible(true);
	btn_login_->SetVisible();
	user_name_edit_->SetPromptText(multilan->GetStringViaID(L"STRID_LOGIN_FORM_ACCOUNT"));
	password_edit_->SetPromptText(multilan->GetStringViaID(L"STRID_LOGIN_FORM_PASSWORD"));
	FindControl(L"scanqrcode_login")->SetVisible(true);
	FindControl(L"enter_login")->SetVisible(false);
	return true;
}
void LoginForm::OnLoginOK()
{
	UTF8String user_name = user_name_edit_->GetUTF8Text();
	UTF8String pass = password_edit_->GetUTF8Text();

	PublicDB::GetInstance()->GetLoginData()->status_ = kLoginDataStatusValid;
	PublicDB::GetInstance()->GetLoginData()->user_id_ = "1";
	PublicDB::GetInstance()->GetLoginData()->user_name_ = user_name;
	PublicDB::GetInstance()->GetLoginData()->user_password_ = pass;
	PublicDB::GetInstance()->GetLoginData()->remember_psw_ = remember_pwd_ckb_->IsSelected() ? 1 : 0;
	PublicDB::GetInstance()->GetLoginData()->remember_user_ = remember_user_ckb_->IsSelected() ? 1 : 0;
	PublicDB::GetInstance()->SaveLoginData();
}
void LoginForm::OnLogin()
{
	DoBeforeLogin();
}

void LoginForm::DoBeforeLogin()
{
	std::string username = user_name_edit_->GetUTF8Text();
	StringHelper::Trim(username);
	std::wstring user_name_temp = nbase::UTF8ToUTF16(username);
	user_name_temp = StringHelper::MakeLowerString(user_name_temp);
	username = nbase::UTF16ToUTF8(user_name_temp);
	if (username.empty())
	{
		usericon_->SetEnabled(false);
		ShowLoginTip(MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_LOGIN_FORM_TIP_ACCOUNT_EMPTY"));
		return;
	}

	std::string password = password_edit_->GetUTF8Text();
	StringHelper::Trim(password);
	if (password.empty())
	{
		passwordicon_->SetEnabled(false);
		ShowLoginTip(MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_LOGIN_FORM_TIP_PASSWORD_EMPTY"));
		return;
	}
	usericon_->SetEnabled(true);
	passwordicon_->SetEnabled(true);
	
	StartLogin(username, password);
}

void LoginForm::StartLogin(std::string username, std::string password)
{
	user_name_edit_->SetEnabled(false);
	password_edit_->SetEnabled(false);
	FindControl(L"scanqrcode_login")->SetEnabled(false);

	login_error_tip_->SetVisible(false);
	login_ing_tip_->SetVisible(true);

	btn_login_->SetVisible(false);
	btn_cancel_->SetVisible(true);


	OnLoginOK();

	RegLoginManagerCallback();
	nim_ui::LoginManager::GetInstance()->DoLogin(username, password);
	 
}
void LoginForm::OnCancelLogin()
{
	usericon_->SetEnabled(true);
	passwordicon_->SetEnabled(true);

	user_name_edit_->SetEnabled(true);
	password_edit_->SetEnabled(true);

	login_ing_tip_->SetVisible(false);
	login_error_tip_->SetVisible(false);

	btn_login_->SetVisible(true);
	btn_cancel_->SetVisible(false);
	btn_cancel_->SetEnabled(true);

	FindControl(L"scanqrcode_login")->SetEnabled(true);
}

void LoginForm::RegLoginManagerCallback()
{
	nim_ui::OnLoginError cb_result = [this](int error){
		this->OnLoginError(error);
	};

	nim_ui::OnCancelLogin cb_cancel = [this]{
		this->OnCancelLogin();
	};

	nim_ui::OnHideWindow cb_hide = [this]{
		this->ShowWindow(false, false);
	};

	nim_ui::OnDestroyWindow cb_destroy = [this]{
		//PublicDB::GetInstance()->SaveLoginData();
		::DestroyWindow(this->GetHWND());
	};

	nim_ui::OnShowMainWindow cb_show_main = [this]{
		nim_ui::WindowsManager::SingletonShow<nim_comp::MainFormEx>(nim_comp::MainFormEx::kClassName, new MainFormMenu());
	};
	nim_ui::LoginManager::GetInstance()->RegLoginManagerCallback(ToWeakCallback(cb_result),
		ToWeakCallback(cb_cancel),
		ToWeakCallback(cb_hide),
		ToWeakCallback(cb_destroy),
		ToWeakCallback(cb_show_main));

	//nim_ui::OnShowMainWindow cb_show_main = [this]{
	//	nim_ui::UIStyle uistyle = nim_ui::UIStyle::join;
	//	switch (ConfigHelper::GetInstance()->GetUIStyle())
	//	{
	//	case  0:
	//		uistyle = nim_ui::UIStyle::conventional;
	//		break;
	//	case 1:
	//		uistyle = nim_ui::UIStyle::join;
	//		break;
	//	default:
	//		break;
	//	}

	//	nim_ui::RunTimeDataManager::GetInstance()->SetUIStyle(uistyle);
	//	switch (nim_ui::RunTimeDataManager::GetInstance()->GetUIStyle())
	//	{
	//	case nim_ui::UIStyle::join:
	//		/*nim_comp::MainPluginsManager::GetInstance()->RegPlugin<CefTestPlugin>("CefTestPlugin");
	//		nim_comp::MainPluginsManager::GetInstance()->RegPlugin<ChatroomPlugin>("ChatroomPlugin");
	//		nim_comp::MainPluginsManager::GetInstance()->RegPlugin<GifTestPlugin>("GifTestPlugin");
	//		nim_comp::MainPluginsManager::GetInstance()->RegPlugin<AddresBookPlugin>("AddresBookPlugin");*/
	//		nim_ui::WindowsManager::SingletonShow<nim_comp::MainFormEx>(nim_comp::MainFormEx::kClassName,new MainFormMenu());
	//		break;
	//	case nim_ui::UIStyle::conventional:
	//		nim_ui::WindowsManager::SingletonShow<MainForm>(MainForm::kClassName);
	//		break;
	//	default:
	//		break;
	//	}	
	//};

	//nim_ui::LoginManager::GetInstance()->RegLoginManagerCallback(ToWeakCallback(cb_result),
	//	ToWeakCallback(cb_cancel),
	//	ToWeakCallback(cb_hide),
	//	ToWeakCallback(cb_destroy),
	//	ToWeakCallback(cb_show_main));
}

void LoginForm::OnLoginError(int error)
{
	if (error == pcim::kPCIMResSuccess)
	{
		OnLoginOK();
	}
	else
	{
		OnCancelLogin();
	 
		MutiLanSupport* mls = MutiLanSupport::GetInstance();
		if (error == pcim::kPCIMResNoProfileError)
		{
			usericon_->SetEnabled(false);
			passwordicon_->SetEnabled(false);
			ShowLoginTip(mls->GetStringViaID(L"STRID_LOGIN_FORM_TIP_NOPROFILE_ERROR"));
		}
		else if (error == pcim::kPCIMResUidPassError)
		{
			usericon_->SetEnabled(false);
			passwordicon_->SetEnabled(false);
			ShowLoginTip(mls->GetStringViaID(L"STRID_LOGIN_FORM_TIP_PASSWORD_ERROR"));
		}
		else if (error == pcim::kPCIMResConnectionError)
		{
			ShowLoginTip(mls->GetStringViaID(L"STRID_LOGIN_FORM_TIP_NETWORK_ERROR"));
		}
		else if (error == pcim::kPCIMResExist)
		{
			ShowLoginTip(mls->GetStringViaID(L"STRID_LOGIN_FORM_TIP_LOCATION_CHANGED"));
		}
		else
		{
			std::wstring tip = nbase::StringPrintf(mls->GetStringViaID(L"STRID_LOGIN_FORM_TIP_ERROR_CODE").c_str(), error);
			ShowLoginTip(tip);
		}
	}
}
bool LoginForm::Notify(ui::EventArgs* msg)
{
	std::wstring name = msg->pSender->GetName();
	if (msg->Type == kEventTextChange)
	{
		if (name == L"username")
		{
			OnCancelLogin();
			password_edit_->SetText(L"");
		}
		else if (name == L"password")
		{
			//È¥³ýÖÐÎÄ×Ö·û
			bool has_chinise = false;
			std::wstring text = password_edit_->GetText(), text_fixed;
			for (size_t i = 0; i < text.length(); i++)
			{
				if (IsAsciiChar(text[i]))
					text_fixed.push_back(text[i]);
				else
					has_chinise = true;
			}
			password_edit_->SetText(text_fixed);

			if (has_chinise)
			{
				MutiLanSupport* multilan = MutiLanSupport::GetInstance();
				ShowLoginTip(multilan->GetStringViaID(L"STRID_LOGIN_FORM_TIP_PASSWORD_RESTRICT2"));
				passwordicon_->SetEnabled(false);
			}
			else
			{
				login_error_tip_->SetVisible(false);
				passwordicon_->SetEnabled(true);
			}
		}
	}
	else if (msg->Type == kEventTab)
	{
		if (user_name_edit_->IsFocused())
		{ 
				password_edit_->SetSelAll();
				password_edit_->SetFocus(); 
		}
		else if (password_edit_->IsFocused())
		{
			user_name_edit_->SetSelAll();
			user_name_edit_->SetFocus();
		}
	}
	else if (msg->Type == kEventReturn)
	{
		if (name == L"username" || name == L"password")
		{ 
				btn_login_->SetFocus();
				OnLogin(); 
		}
	}
	return true;
}
void LoginForm::ShowLoginTip(std::wstring tip_text)
{
	auto task = ToWeakCallback([this, tip_text](){
		login_ing_tip_->SetVisible(false);

		login_error_tip_->SetText(tip_text);
		login_error_tip_->SetVisible(true);
	});
	Post2UI(task);
}
bool LoginForm::OnClicked(ui::EventArgs* msg)
{
	std::wstring name = msg->pSender->GetName();
	if (name == L"btn_login")
	{
		OnLogin();
	}
	else if (name == L"btn_cancel")
	{
		btn_cancel_->SetEnabled(false);
		OnCancelLogin();
	}
	return true;
}