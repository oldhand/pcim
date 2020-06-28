#pragma once
//#include "module/session/force_push_manager.h"

namespace nim_comp
{
/** @class AtMeView
  * @brief �ڻỰ��������ʾ�Լ���@����Ϣ
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/9/6
  */
class AtMeView : public ui::ButtonBox
{
public:
	struct AtMeInfo
	{
		std::wstring msg_body;
		std::wstring sender_name;
		std::wstring uuid;
	};

	/**
	* ��ʼ���ؼ�
	* @return void	�޷���ֵ
	*/
	void InitControl();

	/**
	* ���µ�@me��Ϣ������׷�ӵ�@me��Ϣ�б�ĩβ
	* @param[in] at_me_info ǿ����Ϣ
	* @return void	�޷���ֵ
	*/
	void AddMessage(const AtMeInfo &at_me_info);

	/**
	* ��ʾ��һ��@me��Ϣ
	* @return void	�޷���ֵ
	*/
	void ShowNextMessage();	

	/**
	* ����Ҫ������ʷ��Ϣ�����ҵ�@me��Ϣʱ����ʾ�����ڼ����С�����ʾ�����ҽ��ñ��ؼ�
	* @param[in] show �Ƿ���ʾ��ʾ
	* @return void	�޷���ֵ
	*/
	void ShowLoadingTip(bool show);

	/**
	* ��ȡ@me��Ϣ����
	* @return UINT ��Ϣ����
	*/
	UINT GetAtMeCount();

	/**
	* ��ȡ��ǰ��@me��Ϣ��uuid
	* @return wstring uuid
	*/
	std::wstring GetUuid();

private:
	/**
	* �������һ��@me��Ϣ��ʾ��Ӧ�Ľ���Ч��
	* @return void	�޷���ֵ
	*/
	void UpdateView();
	
private:
	std::vector<AtMeInfo>	at_me_info_;

	ui::Label		*content_;
	ui::Label		*sender_name_;

};
}