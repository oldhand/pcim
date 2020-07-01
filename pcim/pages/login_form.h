#pragma once

class LoginForm : public ui::WindowImplBase
{
public:
	LoginForm();
	~LoginForm();

	/**
	 * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual UINT GetClassStyle() const override;
	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void InitWindow() override;

	/**
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	static const LPCTSTR kClassName;

private:
	/**
	* �������пؼ���������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool Notify(ui::EventArgs* msg);

	/**
	* �������пؼ�������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnClicked(ui::EventArgs* msg);
	/**
	* ��Ӧȡ����¼�Ļص������ý���ؼ�Ч��
	* @return void	�޷���ֵ
	*/
	void OnCancelLogin();
	/**
	* ע��UIKIT�ص���������UIKIT���Ƶ�¼�����һЩ��Ϊ
	* @return void	�޷���ֵ
	*/
	void RegLoginManagerCallback();
	/**
	* ��Ӧ��¼����Ļص���
	* @return void	�޷���ֵ
	*/
	void OnLoginError(int error);
	/**
	* ����û��������ݣ��������Ϸ���ʼ��¼
	* @return void	�޷���ֵ
	*/
	void DoBeforeLogin();
	/**
	* ִ�е�¼����
	* @param[in] username �û�id
	* @param[in] password �û�����
	* @return void	�޷���ֵ
	*/
	void StartLogin(std::string username, std::string password);
	/**
	* �ڽ�������ʾһЩ��ʾ����
	* @return void	�޷���ֵ
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

