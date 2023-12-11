#ifndef H_ORDERWORKER
#define H_ORDERWORKER

#include "dataBaseofMenu.h"
#include "OrderTerminal.h"
#include "OrderMonitor.h"
#include "BaseWindow.h"
#include <Windows.h>
#include <windowsx.h>
#include <vector>

struct cords {
    int X;
    int Y;
    const int HEIGHT = 30;
    const int WIDTH = 105;
    operator RECT() {
        RECT textRect;
        textRect = { this->X,this->Y,this->X + this->WIDTH,this->Y + this->HEIGHT };
        return textRect;
    }
};

class OrderWorker: public BaseWindow<OrderWorker>
{
private:
    static const int xBase = 575;
    static const int yBase = 50;
    static const int yStep = 30;
    std::vector<OrderTerminal> orders;
    std::vector<dataBaseofMenu> data;
    std::vector<cords> cordinates;
    OrderMonitor monitor;
public:
    std::vector<dataBaseofMenu> getDB();
    void setDB(std::vector<dataBaseofMenu>);
    void setMonitor(OrderMonitor);
    void delOrder(OrderTerminal);
    int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);
    PCWSTR ClassName() const { return L"OrderWorkerClass"; }
    LRESULT HandleMessage(UINT uMsgm, WPARAM wParam, LPARAM lParam);
};


#endif