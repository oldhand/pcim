#pragma once
#include "utils/threads.h"

/** @class MiscThread
  * @brief �����̣߳�����һЩ����
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author towik
  * @date 2015/1/1
  */
class MiscThread : public nbase::FrameworkThread
{
public:
	/**
	* ���캯��
	* @param[in] thread_id �߳�id
	* @param[in] name �߳�����
	*/
	MiscThread(enum ThreadId thread_id, const char *name);
	~MiscThread(void);

private:
	/**
	* �麯������ʼ���߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�����߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;

private:
	enum ThreadId thread_id_;
};