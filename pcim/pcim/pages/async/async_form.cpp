#include "stdafx.h"
#include "resource.h"
#include "async_form.h"
#include "async_manager.h"
#include "pages/login_manager.h"
#include "pages/ui_login_manager.h"

using namespace ui;

namespace nim_comp
{
const LPCTSTR AsyncForm::kClassName = L"AsyncForm";

AsyncForm::AsyncForm()
{

}

AsyncForm::~AsyncForm()
{
	
}

std::wstring AsyncForm::GetSkinFolder()
{
	return L"async";
}

std::wstring AsyncForm::GetSkinFile()
{
	return L"async.xml";
}

std::wstring AsyncForm::GetWindowClassName() const 
{
	return kClassName;
}

std::wstring AsyncForm::GetWindowId() const 
{
	return kClassName;
}

UINT AsyncForm::GetClassStyle() const 
{
	return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

void AsyncForm::InitWindow()
{
	StdClosure closure = [this]() {
		try
		{
			std::string profileid = nim_comp::LoginManager::GetInstance()->GetProfileId();
			ShowAsyncInfo(L"STRID_ASYNC_FORM_ASYNCPROFILEINFO", 0);
			AsyncManager::async_profile_info(profileid);
			Sleep(50);
			ShowAsyncInfo(L"STRID_ASYNC_FORM_ASYNCPROFILESETTINGINFO", 0);
			AsyncManager::async_profile_setting_info(profileid);
			Sleep(50);
			ShowAsyncInfo(L"STRID_ASYNC_FORM_ASYNCCONTACTINFO", 0);
			AsyncManager::async_contacts(profileid);
			Sleep(50);
			ShowAsyncInfo(L"STRID_ASYNC_FORM_ASYNCGROUPINFO", 0);
			std::list<std::string> ids = AsyncManager::async_groups(profileid);
			Sleep(50);
			ShowAsyncInfo(L"STRID_ASYNC_FORM_ASYNCGROUPMEMBERINFO", 0);
			AsyncManager::async_group_members(profileid, ids);
			Sleep(50);
			ShowAsyncInfo(L"STRID_ASYNC_FORM_ASYNCFINISHED", 0);
			Sleep(200);
			this->ShowWindow(false, false);
			// 登录成功，显示主界面
			Post2UI([=](){
				nim_ui::LoginManager::GetInstance()->InvokeShowMainForm();
				nim_ui::LoginManager::GetInstance()->InvokeDestroyWindow();
			});
			this->Close();
		}
		catch (std::exception& errorMsg) {
			printf_s("_______AsyncManager_________%s___________\n", errorMsg.what());
		}
	};
	Post2GlobalMisc(ToWeakCallback(closure));
	 
}
void AsyncForm::ShowAsyncInfo(std::wstring text, float value)
{ 
	auto progress = dynamic_cast<ui::Progress*>(FindControl(L"progress"));
	auto message = dynamic_cast<ui::Label*>(FindControl(L"message"));
	MutiLanSupport* mls = MutiLanSupport::GetInstance();
	std::wstring label = mls->GetStringViaID(text);
	auto task = ToWeakCallback([this, label, value, message, progress](){
		message->SetVisible(false); 
		message->SetText(label);
	    message->SetVisible(true); 
		progress->SetValue(value);
	});
	Post2UI(task);
} 

void ShowAsyncForm()
{
	AsyncForm* async_form = (AsyncForm*)( WindowsManager::GetInstance()->GetWindow(AsyncForm::kClassName, AsyncForm::kClassName) );
	if(async_form)
	{
		async_form->CenterWindow();
		async_form->ActiveWindow(); 
		async_form->ShowWindow();
	}
	else
	{
		async_form = new AsyncForm;
		HWND hwnd = async_form->Create(NULL, AsyncForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX, WS_EX_TOOLWINDOW);
		if(hwnd == NULL)
			return;
		async_form->CenterWindow();
		async_form->ShowWindow(); 
	}
}
}