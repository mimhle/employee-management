#include <iostream>
#include <ctime>
#include <string>
#include "User.h"

User::User(std::string name, std::string dateOfBirth, std::string address, std::string phoneNumber,
    std::string email, std::string username, std::string password, std::string role
) {
    _strName = name;
    _strDateOfBirth = dateOfBirth;
    _iAge = userAge();
    _strAddress = address;
    _strPhoneNumber = phoneNumber;
    _strEmail = email;
    _strUserName = username;
    _strPassword = password;
    _strRole = role;
}

User::User() {
    _strName = "";
    _strDateOfBirth = "";
    _iAge = 0;
    _strAddress = "";
    _strPhoneNumber = "";
    _strEmail = "";
    _strUserName = "";
    _strPassword = "";
    _strRole = "";
}

User::~User() {
    _strName = "";
    _strDateOfBirth = "";
    _iAge = 0;
    _strAddress = "";
    _strPhoneNumber = "";
    _strEmail = "";
    _strUserName = "";
    _strPassword = "";
    _strRole = "";
}

int User::userAge() {
    time_t currentTime = time(0);

    tm* pLocalTime = localtime(&currentTime);
    int iCurrentDay = pLocalTime->tm_mday;
    int iCurrentMonth = 1 + pLocalTime->tm_mon;
    int iCurrentYear = 1900 + pLocalTime->tm_year;

    //type string dateOfBirth DD/MM/YYYY
    int dayOfBirth = std::stoi(_strDateOfBirth.substr(0, 2));
    int monthOfBirth = std::stoi(_strDateOfBirth.substr(3, 2));
    int yearOfBirth = std::stoi(_strDateOfBirth.substr(6, 4));

    if (monthOfBirth > iCurrentMonth) {
        _iAge = iCurrentYear - yearOfBirth - 1;
    } else if (monthOfBirth < iCurrentMonth) {
        _iAge = iCurrentYear - yearOfBirth;
    } else {
        if (dayOfBirth > iCurrentDay) {
            _iAge = iCurrentYear - yearOfBirth - 1;
        } else {
            _iAge = iCurrentYear - yearOfBirth;
        }
    }

    return _iAge;
}

std::string User::getName() const { return _strName; }

void User::setName(std::string name) { _strName = name; }

std::string User::getDateOfBirth() const { return _strDateOfBirth; }

void User::setDateOfBirth(std::string dateOfBirth) {
    _strDateOfBirth = dateOfBirth;
    _iAge = userAge();
}

int User::getAge() { return _iAge; }

std::string User::getAddress() const { return _strAddress; }

void User::setAddress(std::string address) { _strAddress = address; }

std::string User::getPhoneNumber() const { return _strPhoneNumber; }

void User::setPhoneNumber(std::string phoneNumber) { _strPhoneNumber = phoneNumber; }

std::string User::getEmail() const { return _strEmail; }

void User::setEmail(std::string email) { _strEmail = email; }

std::string User::getUserName() const { return _strUserName; }

void User::setUserName(std::string username) { _strUserName = username; }

std::string User::getPassword() const { return _strPassword; }

void User::setPassword(std::string password) { _strPassword = password; }

std::string User::getRole() const { return _strRole; }

void User::setRole(std::string role) { _strRole = role; }

bool User::operator!=(const User& user) const {
    return _strUserName != user._strUserName && _strPassword != user._strPassword && _strRole != user._strRole && _strName != user._strName && _strDateOfBirth != user._strDateOfBirth && _iAge != user._iAge && _strAddress != user._strAddress && _strPhoneNumber != user._strPhoneNumber && _strEmail != user._strEmail;
}