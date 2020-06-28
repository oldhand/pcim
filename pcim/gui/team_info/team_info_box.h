#pragma once
#include "iteam_info_ui.h"
#include "services/user_service.h"
#include "services/team_service.h"
#include "ui_components/msgbox/msgbox.h"
#include "services/photo_service.h"
#include "plugins/team/nim_team_helper.h"

namespace nim_comp
{
	class TeamInfoBox : public ui::VBox,public ITeamInfoUI
	{
	public:
		TeamInfoBox() = default;
		TeamInfoBox(bool create_or_display, nim::NIMTeamType type, const std::string& team_id, const nim::TeamInfo& team_info, bool value= false);
		virtual ~TeamInfoBox();

	public:
		virtual void DoInit() override;
		bool IsCreateOrDisplay() const;
		std::wstring GetTeamID() const;
		nim::NIMTeamType GetTeamType() const;
		/**
		* ���ñ���������
		* @param[in] title ����������
		* @return void	�޷���ֵ
		*/
		virtual void SetTaskbarTitle(const std::wstring &title) override;
		virtual void Close(UINT nRet = 0) override;
		virtual void ActiveWindow() override;
		void AttachSetTaskbarTitle(const std::function<void(const std::wstring&)>& cb);
		void AttachClose(const std::function<void(UINT)>& cb);
		void AttachActive(const std::function<void()>& cb);
		/**
		* ����Ⱥ��Ա��Ϣ
		* @return void	�޷���ֵ
		*/
		virtual void UpdateTeamMember() override;
	private:
		/**
		* ��Ӧ��ȡ��Ⱥ��Ա��Ϣ�Ļص����ܻ�
		* @param[in] team_id Ⱥ��id
		* @param[in] count Ⱥ��Ա����
		* @param[in] team_member_list Ⱥ��Ա��Ϣ
		* @return void	�޷���ֵ
		*/
		void OnGetTeamMembers(const std::string& team_id, int count, const std::list<nim::TeamMemberProperty>& team_member_list);

		/**
		* ����Ⱥͷ��������Ϣ
		* @param[in] args ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnHeadImageClicked(ui::EventArgs* args);
	private:
        /**
         * ���� Option ѡ��ѡ���¼�
         * @param[in] ��������
         * @reutrn bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
         */
        bool OnClicked(ui::EventArgs* args);

		/**
		* ����ͷ���޸���Ϻ�Ļص�����
		* @param[in] id �û�id
		* @param[in] url ͷ������ص�ַ
		* @return void	�޷���ֵ
		*/
		void OnModifyHeaderComplete(const std::string& id, const std::string &url);

		/**
		* ���һ�������Ա�İ�ť��������
		* @return void	�޷���ֵ
		*/
		void AddInviteButton();

		/**
		* ���������Ա�İ�ť���������Ϣ
		* @param[in] param ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnInviteUesrBtnClick(ui::EventArgs *param);

		/**
		* ��Ӧ��Ա������ϵĻص�����
		* @param[in] friend_list ����ĺ����б�
		* @param[in] team_list ������ĵĲ���
		* @return void	�޷���ֵ
		*/
		void SelectedCompleted(const std::list<UTF8String>& friend_list, const std::list<UTF8String>& team_list, bool delete_enable);

		/**
		* ����һ��Ⱥ��Ա��ؼ�
		* @param[in] member_info Ⱥ��Ա��Ϣ
		* @return void	�޷���ֵ
		*/
		ui::HBox* CreateTeamMemberListItem(const nim::TeamMemberProperty& member_info, bool delelte_enable = false);

		/**
		* �����Լ�����ݸ��½�����ʾ��Ч��
		* @return void	�޷���ֵ
		*/
		void UpdateUIByIdentity();

		/**
		* ����Ⱥ��Աɾ����ť�ĵ�����Ϣ
		* @param[in] container_element Ⱥ��Ա�ؼ�
		* @param[in] user_id Ⱥ��Ա�û�id
		* @param[in] args ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnBtnDeleteClick(ui::Box* container_element, const UTF8String& user_id, ui::EventArgs* args);

		/**
		* ��Ӧȷ���Ƿ�ɾ������ʾ��Ļص�����
		* @param[in] user_id �û�id
		* @param[in] ret ��ʾ�򷵻�ֵ
		* @return void	�޷���ֵ
		*/
		void OnMsgbox(const UTF8String& user_id, MsgBoxRet ret);

		/**
		* ����Ⱥ��Ա������������Ϣ
		* @param[in] team_member_item Ⱥ��Ա�ؼ�
		* @param[in] args ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnTeamMemberItemMouseEnter(ui::Box* team_member_item, ui::EventArgs* args);

		/**
		* ����Ⱥ��Ա������Ƴ�����Ϣ
		* @param[in] team_member_item Ⱥ��Ա�ؼ�
		* @param[in] args ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnTeamMemberItemMouseLeave(ui::Box* team_member_item, ui::EventArgs* args);

		/**
		* ����Ⱥ��Ա�����Ϣ
		* @param[in] user_id Ⱥ��Աid
		* @param[in] args ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnBtnHeadImageClick(const UTF8String& user_id, ui::EventArgs* args);

		/**
		* ����ȷ�ϰ�ť������Ϣ
		* @param[in] param ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnBtnConfirmClick(ui::EventArgs* param);

		/**
		* ����ȡ����ť������Ϣ
		* @param[in] param ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnBtnCancelClick(ui::EventArgs* param);

		/**
		* �����ɢȺ��ť������Ϣ
		* @param[in] param ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnBtnDissmissClick(ui::EventArgs* param);

		/**
		* �����˳�Ⱥ��ť������Ϣ
		* @param[in] param ��Ϣ�������Ϣ
		* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
		*/
		bool OnBtnQuitClick(ui::EventArgs* param);

