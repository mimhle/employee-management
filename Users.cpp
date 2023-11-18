#include "Users.h"

Users::Users() {
    _pUsers = new LinkedList<UserData*>();
}

Users::~Users() {
    delete _pUsers;
}

void Users::addUser(UserData* userData) {
    _pUsers->addTail(userData);
}

void Users::removeUser(const std::string& userName) {

}

void Users::editUser(const std::string& userName, UserData* userData) {

}

void Users::searchUser(const std::string& userName) {

}

void Users::printUsers() {

}
