#pragma once

class LoginForm : public ui::WindowImplBase
{
public:
	LoginForm();
	~LoginForm();

	/**
	 * 一下三个接口是必须要覆写的接口，父类会调用这三个接口来构建窗口
	 * GetSkinFolder		接口设置你要绘制的窗口皮肤资源路径
	 * GetSkinFile			接口设置你要绘制的窗口的 xml 描述文件
	 * GetWindowClassName	接口设置窗口唯一的类名称
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual UINT GetClassStyle() const override;
	/**
	 * 收到 WM_CREATE 消息时该函数会被调用，通常做一些控件初始化的操作
	 */
	virtual void InitWindow() override;

	/**
	 * 收到 WM_CLOSE 消息时该函数会被调用
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	static const LPCTSTR kClassName;

private:
	/**
	* 处理所有控件的所有消息
	* @param[in] msg 消息的相关信息
	* @return bool true 继续传递控件消息，false 停止传递控件消息
	*/
	bool Notify(ui::EventArgs* msg);

	/**
	* 处理所有控件单击消息
	* @param[in] msg 消息的相关信息
	* @return bool true 继续传递控件消息，false 停止传递控件消息
	*/
	bool OnClicked(ui::EventArgs* msg);
	/**
	* 响应取消登录的回调，重置界面控件效果
	* @return void	无返回值
	*/
	void OnCancelLogin();
	/**
	* 注册UIKIT回调函数，让UIKIT控制登录窗体的一些行为
	* @return void	无返回值
	*/
	void RegLoginManagerCallback();
	/**
	* 响应登录结果的回调，
	* @return void	无返回值
	*/
	void OnLoginError(int error);
	/**
	* 检查用户输入内容，如果输入合法则开始登录
	* @return void	无返回值
	*/
	void DoBeforeLogin();
	/**
	* 执行登录操作
	* @param[in] username 用户id
	* @param[in] password 用户密码
	* @return void	无返回值
	*/
	void StartLogin(std::string username, std::string password);
	/**
	* 在界面上显示一些提示文字
	* @return void	无返回值
	*/
	void ShowLoginTip(std::wstring tip_text);

public:
	void OnLoginOK();

private:
	void InitLoginData();
	void OnLogin();
	void CheckAutoLogin(); 
	bool OnSwitchToLoginPage();
	bool OnSwitchToScanQrcodeLoginPage();

private:
	ui::Control*	usericon_;
	ui::Control*	passwordicon_;
	ui::RichEdit*	user_name_edit_;
	ui::RichEdit*	password_edit_;
	ui::Control*	login_ing_tip_;
	ui::Label*		login_error_tip_;
	ui::Label*		register_ok_toast_;
	ui::Button*		btn_login_;
	ui::Button*		btn_register_;
	ui::Button*		btn_cancel_;
	ui::CheckBox*	remember_pwd_ckb_ = nullptr;
	ui::CheckBox*	remember_user_ckb_ = nullptr;
	ui::CheckBox*   use_new_uistyle_;
	ui::CheckBox*   use_private_settings_;
	ui::CheckBox*   chkbox_private_use_proxy_enable_;
	ui::RichEdit*   private_settings_url_;
};

