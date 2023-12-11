#ifndef H_ORDERMONITOR
#define H_ORDERMONITOR

#include "OrderTerminal.h"
#include "BaseWindow.h"
#include <Windows.h>
#include <windowsx.h>
#include <vector>

class OrderMonitor : public BaseWindow<OrderMonitor>
{
private:
    std::vector<OrderTerminal> orders;
public:
    void addOrder(OrderTerminal);
    int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);
    PCWSTR ClassName() const {return L"OrderMonitorClass"; }
    LRESULT HandleMessage(UINT uMsgm, WPARAM wParam, LPARAM lParam);
};

#endif