#ifndef H_WORKERS
#define H_WORKERS

#include <vector>
#include <string>

class dataBaseofMenu;

class Workers
{
	std::string login;
	std::string password;
	int accessLevel;
public:
	Workers();
	void setLogin(std::string);
	void setPassword(std::string);
	void setAccessLevel(int);
	int getAccessLevel();
	std::string getLogin();
	void addPositionsToMenu(std::vector<dataBaseofMenu>&);
	void changePrice(std::vector<dataBaseofMenu>&);
	void deletePos(std::vector<dataBaseofMenu>&);

	friend class dataBaseofUsers;
};

#endif