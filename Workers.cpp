#include <vector>
#include <iostream>
#include <string>
#include "Workers.h"
#include <Windows.h>
#include <conio.h>
#include "dataBaseofMenu.h"

Workers::Workers() {
	login = "";
	password = "";
	accessLevel = 0;
}

void Workers::setLogin(std::string login) {
	this->login = login;
}
void Workers::setPassword(std::string pass) {
	this->password = pass;
}
void Workers::setAccessLevel(int lvl) {
	this->accessLevel = lvl;
}

int Workers::getAccessLevel() {
	return this->accessLevel;
}
std::string Workers::getLogin() {
	return this->login;
}

void Workers::addPositionsToMenu(std::vector<dataBaseofMenu>& data) {
	std::cout << "Введите количество позиций ";
	int n;
	std::cin >> n;
	std::cin.get();
	dataBaseAddInfo(data, n);
	insertIntoFile(data);
}
void Workers::deletePos(std::vector<dataBaseofMenu>& data) {
	std::cout << "Введите id поля, которое желаете удалить ";
	int n;
	std::cin >> n;
	idOnDelete(data, n);
}

void Workers::changePrice(std::vector<dataBaseofMenu>& data) {
	std::cout << "Введите id поля в меню, цену которого желаете изменить ";
	int id;
	std::string price;
	std::cin >> id;
	std::cout << std::endl;
	size_t size = data.size();
	for (size_t i = 0;i < size;i++) {
		if (data[i].id == id) {
			std::cout << "Введите новую цену ";
			std::cin >> price;
			data[i].price = price;
			std::cout << "Цена успешно изменена!";
			Sleep(1000);
			insertIntoFile(data);
			return;
		}
	}
	std::cout << "Нет позиции с заданным id";
	Sleep(1000);
	return;
}
