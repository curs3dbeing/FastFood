#include <iostream>
#include <fstream>
#include "dataBaseofMenu.h"
#include "dataBaseofUsers.h"
#include "Admins.h"
#include "Workers.h"
#include "OrderTerminal.h"
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <windowsx.h>
#include "OrderMonitor.h"
#include "OrderWorker.h"
#include <thread>
#include <chrono>

#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESCAPE 27

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

const int X = 50;
int Y = 13;

vector<OrderTerminal> setOfOrders;
vector<OrderTerminal> setOfReadyOrders;

// FOR WORK WITH WINAPI
HINSTANCE hInstance; HINSTANCE hPrevInst;
LPTSTR lpszArgs; int nWinMode;

void threadWork(OrderMonitor window) {
	window.wWinMain(hInstance, hPrevInst, lpszArgs, nWinMode);
	return;
}

void _threadWork(OrderWorker window) {
	window.wWinMain(hInstance, hPrevInst, lpszArgs, nWinMode);
	return;
}

// FOR WORK WITH SCREEN
void gotoXY(HANDLE hStdOut, short x, short y);
void SetScreenTitle();
void CursorVisiability(HANDLE hStdOut, bool visible);
void SetUsualTextColor(HANDLE hStdOut);
void SetEventTextColor(HANDLE hStdOut);
void SetBasicTextColor(HANDLE hStdOut);
void cleanScreen();

//FOR WORK WITH CLIENT ORDERS
void orderMenu(OrderTerminal&, vector<dataBaseofMenu>, OrderMonitor&);
void eatingPlaceChoice(OrderTerminal& ,vector<dataBaseofMenu>, OrderMonitor&);
void burgerMenu(OrderTerminal&, vector<dataBaseofMenu>);
void drinksMenu(OrderTerminal&, vector<dataBaseofMenu>);
void friesMenu(OrderTerminal&, vector<dataBaseofMenu>);
void combosMenu(OrderTerminal&, vector<dataBaseofMenu>);
void adminPanel(vector<dataBaseofUsers>&, vector<dataBaseofMenu>&, Admins);
void loginPanel(vector<dataBaseofUsers>&, vector<dataBaseofMenu>&, Admins);
void authorizationPanel(vector<dataBaseofUsers>&,vector<dataBaseofMenu>&);
void userWorkDBmenu(vector<dataBaseofMenu>&, Workers);
void adminWorkDBusers(vector<dataBaseofUsers>&, Admins);
void workerPanel(vector<dataBaseofMenu>&, Workers);

