#include "OrderTerminal.h"
#include <vector>
#include <iostream>

int OrderTerminal::orderidbase;
bool OrderTerminal::orderstarted;

void OrderTerminal::orderSetStarted() {
	OrderTerminal::orderstarted = true;
	OrderTerminal::orderidbase = 10000;
}

void OrderTerminal::IncrementBaseOrderId() {
	if(OrderTerminal::orderidbase<10500) OrderTerminal::orderidbase +=1;
}

void OrderTerminal::setNewOrderId() {
	this->orderid = OrderTerminal::orderidbase;
	OrderTerminal::IncrementBaseOrderId();
}

OrderTerminal::OrderTerminal() {
	eatingPlace = false;
	price = 0;
	orderid = 0;
}

void OrderTerminal::addItem(int item, double prices) {
	order.push_back(item);
	price = prices + price;
}

void OrderTerminal::setEatingPlace(bool choice) {
	eatingPlace = choice;
}

void OrderTerminal::showOrderNames(std::vector<dataBaseofMenu> data) {
	std::vector<std::string> names=showOrder(data,this->order);
	int size = names.size();
	for (int i = 0;i < size;i++) {
		std::cout << names[i] << std::endl;
	}
	std::cout << std::endl << std::endl;
	if (this->price != 0) std::cout << "Цена : " << this->price;
}

void OrderTerminal::showOrders(std::vector<dataBaseofMenu> data) {
	int size = order.size();
	int dbsize = data.size();
	int code = 0;
	for (int i = 0;i < size;i++) {
		code = order[i];
		for (int j = 0;j < dbsize;j++) {
			if (code == data[j].id) std::cout << data[j].nameofItem << std::endl;
		}
	}
}

void OrderTerminal::setToNull() {
	price = 0;
	eatingPlace = false;
	order.clear();
}

std::wstring OrderTerminal::getOrderWNames(std::vector<dataBaseofMenu> data) {
	int size = order.size();
	int dbsize = data.size();
	int code = 0;
	std::string str = "Order:\n";
	for (int i = 0;i < size;i++) {
		code = order[i];
		for (int j = 0;j < dbsize;j++) {
			if (code == data[j].id) {
				if (i != size-1) { str += data[j].nameofItem + ",\n"; }
				else str += data[j].nameofItem + ".\n";
			}
		}
	}
	std::wstring message(str.begin(), str.end());
	return message;
}