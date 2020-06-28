#pragma once
#include "main_form_menu.h"
#include "pop_main_menu.h"
#include "ui_components/msgbox/msgbox.h"
//#include "../msglogmanage/msglog_manage_form.h"

class MainFormMenu : public nim_comp::IMainFormMenuHandler, public nbase::SupportWeakCallback
{
protected:
	virtual void OnPopupMainMenu(POINT point) override;
private:
	/**
	* ����鿴��־Ŀ¼�˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool LookLogMenuItemClick(ui::EventArgs* param);

	/**
	* �����ҵ��ֻ��˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool MobilePhoneMenuItemClick(ui::EventArgs* param);

	/**
	* ����ˢ��ͨѶ¼�˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool AddressMenuItemClick(ui::EventArgs* param);

	/**
	* �����������¼�˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool ExportMsglogToLocal();

	/**
	* �����������¼�˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool ImportMsglogFromLocal();

	/**
	* ����������������¼�˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool ClearChatRecordMenuItemClick(bool del_session, ui::EventArgs* param);

	/**
	* ������ռ�¼�˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	//bool ClearChatRecordBySessionTypeMenuItemClick(bool del_session, nim::NIMSessionType type, ui::EventArgs* param);

	/**
	* ��������Ƶ���ò˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool VChatSettingMenuItemClick(ui::EventArgs* param);

	/**
	* ����װ�طŲ˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool RtsReplayMenuItemClick(ui::EventArgs* param);

	/**
	* ��������DPI�˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool AdaptDpiMenuItemClick(ui::EventArgs* param);

	/**
	* ��ʾ������Ϣ�����صĶ����˵�
	* @param[in] msg ��Ϣ�����Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	//bool ShowMigrateMsglogMenu(ui::EventArgs* param, nim::LogsBackupRemoteOperate migrate_msglog_option);

	/**
	* ��ʾ������Ϣ�����صĶ����˵�
	* @param[in] msg ��Ϣ�����Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool ShowImportMsglogMenu(ui::EventArgs* param);

	/**
	* �رյ���򵼳���Ϣ�Ķ����˵�
	* @param[in] msg ��Ϣ�������Ϣ
	* @param[in] check_mouse true: ��鵽����������б��ϾͲ��رգ�false����������λ�ã�ֱ�ӹر�
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool CloseMigrateMsglogMenu(ui::EventArgs* param, bool check_mouse);

	/**
	* ��������
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	//bool OnMigrateMsglog(ui::EventArgs* param, nim::LogsBackupRemoteOperate option, MigrateMsglogTarget target);

	/**
	* ��ʾ�����б�
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool ShowLanguageList(ui::EventArgs* param);

	/**
	* �ر������б�
	* @param[in] msg ��Ϣ�������Ϣ
	* @param[in] check_mouse true: ��鵽����������б��ϾͲ��رգ�false����������λ�ã�ֱ�ӹر�
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool CloseLanguageList(ui::EventArgs* param, bool check_mouse);

	/**
	* ѡ������
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnSelectLanguage(ui::EventArgs* param);

	/**
	* ѡ�����ԵĻص�
	* @param[in] ret ѡ��İ�ť
	* @return void �޷���ֵ
	*/
	void OnSelectLanguageCallback(nim_comp::MsgBoxRet ret, const std::string& language);

	/**
	* ������ڲ˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool AboutMenuItemClick(ui::EventArgs* param);

	/**
	* ����ע���˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool LogoffMenuItemClick(ui::EventArgs* param);

	/**
	* �����˳��˵���ĵ�����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool QuitMenuItemClick(ui::EventArgs* param);

	/**
	* ���˵��ر�ʱ�ر����ж����˵�
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool CloseAllSubmenu(ui::EventArgs* param);

	/**
	* ���ٶ����˵�
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool DestroySubmenu(const std::wstring& menu_name, bool check_mouse = true);
};