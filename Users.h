#ifndef CTDL_GK_USERS_H
#define CTDL_GK_USERS_H

#include <string>
#include "UserData.h"

class Users {
public:
    Users();

    ~Users();

    void addUser(UserData* userData);

    void removeUser(const std::string& userName);

    void editUser(const std::string& userName, UserData* userData);

    void searchUser(const std::string& userName);

};


#endif //CTDL_GK_USERS_H
