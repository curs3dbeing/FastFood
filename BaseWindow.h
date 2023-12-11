#ifndef H_BASEWINDOW
#define H_BASEWINDOW
#include <Windows.h>
#include <windowsx.h>

template<class T>

class BaseWindow {
public:

	HWND m_hwnd;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		T* ptr = NULL;
		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			ptr = (T*)pCreate->lpCreateParams;
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

	BaseWindow() { m_hwnd = NULL; }

	BOOL Create(
		PCWSTR lpWindowName,
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

		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = ClassName();
		wc.lpfnWndProc = BaseWindow<T>::WindowProc;
		wc.style = 0;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;

		RegisterClass(&wc);

		BaseWindow<T>::m_hwnd = CreateWindowEx(
			dwExStyle,
			ClassName(),
			lpWindowName,
			dwStyle | CS_DBLCLKS,
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

	HWND Window() const { return m_hwnd;}

protected:
	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT, WPARAM, LPARAM) = 0;
};


#endif