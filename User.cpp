#include <iostream>
#include "User.h"

User::User(std::string name, std::string dateOfBirth, int age, std::string address, std::string phoneNumber,
           std::string email, std::string username, std::string password, std::string role
) {
    _strName = name;
    _strDateOfBirth = dateOfBirth;
    _iAge = age;
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

std::string User::getName() const { return _strName; }

void User::setName(std::string name) { _strName = name; }

std::string User::getDateOfBirth() const { return _strDateOfBirth; }

void User::setDateOfBirth(std::string dateOfBirth) { _strDateOfBirth = dateOfBirth; }

int User::getAge() const { return _iAge; }

void User::setAge(int age) { _iAge = age; }

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

void User::display() const {
    std::cout << "Name: " << _strName << std::endl;
    std::cout << "Address: " << _strAddress << std::endl;
    std::cout << "PhoneNumber: " << _strPhoneNumber << std::endl;
    std::cout << "Email: " << _strEmail << std::endl;
    std::cout << "Username: " << _strUserName << std::endl;
    std::cout << "Role: " << _strRole << std::endl;
}
