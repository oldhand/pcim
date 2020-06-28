#include "stdafx.h"
#include <shellapi.h>
#include "ui_kit_tray_icon.h"
namespace nim_comp
{
	const  DWORD				uTrayIconAnimateID = 0x0001;

#define	TRAYICON_ID				1
#define WM_TRAYICON_NOTIFY		(WM_USER + 1)

	static bool bInit = false;

	LRESULT TrayIcon::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		
		TrayIcon* pThis = NULL;
		if (uMsg == WM_NCCREATE) 
		{
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<TrayIcon*>(lpcs->lpCreateParams);
			::SetProp(hWnd, _T("TrayIcon"), (HANDLE)pThis);
			pThis->wnd_ = hWnd;
		}
		else 
		{
			pThis = reinterpret_cast<TrayIcon*>(::GetProp(hWnd, _T("TrayIcon")));
			if (uMsg == WM_NCDESTROY && pThis != NULL) {			
				::SetProp(hWnd, _T("TrayIcon"), NULL);
				pThis->wnd_ = NULL;
				pThis = NULL;
			}
		}
		if (pThis != NULL) 
		{
			LRESULT res = 1;
			switch (uMsg)
			{
			case WM_TRAYICON_NOTIFY:
			{
				if (TRAYICON_ID != wParam)
				{
					break;
				}
				if (WM_LBUTTONUP == lParam)
				{
					pThis->tray_icon_delegate_->LeftClick();
				}
				else if (WM_LBUTTONDBLCLK == lParam)
				{
					pThis->tray_icon_delegate_->LeftDoubleClick();
				}
				else if (WM_RBUTTONUP == lParam)
				{
					pThis->tray_icon_delegate_->RightClick();
				}
				else if (WM_RBUTTONDBLCLK == lParam)
				{
					pThis->tray_icon_delegate_->RightDoubleClick();
				}
				break;
			}
			case WM_TIMER:
			{
				pThis->OnTimer((UINT)wParam);
				break;
			}
			default:
			{
				if (uMsg != 0 && uMsg == pThis->GetTaskbarCreatedMsgId())
				{
					pThis->RestoreTrayIcon();
				}
				res = ::DefWindowProc(hWnd, uMsg, wParam, lParam);
				break;
			}
			return res;
			}
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	TrayIcon::TrayIcon() :
		wnd_(NULL),
		anim_index_array_(),
		index_icon_map_(),
		anim_escape_time_(0),
		anim_current_index_(0),
		tray_icon_delegate_(NULL),
		icon_(NULL),
		tray_icon_text_(L""),
		trayicon_msgid_(0)
	{
	}

	TrayIcon::~TrayIcon()
	{
	}

	void TrayIcon::Init(ITrayIconDelegate* tray_icon_delegate)
	{
		tray_icon_delegate_ = tray_icon_delegate;

		WNDCLASS wndclass;
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = GetModuleHandleW(NULL);
		wndclass.hIcon = NULL;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = L"nim_tray_icon_class_name";
		::RegisterClass(&wndclass);

		//wnd_ = CreateWindowExW(NULL, L"nim_tray_icon_class_name", L"nim_tray_icon_window_name", WS_POPUP | WS_CHILD,
		//	0, 0, 0, 0, NULL, NULL, GetModuleHandleW(NULL), NULL);

		wnd_ = ::CreateWindowEx(NULL, L"nim_tray_icon_class_name", L"nim_tray_icon_class_name", WS_POPUP | WS_CHILD,
			0, 0, 0, 0, NULL, NULL, GetModuleHandle(NULL), this);



		//ע��explorer����������ˢ��trayicon
		trayicon_msgid_ = ::RegisterWindowMessage(L"TaskbarCreated");
		auto text = nbase::StringPrintf("%p",this);
		::SetPropA(wnd_, nbase::StringPrintf("%p", this).c_str(), reinterpret_cast<HANDLE>(this));
		assert(wnd_);
	}

	void TrayIcon::Destroy()
	{
		NOTIFYICONDATAW tnd = { 0 };
		tnd.cbSize = sizeof(NOTIFYICONDATA);
		tnd.uFlags = 0;
		tnd.hWnd = wnd_;
		tnd.uID = TRAYICON_ID;

		::Shell_NotifyIcon(NIM_DELETE, &tnd);
	}

	void TrayIcon::SetTrayIcon(HICON icon, const std::wstring& tray_icon_text)
	{
		assert(icon);
		icon_ = icon;
		tray_icon_text_ = tray_icon_text;
		ModifyTrayIcon(TRAYICON_ID, WM_TRAYICON_NOTIFY, icon, tray_icon_text);
	}

	void TrayIcon::LoadIconList(int icon_res_start_index, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			HICON icon = (HICON)::LoadImage(NULL,
				MAKEINTRESOURCE(icon_res_start_index + i),
				IMAGE_ICON,
				::GetSystemMetrics(SM_CXSMICON),
				::GetSystemMetrics(SM_CYSMICON),
				LR_DEFAULTCOLOR | LR_SHARED);
			assert(icon);
			index_icon_map_[icon_res_start_index + i] = icon;
		}
	}

