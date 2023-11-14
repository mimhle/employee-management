//#pragma once
#ifndef CTDL_GK_USER_CPP
#define CTDL_GK_USER_CPP

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
    std::string getName() const;
    void setName(std::string name);
    std::string getDateOfBirth() const;
    void setDateOfBirth(std::string dateOfBirth);
    int getAge() const;
    void setAge(int age);
    std::string getAddress() const;
    void setAddress(std::string address);
    std::string getPhoneNumber() const;
    void setPhoneNumber(std::string phoneNumber);
    std::string getEmail() const;
    void setEmail(std::string email);
    std::string getUserName() const;
    void setUserName(std::string username);
    std::string getPassword() const;
    void setPassword(std::string password);
    std::string getRole() const;
    void setRole(std::string role);

    //method
    void display() const;
};

#endif // CTDL_GK_USER_CPP