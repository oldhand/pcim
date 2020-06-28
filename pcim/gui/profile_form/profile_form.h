﻿#pragma once
#include "utils/auto_unregister.h"
#include "ui_components/msgbox/msgbox.h"
#include "services/photo_service.h"
#include "iprofile_ui.h"
namespace nim_comp
{
class ProfileBox;
class ProfileForm : public WindowEx,public IProfileUI
{
public:
	static ProfileForm *ShowProfileForm(UTF8String uid, bool is_robot = false);
	static void ShowProfileForm(UTF8String uid, bool is_robot,bool inplugin_box);
	static ProfileForm *ShowProfileForm(UTF8String tid, UTF8String uid, nim::NIMTeamUserType my_type);

private:
	ProfileForm();
	ProfileForm(UTF8String tid, UTF8String uid, nim::NIMTeamUserType my_type);
	~ProfileForm();

public:
	//覆盖虚函数
    virtual std::wstring GetSkinFolder() override;
    virtual std::wstring GetSkinFile() override;
    virtual std::wstring GetWindowClassName() const override;
    virtual std::wstring GetWindowId() const override;

	/**
	* 窗口初始化函数
	* @return void	无返回值
	*/
	virtual void InitWindow() override;
public:
	/**
	* 初始化用户信息，只能使用一次，否则会多次注册回调
	* @param[in] info 用户名片
	* @return void	无返回值
	*/
	virtual void InitUserInfo(const Db::Profile & info) override;

	/**
	* 获取所展示名片信息
	* @return Db::Profile	名片信息
	*/
	virtual Db::Profile	GetNameCard() const override;
	/**
	* 设置标题栏标题
	* @param[in] title 标题栏标题
	* @return void	无返回值
	*/
	virtual void SetTaskbarTitle(const std::wstring &title) override;
	virtual void Close(UINT nRet = 0) override;
	/**
	* 响应多端推送配置改变的回调函数
	* @param[in] switch_on 是否开启多端推送
	* @return void 无返回值
	*/
	virtual void OnMultiportPushConfigChange(bool switch_on) override;
public:
	static const LPCTSTR kClassName;
public:
	ProfileBox* contant_;
	std::string	tid_;
	std::string uid_;
	nim::NIMTeamUserType my_team_user_type_;
};
}