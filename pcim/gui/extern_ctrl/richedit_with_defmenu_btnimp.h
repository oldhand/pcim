#pragma once
namespace nim_comp {
	class CMenuElementUI;
}
class RichEditWithDefMenu;
/** @class MenuBtnHandel
* @brief �˵���ť����������
* @copyright (c) 2017, NetEase Inc. All rights reserved
* @date 2017/10/17
*/
class MenuBtnHandel : public nbase::SupportWeakCallback
{
public:
	MenuBtnHandel(RichEditWithDefMenu* edit, const std::wstring& name);
	virtual ~MenuBtnHandel();
public:
	virtual void Reset(nim_comp::CMenuElementUI* menu_element, unsigned sel_start, unsigned sel_end);
	virtual std::wstring GetMenuName() const;
protected:
	virtual void DoReset(nim_comp::CMenuElementUI* menu_element) = 0;
protected:
	RichEditWithDefMenu* edit_;
	std::wstring menu_name_;
	unsigned sel_start_;
	unsigned sel_end_;
};
/** @class MenuBtnHandel
* @brief �˵���ť(copy) ʵ��
* @copyright (c) 2017, NetEase Inc. All rights reserved
* @date 2017/10/17
*/
class MenuBtnHandel_Copy : public MenuBtnHandel
{
public:
	MenuBtnHandel_Copy(RichEditWithDefMenu* edit);
protected:
	virtual void DoReset(nim_comp::CMenuElementUI* menu_element);
};
/** @class MenuBtnHandel
* @brief �˵���ť(cut) ʵ��
* @copyright (c) 2017, NetEase Inc. All rights reserved
* @date 2017/10/17
*/
class MenuBtnHandel_Cut : public MenuBtnHandel
{
public:
	MenuBtnHandel_Cut(RichEditWithDefMenu* edit);
protected:
	virtual void DoReset(nim_comp::CMenuElementUI* menu_element);
};
/** @class MenuBtnHandel
* @brief �˵���ť(paste) ʵ��
* @copyright (c) 2017, NetEase Inc. All rights reserved
* @date 2017/10/17
*/
class MenuBtnHandel_Paste : public MenuBtnHandel
{
public:
	MenuBtnHandel_Paste(RichEditWithDefMenu* edit);
protected:
	virtual void DoReset(nim_comp::CMenuElementUI* menu_element);
};