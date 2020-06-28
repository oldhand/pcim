#pragma once

/** @class SessionForm
  * @brief ���ڴ���
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @date 2016/10/12
  */
class AboutForm : public nim_comp::WindowEx
{
public:
	AboutForm();
	~AboutForm();
	
	//�����麯��
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual UINT GetClassStyle() const override;
	
	/**
	* ���ڳ�ʼ������
	* @return void	�޷���ֵ
	*/
	virtual void InitWindow() override;
private:

	/**
	* �������пؼ�������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnClicked(ui::EventArgs* arg);
public:
	static const LPCTSTR kClassName;
};