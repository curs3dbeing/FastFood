#include "Admins.h"
#include "dataBaseofUsers.h"
#include <vector>
#include <iostream>
#include <string>

void Admins::addAdmin(std::vector<dataBaseofUsers>& data) {
	Admins admin;
	dataBaseAddInfo(admin, data);
}

void Admins::addUser(std::vector<dataBaseofUsers>& data) {
	Workers admin;
	dataBaseAddInfo(admin, data);
}

void Admins::deleteUser(std::vector<dataBaseofUsers>& data) {
	std::cout << "Введите логин пользователя, которого вы желаете удалить : ";
	std::string login;
	getline(std::cin, login);
	userOnDelete(data, login);
	insertIntoFile(data);
}

void Admins::changeLevelAccess(std::vector<dataBaseofUsers>& data) {
	std::cout << "Введите логин пользователя, уровень доступа которого вы желаете изменить : ";
	std::string login;
	getline(std::cin, login);
	changeUserAccessLevel(data, login);
	insertIntoFile(data);
}