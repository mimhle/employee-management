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

void UserAction::addUser(const UserData& user) {
    if (!(_strRole == "Admin")) return;
    CsvFile csvFileEmployee("Employees.txt");
    csvFileEmployee.append(
        {
            {user.getUserName(), ",", user.getPassword()}
        }
    );
    CsvFile newUser(user.getUserName() + ".txt");
    newUser.write(
        {
            {user.getName()},
            {user.getDateOfBirth()},
            {user.getAddress()},
            {user.getPhoneNumber()},
            {user.getEmail()}
        }
    );
    _usersList.addUser(user);
}

void UserAction::deleteUser(const UserData& user) {
    if (!(_strRole == "Admin")) return;
    CsvFile csvFileEmployee("Employees.txt");
    std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
    int iLine = -1;
    for (int i = 0; i < vtEmployeeAccounts.size(); i++) {
        if (vtEmployeeAccounts[i][0] == user.getName()) {
            iLine = i;
            break;
        }
    }
    if (iLine != -1) {
        csvFileEmployee.remove(iLine);
        _usersList.removeUser(user);
    }
}

UserData UserAction::findUser(const std::string& userName) {
    if (!(_strRole == "Admin")) return {};
    std::vector<UserData> vtUsersDataList = _usersList.listUsers();
    int userNum = _usersList.searchUser(userName);
    return vtUsersDataList[userNum];
}

void UserAction::updateUserInformation(const std::string& userName, const UserData& user) {
    _usersList.editUser(userName, user);
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
    CsvFile csvFileEmployee("Employees.txt");
    std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
    int iLine = -1;
    for (int i = 0; i < vtEmployeeAccounts.size(); i++) {
        if (vtEmployeeAccounts[i][0] == user.getName()) {
            iLine = i;
            break;
        }
    }
    if (iLine != 1) {
        csvFileEmployee.remove(iLine);
        csvFileEmployee.append(
            {
                {user.getUserName(), ",", user.getPassword()}
            }
        );
    }
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
    for (auto& data: vtUsersDataList) {
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
    std::vector<std::vector<std::string>> vtUserAccounts;
    if (_strRole == "Admin") {
        CsvFile csvFileUsers("Administrators.txt");
        vtUserAccounts = csvFileUsers.read();
    } else {
        CsvFile csvFileUsers("Employees.txt");
        vtUserAccounts = csvFileUsers.read();
    }
    for (auto& row: vtUserAccounts) {
        if (row[0] == userName && row[1] == password) return true;
    }
    return false;
}

