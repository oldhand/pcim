#pragma once
#include "utils/threads.h"

/** @class DBThread
  * @brief ���ݿ�����߳�
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author towik
  * @date 2015/1/1
  */
class DBThread : public nbase::FrameworkThread
{
public:
	/**
	* ���캯��
	* @param[in] thread_id �߳�id
	* @param[in] name �߳�����
	*/
	DBThread(enum  ThreadId thread_id, const char *name);
	~DBThread(void);

private:
	/**
	* �麯������ʼ�����ݿ��߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�������ݿ��߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;

private:
	enum ThreadId thread_id_;
};