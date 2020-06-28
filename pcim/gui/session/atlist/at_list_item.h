#pragma once

namespace nim_comp
{
/** @class AtListItem
  * @brief @�б����е��б���
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/9/6
  */
class AtListItem :public ui::ListContainerElement
{
public:
	AtListItem(bool is_last_five);
	~AtListItem();
	
	/**
	* ��ʼ���ؼ�
	* @return void	�޷���ֵ
	*/
	void InitControls();

	/**
	* ��д���ؼ����麯�������ڴ���������Ϣ
	* @return void	�޷���ֵ
	*/
	virtual void Activate() override;

	/**
	* �Ƿ�Ϊ���5����������
	* @return bool true �ǣ�false ��
	*/
	bool IsLastFive() const	{ return is_last_five_; }

	/**
	* �����û�id
	* @param[in] uid �û�id
	* @return void	�޷���ֵ
	*/
	void SetUserID(const std::string& uid);

	/**
	* ��ȡ�û�id
	* @return string �û�id
	*/
	std::string GetUserID() const { return uid_;	}

	/**
	* ���ûỰID
	* @param[in] id �Ựid
	* @return void	�޷���ֵ
	*/
	void SetSessionId(const std::string& id) { session_id_ = id; }

	/**
	* ��ȡ��ȡID
	* @return string �Ựid
	*/
	std::string GetSessionId() const { return session_id_; }

	/**
	* ���ñ�ע��
	* @param[in] name ��ע��
	* @return void	�޷���ֵ
	*/
	void SetAliasName(const std::wstring& name);

	/**
	* ��ȡ��ע��
	* @return string ��ע��
	*/
	std::string GetAliasName() const	{ return alias_name_; }

	/**
	* ����Ⱥ�ǳ�
	* @param[in] name Ⱥ�ǳ�
	* @return void	�޷���ֵ
	*/
	void SetTeamCardName(const std::wstring& name);
	 
	/**
	* ��ȡȺ�ǳ�
	* @return string Ⱥ�ǳ�
	*/
	std::string GetTeamCardName() const { return team_card_name_; }

	/**
	* �����ǳ�
	* @param[in] name �ǳ�
	* @return void	�޷���ֵ
	*/
	void SetNickName(const std::wstring& name);

	/**
	* ��ȡ�û��ǳ�
	* @return string �ǳ�
	*/
	std::string GetNickName() const { return nick_name_; }

	/**
	* �����û�ͷ��
	* @param[in] head ͷ��·��
	* @return void	�޷���ֵ
	*/
	void SetHeadImage(std::wstring head);

	/**
	* �����б���ʵ����ʾ�����֣�������ʾ��ע���������ʾȺ��Ƭ�������ʾ�ǳ�
	* @param[in] name ����
	* @return void	�޷���ֵ
	*/
	void SetShowName(const std::wstring& name);

	/**
	* ��ȡʵ����ʾ������
	* @return string ����
	*/
	std::wstring GetShowName() const { return name_label_->GetText(); }

	/**
	* �ֱ�ƥ�䱸ע����Ⱥ��Ƭ���ǳƣ�uid
	* @param[in] search_key ƥ��ؼ���
	* @return bool true ƥ��ɹ���false ƥ��ʧ��
	*/
	bool Match(const std::string& search_key);

public:
	static const char *kLastFiveItemName;
private:
	bool		is_last_five_;	//�Ƿ�Ϊ��ʾ���б���ǰ���������Ե�5��֮һ
	std::string	session_id_;
	ui::Control	*head_icon_;
	ui::Label	*name_label_;

	std::string	uid_;

	std::string	alias_name_;	//�û���ע��,������ʾ
	std::string	alias_full_name_;
	std::string	alias_simple_name_;
	std::string	team_card_name_;//�û�Ⱥ��Ƭ,�����ʾ
	std::string	team_card_full_name_;
	std::string	team_card_simple_name_;
	std::string	nick_name_;		//�û��ǳ�,�����ʾ
	std::string	nick_full_name_;
	std::string	nick_simple_name_;

};
}