void gotoXY(HANDLE hStdOut, short x, short y) {
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void SetScreenTitle() {
	SetConsoleTitle(L"Order Menu");
}

void CursorVisiability(HANDLE hStdOut, bool visible) {
	visible = 0;
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(hStdOut, &cursor);
	cursor.bVisible = false;
}

void SetUsualTextColor(HANDLE hStdOut) {
	SetConsoleTextAttribute(hStdOut, 3);
}

void SetEventTextColor(HANDLE hStdOut) {
	SetConsoleTextAttribute(hStdOut, 11);
}

void SetBasicTextColor(HANDLE hStdOut) {
	SetConsoleTextAttribute(hStdOut, 7);
}

void cleanScreen() {
	system("cls");
}

void combosMenu(OrderTerminal& orders, vector<dataBaseofMenu> data) {
	cleanScreen();
	size_t sizes = data.size();
	int sz = 1;
	string* menu;
	for (size_t i = 0;i < sizes;i++) {
		if (data[i].id >= 400 && data[i].id < 500) sz++;
	}
	menu = new string[sz];
	for (int i = 0, j = 0;i < sizes;i++) {
		if (data[i].id >= 400 && data[i].id < 500) {
			menu[j++] = data[i].nameofItem;
		}
	}
	menu[sz - 1] = "Выйти";
	int id = 0;
	double price = 0;
	char ch;
	int activeMenu = 0;
	while (true) {
		gotoXY(hStdOut, 0, 0);
		cout << "Ваш заказ:";
		gotoXY(hStdOut, 0, 1);
		orders.showOrderNames(data);
		Y = 13;
		for (int i = 0;i < sz;i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:  if (activeMenu != 0) activeMenu--; break;
		case DOWN:if (activeMenu != sz - 1) activeMenu++;break;
		case ENTER:
			for (int i = 0;i < sz - 1;i++) {
				if (activeMenu == i) { id = findID(menu[activeMenu], data); price = findPrice(menu[activeMenu], data); orders.addItem(id, price);	 cleanScreen(); gotoXY(hStdOut, X - 10, Y); cout << menu[activeMenu] << " успешно добавлен в заказ!" << endl; system("pause"); delete[] menu; return; }
			}
			if (activeMenu == sz-1) delete[] menu; return;
		case ESCAPE: delete[] menu; return;
		default: continue;
		}
		cleanScreen();
	}
}

void drinksMenu(OrderTerminal& orders, vector<dataBaseofMenu> data) {
	cleanScreen();
	size_t sizes = data.size();
	int sz = 1;
	string* menu;
	for (size_t i = 0;i < sizes;i++) {
		if (data[i].id >= 300 && data[i].id < 400) sz++;
	}
	menu = new string[sz];
	for (int i = 0, j = 0;i < sizes;i++) {
		if (data[i].id >= 300 && data[i].id < 400) {
			menu[j++] = data[i].nameofItem;
		}
	}
	menu[sz - 1] = "Выйти";
	int id = 0;
	double price = 0;
	char ch;
	int activeMenu = 0;
	while (true) {
		gotoXY(hStdOut, 0, 0);
		cout << "Ваш заказ:";
		gotoXY(hStdOut, 0, 1);
		orders.showOrderNames(data);
		Y = 13;
		for (int i = 0;i < sz;i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:  if (activeMenu != 0) activeMenu--; break;
		case DOWN:if (activeMenu != sz - 1) activeMenu++;break;
		case ENTER:
			for (int i = 0;i < sz - 1;i++) {
				if (activeMenu == i) { id = findID(menu[activeMenu], data); price = findPrice(menu[activeMenu], data); orders.addItem(id, price);	 cleanScreen(); gotoXY(hStdOut, X - 10, Y); cout << menu[activeMenu] << " успешно добавлен в заказ!" << endl; system("pause"); delete[] menu; return; }
			}
			if (activeMenu == sz-1) delete[] menu; return;
		case ESCAPE: delete[] menu; return;
		default: continue;
		}
		cleanScreen();
	}
}

void friesMenu(OrderTerminal& orders, vector<dataBaseofMenu> data) {
	cleanScreen();
	size_t sizes = data.size();
	int sz = 1;
	string* menu;
	for (size_t i = 0;i < sizes;i++) {
		if (data[i].id >= 200 && data[i].id < 300) sz++;
	}
	menu = new string[sz];
	for (int i = 0, j = 0;i < sizes;i++) {
		if (data[i].id >= 200 && data[i].id < 300) {
			menu[j++] = data[i].nameofItem;
		}
	}
	menu[sz - 1] = "Выйти";
	int id = 0;
	double price = 0;
	char ch;
	int activeMenu = 0;
	while (true) {
		gotoXY(hStdOut, 0, 0);
		cout << "Ваш заказ:";
		gotoXY(hStdOut, 0, 1);
		orders.showOrderNames(data);
		Y = 13;
		for (int i = 0;i < sz;i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:  if (activeMenu != 0) activeMenu--; break;
		case DOWN:if (activeMenu != sz - 1) activeMenu++;break;
		case ENTER:
			for (int i = 0;i < sz - 1;i++) {
				if (activeMenu == i) { id = findID(menu[activeMenu], data); price = findPrice(menu[activeMenu], data); orders.addItem(id, price);	 cleanScreen(); gotoXY(hStdOut, X - 10, Y); cout << menu[activeMenu] << " успешно добавлен в заказ!" << endl; system("pause"); delete[] menu; return; }
			}
			if (activeMenu == sz-1) delete[] menu; return;
		case ESCAPE: delete[] menu; return;
		default: continue;
		}
		cleanScreen();
	}
}

void burgerMenu(OrderTerminal& orders, vector<dataBaseofMenu> data) {
	cleanScreen();
	size_t sizes = data.size();
	int sz=1;
	string* menu;
	for (size_t i = 0;i < sizes;i++) {
		if (data[i].id >= 100 && data[i].id < 200) sz++;
	}
	menu = new string[sz];
	for (int i = 0,j=0;i < sizes;i++) {
		if (data[i].id >= 100 && data[i].id < 200) {
			menu[j++] = data[i].nameofItem;
		}
	}
	menu[sz-1] = "Выйти";
	int id=0;
	double price = 0;
	char ch;
	int activeMenu = 0;
	while (true) {
		gotoXY(hStdOut, 0, 0);
		cout << "Ваш заказ:";
		gotoXY(hStdOut, 0, 1);
		orders.showOrderNames(data);
		Y = 13;
		for (int i = 0;i < sz;i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:  if (activeMenu != 0) activeMenu--; break;
		case DOWN:if (activeMenu != sz - 1) activeMenu++;break;
		case ENTER: 
			for (int i = 0;i < sz - 1;i++) {
				if (activeMenu == i) { id = findID(menu[activeMenu], data); price = findPrice(menu[activeMenu], data); orders.addItem(id, price);	 cleanScreen(); gotoXY(hStdOut, X - 10, Y); cout << menu[activeMenu] << " успешно добавлен в заказ!" << endl; system("pause"); delete[] menu; return; }
					}
			    if (activeMenu == sz-1) delete[] menu; return;
		case ESCAPE: delete[] menu; return;
		default: continue;
		}
		cleanScreen();
	}
}

void orderMenu(OrderTerminal& orders, vector<dataBaseofMenu> data, OrderMonitor& window) {
	cleanScreen();
	string menu[] = { "Бургеры", "Картошка", "Напитки", "Комбо", "Подтвердить заказ" ,"Выйти"};
	char ch;
	int activeMenu = 0;
	while (true) {
		gotoXY(hStdOut, 0, 0);
		cout << "Ваш заказ:";
		gotoXY(hStdOut, 0, 1);
		orders.showOrderNames(data);
		Y = 13;
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP: if (activeMenu != 0) activeMenu--; break;
		case DOWN: if (activeMenu != size(menu) - 1) activeMenu++;break;
		case ENTER: if (activeMenu == 0) { burgerMenu(orders, data); break; }
				    if (activeMenu == 1) { friesMenu(orders, data) ; break; }
					if (activeMenu == 2) { drinksMenu(orders, data); break; }
					if (activeMenu == 3) { combosMenu(orders, data); break; }
					if (activeMenu == 4) { if (orders.order.empty()) { system("cls"); gotoXY(hStdOut, X, Y); cout << "Ваш заказ - пуст!"; Sleep(1500); break; }
					orders.setNewOrderId();
					window.addOrder(orders);
					setOfOrders.push_back(orders);
					InvalidateRect(window.m_hwnd, 0, true);
					system("cls"); gotoXY(hStdOut, X, Y);
					cout << "Ваш заказ успешно добавлен!";
					Sleep(1500);
					return; }
					if (activeMenu == 5) { return; }
		case ESCAPE: return;
		default: continue;
		}
		cleanScreen();
	}
}

