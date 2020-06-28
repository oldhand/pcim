#pragma once
namespace nim_comp
{
	class ITeamInfoUI
	{
	public:
		/**
		* ���ñ���������
		* @param[in] title ����������
		* @return void	�޷���ֵ
		*/
		virtual void SetTaskbarTitle(const std::wstring &title) = 0;
		virtual void Close(UINT nRet = 0) = 0;
		virtual void ActiveWindow() = 0;
		/**
		* ����Ⱥ��Ա��Ϣ
		* @return void	�޷���ֵ
		*/
		virtual void UpdateTeamMember() = 0;
	};
}