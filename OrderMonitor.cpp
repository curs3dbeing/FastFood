#include "OrderMonitor.h"
#include "OrderTerminal.h"
#include <Windows.h>
#include <windowsx.h>
#include <iostream>
#include <vector>

extern std::vector<OrderTerminal> setOfOrders;
extern std::vector<OrderTerminal> setOfReadyOrders; 

int length(int num) {
    int length = 0;
    while (num >= 1) {
        num /= 10;
        length++;
    }
    return length;
}

int WINAPI OrderMonitor::wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR pCmdLine, int nCmdShow) {

	if (!this->Create(L"OrderMonitor", WS_OVERLAPPEDWINDOW)) {
		std::cerr << "Unable to create window 'OrderMonitor'" << std::endl;
		return 0;
	}

    HWND hSeparator = CreateWindow(
        L"Static", 
        NULL, 
        WS_CHILD | WS_VISIBLE | SS_ETCHEDVERT, 
        570, 0, 2, 2000, 
        m_hwnd, 
        NULL, 
        hInstance, 
        NULL 
    );

	ShowWindow(m_hwnd, SW_SHOWDEFAULT);

	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    
	return 0;
}


LRESULT OrderMonitor::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        static LOGFONT lf;
        lf.lfCharSet = DEFAULT_CHARSET;
        lf.lfPitchAndFamily = DEFAULT_PITCH;
        wcscpy_s(lf.lfFaceName, L"Times New Roman");
        lf.lfHeight = 30;
        lf.lfWidth = 0;
        lf.lfEscapement = 0;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        HFONT hFont;
        hFont = CreateFontIndirect(&lf);
        SelectObject(hdc, hFont);
        int Y = 40;
        int X = 575;
        int lengthOfNumber = 0;
        wchar_t ordersid[6]; 
        wchar_t orderCounter[10];
        TextOut(hdc, 230, 10, L"Not ready", strlen("Not ready"));
        TextOut(hdc, 800, 10, L"Ready", strlen("Ready"));
        DeleteObject(hFont);
        for (int i = 0;i < setOfOrders.size();i++) {
            lengthOfNumber = length(i+1);
            swprintf_s(orderCounter, L"%d", i + 1);
            orderCounter[lengthOfNumber + 1] = '\0';
            orderCounter[lengthOfNumber] = ':';
            TextOut(hdc, 0, 10 + Y, orderCounter, wcslen(orderCounter));
            swprintf_s(ordersid, L"%d", setOfOrders[i].orderid);
            TextOut(hdc, 35, Y+10, ordersid, wcslen(ordersid));
            Y = Y + 25;
        }
        Y = 40;
        X = 575;
        for (int i = 0;i < setOfReadyOrders.size();i++) {
            lengthOfNumber = length(i + 1);
            swprintf_s(orderCounter, L"%d", i + 1);
            orderCounter[lengthOfNumber + 1] = '\0';
            orderCounter[lengthOfNumber] = ':';
            TextOut(hdc, X, 10 + Y, orderCounter, wcslen(orderCounter));
            swprintf_s(ordersid, L"%d", setOfReadyOrders[i].orderid);
            TextOut(hdc, X+35, Y + 10, ordersid, wcslen(ordersid));
            Y = Y + 25;
        }
        EndPaint(m_hwnd, &ps);
        return 0;
    }
    default:
        return DefWindowProc(this->Window(), uMsg, wParam, lParam);
    }
    return TRUE;
}

void OrderMonitor::addOrder(OrderTerminal _order) {
    orders.push_back(_order);
}