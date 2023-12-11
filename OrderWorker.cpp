#include "OrderWorker.h"
#include "OrderTerminal.h"
#include "OrderMonitor.h"
#include "dataBaseofMenu.h"
#include <Windows.h>
#include <windowsx.h>
#include <iostream>
#include <string>
#include <vector>

extern std::vector<OrderTerminal> setOfOrders;
extern std::vector<OrderTerminal> setOfReadyOrders;

const int OrderWorker::xBase;
const int OrderWorker::yBase;
const int OrderWorker::yStep;
int selectedOrder = -1;
static int windowX;
static int windowY;

HWND OKButton, CANCELButton;
 
void drawFrame(RECT*, OrderWorker*);
void drawOrderPlaces(OrderWorker*);

void drawOrderPlaces(OrderWorker* window) {
    OrderTerminal _order = setOfOrders[selectedOrder];
    std::wstring message = _order.getOrderWNames(window->getDB());
    MessageBox(window->m_hwnd, message.c_str(), L"Order Information", MB_OK | MB_ICONINFORMATION);
}

void OrderWorker::setDB(std::vector<dataBaseofMenu> _data) {
    this->data = _data;
}

std::vector<dataBaseofMenu> OrderWorker::getDB() {
    return this->data;
}

bool isSelected() {
    if (selectedOrder != -1) return true;
    else return false;
}

void drawFrame(RECT* textRect, OrderWorker* window) {
    HDC hdc = GetDC(window->m_hwnd);
    HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    FrameRect(hdc, textRect, hBrush);
    ReleaseDC(window->m_hwnd, hdc);
}

int getlength(int num) {
    int length = 0;
    while (num >= 1) {
        num /= 10;
        length++;
    }
    return length;
}

int WINAPI OrderWorker::wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR pCmdLine, int nCmdShow) {

    if (!this->Create(L"OrderWorker", WS_OVERLAPPEDWINDOW)) {
        std::cerr << "Unable to create window 'OrderWorker'" << std::endl;
        return 0;
    }

    ShowWindow(m_hwnd, SW_SHOWDEFAULT);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT OrderWorker::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_SIZE: {
        windowX = LOWORD(lParam);
        windowY = HIWORD(lParam);
        break;
    }
    case WM_CREATE: {
        RECT rect;
        GetWindowRect(m_hwnd, &rect);
        windowX = rect.right - rect.left;
        windowY = rect.bottom - rect.top;
        OKButton = CreateWindow(
            L"BUTTON",   
            L"OK",      
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_DISABLED,
            windowX * 0.35,          
            windowY * 0.8,         
            80,        
            40,        
            m_hwnd,    
            (HMENU)1,
            (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
            NULL);      
        CANCELButton = CreateWindow(
            L"BUTTON",  
            L"CANCEL",     
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_DISABLED,
            windowX * 0.55,         
            windowY * 0.8,      
            80,        
            40,        
            m_hwnd,     
            (HMENU)2,
            (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
            NULL);    
        return 0;
    }
    case WM_ENABLE:
    {
        EnableWindow(OKButton, isSelected());
        EnableWindow(CANCELButton, isSelected());
        return 0;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case 1: {
            setOfReadyOrders.push_back(setOfOrders[selectedOrder]);
            delOrder(setOfOrders[selectedOrder]);
            selectedOrder = -1;
            InvalidateRect(m_hwnd, 0, true);
            UpdateWindow(m_hwnd);
            InvalidateRect(monitor.m_hwnd, 0, true);
            SendMessageW(m_hwnd, WM_ENABLE, wParam, lParam);
            return 0;
        }
        case 2: {
            selectedOrder = -1;
            InvalidateRect(m_hwnd, 0, true);
            UpdateWindow(m_hwnd);
            SendMessageW(m_hwnd, WM_ENABLE, wParam, lParam);
            return 0;
        }
        default:
            return 0;
        }
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        static LOGFONT lf;
        cordinates.clear();
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

        int xCurr = windowX*0.2;
        int yCurr = yBase;

        int lengthOfNumber = 0;
        wchar_t ordersid[6];
        wchar_t orderCounter[10];

        TextOut(hdc, windowX*0.45, 10, L"Not ready", strlen("Not ready"));
        /*TextOut(hdc, 800, 10, L"Ready", strlen("Ready"));*/

        DeleteObject(hFont);

        for (int i = 0;i < setOfOrders.size();i++) {

            lengthOfNumber = getlength(i + 1);

            swprintf_s(orderCounter, L"%d", i + 1);

            orderCounter[lengthOfNumber + 1] = '\0';
            orderCounter[lengthOfNumber] = ':';

            TextOut(hdc, xCurr, yCurr, orderCounter, wcslen(orderCounter));

            swprintf_s(ordersid, L"%d", setOfOrders[i].orderid);

            TextOut(hdc, xCurr+35, yCurr, ordersid, wcslen(ordersid));
            cordinates.push_back({ xCurr, yCurr });
            //35 отступ  75 - длина по x (105 po x)
            //Y - 30
            yCurr += yStep;
        }

        if (selectedOrder != -1) {
            RECT textRect;
            textRect = (RECT)cordinates[selectedOrder];
            drawFrame(&textRect, this);
        }

        EndPaint(m_hwnd, &ps);
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        if (selectedOrder != -1) break;
        POINT cursorPos;
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);
        cursorPos = { mouseX,mouseY };

        RECT textRect;

        int size = cordinates.size();
        for (int i = 0;i < size;i++) {
            textRect = {cordinates[i].X,cordinates[i].Y,cordinates[i].WIDTH+ cordinates[i].X,cordinates[i].HEIGHT+ cordinates[i].Y };
            if (PtInRect(&textRect, cursorPos)) {
                selectedOrder = i;
                break;
            }
        }
        if (selectedOrder != -1) {
            drawFrame(&textRect, this);
            drawOrderPlaces(this);
        }
        SendMessageW(m_hwnd, WM_ENABLE, wParam, lParam);
        break;
    }
    default:
        return DefWindowProc(this->Window(), uMsg, wParam, lParam);
    }
    return TRUE;
}

int findID(OrderTerminal _order) {
    int n = setOfOrders.size();
    for (int i = 0;i < n;i++) { 
        if (_order.orderid == setOfOrders[i].orderid) return i;
    }
    return -1;
}

void OrderWorker::delOrder(OrderTerminal _order) {
    int id = findID(_order);
    setOfOrders.erase(setOfOrders.begin() + id);
}

void OrderWorker::setMonitor(OrderMonitor monitor) {
    this->monitor = monitor;
}