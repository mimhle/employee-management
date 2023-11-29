#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
//#pragma once
#ifndef CTDL_GK_USERDATA_CPP
#define CTDL_GK_USERDATA_CPP

#include <string>

/**
* @class User
* @brief Class representing a User
* @details This class encapsulates the data and operations for a User. It includes attributes such as name, date of birth, age, address, phone number, email, username, password, and role.
* @note This class can be used on any platform that supports C++.
*/
class UserData {
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

    /**
     * @brief Calculates the age of the user
     * @details This function calculates the age of the user based on the date of birth.
     * @return void
    */
    int userAge();

public:
    /**
    * @brief Constructs a new User object with the provided data.
    * @param name The user's name
    * @param dateOfBirth The user's date of birth (format: DD/MM/YYYY)
    * @param address The user's address
    * @param phoneNumber The user's phone number
    * @param email The user's email
    * @param username The user's username
    * @param password The user's password
    * @param role The user's role(Admintrator, Employee)
    */
    UserData(std::string name, std::string dateOfBirth, std::string address, std::string phoneNumber,
        std::string email, std::string username, std::string password, std::string role
    );

    UserData();

    ~UserData();

    /**
     * @brief Getters and setters
     * @details Getters and setters for private attributes
     * @return Value of private attributes
    */
    std::string getName() const;

    void setName(std::string name);

    std::string getDateOfBirth() const;

    void setDateOfBirth(std::string dateOfBirth);

    int getAge();

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

    // void setRole(std::string role);

    /**
     * @brief Overloads the != operator
     * @details This function overloads the != operator to compare two users.
     * @return True if the two users are not equal, false otherwise
    */
    bool operator!=(const UserData& user) const;
};

#endif // CTDL_GK_USERDATA_CPP
#pragma clang diagnostic pop