#pragma once
#include "ui_components/windows_manager/window_ex.h"
#include "at_list_item.h"
#include "plugins/team/nim_team_helper.h"
#include "services/photo_service.h"
#include "services/user_service.h"
#include "services/team_service.h"

typedef std::function<void(const std::string& uid)> OnSelectAtItem;

namespace nim_comp
{
/** @class AtlistForm
  * @brief @�б���
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/9/6
  */
class AtListItem;
class AtlistForm : public WindowEx
{
public:
	/**
	* ���캯��
	* @param[in] session_id �ỰID
	* @param[in] session_type �Ự����
	* @param[in] cb ĳ�ѡ�еĻص�����
	* @return void	�޷���ֵ
	*/
	AtlistForm(std::string session_id, nim::NIMSessionType session_type, OnSelectAtItem cb);
	virtual ~AtlistForm();

	//�����麯��
    virtual std::wstring GetSkinFolder() override;
    virtual std::wstring GetSkinFile() override;
    virtual std::wstring GetWindowClassName() const override;
    virtual std::wstring GetWindowId() const override;
	virtual void ShowWindow(bool bShow = true, bool bTakeFocus = true) override;
	/**
	* ���ڳ�ʼ������
	* @return void	�޷���ֵ
	*/
	virtual void InitWindow() override;
   
	/**
	* Ϊ@�б��ʼ��Ⱥ��Ա��Ϣ
	* @param[in] team_member_info_list Ⱥ��Ա��Ϣ��
	* @return void �޷���ֵ
	*/
	void InitTeamMembers(const std::map<std::string, nim::TeamMemberProperty>& team_member_info_list);

	/**
	* ���ݹؼ���ȥ��ʾ������@�б���
	* @param[in] search_key �ؼ���
	* @param[in] match_visible true ֻ�����б����Ѿ���ʾ����Ŀ����ƥ��ؼ�������ʱʹ�ã�,false ���±���������Ŀ����ƥ��Ĺؼ��ּ���ʱʹ�ã�
	* @return bool true ƥ��ɹ���false ƥ��ʧ��
	*/
	bool Match(const std::wstring& search_key, bool match_visible);

	/**
	* ����@�����ɾ����ֻʣ����һ��@��������ʾ���е��б���
	* @param[in] last_five ���5��������
	* @return void	�޷���ֵ
	*/
	void ShowMemberItems(std::list<std::string> &last_five);

	/**
	* ����@�б���ʾ��λ�ã�ͬʱ������ʾ��ˢ��@�б�Ĺ���
	* @param[in] pt ��ʾ����
	* @return void	�޷���ֵ
	*/
	void SetShowPos(POINT pt);

	/**
	* �Ự�����յ��˼��̺������Ϣ��ת��AtListForm�������Enter����Ϣ
	* @return bool true �Ѵ���false û�д���
	*/
	bool HandleKeyEnter();

	/**
	* �Ự�����յ��˼��̺������Ϣ��ת��AtListForm�������Down����Ϣ
	* @return bool true �Ѵ���false û�д���
	*/
	bool HandleKeyDown();

	/**
	* �Ự�����յ��˼��̺������Ϣ��ת��AtListForm�������Up����Ϣ
	* @return bool true �Ѵ���false û�д���
	*/
	bool HandleKeyUp();

	/**
	* �Ự�����յ��˼��̺������Ϣ��ת��AtListForm���������������Ϣ
	* @param[in] is_up �Ƿ����Ϲ���
	* @return bool true �Ѵ���false û�д���
	*/
	bool HandleMouseWheel(bool is_up);

	/**
	* ֱ�����ٴ���
	* @return void	�޷���ֵ
	*/
	void CloseForm();

private:
	/**
	* ���ز������ڹر���Ϣ�������Զ����أ�����CloseForm����ֱ�����ٴ���
	* @param[in] bHandled �Ƿ�������Ϣ��Ϊtrue�򲻼�������
	* @return LRESULT ������
	*/
	virtual LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;

	/**
	* ����һ���б���ؼ�
	* @param[in] uid �û�id
	* @param[in] is_last_five �Ƿ�Ϊ���������
	* @return AtListItem* �б���ؼ�
	*/
	AtListItem* CreateAtListItem(const std::string& uid, bool is_last_five);

