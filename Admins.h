#ifndef H_ADMINS
#define H_ADMINS

#include "Workers.h"
#include <string>

class dataBaseofUsers;

class Admins :
    public Workers
{
public:
    void addUser(std::vector<dataBaseofUsers>&);
    void addAdmin(std::vector<dataBaseofUsers>&);
    friend void dataBaseAddInfo(Workers, std::vector<dataBaseofUsers>&);
    friend void dataBaseAddInfo(Admins, std::vector<dataBaseofUsers>&);
    void deleteUser(std::vector<dataBaseofUsers>&);
    void changeLevelAccess(std::vector<dataBaseofUsers>&);
    
};


#endif