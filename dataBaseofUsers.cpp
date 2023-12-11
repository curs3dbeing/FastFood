#include <iostream>
#include <fstream>
#include "dataBaseofUsers.h"
#include <vector>
#include <string>
#include "Admins.h"
#include "Workers.h"
#include <Windows.h>
#include <conio.h>



dataBaseofUsers::dataBaseofUsers() {
	login = "";
	password = "";
	accessLevel = 0;
}

dataBaseofUsers::dataBaseofUsers(std::string login1, std::string password1, int accessLevel1) {
	login = login1;
	password = password1;
	accessLevel = accessLevel1;
}

std::string dataBaseofUsers::getPassword() {
	return this->password;
}

std::string dataBaseofUsers::getLogin() {
	return this->login;
}

int dataBaseofUsers::getAccessLevel() {
	return this->accessLevel;
}

int countFileSize1(const char* path) {
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

void insertIntoFile(std::vector<dataBaseofUsers> data) {
	const char* path = "C:\\Users\\USER\\Desktop\\Practice\\Users.dat";
	std::ofstream insert(path, std::ios::out | std::ios::trunc);
	if (!insert.is_open()) {
		std::cerr << "Ошибка при открытии файла." << std::endl;
		return;
	}
	int size = data.size();
	insert << size << " ";
	for (int i = 0;i < size;i++) {
		insert << data[i].getLogin() << " ";
		insert << data[i].getPassword() << " ";
		insert << data[i].getAccessLevel() << " ";
	}
}

void readFromFile(std::vector<dataBaseofUsers>& data) {
	const char* path = "C:\\Users\\USER\\Desktop\\Practice\\Users.dat";
	std::ifstream read(path, std::ios::in);
	if (!read.is_open()) {
		std::cerr << "Ошибка при открытии файла." << std::endl;
		return;
	}
	dataBaseofUsers temp;
	std::string login;
	std::string pass;
	std::string access;
	getline(read, login, ' ');
	int size = stoi(login);
	while (getline(read, temp.login, ' ')) {
		getline(read, temp.password, ' ');
		getline(read, access, ' ');
		temp.accessLevel = stoi(access);
		data.push_back(temp);
	}
}

void dataBasePrint(std::vector<dataBaseofUsers> data) {
	int n = data.size();
	std::cout.width(20);
	std::cout << std::left << "LOGIN" << std::right << "PASSWORD";
	std::cout.width(30);
	std::cout << std::right << "ACCESSLEVEL" << std::endl;
	for (int i = 0;i < n;i++) {
		std::cout.width(20);
		std::cout << std::left << data[i].getLogin();
		std::cout << std::right << data[i].getPassword();
		std::cout.width(28 - (data[i].getPassword()).size());
		std::cout << std::right << data[i].getAccessLevel();
		std::cout << std::endl;
	}
}

void dataBaseAddInfo(Workers user, std::vector<dataBaseofUsers>& data) {
	std::string login, password;
	std::cout << "Enter login" << std::endl;
	std::getline(std::cin, login);
	std::cout << "Enter password" << std::endl;
	std::getline(std::cin, password);
	data.push_back(dataBaseofUsers(login, password, 1));
	user.setAccessLevel(1);
	user.setLogin(login);
	user.setPassword(password);
	insertIntoFile(data);
	std::cout << "User created!" << std::endl;
	Sleep(1000);
}

void dataBaseAddInfo(Admins user, std::vector<dataBaseofUsers>& data) {
	std::string login, password;
	std::cout << "Enter login" << std::endl;
	std::getline(std::cin, login);
	std::cout << "Enter password" << std::endl;
	std::getline(std::cin, password);
	data.push_back(dataBaseofUsers(login, password, 2));
	user.setAccessLevel(2);
	user.setLogin(login);
	user.setPassword(password);
	std::cout << "Admin created!" << std::endl;
	insertIntoFile(data);
	Sleep(1000);
}

bool findUser(std::string login, std::vector<dataBaseofUsers> data) {
	size_t size = data.size();
	for (size_t i = 0;i < size;i++) {
		if (login == data[i].getLogin()) return true;
	}
	return false;
}

int matchPass(std::string login, std::string pass, std::vector<dataBaseofUsers> data)
{
	size_t size = data.size();
	for (size_t i = 0;i < size;i++) {
		if (login == data[i].getLogin() && pass == data[i].getPassword()) return data[i].getAccessLevel();
	}
	return 0;
}

void userOnDelete(std::vector<dataBaseofUsers>& data, std::string login) {
	size_t size = data.size();
	std::cout.width(63);
	std::cout.right;
	for (size_t i = 0;i < size;i++) {
		if (data[i].getLogin() == login)
		{
			data.erase(data.begin() + i);
			std::cout << "Пользователь с логином " << login << " удален!";
			Sleep(1000);
			system("cls");
			return;
		}
	}
	std::cout << "Пользователь с логином " << login << " не найден!";
	Sleep(1000);
	system("cls");
}

void changeUserAccessLevel(std::vector<dataBaseofUsers>& data, std::string login) {
	size_t size = data.size();
	for (size_t i = 0;i < size;i++) {
		if (data[i].getLogin() == login)
		{
			if (data[i].getAccessLevel() == 2) {
				data[i].accessLevel = 1;
				std::cout.width(63);
				std::cout.right;
				std::cout << "Уровень доступа пользователя " << login << " изменен!";
				Sleep(1000);
				system("cls");
				return;
			}
			else {
				std::cout.width(33);
				std::cout.right;
				std::cout << "Уровень доступа пользователя " << login << " не может быть изменен, он равен 1, удалите пользователя.";
				Sleep(1000);
				system("cls");
				return;
			}
		}
	}
	std::cout.width(63);
	std::cout.right;
	std::cout << "Пользователь с логином " << login << " не найден!";
	Sleep(1000);
	system("cls");
}