	void TrayIcon::SetAnimateTray(const std::vector<int>& aniIndex, int anim_escape_time)
	{
		ClearAnimateInfo();
		anim_index_array_ = aniIndex;
		anim_escape_time_ = anim_escape_time;
	}

	void TrayIcon::StartTrayIconAnimate()
	{
		assert(index_icon_map_.size());

		anim_current_index_ = 0;
		KillTimer(wnd_, uTrayIconAnimateID);
		SetTimer(wnd_, uTrayIconAnimateID, anim_escape_time_, NULL);
	}

	void TrayIcon::StopTrayIconAnimate()
	{
		KillTimer(wnd_, uTrayIconAnimateID);
	}

	void TrayIcon::ClearAnimateInfo()
	{
		anim_index_array_.clear();
		anim_current_index_ = 0;
		anim_escape_time_ = 0;
	}

	void TrayIcon::OnTimer(UINT event_id)
	{
		switch (event_id)
		{
		case uTrayIconAnimateID:
			if (0 != anim_index_array_.size())
			{
				anim_current_index_ %= anim_index_array_.size();
				SetTrayIconIndex(anim_index_array_[anim_current_index_++]);
			}
			else
			{
				StopTrayIconAnimate();
			}
			break;
		default:
		{
			assert(FALSE);
			break;
		}
		}
	}

	void TrayIcon::SetTrayIconIndex(int index)
	{
		HICON	hIcon = index_icon_map_[index];
		assert(hIcon);
		SetTrayIcon(hIcon, L"");
	}

	BOOL TrayIcon::RestoreTrayIcon()
	{
		if (!IsWindow(wnd_))
			return FALSE;
		bInit = false;
		SetTrayIcon(icon_, tray_icon_text_);

		return TRUE;
	}

	void TrayIcon::ModifyTrayIcon(UINT uTrayID, DWORD dwTrayMsg,
		HICON hTrayIcon, const std::wstring &tray_icon_text)
	{
		NOTIFYICONDATAW tnd = { 0 };
		tnd.cbSize = sizeof(NOTIFYICONDATA);
		tnd.hWnd = wnd_;
		tnd.uID = uTrayID;
		tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		tnd.uCallbackMessage = dwTrayMsg;
		tnd.hIcon = hTrayIcon;
#ifdef NDEBUG
		wcscpy_s(tnd.szTip, 128, tray_icon_text.c_str());
#else
		std::wstring debug_text = tray_icon_text + L"[DEBUG]";
		wcscpy_s(tnd.szTip, 128, debug_text.c_str());
#endif

		if (!bInit)
		{
			bInit = true;
			BOOL res = ::Shell_NotifyIconW(NIM_ADD, &tnd);
			//�ڼ���������п��ܻᰲװ����ʧ�ܣ������ٳ�����
			if (!res)
			{
				res = ::Shell_NotifyIconW(NIM_ADD, &tnd);
			}
		}
		else
		{
			BOOL res = ::Shell_NotifyIcon(NIM_MODIFY, &tnd);
			assert(res);
		}
	}
}