void eatingPlaceChoice(OrderTerminal& orders,vector<dataBaseofMenu> data, OrderMonitor& window) {
	cleanScreen();
	string menu[] = { "На месте", "С собой" };
	char ch;
	int activeMenu = 0;
	while (true) {
		Y = 13;
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:    if (activeMenu != 0) activeMenu--; break;
		case DOWN:  if (activeMenu != size(menu) - 1) activeMenu++; break;
		case ENTER: if (activeMenu == 0) { orders.setEatingPlace(true);  orderMenu(orders, data, window); return; }
				    if (activeMenu == 1) { orders.setEatingPlace(false); orderMenu(orders, data, window); return; }
		case ESCAPE: return;
		default: continue;
		}
		cleanScreen();
	}
}

void userWorkDBmenu(vector<dataBaseofMenu>& data, Workers user)
{
	cleanScreen();
	char ch;
	int activeMenu = 0;
	string menu[] = { "Добавить позиции в меню", "Изменить цены позиций в меню", "Удалить позиции из меню", "Выйти" };
	while (true) {
		Y = 13;
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:    if (activeMenu != 0) activeMenu--; break;
		case DOWN:  if (activeMenu != size(menu) - 1) activeMenu++; break;
		case ENTER: if (activeMenu == 0) { cleanScreen(); user.addPositionsToMenu(data); cleanScreen(); break; }
				    if (activeMenu == 1) { cleanScreen(); dataBasePrint(data); cout << endl; user.changePrice(data); cleanScreen(); break; }
					if (activeMenu == 2) { cleanScreen(); dataBasePrint(data); cout << endl; user.deletePos(data); cleanScreen(); break; }
				    if (activeMenu == 3) return;
		case ESCAPE: return;
		default: continue;
		}
		cleanScreen();
	}
}

