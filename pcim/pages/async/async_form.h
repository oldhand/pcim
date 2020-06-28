#pragma once

namespace nim_comp
{
/** @class LinkForm
  * @brief 断线重连提示窗口
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @date 2016/09/19
  */
class AsyncForm : public WindowEx
{
	enum LinkPage
	{
		LINK_TIP,
		LINK_ING,
		LINK_SUCCESS
	};
public:
	AsyncForm();
	~AsyncForm();
	
	//覆盖虚函数
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual UINT GetClassStyle() const override;
	
	/**
	* 窗口初始化函数
	* @return void	无返回值
	*/
	virtual void InitWindow() override; 
public:
	void ShowAsyncInfo(std::wstring text, float value);

public:
	static const LPCTSTR kClassName;
private:
	nbase::WeakCallbackFlag timer_;
	AutoUnregister unregister_cb;
};

/**
* 显示数据同步窗口
* @return void	无返回值
*/
void ShowAsyncForm();
}