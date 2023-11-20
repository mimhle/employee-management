#include "Users.h"

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
    std::vector<UserData> vtResult;
    for (int i = 0; i < _list.getSize(); i++) {
        vtResult.push_back(_list[i]);
    }
    return vtResult;
}

bool Users::importUserData() {
    std::vector<std::vector<std::string>> vtAdminAccounts;
    try {
        CsvFile csvFileAdmin("Administrators.txt");
        vtAdminAccounts = csvFileAdmin.read(1);
    } catch (const std::exception& e) {
        return false;
    }

    std::vector<std::vector<std::string>> vtEmployeeAccounts;
    try {
        CsvFile csvFileEmployee("Employees.txt");
        vtEmployeeAccounts = csvFileEmployee.read(1);
    } catch (const std::exception& e) {
        return false;
    }

    std::vector<std::vector<std::string>> vtAccount = vtAdminAccounts;
    vtAccount.insert(vtAccount.end(), vtEmployeeAccounts.begin(), vtEmployeeAccounts.end());

    for (int i = 0; i < vtAccount.size(); i++) {
        std::vector<std::vector<std::string>> data;
        try {
            CsvFile csvFile(vtAccount[i][0] + ".txt");
            data = csvFile.read();
        } catch (const std::exception& e) {
            return false;
        }
        std::string role = (i >= vtAdminAccounts.size()) ? "Employee" : "Administrators";
        UserData user = UserData(data[1][0], "01/01/1900", data[1][1], data[1][2], data[1][3], vtAccount[i][0], vtAccount[i][1], role);
        _list.addTail(user);
    }

    return true;
}