#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
//#pragma once
#ifndef CTDL_GK_USER_CPP
#define CTDL_GK_USER_CPP

#include <iostream>

/**
* @class User
* @brief Class representing a User
* @details This class encapsulates the data and operations for a User. It includes attributes such as name, date of birth, age, address, phone number, email, username, password, and role.
* @note This class can be used on any platform that supports C++.
*/
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
    User(std::string name, std::string dateOfBirth, int age, std::string address, std::string phoneNumber,
        std::string email, std::string username, std::string password, std::string role
    );

    User();

    ~User();

    /**
     * @brief Getters and setters
     * @details Getters and setters for private attributes
     * @return Value of private attributes
    */
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

    /**
    *@brief Display information of user
    *@details Display information of user
    *@return void
    */
    void display() const;
};

#endif // CTDL_GK_USER_CPP
#pragma clang diagnostic pop