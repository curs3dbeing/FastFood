#ifndef H_ORDERTERMINAL
#define H_ORDERTERMINAL

#include "dataBaseofMenu.h"
#include <vector>

class OrderTerminal {
public:
	static int orderidbase;
	static bool orderstarted;
	double price;
	std::vector<int> order;
	bool eatingPlace;
	int orderid;

	OrderTerminal();

	static void orderSetStarted();
	static void IncrementBaseOrderId();
	void setNewOrderId();
	void setToNull();
	void addItem(int, double);
	void showOrders(std::vector<dataBaseofMenu>);
	void showOrderNames(std::vector<dataBaseofMenu> data);
	void setEatingPlace(bool);
	std::wstring getOrderWNames(std::vector<dataBaseofMenu>);
};

#endif