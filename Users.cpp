#include "Users.h"
#include "UserData.h"
#include "LinkedList.h"
#include "CSVFile.h"

Users::Users() {
    _list = LinkedList<UserData>();
}

Users::~Users() {
    _list.~LinkedList();
}

bool Users::addUser(const UserData& user) {
    for (int i = 0; i < _list.getSize(); i++)
    {
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

bool Users::editUser(const std::string userName, const UserData& user) {
    for (int i = 0; i < _list.getSize(); i++)
    {
        if (_list[i].getUserName() == userName) {
            _list[i] = user;
            return true;
        }
    }
    return false;
}

int Users::searchUser(const std::string userName) const {
    for (int i = 0; i < _list.getSize(); i++)
    {
        if (_list[i].getUserName() == userName) {
            return i;
        }
    }
    return -1;
}

std::vector<UserData> Users::listUsers() const {
    std::vector<UserData> result;
    for (int i = 0; i < _list.getSize(); i++)
    {
        result.push_back(_list[i]);
    }
    return result;
}

bool Users::importUserData() {
    CsvFile csvFile("Administrators.txt");
    try {
        csvFile.read();
    }
    catch (const std::exception& e) {
        return false;
    }

    std::vector<std::vector<std::string>> account = csvFile.read();
    int iSizeAdmin = account.size();
    CsvFile csvFile("Employee.txt");

    try {
        csvFile.read();
    }
    catch (const std::exception& e) {
        return false;
    }

    std::vector<std::vector<std::string>> newData = CsvFile("Employee.txt").read();
    account.insert(account.end(), newData.begin(), newData.end());

    for (int i = 1; i <= account.size(); i++) {
        std::string path = account[i][0] + ".txt";
        CsvFile csvFile(path);
        std::vector<std::vector<std::string>> data = csvFile.read();
        std::string role;
        if (i <= iSizeAdmin) role = "Administrators";
        else role = "Employee";
        UserData user = UserData(data[1][0], "01/01/1900", data[1][1], data[1][2], data[1][3], account[i][0], account[i][1], role);
        _list.addTail(user);
    }

    return true;
}