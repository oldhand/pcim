// basic.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "main.h"
#include "pages/login_form.h"
#include "common/config/config_helper.h"
#include "apis/db/provider_db.h"
#include "utils/threads.h"
#include "gui/extern_ctrl/extern_ctrl_manager.h"
 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef _DEBUG
	AllocConsole();
	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	wprintf_s(L"Command:\n%s\n\n", lpCmdLine);
#endif

	// 创建主线程
	MainThread thread;

	// 执行主线程循环
	thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

#ifdef _DEBUG
	AllocConsole();
	if (fp != nullptr)
	{
		fclose(fp);
		fp = nullptr;
	}
#endif 

	return 0;
}

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);
	PreMessageLoop();
	// 获取资源路径，初始化全局参数
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();
	std::wstring language = nbase::UTF8ToUTF16(ConfigHelper::GetInstance()->GetLanguage());
	ui::LanguageSetting language_setting;
	language_setting.m_strResource = language;
	if (language.compare(L"lang\\zh_CN") == 0)
		language_setting.m_enumType = ui::LanguageType::Simplified_Chinese;
	else if (language.compare(L"lang\\en_US") == 0)
		language_setting.m_enumType = ui::LanguageType::American_English;
	else
		language_setting.m_enumType = ui::LanguageType::Simplified_Chinese;
#ifdef _DEBUG
	// Debug 模式下使用本地文件夹作为资源
	// 默认皮肤使用 resources\\themes\\default
	// 默认语言使用 resources\\lang\\zh_CN
	// 如需修改请指定 Startup 最后两个参数

	ui::GlobalManager::Startup(theme_dir + L"resources\\", ExternCtrlManager::CreateExternCtrl, false, L"themes\\default", language_setting);
#else
	// Release 模式下使用资源中的压缩包作为资源
	// 资源被导入到资源列表分类为 THEME，资源名称为 IDR_THEME
	// 如果资源使用的是本地的 zip 文件而非资源中的 zip 压缩包
	// 可以使用 OpenResZip 另一个重载函数打开本地的资源压缩包
	ui::GlobalManager::OpenResZip(MAKEINTRESOURCE(IDR_THEME), L"THEME", "");
	// ui::GlobalManager::OpenResZip(L"resources.zip", "");
	ui::GlobalManager::Startup(L"resources\\", ui::CreateControlCallback(), false, L"themes\\default", language_setting);
#endif


	Rest::XN_Rest::application = Env::application;
	Rest::XN_Rest::baseUrl = Env::baseUrl;
	Rest::XN_Rest::appid = Env::appid;
	Rest::XN_Rest::secret = Env::secret;
	Rest::XN_Rest::init();

	Db::ProviderDb::GetInstance()->initdb();
	Db::ProviderDb::GetInstance()->initindex();
	/*try {
	Content content = XN_Content::load("13878");
	}
	catch (std::exception& errorMsg) {
	printf_s("_______XN_Content::load();__________%s___________\n", errorMsg.what());
	}
	try {
		std::list<Content> lists = XN_Content::loadMany({ 13878, 1332 });
	}
	catch (std::exception& errorMsg) {
		printf_s("_______XN_Content::loadMany();__________%s___________\n", errorMsg.what());
	}
	try {
		Content newcontent = XN_Content::create("im_likes", "", false);
		std::string tmp = "中华人民共和国"; 
		tmp = nbase::strings::gbk_to_utf8(tmp);
		newcontent.my["supplierid"] = "admin";
		newcontent.my["deleted"] = "0";
		newcontent.my["aa"] = tmp;
		newcontent.my["bb"] = "0123123123";
		newcontent.save("im_likes,im_likes_123");
		newcontent.my["cc"] = "0123123123";
		newcontent.my["dd"] = "asdasdasdasdad";
		newcontent.save("im_likes,im_likes_123");

		newcontent.erase("im_likes,im_likes_123");
		newcontent.erase("im_likes,im_likes_123");
	}
	catch (std::exception& errorMsg) {
		printf_s("________________%s___________\n", errorMsg.what());
	}*/
	// 创建一个默认带有阴影的居中窗口
	LoginForm* loginform = new LoginForm();
	loginform->Create(NULL, LoginForm::kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	loginform->CenterWindow();
	loginform->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Shutdown();
	PostMessageLoop();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}


void MainThread::PreMessageLoop()
{
	misc_thread_.reset(new MiscThread(kThreadGlobalMisc, "Global Misc Thread"));
	misc_thread_->Start();

	screen_capture_thread_.reset(new MiscThread(kThreadScreenCapture, "screen capture"));
	screen_capture_thread_->Start();

	db_thread_.reset(new DBThread(kThreadDatabase, "Database Thread"));
	db_thread_->Start();

}

void MainThread::PostMessageLoop()
{

	misc_thread_->Stop();
	misc_thread_.reset(NULL);

	screen_capture_thread_->Stop();
	screen_capture_thread_.reset(NULL);

	db_thread_->Stop();
	db_thread_.reset(NULL);


}