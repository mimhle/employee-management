#include "UserAction.h"
#include "CsvFile.h"
#include "Users.h"
#include "UserData.h"

UserAction::UserAction(std::string role) {
    _strRole = std::move(role);
    _usersList.importUserData(); 
}

UserAction::UserAction() {
    _strRole = "";
    _usersList.importUserData();
}

void UserAction::setRole(std::string role) {
    _strRole = role;
    _usersList.~Users();
    _usersList.importUserData();
}

bool UserAction::addUser(const UserData& user) {
    if (!(_strRole == "Admin" && _usersList.addUser(user))) return false;
    CsvFile csvFileEmployee("Employees.txt");
    csvFileEmployee.append(
        {
            {user.getUserName() + "," + user.getPassword()}
        }
    );
    CsvFile csvFileNewUser(user.getUserName() + ".txt");
    csvFileNewUser.write(
        {
            {user.getName()},
            {user.getDateOfBirth()},
            {user.getAddress()},
            {user.getPhoneNumber()},
            {user.getEmail()}
        }
    );
    return true;
}

bool UserAction::deleteUser(const std::string& userName) {
    if (_strRole == "Admin" && _usersList.removeUser(userName)) {
        CsvFile csvFileEmployee("Employees.txt");
        std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
        int iLine = -1;
        for (int i = 0; i < vtEmployeeAccounts.size(); i++) {
            if (vtEmployeeAccounts[i][0] == userName) {
                iLine = i;
                break;
            }
        }
        if (iLine != -1) {
            csvFileEmployee.remove(iLine);
            CsvFile csvFileDelete(userName + ".txt");
            csvFileDelete.del();
            return true;
        }
    }
    return false;
}

UserData UserAction::findUser(const std::string& userName) {
    if (!( _usersList.searchUser(userName)!=-1)) return {};
    std::vector<UserData> vtUsersDataList = _usersList.listUsers();
    int iUserNum = _usersList.searchUser(userName);
    return vtUsersDataList[iUserNum];
}

bool UserAction::updateUserInformation(const std::string& userName, const UserData& user) {
    if(!(_usersList.editUser(userName,user))) return false;
    CsvFile csvFileEmployee("Employees.txt");
    std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
    int iLine = -1;
    for (int i = 1; i <= vtEmployeeAccounts.size(); i++) {
        if (vtEmployeeAccounts[i][0] == userName) {
            iLine = i;
            break;
        }
    }
    if (iLine != -1) {
        csvFileEmployee.remove(iLine);
        csvFileEmployee.append(
            {
                {user.getUserName() + "," + user.getPassword()}
            }
        );
        CsvFile csvFileUser(userName + ".txt");
        csvFileUser.write(
            {
                {user.getName()},
                {user.getDateOfBirth()},
                {user.getAddress()},
                {user.getPhoneNumber()},
                {user.getEmail()}
            }
        );
        return true;
    }
    return false;
}

std::string UserAction::getUserInformation(const std::string& userName) {
    std::string strUserData;
    CsvFile csvFileUser(userName + ".txt");
    std::vector<std::vector<std::string>> vtDataUser = csvFileUser.read();
    for (auto& v: vtDataUser) {
        for (auto& s: v) {
            strUserData += s + " ";
        }
    }
    return strUserData;
}

std::vector<std::string> UserAction::getAllUsersInformation() {
    if (_strRole != "Admin") return {"None user were found"};
    std::vector<std::string> strUsers;
    std::vector<UserData> vtUsersDataList = _usersList.listUsers();
    for (const auto& data: vtUsersDataList) {
        if (data.getRole() == "Employee") {
            strUsers.push_back(
                data.getName() + " " + data.getDateOfBirth() + " " + data.getAddress() + " " + data.getPhoneNumber() +
                " " + data.getEmail()
            );
        }
    }
    return strUsers;
}

bool UserAction::authenticateUser(const std::string& userName, const std::string& password) {
    std::vector<std::vector<std::string>> vtAccountsUser;
    if (_strRole == "Admin") {
        CsvFile csvFileAdmin("Administrators.txt");
        vtAccountsUser = csvFileAdmin.read();
        for (int i = 1; i < vtAccountsUser.size(); i++) {
            if (vtAccountsUser[i][0] == userName && vtAccountsUser[i][1] == password) return true;
        }
    }
    else {
        CsvFile csvFileEmployee("Employees.txt");
        vtAccountsUser = csvFileEmployee.read();
        for (int i = 1; i < vtAccountsUser.size(); i++) {
           if (vtAccountsUser[i][0] == userName && vtAccountsUser[i][1] == password) return true;
        }
    }
    return false;
}