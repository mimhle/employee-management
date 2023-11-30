#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef CTDL_GK_USERS_H
#define CTDL_GK_USERS_H

#include <string>
#include <vector>
#include "LinkedList.cpp"
#include "UserData.h"
#include "CsvFile.h"

/**
 * @class Users
 * @brief Class for Users
 * @details This class contains functions for Users
 */
class Users {
private:
    LinkedList<UserData> _list;
public:
    Users();

    ~Users();

    /**
     * @brief Add user to list
     * @param user User to add
     * @return True if success, false if failed
     */
    bool addUser(const UserData& user);

    /**
     * @brief Remove user from list
     * @param userName Username of user to remove
     * @return True if success, false if failed
     */
    bool removeUser(const std::string& userName);

    /**
     * @brief Edit user in list
     * @param userName Username of user to edit
     * @param user New user data
     * @return True if success, false if failed
     */
    bool editUser(const std::string& userName, const UserData& user);

    /**
     * @brief Search user in list
     * @param userName Username of user to search
     * @return Index of user in list if found, -1 if not found
     */
    int searchUser(const std::string& userName) const;

    /**
     * @brief List all users
     * @return List of users
     */
    std::vector<UserData> listUsers() const;

    /**
     * @brief Import user data from file
     * @return True if success, false if failed
     */
    bool importUserData();
};


#endif //CTDL_GK_USERS_H

#pragma clang diagnostic pop