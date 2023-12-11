#ifndef H_DATABASEOFMENU
#define H_DATABASEOFMENU

#include <vector>
#include <string>
#include <fstream>

class dataBaseofMenu {
public:
	int id;
	std::string price;
	std::string nameofItem;

	dataBaseofMenu();
	dataBaseofMenu(int, std::string, std::string);

	friend void insertIntoFile(std::vector<dataBaseofMenu>);
	friend void readFromFile(std::vector<dataBaseofMenu>&);

	friend void dataBaseAddInfo(std::vector<dataBaseofMenu>&,int);
	friend void dataBasePrint(std::vector<dataBaseofMenu>);

	friend double findPrice(std::string, std::vector<dataBaseofMenu>);
	friend dataBaseofMenu findItem(std::vector<dataBaseofMenu>, int);
	friend int findID(std::string, std::vector<dataBaseofMenu>);
	friend void idOnDelete(std::vector<dataBaseofMenu>&, int);

	friend std::vector<std::string> showOrder(std::vector<dataBaseofMenu>, std::vector<int>);
	void getInfo();

	dataBaseofMenu& operator=(const dataBaseofMenu& temp);
};
#endif
