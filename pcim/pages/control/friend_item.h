#pragma once

#include "utils/list_item_util.h"
#include "utils/pin_yin_helper.h"
#include "plugins/contact/nim_user_helper.h"
//#include "gui/subscribe_event/subscribe_event_manager.h"

namespace nim_comp
{
/** @class FriendItem
  * @brief �����б����UI��
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author towik
  * @date 2015/1/1
  */
class FriendItem : public ui::TreeNode
{
public:
	FriendItem();
	virtual ~FriendItem();

	/**
	* ��ʼ���ؼ�
	* @param[in] type ����
	* @param[in] accid �û�id����Ⱥ��id
	* @return void	�޷���ֵ
	*/
	virtual void Init(FriendItemType type, const std::string &accid);

	/**
	* ��ѯ����
	* @return FriendItemType
	*/
	FriendItemType GetFriendItemType() const { return type_; }

	/**
	* ��ȡ�û�id����Ⱥ��id
	* @return string �û�id����Ⱥ��id
	*/
	std::string GetId()	{ return id_; }

	/**
	* ��ȡ�û�������Ⱥ����
	* @return string �û�id����Ⱥ��id
	*/
	std::wstring GetNickName() { return nick_name_; }

	/**
	* ���ǳơ��û�������Ϣƥ�������ؼ���
	* @param[in] search_key �ؼ���
	* @return bool true ƥ��ɹ���false ƥ��ʧ��
	*/
	bool Match(const UTF8String& search_key);

	/**
	* ���ú�������״̬
	* @param[in] EventDataEx �¼�����
	* @return void	�޷���ֵ
	*/
	//void SetOnlineState(const EventDataEx& data);

	/**
	* ����һ��������ؼ����бȽϣ������ǳ��жϴ�С
	* @param[in] elment2 ������ؼ�
	* @return bool true �ǳ�����һ���ؼ�֮ǰ��false �ǳ�����һ���ؼ�֮��
	*/
	bool operator < (const FriendItem& elment2) const
	{
		static DWORD lcid = MAKELCID(MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRCP);
		return ::CompareString(lcid, 0, this->nick_name_.c_str(), (int)this->nick_name_.length(), elment2.nick_name_.c_str(),(int)elment2.nick_name_.length()) == 1;
	}

	/**
	* �ж�����һ��������ؼ�id�Ƿ�һ��
	* @param[in] elment2 ������ؼ�
	* @return bool true һ����false ��һ��
	*/
	bool operator == (const FriendItem& elment2) const 
	{
		return this->id_ == elment2.id_;
	}

	/**
	* ������ѿؼ�˫����Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnDbClicked(ui::EventArgs* arg);

	/**
	* ��ӦȺ���Ƹı�Ļص�����
	* @param[in] team_info Ⱥ��Ϣ
	* @return void �޷���ֵ
	*/
	//void OnTeamNameChange(const nim::TeamInfo& team_info);

private:
	ui::Label*		label_online_state_;
	ui::Label*		contact_;

	FriendItemType	type_;
	std::string		id_;

	std::wstring	nick_name_;
	UTF8String		nick_name_full_spell_;
	UTF8String		nick_name_simple_spell_;

	AutoUnregister unregister_cb;
};
}