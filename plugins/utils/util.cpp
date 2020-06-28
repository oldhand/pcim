#include "stdafx.h"
#include "util.h"
#include "log.h"
#include "shellapi.h"
#include "md5.h"

std::string QString::GetGUID()
{
	//return nim::Tool::GetUuid();
	return "";
}

std::string QString::GetMd5(const std::string& input)
{
	return nbase::md5(input);
}

void QString::NIMFreeBuf(void *data)
{
	//return nim::Global::FreeBuf(data);
}

std::wstring QPath::GetAppPath()
{
	return nbase::win32::GetCurrentModuleDirectory();
}

std::wstring QPath::GetUserAppDataDir(const std::string& app_account)
{
	//return nbase::UTF8ToUTF16(nim::Tool::GetUserAppdataDir(app_account));
	std::wstring dir = nbase::win32::GetLocalAppDataDir();
	dir.append(L"bitvalue"); 
	if (dir[dir.length() - 1] == L'/' || dir[dir.length() - 1] == L'\\')
		dir.resize(dir.length() - 1);
	dir.append(L"\\IM\\");
	dir.append(nbase::UTF8ToUTF16(app_account));
	dir.append(L"\\");
	return dir;
}

std::wstring QPath::GetLocalAppDataDir()
{
	return nbase::win32::GetLocalAppDataDir();
}

std::wstring QPath::GetNimAppDataDir(const std::wstring& app_data_dir)
{
	std::wstring dir = nbase::win32::GetLocalAppDataDir();
	if (app_data_dir.empty() || app_data_dir.find(L"\\") != std::wstring::npos)
	{
		dir.append(L"bitvalue");
	}
	else
	{
		dir.append(app_data_dir);
	}
	if (dir[dir.length() - 1] == L'/' || dir[dir.length() - 1] == L'\\')
		dir.resize(dir.length() - 1);
#ifdef _DEBUG
	dir.append(L"\\IM\\");
#else
	dir.append(L"\\IM\\");
#endif

	return dir;
}

void QPath::AddNewEnvironment(const std::wstring& directory)
{
	TCHAR path_environment[4096];
	GetEnvironmentVariable(L"PATH", path_environment, 4096);
	std::wstring new_path = directory + L";";
	std::wstring new_environment = new_path + path_environment;
	SetEnvironmentVariable(L"PATH", new_environment.c_str());
}

//
std::map<std::wstring,std::wstring> QCommand::key_value_;

void QCommand::ParseCommand( const std::wstring &cmd )
{
	std::list<std::wstring> arrays = ui::StringHelper::Split(cmd, L"/");
	for(std::list<std::wstring>::const_iterator i = arrays.begin(); i != arrays.end(); i++)
	{
		std::list<std::wstring> object = ui::StringHelper::Split(*i, L" ");
		assert(object.size() == 2);
		key_value_[ *object.begin() ] = *object.rbegin();
	}
}

std::wstring QCommand::Get( const std::wstring &key )
{
	std::map<std::wstring,std::wstring>::const_iterator i = key_value_.find(key);
	if(i == key_value_.end())
		return L"";
	else
		return i->second;
}

void QCommand::Set( const std::wstring &key, const std::wstring &value )
{
	key_value_[key] = value;
}

void QCommand::Erase(const std::wstring &key)
{
	key_value_.erase(key);
}

bool QCommand::AppStartWidthCommand( const std::wstring &app, const std::wstring &cmd )
{
	HINSTANCE hInst = ::ShellExecuteW(NULL, L"open", app.c_str(), cmd.c_str(), NULL, SW_SHOWNORMAL);
	return (int)hInst > 32;
}

bool QCommand::RestartApp(const std::wstring &cmd)
{
	wchar_t app[1024] = { 0 };
	GetModuleFileName(NULL, app, 1024);
	HINSTANCE hInst = ::ShellExecuteW(NULL, L"open", app, cmd.c_str(), NULL, SW_SHOWNORMAL);
	return (int)hInst > 32;
}