void adminWorkDBusers(vector<dataBaseofUsers>& usersData, Admins admin) {
	cleanScreen();
	char ch;
	int activeMenu = 0;
	string menu[] = { "Создать нового пользователя 'Админ'","Создать нового пользователя 'Работник'", "Удалить пользователя из базы данных", "Изменить уровень доступа у пользователя", "Выйти"};
	while (true) {
		Y = 13;
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:    if (activeMenu != 0) activeMenu--; break;
		case DOWN:  if (activeMenu != size(menu) - 1) activeMenu++; break;
		case ENTER: if (activeMenu == 0) { cleanScreen(); admin.addAdmin(usersData); cleanScreen(); break; }
				    if (activeMenu == 1) { cleanScreen();  admin.addUser(usersData);  cleanScreen(); break; }
				    if (activeMenu == 2) { cleanScreen();dataBasePrint(usersData); gotoXY(hStdOut, X-10, Y++-usersData.size()); admin.deleteUser(usersData); cleanScreen(); break; }
					if (activeMenu == 3) { cleanScreen();dataBasePrint(usersData); gotoXY(hStdOut, X - 30, Y++ - usersData.size()); admin.changeLevelAccess(usersData); cleanScreen(); break; }
				    if (activeMenu == 4) return;
		case ESCAPE: return;
		default: continue;
		}
		cleanScreen();
	}
}

void adminPanel(vector<dataBaseofUsers>& usersData, vector<dataBaseofMenu>& data, Admins admin) {
	cleanScreen();
	char ch;
	int activeMenu = 0;
	string menu[] = { "Работа с базой данных меню","Работа с базой данных пользователей", "Деавторизоваться" };
	while (true) {
		Y = 13;
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:    if (activeMenu != 0) activeMenu--; break;
		case DOWN:  if (activeMenu != size(menu) - 1) activeMenu++; break;
		case ENTER: if (activeMenu == 0) { userWorkDBmenu(data, admin); break; }
					if (activeMenu == 1) { adminWorkDBusers(usersData, admin); break; }
				    if (activeMenu == 2) return;
		case ESCAPE: return;
		default: continue;
		}
		cleanScreen();
	}
}

void workerPanel(vector<dataBaseofMenu>& data, Workers user) {
	cleanScreen();
	char ch;
	int activeMenu = 0;
	string menu[] = { "Работа с базой данных меню", "Деавторизоваться" };
	while (true) {
		Y = 13;
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:    if (activeMenu != 0) activeMenu--; break;
		case DOWN:  if (activeMenu != size(menu) - 1) activeMenu++; break;
		case ENTER: if (activeMenu == 0) { userWorkDBmenu(data, user); break; }
				    if (activeMenu == 1) return;
		case ESCAPE: return;
		default: continue;
		}
		cleanScreen();
	}
}

