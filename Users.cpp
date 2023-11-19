#include "Users.h"
#include "UserData.h"
#include "CsvFile.h"
#include "LinkedList.h"

Users::Users() {
    _list = LinkedList<UserData>();
}

Users::~Users() {
    _list.~LinkedList();
}

bool Users::addUser(const UserData& user) {
    for (int i = 0; i < _list.getSize(); i++) {
        if (_list[i].getUserName() == user.getUserName()) {
            return false;
        }
    }

    _list.addTail(user);
    return true;
}

void Users::removeUser(const UserData& user) {
    _list.remove(user);
}

bool Users::editUser(const std::string& userName, const UserData& user) {
    for (int i = 0; i < _list.getSize(); i++) {
        if (_list[i].getUserName() == userName) {
            _list[i] = user;
            return true;
        }
    }
    return false;
}

int Users::searchUser(const std::string& userName) const {
    for (int i = 0; i < _list.getSize(); i++) {
        if (_list[i].getUserName() == userName) {
            return i;
        }
    }
    return -1;
}

std::vector<UserData> Users::listUsers() const {
    std::vector<UserData> result;
    for (int i = 0; i < _list.getSize(); i++) {
        result.push_back(_list[i]);
    }
    return result;
}

bool Users::importUserData() {
    CsvFile csvFileAdmin("Administrators.txt");
    try {
        csvFileAdmin.read();
    } catch (const std::exception& e) {
        return false;
    }

    std::vector<std::vector<std::string>> accounts = csvFileAdmin.read();
    int iSizeAdmin = (int)accounts.size();

    CsvFile csvFileEmployee("Employees.txt");
    try {
        csvFileEmployee.read();
    } catch (const std::exception& e) {
        return false;
    }

    std::vector<std::vector<std::string>> newData = csvFileEmployee.read();
    accounts.insert(accounts.end(), newData.begin(), newData.end());

    for (auto userData : accounts) {
        std::vector<std::vector<std::string>> data = CsvFile(userData[0] + ".txt").read();
        std::string role = (userData.size() > iSizeAdmin) ? "Employee" : "Administrators";
        UserData user = UserData(data[1][0], "01/01/1900", data[1][1], data[1][2], data[1][3], userData[0], userData[1], role);
        _list.addTail(user);
    }

    return true;
}