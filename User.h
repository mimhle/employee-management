#pragma once

#include <iostream>

class User {
private:
    std::string _strName;
    std::string _strDateOfBirth;
    int _iAge;
    std::string _strAddress;
    std::string _strPhoneNumber;
    std::string _strEmail;
    std::string _strUserName;
    std::string _strPassword;
    std::string _strRole;

public:
    User(std::string name, std::string dateOfBirth, int age, std::string address, std::string phoneNumber, std::string email, std::string username, std::string password, std::string role);

    //destructor
    ~User();

    //getter && setter
    std::string getName();
    void setName(std::string name);
    std::string getDateOfBirth();
    void setDateOfBirth(std::string dateOfBirth);
    int getAge();
    void setAge(int age);
    std::string getAddress();
    void setAddress(std::string address);
    std::string getPhoneNumber();
    void setPhoneNumber(std::string phoneNumber);
    std::string getEmail();
    void setEmail(std::string email);
    std::string getUserName();
    void setUserName(std::string username);
    std::string getPassword();
    void setPassword(std::string password);
    std::string getRole();
    void setRole(std::string role);

    //method
    void display();
};