void authorizationPanel(vector<dataBaseofUsers>& usersData, vector<dataBaseofMenu>& data) {
	cleanScreen();
	string login,pass;
	Admins admin;
	Workers worker;
	Y = 13;
	int access = 0;
	gotoXY(hStdOut, X, Y++);
	SetBasicTextColor(hStdOut);
	cout << "Введите логин: ";
	getline(cin, login);
	gotoXY(hStdOut, X, Y++);
	if (findUser(login, usersData))
	{
		SetBasicTextColor(hStdOut);
		cout << "Введите пароль: ";
		getline(cin, pass);
		gotoXY(hStdOut, X, Y++);
		SetBasicTextColor(hStdOut);

		if (access = matchPass(login, pass, usersData)) {
			cout << "Вы успешно авторизовались!"; Sleep(3000); 
			if (access == 2) { admin.setLogin(login); admin.setPassword(pass); admin.setAccessLevel(access); adminPanel(usersData, data, admin); }
			else {
				worker.setLogin(login); worker.setPassword(pass); worker.setAccessLevel(access); workerPanel(data, worker);
			}
		}
		else { cout << "Вы ввели неверный пароль!"; Sleep(3000); return; }
	}
	else {
		SetBasicTextColor(hStdOut);
		cout << "Пользователь с таким логином не найден."; Sleep(3000);
		return;
	}
}

void loginPanel(vector<dataBaseofUsers>& usersData, vector<dataBaseofMenu>& data) {
	cleanScreen();
	char ch;
	int activeMenu = 0;
	vector<string> menu;
	menu.push_back("Авторизоваться");
	menu.push_back("Выйти");
	while (true) {
		Y = 13;
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:    if (activeMenu != 0) activeMenu--; break;
		case DOWN:  if (activeMenu != size(menu) - 1) activeMenu++; break;
		case ENTER: if (activeMenu == 0) { authorizationPanel(usersData,data); break; }
					if (activeMenu == 1) return;
		case ESCAPE: return;
		default: continue;
		}
		cleanScreen();
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	vector<dataBaseofUsers> usersData;
	vector<dataBaseofMenu> data;
	readFromFile(usersData);
	readFromFile(data);
	OrderTerminal orders;
	OrderMonitor window;
	OrderWorker windowAcception;
	windowAcception.setDB(data);
	windowAcception.setMonitor(window);
	std::thread windowThread(threadWork,window);
	windowThread.detach();
	std::thread _windowThread(_threadWork, windowAcception);
	_windowThread.detach();
	string menu[] = { "Сделать заказ", "Выход" };
	OrderTerminal::orderSetStarted();
	int activeMenu = 0;

	SetScreenTitle();
	SetUsualTextColor(hStdOut);
	CursorVisiability(hStdOut, false);

	char ch;
	while (true) {
		orders.setToNull();
		Y = 13;
		cleanScreen();
		for (int i = 0;i < size(menu);i++) {
			if (activeMenu == i) SetEventTextColor(hStdOut);
			else SetUsualTextColor(hStdOut);
			gotoXY(hStdOut, X, Y++);
			cout << menu[i];
		}
		ch = _getch();
		if (ch == 97) {
			ch = _getch();
			if (ch == 100) {
				ch = _getch();
				if (ch == 109) {
					loginPanel(usersData, data);
					continue;
				}
			}
		}
		if (ch == -32) {
			ch = _getch();
		}
		switch (ch) {
		case UP:    if (activeMenu != 0) activeMenu--; break;
		case DOWN:  if (activeMenu != size(menu) - 1) activeMenu++; break;
		case ENTER: if (activeMenu == 0) { eatingPlaceChoice(orders, data, window); break; }
				    if (activeMenu == 1) return 0;
		case ESCAPE: return 0;
		default: continue;
		}
		cleanScreen();
	}
}