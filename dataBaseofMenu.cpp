#include <iostream>
#include <fstream>
#include "dataBaseofMenu.h"
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>

dataBaseofMenu::dataBaseofMenu() {
	id = 0;
	price = "";
	nameofItem = "";
}

dataBaseofMenu::dataBaseofMenu(int items, std::string prices, std::string name) {
	id = items;
	nameofItem = name;
	price = prices;
}

int countFileSize(const char* path) {
	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
	if (path) {
		std::ifstream::pos_type size = file.tellg();
		file.close();
		return size;
	}
	else {
		file.close();
		std::cerr << "No file in such derictory" << std::endl;
		return 0;
	}
}

void insertIntoFile(std::vector<dataBaseofMenu> data) {
	const char* path = "C:\\Users\\USER\\Desktop\\Practice\\FoodMenu.dat";
	std::ofstream insert(path, std::ios::out | std::ios::trunc);
	if (!insert.is_open()) {
		std::cerr << "Ошибка при открытии файла." << std::endl;
		return;
	}
	int size = data.size();
	insert << size << ";";
	for (int i = 0;i < size;i++) {
		insert << data[i].id << ";";
		insert << data[i].price << ";";
		insert << data[i].nameofItem << ";";
	}
}

void readFromFile(std::vector<dataBaseofMenu>& data) {
	const char* path = "C:\\Users\\USER\\Desktop\\Practice\\FoodMenu.dat";
	std::ifstream read(path, std::ios::in | std::ios::binary);
	if (!read.is_open()) {
		std::cerr << "Ошибка при открытии файла." << std::endl;
		return;
	}
	dataBaseofMenu temp;
	std::string nameofitem;
	std::string id;
	std::string price;
	getline(read, nameofitem, ';');
	while (getline(read, id, ';')) {
		temp.id = stoi(id);
		getline(read, price, ';');
		temp.price = price;
		getline(read, nameofitem, ';');
		temp.nameofItem = nameofitem;
		data.push_back(temp);
	}
}

void dataBaseofMenu::getInfo() {
	std::cout << this->id << " " << nameofItem << " " << price << std::endl;
}

int findID(std::string name,std::vector<dataBaseofMenu> data) {
	int size = data.size();
	for (int i = 0;i < size;i++) {
		if (name == data[i].nameofItem) return data[i].id;
	}
}

double findPrice(std::string name, std::vector<dataBaseofMenu> data) {
	int size = data.size();
	for (int i = 0;i < size;i++) {
		if (name == data[i].nameofItem) return stod(data[i].price);
	}
}

std::vector<std::string> showOrder(std::vector<dataBaseofMenu> data, std::vector<int> order) {
	int dbsize = data.size();
	int vecsize = order.size();
	std::vector<std::string> str;
	for (int i = 0;i < vecsize;i++) {
		for (int j = 0;j < dbsize;j++) {
			if (order[i] == data[j].id)
			{
				str.push_back(data[j].nameofItem);
				break;
			}
		}
	}
	return str;
}

dataBaseofMenu& dataBaseofMenu::operator=(const dataBaseofMenu& temp) {
	this->id = temp.id;
	this->nameofItem = temp.nameofItem;
	this->price = temp.price;
	return *this;
}

void dataBaseAddInfo(std::vector<dataBaseofMenu>& data, int n) {
	std::string name;
	int code = 0;
	std::string price;
	for (int i = 0;i < n;i++) {
		std::cout << "Enter name of position in menu" << std::endl;
		std::getline(std::cin, name);
		std::cout << "Enter code of this position in menu" << std::endl;
		std::cin >> code;
		std::cout << "Enter price of this position in menu" << std::endl;
		std::cin >> price;
		data.push_back(dataBaseofMenu(code,price,name));
		name.clear();
		std::cin.get();
	}
	std::system("cls");
}

void dataBasePrint(std::vector<dataBaseofMenu> data) {
	int n = data.size();
	std::cout.width(23);
	std::cout << std::left << "ID" << std::right << "NAME";
	std::cout.width(30);
	std::cout << std::right << "PRICE" << std::endl;
	for (int i = 0;i < n;i++) {
		std::cout << std::left << data[i].id;
		std::cout.width(20+std::string(data[i].nameofItem).size());
		std::cout << std::right << data[i].nameofItem;
		if (stod(data[i].price) <= 10) {
			std::cout.width(29 + 4 - data[i].nameofItem.size());
			std::cout << std::right << data[i].price << std::endl;
		}
		else {
			std::cout.width(29 + 5 - data[i].nameofItem.size());
			std::cout << std::right << data[i].price << std::endl;
		}
	}
}

void idOnDelete(std::vector<dataBaseofMenu>& data, int id) {
	size_t size = data.size();
	std::cout.width(63);
	std::cout.right;
	for (size_t i = 0;i < size;i++) {
		if (data[i].id == id)
		{
			data.erase(data.begin() + i);
			std::cout << "Поле в меню с id " << id << " удаленo!";
			Sleep(1000);
			system("cls");
			insertIntoFile(data);
			return;
		}
	}
	std::cout << "Поле в меню с id " << id << " не найдено!";
	Sleep(1000);
	system("cls");
}