	/**
	* ���һ���б���ؼ����б�
	* @param[in] uid �û�id
	* @param[in] index ����λ�ã�-1������뵽ĩβ
	* @param[in] is_last_five �Ƿ�Ϊ���������
	* @return AtListItem* �б���ؼ�
	*/
	AtListItem* AddListItem(const std::string& uid, int index, bool is_last_five);

	/**
	* �Ƴ�һ���б���ؼ�
	* @param[in] uid �û�id
	* @return void	�޷���ֵ
	*/
	void RemoveListItem(const std::string& uid);

	/**
	* ˢ��ĳ���б����ͷ����ʾ
	* @param[in] uid �û�id
	* @param[in] photo_path ͷ��·��
	* @return void	�޷���ֵ
	*/
	void CheckListItemHeadIcon(const std::string& uid, const std::wstring& photo_path);

	/**
	* ɾ�����������
	* @return void	�޷���ֵ
	*/
	void RemoveLastFiveSender();

	/**
	* �����5�������������
	* @param[in] uid �û�id
	* @return AtListItem* �б���ؼ�
	*/
	AtListItem* FindInLastFiveSender(const std::wstring& uid);

private:
	/**
	* ��ȡȺ�ǳ�
	* @param[in] uid �û�id
	* @return std::wstring	Ⱥ�ǳ�
	*/
	std::wstring GetTeamCardName(const std::string& uid);

	/**
	* ��ȡʵ����ʾ������
	* @param[in] uid �û�id
	* @return std::wstring	����
	*/
	std::wstring GetShowName(const std::string& uid);

	/**
	* �������пؼ���ѡ����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnSelectItem(ui::EventArgs *param);
private:
	/**
	* ��Ӧ�û�ͷ��ı�Ļص�����
	* @param[in] type ͷ������
	* @param[in] accid �û�id
	* @param[in] photo_path ͷ��·��
	* @return void	�޷���ֵ
	*/
	void OnUserPhotoChange(PhotoType type, const std::string& accid, const std::wstring &photo_path);

	/**
	* ��Ӧ�û���Ϣ�ı�Ļص�����
	* @param[in] uinfos �û���Ϣ�б�
	* @return void	�޷���ֵ
	*/
	void OnUserInfoChange(const std::list<Db::Profile> &uinfos);

	/**
	* ��Ӧ���Ѹı�Ļص�����
	* @param[in] change_type ���Ѹı�����
	* @param[in] accid �û�id
	* @return void	�޷���ֵ
	*/
	void OnFriendInfoChange(FriendChangeType change_type, const std::string& accid);

	/**
	* ��ӦȺ��Ա�ǳƸı�Ļص�����
	* @param[in] tid_uid ����Ⱥ��id���û�id���ַ���
	* @param[in] team_card Ⱥ�ǳ�
	* @return void	�޷���ֵ
	*/
	void OnTeamCardChange(const std::string& tid_uid, const std::string& team_card);

	/**
	* ��ӦȺ��Ա���ӵĻص�����
	* @param[in] tid Ⱥ��id
	* @param[in] team_member_info Ⱥ��Ա��Ϣ
	* @return void	�޷���ֵ
	*/
	void OnTeamMemberAdd(const std::string& tid, const nim::TeamMemberProperty& team_member_info);

	/**
	* ��ӦȺ��Ա���ٵĻص�����
	* @param[in] tid Ⱥ��id
	* @param[in] uid �û�id
	* @return void	�޷���ֵ
	*/
	void OnTeamMemberRemove(const std::string& tid, const std::string& uid);

public:
    static const LPCTSTR kClassName;

private:
    std::string	session_id_;
	nim::NIMSessionType session_type_;

	std::map<std::string, nim::TeamMemberProperty> team_member_info_list_;
	ui::ListBox				*robot_members_container_ = nullptr;
	ui::ListBox				*team_members_container_ = nullptr;

	std::list<std::string>	uid_last_five_;	//�������Ϣ��5���ˣ��������Լ���,���·��Ե����б����

	OnSelectAtItem			callback_select_;//ѡ��ĳ���Ļص�����
	AutoUnregister	unregister_cb;
};
}