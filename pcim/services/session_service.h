#pragma once
#include "utils/threads.h"
#include "utils/auto_unregister.h"
#include "plugins/session/nim_session_helper.h"

namespace nim_comp
{
	typedef std::function<void(const std::list<nim::SessionData>& sessions)> OnSessionDataChangedCallback;

	/** @class SessionService
	* @brief �Ự�б����
	* @copyright (c) 2016, NetEase Inc. All rights reserved
	* @date 2018/04/28
	*/
	class SessionService : public nbase::SupportWeakCallback
	{
	public:
		SINGLETON_DEFINE(SessionService);

	private:
		SessionService() {}
		~SessionService() {}

	public:
		/**
		* ������sdk��ѯ֮ǰ����ĻỰ�б�Ȼ�������ӵ�����ĻỰ�б���
		* @return void �޷���ֵ
		*/
		void InvokeLoadSessionList();

		/**
		* �ӻỰ�б���һỰ�ؼ�
		* @param[in] session_id �Ựid
		* @return SessionItem* �Ự�ؼ���ָ��
		*/
		nim::SessionData GetSessionItem(const std::string &session_id);

		void OnQuerySessionList(const std::list<nim::SessionData>& sessions);

		/**
		* 
		* @param[in] callback 
		* @return 
		*/
		void RegSessionDataChangedCallback(const OnSessionDataChangedCallback& callback) { session_data_changed_callback_.reset(new OnSessionDataChangedCallback(callback)); }

	private:
		/**
		* ��sdk��ѯ�Ự�б�Ľ���ص���
		* @param[in] unread_count δ����Ϣ����
		* @param[in] session_list �Ự�б�����
		* @return void	�޷���ֵ
		*/
		static void OnQuerySessionListCallback(int unread_count, const nim::SessionDataList& session_list);


	private:
		std::map<std::string, nim::SessionData> sessions_;
		std::unique_ptr<OnSessionDataChangedCallback> session_data_changed_callback_;
	};
}