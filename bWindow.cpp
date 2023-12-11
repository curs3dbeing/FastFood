#include "BaseWindow.h"
#include <Windows.h>
#include <windowsx.h>

template<class T>

LRESULT CALLBACK BaseWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	T* ptr = NULL;
	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>lParam;
		ptr = reinterpret_cast<T*>pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ptr);
		ptr->m_hwnd = hwnd;
	}
	else {
		ptr = (T*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}
	if (ptr) {
		return ptr->HandleMessage(uMsg, wParam, lParam);
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

BOOL BaseWindow::Create(
	DWORD dwStyle,
	DWORD dwExStyle = 0,
	int x = CW_USEDEFAULT,
	int y = CW_USEDEFAULT,
	int nWidth = CW_USEDEFAULT,
	int nHeight = CW_USEDEFAULT,
	HWND hWndParent = 0,
	HMENU hMenu = 0
) 
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = BaseWindow<T>::WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = ClassName();

	RegisterClass(&wc);

	BaseWindow<T>::m_hwnd = CreateWindowEx(
		dwExStyle, 
		ClassName(), 
		lpWindowName, 
		dwStyle, 
		x, 
		y,
		nWidth, 
		nHeight, 
		hWndParent, 
		hMenu, 
		GetModuleHandle(NULL), 
		this);
	return (m_hwnd ? TRUE : FALSE);
}