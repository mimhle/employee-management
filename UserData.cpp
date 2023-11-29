#include <iostream>
#include <ctime>
#include <string>
#include "UserData.h"

UserData::UserData(std::string name, std::string dateOfBirth, std::string address, std::string phoneNumber,
    std::string email, std::string username, std::string password, std::string role
) {
    _strName = name;
    _strDateOfBirth = dateOfBirth;
    _iAge = userAge(dateOfBirth);
    _strAddress = address;
    _strPhoneNumber = phoneNumber;
    _strEmail = email;
    _strUserName = username;
    _strPassword = password;
    _strRole = role;
}

UserData::UserData() {
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

UserData::~UserData() {
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

int UserData::userAge(std::string dateOfBirth) {
    int iAge = 0;
    time_t currentTime = time(0);

    tm* pLocalTime = localtime(&currentTime);
    int iCurrentDay = pLocalTime->tm_mday;
    int iCurrentMonth = 1 + pLocalTime->tm_mon;
    int iCurrentYear = 1900 + pLocalTime->tm_year;

    //type string dateOfBirth DD/MM/YYYY
    int iDayOfBirth = std::stoi(dateOfBirth.substr(0, 2));
    int iMonthOfBirth = std::stoi(dateOfBirth.substr(3, 2));
    int iYearOfBirth = std::stoi(dateOfBirth.substr(6, 4));

    if (iMonthOfBirth > iCurrentMonth) {
        iAge = iCurrentYear - iYearOfBirth - 1;
    } else if (iMonthOfBirth < iCurrentMonth) {
        iAge = iCurrentYear - iYearOfBirth;
    } else {
        if (iDayOfBirth > iCurrentDay) {
            iAge = iCurrentYear - iYearOfBirth - 1;
        } else {
            iAge = iCurrentYear - iYearOfBirth;
        }
    }

    return iAge;
}

std::string UserData::getName() const { return _strName; }

void UserData::setName(std::string name) { _strName = name; }

std::string UserData::getDateOfBirth() const { return _strDateOfBirth; }

void UserData::setDateOfBirth(std::string dateOfBirth) {
    _strDateOfBirth = dateOfBirth;
    _iAge = userAge(dateOfBirth);
}

int UserData::getAge() { return _iAge; }

std::string UserData::getAddress() const { return _strAddress; }

void UserData::setAddress(std::string address) { _strAddress = address; }

std::string UserData::getPhoneNumber() const { return _strPhoneNumber; }

void UserData::setPhoneNumber(std::string phoneNumber) { _strPhoneNumber = phoneNumber; }

std::string UserData::getEmail() const { return _strEmail; }

void UserData::setEmail(std::string email) { _strEmail = email; }

std::string UserData::getUserName() const { return _strUserName; }

void UserData::setUserName(std::string username) { _strUserName = username; }

std::string UserData::getPassword() const { return _strPassword; }

void UserData::setPassword(std::string password) { _strPassword = password; }

std::string UserData::getRole() const { return _strRole; }

// void UserData::setRole(std::string role) { _strRole = role; }

bool UserData::operator!=(const UserData& user) const {
    return _strUserName != user._strUserName || _strPassword != user._strPassword || _strRole != user._strRole || _strName != user._strName || _strDateOfBirth != user._strDateOfBirth || _iAge != user._iAge || _strAddress != user._strAddress || _strPhoneNumber != user._strPhoneNumber || _strEmail != user._strEmail;
}

UserData& UserData::operator=(const UserData& user) {
    if (this != &user) {
        _strName = user._strName;
        _strDateOfBirth = user._strDateOfBirth;
        _iAge = user._iAge;
        _strAddress = user._strAddress;
        _strPhoneNumber = user._strPhoneNumber;
        _strEmail = user._strEmail;
        _strUserName = user._strUserName;
        _strPassword = user._strPassword;
        _strRole = user._strRole;
    }
    return *this;
}
