#include "Users.h"
#include "UserData.h"
#include "LinkedList.h"

Users::Users() {
    _list = LinkedList<UserData>();
}

Users::~Users() {
    _list.~LinkedList();
}

void Users::addUser(const UserData& user) {
    for (int i = 0; i < _list.getSize(); i++)
    {
        if (_list[i].getUserName() == user.getUserName()) {
            throw std::invalid_argument("User already exists");
        }
    }

    _list.addTail(user);
}

void Users::removeUser(const UserData& user) {
    _list.remove(user);
}

void Users::editUser(const std::string userName, const UserData& user) {
    for (int i = 0; i < _list.getSize(); i++)
    {
        if (_list[i].getUserName() == userName) {
            _list[i] = user;
            return;
        }
    }
    throw std::invalid_argument("User not found");
}

UserData Users::searchUser(const std::string userName) const {
    for (int i = 0; i < _list.getSize(); i++)
    {
        if (_list[i].getUserName() == userName) {
            return _list[i];
        }
    }
    throw std::invalid_argument("User not found");
}