#ifndef H_DATABASEOFUSERS
#define H_DATABASEOFUSERS

#include <string>
#include <vector>
#include "dataBaseofMenu.h"
#include "Workers.h"
#include "Admins.h"

class dataBaseofUsers
{
private:
	std::string password;
	std::string login;
	int accessLevel;
public:
	dataBaseofUsers();
	dataBaseofUsers(std::string, std::string, int);

	std::string getPassword();
	std::string getLogin();
	int getAccessLevel();

	friend class Workers;
	friend class Admins;

	friend int countFileSize1(const char*);
	friend void insertIntoFile(std::vector<dataBaseofUsers>);
	friend void readFromFile(std::vector<dataBaseofUsers>&);
	friend void dataBasePrint(std::vector<dataBaseofUsers>);
	friend void dataBaseAddInfo(Workers, std::vector<dataBaseofUsers>&);
	friend void dataBaseAddInfo(Admins, std::vector<dataBaseofUsers>&);
	friend bool findUser(std::string, std::vector<dataBaseofUsers>);
	friend void userOnDelete(std::vector<dataBaseofUsers>&, std::string);
	friend int matchPass(std::string, std::string, std::vector<dataBaseofUsers>);
	friend void changeUserAccessLevel(std::vector<dataBaseofUsers>&, std::string);
};

#endif