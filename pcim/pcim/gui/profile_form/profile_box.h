#pragma once
#include "iprofile_ui.h"
#include "services/photo_service.h"
#include "services/user_service.h"

namespace nim_comp
{
class ProfileForm;
class ProfileBox : public ui::VBox,  public IProfileUI
{
	friend class ProfileForm;
public:
	ProfileBox();
	ProfileBox(UTF8String tid, UTF8String uid, nim::NIMTeamUserType my_type);
	~ProfileBox();
public:
	/**
	* ��Ӧ����������øı�Ļص�����
	* @param[in] switch_on �Ƿ����������
	* @return void �޷���ֵ
	*/
	virtual void OnMultiportPushConfigChange(bool switch_on) override;
	virtual void DoInit() override;
	/**
	* ��ʼ���û���Ϣ��ֻ��ʹ��һ�Σ��������ע��ص�
	* @param[in] info �û���Ƭ
	* @return void	�޷���ֵ
	*/
	virtual void InitUserInfo(const Db::Profile & info) override;
	/**
	* ��ȡ��չʾ��Ƭ��Ϣ
	* @return Db::Profile	��Ƭ��Ϣ
	*/
	virtual Db::Profile	GetNameCard() const override;
	/**
	* ���ñ���������
	* @param[in] title ����������
	* @return void	�޷���ֵ
	*/
	virtual void SetTaskbarTitle(const std::wstring &title) override;
	virtual void Close(UINT nRet = 0) override;
	void AttachSetTaskbarTitle(const std::function<void(const std::wstring&)>& cb);
	void AttachClose(const std::function<void(UINT)>& cb);
private:
	/**
	* �������пؼ���������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool Notify(ui::EventArgs* msg);

	/**
	* ������ʹ򿪣����������ʱ�ƶ��˲������ͣ�
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnMultiPushSwitchSelected(ui::EventArgs* args);

	/**
	* ������͹رգ����������ʱ�ƶ��������ͣ�
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnMultiPushSwitchUnSelected(ui::EventArgs* args);

	/**
	* WebRTC��
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnWebRtcSelected(ui::EventArgs* args);

	/**
	* WebRTC�ر�
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnWebRtcUnSelected(ui::EventArgs* args);

	/**
	* ��Ϣ���Ѵ򿪣����ո��û�����Ϣ��
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnNotifySwitchSelected(ui::EventArgs* args);

	/**
	* ��Ϣ���ѹرգ����θ��û�����Ϣ��
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnNotifySwitchUnSelected(ui::EventArgs* args);

	/**
	* ������ѡ��򿪣������û������������
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBlackSwitchSelected(ui::EventArgs* args);

	/**
	* ������ѡ��رգ������û��Ӻ������Ƴ���
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBlackSwitchUnSelected(ui::EventArgs* args);

	/**
	* ���ý���ѡ��򿪣������û��������״̬��
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnMuteSwitchSelected(ui::EventArgs* args);

	/**
	* ���ý���ѡ��رգ������û��ӽ���״̬�н������
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnMuteSwitchUnSelected(ui::EventArgs* args);
	void OnNotifyChangeCallback(std::string id, bool mute);
	void OnBlackChangeCallback(std::string id, bool black);

	/**
	* �������찴ť���������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnStartChatBtnClicked(ui::EventArgs* args);

	/**
	* ����ɾ�����Ѱ�ť���������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnDeleteFriendBtnClicked(ui::EventArgs* args);

	/**
	* ����ȷ��ɾ�����ѵ���ʾ�򷵻صĻص����
	* @param[in] ret ��ʾ��ķ���ֵ
	* @return void �޷���ֵ
	*/
	void OnDeleteFriendMsgBox(MsgBoxRet ret);

	/**
	* ������Ӻ��Ѱ�ť���������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnAddFriendBtnClicked(ui::EventArgs* args);

	/**
	* �����������յ���Ͽ��ѡ����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBirthdayComboSelect(ui::EventArgs* args);

	/**
	* ����༭��Ϣ��ȡ���༭��ť���������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnModifyOrCancelBtnClicked(ui::EventArgs* args, bool to_modify);

	/**
	* ������༭��Ϣ��ť���������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnSaveInfoBtnClicked(ui::EventArgs* args);

	/**
	* ����ע���༭���ý�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnAliasEditGetFocus(ui::EventArgs* args);

	/**
	* ����ע���༭��ʧȥ������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnAliasEditLoseFocus(ui::EventArgs* args);

	/**
	* ���������뱸ע���༭����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnAliasEditMouseEnter(ui::EventArgs* args);

	/**
	* ��������뿪��ע���༭����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnAliasEditMouseLeave(ui::EventArgs* args);

	/**
	* ����ע���༭��س���Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnReturnOnAliasEdit(ui::EventArgs* args);	

	/**
	* ����Ƭ�󣬳�ʼ��������ʾ��Ϣ
	* @return void	�޷���ֵ
	*/
	void InitLabels();

