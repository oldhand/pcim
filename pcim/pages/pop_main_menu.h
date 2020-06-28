#pragma once
namespace nim_comp
{
	class IMainFormMenuHandler
	{
	public:
		IMainFormMenuHandler() : host_window_(nullptr){}
		virtual ~IMainFormMenuHandler(){};
		/**
		* �������˵�
		* @param[in] point ��������
		* @return void	�޷���ֵ
		*/
		virtual void PopupMainMenu(POINT point)
		{
			if (host_window_ == nullptr)
				return;
			OnPopupMainMenu(point);
		}
		virtual void SetHostWindow(WindowEx* host_windows) { host_window_ = host_windows; }
	protected:
		virtual void OnPopupMainMenu(POINT point) = 0;
	protected:
		WindowEx* host_window_;
	};
	
}