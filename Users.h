#ifndef CTDL_GK_USERS_H
#define CTDL_GK_USERS_H

#include <string>
#include <vector>
#include "UserData.h"
#include "LinkedList.h"

class Users {
private:
    LinkedList<UserData> _list;
public:
    Users();

    ~Users();

    void addUser(const UserData& user);

    void removeUser(const UserData& user);

    void editUser(const std::string userName, const UserData& user);

    UserData searchUser(const std::string userName) const;

    std::vector<std::vector<std::string>> listUsers(...) const;

    void loadListUsers();
};


#endif //CTDL_GK_USERS_H