	/**
	* �����ǳơ���ע����
	* @return void	�޷���ֵ
	*/
	void SetShowName();

	/**
	* ����༭��ť֮�󣬳�ʼ��������������ı������
	* @return void	�޷���ֵ
	*/
	void InitEdits();

	/**
	* ��ʼ������������
	* @return void	�޷���ֵ
	*/
	void InitBirthdayCombo();

	/**
	* �����û��Ƿ����Լ��ľ����б�ͺ�������
	* @return void	�޷���ֵ
	*/
	void CheckInMuteBlack();

	/**
	* ��Ӧ�����б�ı�Ļص�����
	* @param[in] change_type ���ѱ仯����
	* @param[in] accid �û�id
	* @return void �޷���ֵ
	*/
	void OnFriendListChange(FriendChangeType change_type, const std::string& accid);

	/**
	* ��Ӧ�û���Ϣ�ı�Ļص�����
	* @param[in] uinfos �û���Ϣ�б�
	* @return void �޷���ֵ
	*/
	void OnUserInfoChange(const std::list<Db::Profile> &uinfos);

	/**
	* ��Ӧ�û�ͷ��ı�Ļص�����
	* @param[in] type ͷ������
	* @param[in] account �û�id
	* @param[in] photo_path ͷ��·��
	* @return void �޷���ֵ
	*/
	void OnUserPhotoReady(PhotoType type, const std::string& account, const std::wstring& photo_path);

	/**
	* ��Ӧ�����û���Ϣ�ı�Ļص�����
	* @param[in] uinfos �û���Ϣ�б�
	* @return void �޷���ֵ
	*/
	void OnMiscUInfoChange(const std::list<Db::Profile> &uinfos);

	/**
	* �����Լ���Ƭ��ͷ�񱻵������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnHeadImageClicked(ui::EventArgs* args);
private:
	/**
	* ����ͷ���޸���Ϻ�Ļص�����
	* @param[in] id �û�id
	* @param[in] url ͷ������ص�ַ
	* @return void	�޷���ֵ
	*/
	void OnModifyHeaderComplete(const std::string& id, const std::string &url);

	/**
	* ����ͷ�������Ϻ�Ļص�����
	* @param[in] res ������
	* @return void	�޷���ֵ
	*/
	void UpdateUInfoHeaderCallback(int res);
public:
	std::string	tid_;
	nim::NIMTeamUserType my_team_user_type_;
	bool have_mute_right_ = false;
	std::function<void(const std::wstring& title)> taskbar_title_function_;
	std::function<void(UINT nRet)> close_function_;
private:
	Db::Profile	m_uinfo;
	//nim::RobotInfo	m_robot;
	int				user_type; // -1���Լ���0��İ���ˣ�1������
	AutoUnregister	unregister_cb;

private:
	ui::Button*		head_image_btn = NULL;
	ui::Label*		show_name_label = NULL;
	ui::Label*		user_id_label = NULL;
	ui::Label*		nickname_label = NULL;

	ui::VBox*		common_info_ = NULL;
	ui::VBox*		robot_info_ = NULL;
	ui::VBox*		common_other_ = NULL;
	ui::RichEdit*	robot_intro_ = NULL;

	ui::CheckBox*	multi_push_switch = NULL;
	ui::CheckBox*	webrtc_setting_ = NULL;
	ui::CheckBox*	notify_switch = NULL;
	ui::CheckBox*	black_switch = NULL;
	ui::CheckBox*	mute_switch = NULL;
	ui::Button*		start_chat = NULL;
	ui::TabBox*		add_or_del = NULL;
	ui::Button*		delete_friend = NULL;
	ui::Button*		add_friend = NULL;

	ui::CheckBox*	sex_icon = NULL;
	ui::Button*		btn_modify_info = NULL;
	ui::Button*		btn_cancel_modify = NULL;
	ui::Button*		btn_save_modify = NULL;
	ui::HBox*		alias_box = NULL;
	ui::RichEdit*	alias_edit = NULL;
	ui::HBox*		nickname_box = NULL;
	ui::RichEdit*	nickname_edit = NULL;
	ui::Label*		nickname_error_tip = NULL;
	ui::HBox*		sex_box = NULL;
	ui::Combo*		sex_option = NULL;
	ui::Label*		birthday_label = NULL;
	ui::HBox*		birthday_combo_box = NULL;
	ui::Combo*		birth_year_combo = NULL;
	ui::Combo*		birth_month_combo = NULL;
	ui::Combo*		birth_day_combo = NULL;
	ui::Label*		phone_label = NULL;
	ui::RichEdit*	phone_edit = NULL;
	ui::Label*		email_label = NULL;
	ui::RichEdit*	email_edit = NULL;
	ui::Label*		signature_label = NULL;
	ui::RichEdit*	signature_edit = NULL;
};
}