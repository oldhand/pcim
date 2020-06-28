#include "stdafx.h"
#include "gui/main/group_list.h"
#include "utils/tool.h"
#include "pages/control/friend_item.h"
//#include "gui/main/control/session_item.h"
//#include "module/service/team_service.h"
//#include "module/session/session_manager.h"
#include "gui/profile_form/profile_form.h"
#include "gui/runtime_data/runtime_data_manager.h"
//#include "gui\contact_select_form\contact_select_form.h"
//#include "gui\team_info\team_search.h"
//#include "callback\team\team_callback.h"
using namespace ui;

namespace nim_comp
{
GroupList::GroupList(ui::TreeView* group_list) :
	group_list_(group_list)
{
	//auto add_team_cb = nbase::Bind(&GroupList::OnAddTeam, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	//unregister_cb.Add(TeamService::GetInstance()->RegAddTeam(add_team_cb));
	//auto remove_team_cb = nbase::Bind(&GroupList::OnRemoveTeam, this, std::placeholders::_1);
	//unregister_cb.Add(TeamService::GetInstance()->RegRemoveTeam(remove_team_cb));
	//auto change_team_name_cb = nbase::Bind(&GroupList::OnTeamNameChanged, this, std::placeholders::_1);
	//unregister_cb.Add(TeamService::GetInstance()->RegChangeTeamName(change_team_name_cb));
	//auto photo_ready_cb = nbase::Bind(&GroupList::OnUserPhotoReady, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	//unregister_cb.Add(PhotoService::GetInstance()->RegPhotoReady(photo_ready_cb));

	//nim::Team::QueryAllMyTeamsInfoAsync(nbase::Bind(&GroupList::OnQueryAllMyTeams, this, std::placeholders::_1, std::placeholders::_2));

	//��Ӵ���������Ⱥ��listitem��λ���б��ͷλ��
	ui::TreeNode* create_group_item = (ui::TreeNode*)ui::GlobalManager::CreateBox(L"main/main_create_normal_group_list_item.xml");
	group_list_->GetRootNode()->AddChildNodeAt(create_group_item, 0);

	ui::TreeNode* create_advanced_group_item = (ui::TreeNode*)ui::GlobalManager::CreateBox(L"main/main_create_advanced_group_list_item.xml");
	group_list_->GetRootNode()->AddChildNodeAt(create_advanced_group_item, 1);

	ui::TreeNode* search_group_item = (ui::TreeNode*)ui::GlobalManager::CreateBox(L"main/main_search_group_list_item.xml");
	group_list_->GetRootNode()->AddChildNodeAt(search_group_item, 2);

	//��ʼ��������
	ui::TreeNode* tree_node;
	tree_node = ListItemUtil::CreateFirstLetterListItem(ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_MAINWINDOW_ADVANCED_TEAM"));
	group_list_->GetRootNode()->AddChildNode(tree_node);
	tree_node_ver_.push_back(tree_node);
	tree_node->SetVisible(false);
	tree_node->SetEnabled(false);

	tree_node = ListItemUtil::CreateFirstLetterListItem(ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_MAINWINDOW_NORMAL_TEAM"));
	group_list_->GetRootNode()->AddChildNode(tree_node);
	tree_node_ver_.push_back(tree_node);
	tree_node->SetVisible(false);
	tree_node->SetEnabled(false);

	group_list_->AttachBubbledEvent(kEventReturn, nbase::Bind(&GroupList::OnReturnEventsClick, this, std::placeholders::_1));

	if (RunTimeDataManager::GetInstance()->GetUIStyle() == UIStyle::join)
	{
		create_group_item->AttachSelect(nbase::Bind(&GroupList::OnCreateGroupItemSelected, this, std::placeholders::_1));
		create_advanced_group_item->AttachSelect(nbase::Bind(&GroupList::OnCreateTeamItemSelected, this, std::placeholders::_1));
		search_group_item->AttachSelect(nbase::Bind(&GroupList::OnSearchItemSelected, this, std::placeholders::_1));
	}
}

bool GroupList::OnReturnEventsClick(ui::EventArgs* param)
{
	if (param->Type == kEventReturn)
	{
		FriendItem* item = dynamic_cast<FriendItem*>(param->pSender);
		assert(item);
		if (item)
		{
			//SessionManager::GetInstance()->OpenSessionBox(item->GetUTF8DataID(), nim::kNIMSessionTypeTeam);
		}
	}

	return true;
}

void GroupList::OnQueryAllMyTeams(int team_count, const std::list<nim::TeamInfo>& team_info_list)
{
	for (auto it = team_info_list.begin(); it != team_info_list.end(); it++)
	{
		if (it->IsValid() && it->IsMemberValid())
			AddListItem(*it);
	}

	// ������ѯ�Լ���ÿ��Ⱥ��ĳ�Ա��Ϣ
	/*if (!team_info_list.empty())
		SessionManager::GetInstance()->QueryMyAllTeamMemberInfos();*/
}

GroupList::~GroupList()
{

}

void GroupList::AddListItem(const nim::TeamInfo& team_info)
{
	ui::TreeNode* tree_node;
	if (team_info.GetType() == nim::kNIMTeamTypeAdvanced)
	{
		tree_node = tree_node_ver_[0];
	}
	else
	{
		tree_node = tree_node_ver_[1];
	}
	AddListItemInGroup(team_info, tree_node);
}

bool GroupList::OnHeadImageClick(const std::string& uid, ui::EventArgs*)
{
	/*auto team_info = nim::Team::QueryTeamInfoBlock(uid);
	TeamInfoForm::ShowTeamInfoForm(false, team_info.GetType(), uid, team_info);*/
	return true;
}

void GroupList::AddListItemInGroup(const nim::TeamInfo& team_info, ui::TreeNode* tree_node)
{
	if (tree_node->GetChildNodeCount() == 0)
	{
		tree_node->SetVisible(true);
	}

	FriendItem* item = new FriendItem;
	ui::GlobalManager::FillBoxWithCache( item, L"main/friend_item.xml" );
	item->Init(kFriendItemTypeTeam, team_info.GetTeamID());
	ui::ButtonBox* head_image = (ui::ButtonBox*)(item->FindSubControl(L"head_image"));
	if (RunTimeDataManager::GetInstance()->GetUIStyle() == UIStyle::join)
	{
		auto tid = team_info.GetTeamID();
		head_image->SetMouseEnabled(false);
		item->AttachSelect([tid](ui::EventArgs* param){
			/*auto team_info = nim::Team::QueryTeamInfoBlock(tid);
			TeamInfoForm::ShowTeamInfoForm(false, team_info.GetType(), team_info.GetTeamID(), team_info,true);*/
			return true;
		});
	}		
	else
	{
		head_image->AttachClick(nbase::Bind(&GroupList::OnHeadImageClick, this, team_info.GetTeamID(), std::placeholders::_1));
	}
	
	//tree_node->AddChildNode(item);
	FriendItem* container_element = item;
	std::size_t index = 0;
	for (index = 0; index < tree_node->GetChildNodeCount(); index++)
	{
		FriendItem* temp = (FriendItem*)tree_node->GetChildNode(index);
		if (*container_element == *temp)
		{
			//delete item;
			//ASSERT(FALSE);
			return;
		}
		if (*container_element < *temp)
		{
			tree_node->AddChildNodeAt(container_element, index);
			break;
		}
	}

	if (index == tree_node->GetChildNodeCount())
	{
		tree_node->AddChildNodeAt(container_element, index);
	}
}

void GroupList::OnAddTeam(const std::string& tid, const std::string& tname, nim::NIMTeamType type)
{
	OnRemoveTeam(tid);
	nim::TeamInfo user_info;
	user_info.SetTeamID(tid);
	user_info.SetName(tname);
	user_info.SetType(type);
	AddListItem(user_info);
}

void GroupList::OnRemoveTeam(const std::string& tid)
{
	for (int i = 0; i < group_list_->GetCount(); i++)
	{
		FriendItem* friend_item = dynamic_cast<FriendItem*>(group_list_->GetItemAt(i));
		if (friend_item)
		{
			if (friend_item->GetId() == tid)
			{
				friend_item->GetParentNode()->RemoveChildNode(friend_item);
				break;
			}
		}
	}
}

void GroupList::OnTeamNameChanged(const nim::TeamInfo& team_info)
{
	for (int i = 0; i < group_list_->GetCount(); i++)
	{
		FriendItem* friend_item = dynamic_cast<FriendItem*>(group_list_->GetItemAt(i));
		if (friend_item)
		{
			if (friend_item->GetId() == team_info.GetTeamID())
			{
				//friend_item->OnTeamNameChange(team_info);
				break;
			}
		}
	}
}

//void GroupList::OnUserPhotoReady(PhotoType type, const std::string& accid, const std::wstring &photo_path)
//{
//	if (type == kTeam)
//	{
//		FriendItem* friend_item = (FriendItem*)group_list_->FindSubControl(nbase::UTF8ToUTF16(accid));
//		if (friend_item)
//		{
//			if (friend_item->GetId() == accid)
//				friend_item->FindSubControl(L"head_image")->SetBkImage(photo_path);
//		}
//	}
//}
bool GroupList::OnCreateTeamItemSelected(ui::EventArgs* param)
{
	//std::wstring caption = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRING_INVITEUSERFORM_INVITE_JOINCHAT");
	//nim_comp::TeamInfoForm* team_info_form = (nim_comp::TeamInfoForm*)nim_comp::WindowsManager::GetInstance()->GetWindow\
	//	(nim_comp::TeamInfoForm::kClassName, nim_comp::TeamInfoForm::kTeamInfoWindowId);
	//if (team_info_form == NULL)
	//{
	//	team_info_form = new nim_comp::TeamInfoForm(true, nim::kNIMTeamTypeAdvanced, "", nim::TeamInfo());
	//	team_info_form->Create(NULL, caption.c_str(), WS_OVERLAPPEDWINDOW& ~WS_MAXIMIZEBOX, 0L);
	//	team_info_form->CenterWindow();
	//	team_info_form->ShowWindow(true);
	//}
	//else
	//{
	//	team_info_form->ActiveWindow();
	//}
	return true;
}
bool GroupList::OnCreateGroupItemSelected(ui::EventArgs* param)
{
	/*nim_comp::ContactSelectForm *contact_select_form = (nim_comp::ContactSelectForm *)nim_comp::WindowsManager::GetInstance()->GetWindow\
		(nim_comp::ContactSelectForm::kClassName, nbase::UTF8ToUTF16(nim_comp::ContactSelectForm::kCreateGroup));

	if (!contact_select_form)
	{
		auto cb = ToWeakCallback([this](const std::list<std::string> &friend_list, const std::list<std::string> &team_list)
		{
			if (friend_list.empty())
			{
				ShowMsgBox(group_list_->GetWindow()->GetHWND(), MsgboxCallback(), L"STRID_MAINWINDOW_PLEASE_INVITE_FRIEND");
				return;
			}

			UTF16String user_names;
			auto it = friend_list.cbegin();
			for (int i = 0; it != friend_list.cend() && i < 2; it++, i++)
				user_names += nim_comp::UserService::GetInstance()->GetUserName(*it, false) + L";";
			user_names += nim_comp::UserService::GetInstance()->GetUserName(it == friend_list.end() ? nim_comp::LoginManager::GetInstance()->GetAccount() : *it, false);

			nim::TeamInfo tinfo;
			tinfo.SetType(nim::kNIMTeamTypeNormal);
			tinfo.SetName(nbase::UTF16ToUTF8(user_names));
			nim::Team::CreateTeamAsync(tinfo, friend_list, "", nbase::Bind(&nim_comp::TeamCallback::OnTeamEventCallback, std::placeholders::_1));
		});
		contact_select_form = new nim_comp::ContactSelectForm(nim_comp::ContactSelectForm::kCreateGroup, std::list<UTF8String>(), cb);
		contact_select_form->Create(NULL, L"", UI_WNDSTYLE_FRAME& ~WS_MAXIMIZEBOX, 0L);
		contact_select_form->CenterWindow();
	}
	else
	{
		contact_select_form->ActiveWindow();
	}*/
	return true;
}
bool GroupList::OnSearchItemSelected(ui::EventArgs* param)
{
	//nim_comp::WindowsManager::GetInstance()->SingletonShow<nim_comp::TeamSearchForm>(nim_comp::TeamSearchForm::kClassName);
	return true;
}
}