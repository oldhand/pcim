#pragma once
namespace nim_comp
{
	/** @class ITrayIconDelegate
	* @brief ����ͼ���¼�����ӿ�
	* @copyright (c) 2015, NetEase Inc. All rights reserved
	* @date 2016/10/12
	*/
	class ITrayIconDelegate
	{
	public:
		virtual void LeftClick(){}
		virtual void LeftDoubleClick(){ }
		virtual void RightClick(){ }
		virtual void RightDoubleClick(){ }
	};

	/** @class TrayIcon
	* @brief ����ͼ�����
	* @copyright (c) 2015, NetEase Inc. All rights reserved
	* @date 2016/10/12
	*/
	class TrayIcon
	{
	public:
		TrayIcon();
		virtual ~TrayIcon();

	public:
		/**
		* ��ʼ������ͼ��
		* @param[in] tray_icon_delegate ָ������ͼ���¼�����ӿ�
		* @return void	�޷���ֵ
		*/
		void Init(ITrayIconDelegate* tray_icon_delegate);

		/**
		* ��������ͼ��
		* @return void	�޷���ֵ
		*/
		void Destroy();

		/**
		* ��������ͼ�����ʾ�ı�
		* @param[in] icon ͼ����
		* @param[in] tray_icon_text ��ʾ�ı�
		* @return void	�޷���ֵ
		*/
		void SetTrayIcon(HICON icon, const std::wstring& tray_icon_text);

		/**
		* ����Դ�м���һ��ͼ����Դ����������
		* @param[in] icon_res_start_index Ҫͼ����Դ�ĵ�һ����Դ��ID
		* @param[in] count Ҫ���ص�ͼ�������
		* @return void	�޷���ֵ
		*/
		void LoadIconList(int icon_res_start_index, int count);

		/**
		* �������̶����У����ڶ���Ч��ͼ��֡��������
		* @param[in] aniIndex ͼ��֡����������
		* @param[in] anim_escape_time �������ʱ��
		* @return void	�޷���ֵ
		*/
		void SetAnimateTray(const std::vector<int>& aniIndex, int anim_escape_time);

		/**
		* ��ʼ����ͼ�궯��Ч��
		* @return void	�޷���ֵ
		*/
		void StartTrayIconAnimate();

		/**
		* ֹͣ����ͼ�궯��Ч��
		* @return void	�޷���ֵ
		*/
		void StopTrayIconAnimate();

		/**
		* ��ȡ������ͼ�괴����ɵ���Ϣ����Ϣֵ
		* @return UINT ��Ϣֵ
		*/
		UINT GetTaskbarCreatedMsgId(){ return trayicon_msgid_; }

	private:
		/**
		* �����ڲ�������Ϣ
		* @param[in] hWnd ���ھ��
		* @param[in] uMsg ��Ϣֵ
		* @param[in] wParam ���Ӳ���
		* @param[in] lParam ���Ӳ���
		* @return LRESULT ��Ϣ������
		*/
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		/**
		* ������̶��������Ϣ
		* @return void	�޷���ֵ
		*/
		void ClearAnimateInfo();

		/**
		* ����WM_TIMER��Ϣ
		* @param[in] event_id �¼�id
		* @return void	�޷���ֵ
		*/
		void OnTimer(UINT event_id);

		/**
		* ����ͼ��������������ͼ��
		* @param[in] index
		* @return void	�޷���ֵ
		*/
		void SetTrayIconIndex(int index);

		/**
		* �ָ�����ͼ�굽Ĭ��ֵ
		* @return BOOL	TRUE���ظ��ɹ��� FALSE���ָ�ʧ��
		*/
		BOOL RestoreTrayIcon();

		/**
		* �޸�����ͼ��
		* @param[in] uTrayID ����ID
		* @param[in] dwTrayMsg ָ�����ڽ���������Ϣ�Ļص���Ϣֵ
		* @param[in] hTrayIcon ͼ����
		* @param[in] strTrayText ������ʾ�ı�
		* @return void	�޷���ֵ
		*/
		void ModifyTrayIcon(UINT uTrayID, DWORD dwTrayMsg, HICON hTrayIcon, const std::wstring& strTrayText);

	private:
		HWND	wnd_;

		HICON			icon_;
		std::wstring	tray_icon_text_;
		UINT			trayicon_msgid_;

		std::map<int, HICON>	index_icon_map_;
		std::vector<int>		anim_index_array_;
		int						anim_escape_time_;
		int						anim_current_index_;

		ITrayIconDelegate		*tray_icon_delegate_;

	};
}

