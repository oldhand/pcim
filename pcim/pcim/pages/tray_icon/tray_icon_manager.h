#pragma once
#include "ui_kit_tray_icon.h"
namespace nim_comp
{
	class ITrayIconEventHandler : public virtual nbase::SupportWeakCallback
	{
	public:
		virtual bool LeftClick(){ return OnLeftClick(); }
		virtual bool LeftDoubleClick(){ return OnLeftDoubleClick(); }
		virtual bool RightClick(){ return OnRightClick(); }
		virtual bool RightDoubleClick(){ return OnRightClick(); }
	protected:
		virtual bool OnLeftClick(){ return false; }
		virtual bool OnLeftDoubleClick(){ return false; }
		virtual bool OnRightClick(){ return false; }
		virtual bool OnRightDoubleClick(){ return false; }
	};
	/** @class TrayIconManager
	* @brief ����ͼ�����
	* @copyright (c) 2015, NetEase Inc. All rights reserved
	* @date 2016/10/12
	*/
	class TrayIconManager : public ITrayIconDelegate
	{
	public:
		SINGLETON_DEFINE(TrayIconManager);
		TrayIconManager();
		virtual ~TrayIconManager();

	public:
		void AddTrayIconEventHandler(ITrayIconEventHandler* handler);
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
		UINT GetTaskbarCreatedMsgId();

		virtual void LeftClick() override;
		virtual void LeftDoubleClick() override;
		virtual void RightClick() override;
		virtual void RightDoubleClick() override;
	private:
		std::unique_ptr<TrayIcon> tray_icon_;
		std::list<std::pair<nbase::SupportWeakCallback::_TyWeakFlag, ITrayIconEventHandler*>> handler_list_;
	};
}