		/**
		* ��ӦȺ��Ա���ӵĻص�����
		* @param[in] tid Ⱥ��id
		* @param[in] team_member_info Ⱥ��Ա��Ϣ
		* @return void	�޷���ֵ
		*/
		void OnTeamMemberAdd(const std::string& tid, const nim::TeamMemberProperty& team_member_info);

		/**
		* ��ӦȺ��Ա�Ƴ��Ļص�����
		* @param[in] tid Ⱥ��id
		* @param[in] uid �û�id
		* @return void	�޷���ֵ
		*/
		void OnTeamMemberRemove(const std::string& tid, const std::string& uid);

		/**
		* ��ӦȺ��Ա�ǳƸı�Ļص�����
		* @param[in] tid_uid ����Ⱥ��id���û�id���ַ���
		* @param[in] team_card Ⱥ�ǳ�
		* @return void	�޷���ֵ
		*/
		void OnTeamMemberChange(const std::string& tid_uid, const std::string& team_card);

		/**
		* ��ӦȺ����Ա�ı�Ļص�����
		* @param[in] tid Ⱥ��id
		* @param[in] uid �û�id
		* @param[in] admin �Ƿ�Ϊ����Ա
		* @return void	�޷���ֵ
		*/
		void OnTeamAdminSet(const std::string& tid, const std::string& uid, bool admin);

		/**
		* ��ӦȺ���ı�Ļص�����
		* @param[in] tid Ⱥ��id
		* @param[in] uid ��Ⱥ��id
		* @return void	�޷���ֵ
		*/
		void OnTeamOwnerChange(const std::string& tid, const std::string& uid);

		/**
		* ��Ӧ�û���Ϣ�ı�Ļص�����
		* @param[in] uinfos �û���Ϣ�б�
		* @return void	�޷���ֵ
		*/
		void OnUserInfoChange(const std::list<Db::Profile>& uinfos);

		/**
		* ��Ӧ�û�ͷ��ı�Ļص�����
		* @param[in] type ͷ������
		* @param[in] tid Ⱥ��id
		* @param[in] photo_path ͷ��·��
		* @return void	�޷���ֵ
		*/
		void OnUserPhotoReady(PhotoType type, const std::string& tid, const std::wstring &photo_path);

		/**
		* ��ӦȺ�Ƴ��Ļص�����
		* @param[in] tid Ⱥ��id
		* @return void	�޷���ֵ
		*/
		void OnTeamRemove(const std::string& tid);
		/**
		* ��ӦȺ���Ƹı��¼�
		* @param[in] team_info Ⱥ��Ϣ
		* @return void	�޷���ֵ
		*/
		void OnTeamNameChange(const nim::TeamInfo& team_info);
        /**
        * ��ӦȺ����״̬�ı��¼�
        * @param[in] tid Ⱥid
        * @param[in] mute_all �Ƿ���ԣ�true Ϊ���ԣ�����Ϊ false
        * @return void	�޷���ֵ
        */
        void OnTeamMuteChange(const std::string& tid, bool mute_all);
		/**
		* �ж��Ƿ�Ϊ������ʾ��Ⱥ�б��Ⱥ��Ա����
		* @param[in] user_type Ⱥ��Ա����
		* @return bool true �ǣ�false ��
		*/
		bool IsTeamMemberType(const nim::NIMTeamUserType user_type);
        /**
        * �޸�Ⱥ����Ϣ֪ͨ״̬�ı��¼�
        * @param[in] id Ⱥ�� id
        * @param[in] bits 
        */
        void OnTeamNotificationModeChangeCallback(const std::string& id, int64_t bits);
	
		void RefreshInfo(nim::TeamInfo* team_info);
	private:
		ui::ListBox* tile_box_;
		ui::RichEdit* re_team_name_;
		ui::RichEdit* re_team_intro_;
		ui::Button* invitebtn_;
		ui::Button* btn_dismiss_;
		ui::Button* btn_quit_;
		ui::Button* btn_header_ = nullptr;

	private:
		bool create_or_display_;
		std::string tid_;
		nim::NIMTeamType type_;
		nim::TeamInfo team_info_;
		std::map<std::string, nim::TeamMemberProperty> team_member_list_;
		nim::TeamMemberProperty my_property_;
		AutoUnregister unregister_cb;
		std::function<void(const std::wstring& title)> taskbar_title_function_;
		std::function<void(UINT nRet)> close_function_;
		std::function<void()> active_function_;
	private:
		std::wstring temp_file_path_;
		std::string new_header_url_;
		bool view_mode_;
        bool saving_settings_ = false;
		static const std::vector<std::wstring> options_name_list_;
	};
}