﻿#include "stdafx.h"
#include "login_callback.h"
#include "login_manager.h"
#include "ui_login_manager.h"
#include "ui_window_manager.h"
#include "apis/ProfileApi.h"
#include "async/async_form.h"
//#include "export/nim_ui_all.h"
#include "gui/link/link_form.h"
#include "async/async_manager.h"
//#include "module/local/local_helper.h"
//#include "module/login/login_manager.h"
//#include "module/session/session_manager.h"
//#include "module/session/force_push_manager.h"
//#include "module/subscribe_event/subscribe_event_manager.h"
//#include "module/service/user_service.h"
//#include "module/audio/audio_manager.h"
//#include "cef/cef_module/manager/cef_manager.h"
//#include "util/user.h"
//#include "shared/xml_util.h"
//#include "module\runtime_data\runtime_data_manager.h"

namespace nim_comp
{
void _InitUserFolder()
{
	//nbase::CreateDirectory(GetUserDataPath());
	//nbase::CreateDirectory(GetUserImagePath());
	//nbase::CreateDirectory(GetUserAudioPath());
	//nbase::CreateDirectory(GetUserOtherResPath());
}

void _InitLog()
{
//#ifdef _DEBUG
//	QLogImpl::GetInstance()->SetLogLevel(LV_PRO);
//#else
//	QLogImpl::GetInstance()->SetLogLevel(LoginManager::GetInstance()->GetDemoLogLevel());
//#endif
//	std::wstring dir = GetUserDataPath();
//	QLogImpl::GetInstance()->SetLogFile(dir + kLogFile);
}

void _LogRobot()
{
	//const long m2 = 2*1024*1024, m1 = 1024*1024;
	//QLogImpl::GetInstance()->HalfTo(m2, m1);

	//StdClosure task = nbase::Bind(&_LogRobot);
	//nbase::ThreadManager::PostDelayedTask(kThreadGlobalMisc, task, nbase::TimeDelta::FromMinutes(10));
}

//登录之后的处理：比如读取数据
void _DoAfterLogin()
{
	/*QLOG_APP(L"-----{0} account login-----") << LoginManager::GetInstance()->GetAccount();

	bool ret = AudioManager::GetInstance()->InitAudio(GetUserDataPath());
	assert(ret);

	LoginManager::GetInstance()->CreateSingletonRunMutex();
	TeamService::GetInstance()->QueryAllTeamInfo();

	ForcePushManager::GetInstance()->Load();

	StdClosure task = nbase::Bind(&_LogRobot);
	nbase::ThreadManager::PostDelayedTask(kThreadGlobalMisc, task, nbase::TimeDelta::FromMinutes(1));*/
}

//退出程序前的处理：比如保存数据
void _DoBeforeAppExit()
{
	//ForcePushManager::GetInstance()->Save();
	//QLOG_APP(L"-----{0} account logout-----") << LoginManager::GetInstance()->GetAccount();
}

//执行sdk退出函数
void NimLogout(nim::NIMLogoutType type = nim::kNIMLogoutAppExit)
{
	//QLOG_APP(L"-----logout begin {0}-----") << type;
	//nim::Client::Logout( type, &LoginCallback::OnLogoutCallback );
}

void LoginCallback::DoLogin(std::string user, std::string pass)
{ 
	QLOG_APP(L"login user {0}") << user;
	QLOG_APP(L"-----login begin-----");
	static auto dologin_task = [](bool do_login,const std::string& formated_user, const std::string& formated_pass){

		assert(nim_comp::LoginManager::GetInstance()->GetLoginStatus() == LoginStatus_NONE);
		nim_comp::LoginManager::GetInstance()->SetLoginStatus(LoginStatus_LOGIN);
		nim_comp::LoginManager::GetInstance()->SetAccount(formated_user);
		nim_comp::LoginManager::GetInstance()->SetPassword(formated_pass);

		try {
		    Rest::Profile profile = Api::ProfileApi::get_mobile_profile_info("+86", formated_user);
			bool signin_result = Api::ProfileApi::signin(profile.id, formated_pass);
			if (signin_result) {
				
				nim_ui::LoginManager::GetInstance()->InvokeHideWindow(); 
				LoginManager::GetInstance()->SetLoginStatus(LoginStatus_SUCCESS);
				nim_comp::LoginManager::GetInstance()->SetSupplierId(Env::supplierid);
				nim_comp::LoginManager::GetInstance()->SetProfileId(profile.id); 
				nim_comp::LoginManager::GetInstance()->SetProfileInfo(profile);
				_DoAfterLogin();
				ShowAsyncForm();

			/*	if (AsyncManager::StartAsync(profile.id)) {

				}
				else {

				}*/

				//_DoAfterLogin();
				//// 登录成功，显示主界面
	/*			nim_ui::LoginManager::GetInstance()->InvokeShowMainForm();
				nim_ui::LoginManager::GetInstance()->InvokeDestroyWindow();*/
			}
			else {
				LoginManager::GetInstance()->SetLoginStatus(LoginStatus_NONE);
				LoginManager::GetInstance()->SetLinkActive(false);

				pcim::LoginRes login_res;
				login_res.res_code = pcim::PCIMResCode::kPCIMResUidPassError;
				login_res.message = "UidPassError";
				Post2UI(nbase::Bind(&UILoginCallback, login_res));
			}
	
		}
		catch (std::exception& errorMsg) {
			LoginManager::GetInstance()->SetLoginStatus(LoginStatus_NONE);
			LoginManager::GetInstance()->SetLinkActive(false); 
			
			pcim::LoginRes login_res;
			login_res.res_code = pcim::PCIMResCode::kPCIMResNoProfileError;
			login_res.message = errorMsg.what(); 
			if (std::strcmp(errorMsg.what(), "no Profile") == 0)
			{
				login_res.res_code = pcim::PCIMResCode::kPCIMResNoProfileError;
			}
	/*		nim::LoginRes login;
			ShowLinkForm(login.res_code_, login_res.relogin);*/
			Post2UI(nbase::Bind(&UILoginCallback, login_res));
		} 
		
	};
	
	Post2UI([=](){
		dologin_task(false, user, pass);
	});
				

	//LoginCallback::DoLogout(false);



	//static auto dologin_task = [](bool do_login,const std::string& formated_user, const std::string& formated_pass){
	//	if (!do_login)
	//		return;
	//	assert(LoginManager::GetInstance()->GetLoginStatus() == LoginStatus_NONE);
	//	LoginManager::GetInstance()->SetLoginStatus(LoginStatus_LOGIN);
	//	LoginManager::GetInstance()->SetAccount(formated_user);	
	//	LoginManager::GetInstance()->SetPassword(formated_pass);
	//	_InitUserFolder();
	//	_InitLog();
	//	{
	//		std::wstring ver;
	//		LocalHelper::GetSDKVersion(ver);
	//		QLOG_APP(L"App Version {0}") << ver;
	//		QLOG_APP(L"Account {0}") << LoginManager::GetInstance()->GetAccount();
	//		QLOG_APP(L"UI ThreadId {0}") << GetCurrentThreadId();
	//		QLOG_APP(L"-----login begin-----");
	//	}
	//	//注意：
	//	//1. app key是应用的标识，不同应用之间的数据（用户、消息、群组等）是完全隔离的。开发自己的应用时，请替换为自己的app key。
	//	//2. 用户登录自己的应用是不需要对密码md5加密的，替换app key之后，请记得去掉加密。
	//	std::string app_key = app_sdk::AppSDKInterface::GetAppKey();
	//	auto cb = std::bind(OnLoginCallback, std::placeholders::_1, nullptr);
	//	nim::Client::Login(app_key, LoginManager::GetInstance()->GetAccount(), LoginManager::GetInstance()->GetPassword(), cb);
	//};
	//app_sdk::AppSDKInterface::GetInstance()->InvokeFormatAccountAndPassword(user, pass, [](bool do_login, const std::string& formated_user, const std::string& formated_pass){
	//	if (nbase::FrameworkThread::GetManagedThreadId() != ThreadId::kThreadUI)
	//		Post2UI([=](){
	//		dologin_task(do_login, formated_user, formated_pass); 
	//	});
	//	else
	//		dologin_task(do_login, formated_user, formated_pass);
	//});
}

void LoginCallback::OnLoginCallback(const pcim::LoginRes& login_res, const void* user_data)
{
	/*QLOG_APP(L"OnLoginCallback: {0} - {1}") << login_res.login_step_ << login_res.res_code_;

	if (login_res.res_code_ == nim::kNIMResSuccess)
	{
		if (login_res.login_step_ == nim::kNIMLoginStepLogin)
		{
			Post2UI(nbase::Bind(&UILoginCallback, login_res));
			if (!login_res.other_clients_.empty())
			{
				Post2UI(nbase::Bind(LoginCallback::OnMultispotChange, true, login_res.other_clients_));
			}
		}
	}
	else
	{
		Post2UI(nbase::Bind(&UILoginCallback, login_res));
	}*/
}

void LoginCallback::UILoginCallback(const pcim::LoginRes& login_res)
{
	LoginManager::GetInstance()->SetErrorCode(login_res.res_code);
	QLOG_APP(L"-----login callback {0}-----") << login_res.res_code;
	if (nim_ui::LoginManager::GetInstance()->IsLoginFormValid())
	{
		if (LoginManager::GetInstance()->GetLoginStatus() == LoginStatus_CANCEL)
		{
			QLOG_APP(L"-----login cancel end-----");
			UILogoutCallback();
			return;
		}
		else {
			LoginManager::GetInstance()->SetLoginStatus(LoginStatus_NONE);
		}
		nim_ui::LoginManager::GetInstance()->InvokeLoginError(login_res.res_code); 
	}
	else
	{
		QLOG_APP(L"login form has been closed");
		LoginManager::GetInstance()->SetLoginStatus(LoginStatus_NONE);
		LoginCallback::DoLogout(false);
	}
}

void LoginCallback::CacelLogin()
{
	assert(LoginManager::GetInstance()->GetLoginStatus() == LoginStatus_LOGIN);
	LoginManager::GetInstance()->SetLoginStatus(LoginStatus_CANCEL);
	QLOG_APP(L"-----login cancel begin-----");
}

void LoginCallback::DoLogout(bool over, nim::NIMLogoutType type)
{
	QLOG_APP(L"DoLogout: {0} {1}") <<over <<type;

	LoginStatus status = LoginManager::GetInstance()->GetLoginStatus();
	if(status == LoginStatus_EXIT)
		return;
	LoginManager::GetInstance()->SetLoginStatus(LoginStatus_EXIT);

	WindowsManager::GetInstance()->SetStopRegister(true);
	WindowsManager::GetInstance()->DestroyAllWindows();
    //VideoManager::GetInstance()->DestroyVideoChatForm();

	if(status == LoginStatus_NONE)
	{
		UILogoutCallback();
		return;
	}

	if(over)
	{
		/*if (type == nim::kNIMLogoutKickout || type == nim::kNIMLogoutRelogin)
		{
			QCommand::Set(kCmdAccount, nbase::UTF8ToUTF16(LoginManager::GetInstance()->GetAccount()));
			QCommand::Set(kCmdRestart, L"true");
			std::wstring param = nbase::StringPrintf(L"%d", type);
			QCommand::Set(kCmdExitWhy, param);
		}*/
		UILogoutCallback();
	}
	else
	{
		NimLogout(type);
	}
	PostQuitMessage(0L);
}

void LoginCallback::OnLogoutCallback(nim::NIMResCode res_code)
{
	QLOG_APP(L"OnLogoutCallback: {0}") << res_code;
	QLOG_APP(L"-----logout end-----");
	UILogoutCallback();
}

void LoginCallback::UILogoutCallback()
{
	if (LoginManager::GetInstance()->GetLoginStatus() == LoginStatus_CANCEL)
	{
		LoginManager::GetInstance()->SetLoginStatus(LoginStatus_NONE);

		nim_ui::LoginManager::GetInstance()->InvokeCancelLogin();
	}
	else
	{
        //nim_cef::CefManager::GetInstance()->PostQuitMessage(0);
		auto status = LoginManager::GetInstance()->GetLoginStatus();
		//if(RunTimeDataManager::GetInstance()->IsSDKInited())
		//	_DoBeforeAppExit();
		LoginManager::GetInstance()->SetLoginStatus(LoginStatus_NONE);

		nim_ui::LoginManager::GetInstance()->InvokeCancelLogin();
	}
}

void LoginCallback::ReLogin()
{
	assert(LoginManager::GetInstance()->GetLoginStatus() == LoginStatus_NONE);
	LoginManager::GetInstance()->SetLoginStatus(LoginStatus_LOGIN);

	QLOG_APP(L"-----relogin begin-----");
	//nim::Client::Relogin();
}

void LoginCallback::OnKickoutCallback(const nim::KickoutRes& res)
{
	QLOG_APP(L"OnKickoutCallback: {0} - {1}") << res.client_type_ << res.kick_reason_;
	DoLogout(true, nim::kNIMLogoutKickout);
}

void LoginCallback::OnDisconnectCallback()
{
	QLOG_APP(L"OnDisconnectCallback");
	LoginManager::GetInstance()->SetLinkActive(false);
}

void LoginCallback::OnReLoginCallback(const pcim::LoginRes& login_res)
{
	QLOG_APP(L"OnReLoginCallback: {0}") << login_res.res_code;

	if (login_res.res_code == nim::kNIMResSuccess)
	{
		//if (login_res.login_step == nim::kNIMLoginStepLogin)
		//{
		//	Post2UI(nbase::Bind(&UILoginCallback, login_res));
		//}
	}
	else
	{
		Post2UI(nbase::Bind(&UILoginCallback, login_res));
	}
}

//多端
void LoginCallback::OnMultispotLoginCallback(const nim::MultiSpotLoginRes& res)
{
	/*QLOG_APP(L"OnMultispotLoginCallback: {0} - {1}") << res.notify_type_ << res.other_clients_.size();

	bool online = res.notify_type_ == nim::kNIMMultiSpotNotifyTypeImIn;
	if (!res.other_clients_.empty())
		Post2UI(nbase::Bind(LoginCallback::OnMultispotChange, online, res.other_clients_));*/

}

void LoginCallback::OnMultispotChange(bool online, const std::list<nim::OtherClientPres>& clients)
{
	//nim_ui::SessionListManager::GetInstance()->OnMultispotChange(online, clients);

	//// 将其他端登录信息同步到事件订阅的缓存中，保证第一次登录时可以看到自己账号其他端的登录信息
	//// 只能保证详细到端的信息，无法详细到网络情况（如 WIFI 或 4G）
	//std::list<nim::EventData> event_list;
	//nim::EventData data;
	//Json::Value values;
	//int i = 0;

	//for (auto client : clients)
	//{
	//	values["online"][i] = client.client_type_;
	//	i++;
	//}

	//data.event_type_ = 1;
	//data.readonly_event_time_ = clients.front().login_time_;
	//data.readonly_client_type_ = clients.front().client_type_;
	//data.readonly_publisher_accid_ = clients.front().app_account_;
	//data.readonly_nim_config_ = values.toStyledString();

	//event_list.push_back(data);
	//SubscribeEventManager::GetInstance()->OnPushEventCallback(event_list);
}

void LoginCallback::OnKickoutOtherClientCallback(const nim::KickOtherRes& res)
{
	/*bool success = res.res_code_ == nim::kNIMResSuccess;
	if (success && !res.device_ids_.empty())
	{
		nim_ui::SessionListManager::GetInstance()->OnMultispotKickout(res.device_ids_);
	}*/
}
}