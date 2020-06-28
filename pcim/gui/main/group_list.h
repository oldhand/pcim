#pragma once

#include "utils/list_item_util.h"
#include "plugins/team/nim_team_helper.h"
#include "services/photo_service.h"
namespace nim_comp
{
/** @class GroupList
  * @brief ���ڲ�ѯ�ͱ���Ⱥ�б�
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author towik
  * @date 2015/1/1
  */
class GroupList : public nbase::SupportWeakCallback
{
public:
	/**
	* ���캯��
	* @param[in] group_list ��Ϊ�����б��TreeView�ؼ�ָ��
	*/
	GroupList(ui::TreeView* group_list);
	virtual ~GroupList();

	/**
	* ��ȡ��Ϊ�����б��TreeView�ؼ�ָ��
	* @return ui::TreeView*	��Ϊ�����б��TreeView�ؼ�ָ��
	*/
	ui::TreeView* GetGroupList() { return group_list_; }
private:

	/**
	* ���һ��Ⱥ���б���
	* @param[in] team_info Ⱥ����Ϣ
	* @return void	�޷���ֵ
	*/
	void AddListItem(const nim::TeamInfo& team_info);

	/**
	* ���һ��Ⱥ���б��ָ���ķ�����
	* @param[in] accid �û�id
	* @param[in] tree_node ����ؼ�ָ��
	* @return void	�޷���ֵ
	*/
	void AddListItemInGroup(const nim::TeamInfo& team_info, ui::TreeNode* tree_node);

	/**
	* ��Ӧ��ѯ����Ⱥ��Ϣ�Ļص�����
	* @param[in] team_count Ⱥ������
	* @param[in] team_info_list Ⱥ����Ϣ�б�
	* @return void �޷���ֵ
	*/
	void OnQueryAllMyTeams(int team_count, const std::list<nim::TeamInfo>& team_info_list);

	/**
	* ��Ӧ���Ⱥ�Ļص�����
	* @param[in] tid Ⱥ��id
	* @param[in] tname Ⱥ������
	* @param[in] type Ⱥ������
	* @return void �޷���ֵ
	*/
	void OnAddTeam(const std::string& tid, const std::string& tname, nim::NIMTeamType type);
	
	/**
	* ��Ӧ�Ƴ�Ⱥ�Ļص�����
	* @param[in] tid Ⱥ��id
	* @return void �޷���ֵ
	*/
	void OnRemoveTeam(const std::string& tid);

	/**
	* ��ӦȺ���Ƹı�Ļص�����
	* @param[in] team_info Ⱥ����Ϣ
	* @return void �޷���ֵ
	*/
	void OnTeamNameChanged(const nim::TeamInfo& team_info);

	/**
	* ��Ӧ�û�ͷ��ı�Ļص�����
	* @param[in] type ͷ������
	* @param[in] accid �û�id
	* @param[in] photo_path ͷ��·��
	* @return void �޷���ֵ
	*/
	void OnUserPhotoReady(PhotoType type, const std::string& accid, const std::wstring &photo_path);

	bool OnReturnEventsClick(ui::EventArgs* param);

	/**
	* ������ѿؼ�ͷ�񵥻���Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnHeadImageClick(const std::string& uid, ui::EventArgs*);

	bool OnCreateTeamItemSelected(ui::EventArgs* param);
	bool OnCreateGroupItemSelected(ui::EventArgs* param);
	bool OnSearchItemSelected(ui::EventArgs* param);
private:
	ui::TreeView* group_list_;
	vector<ui::TreeNode*> tree_node_ver_;

	AutoUnregister unregister_cb;
};
}