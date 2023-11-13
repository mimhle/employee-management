#ifndef User_H
#define User_H

#include <string>

class User {
    private:
    std::string _name;
    std::string _address;
    std::string _phoneNumber;
    std::string _email;
    std::string _username;
    std::string _password;
    std::string _role;

    public:
    //constructor
    User() {
        _name = "";
        _address = "";
        _phoneNumber = "";
        _email = "";
        _username = "";
        _password = "";
        _role = "";
    }
    User(std::string name, std::string address, std::string phoneNumber, std::string email, std::string username, std::string password, std::string role) {
        _name = name;
        _address = address;
        _phoneNumber = phoneNumber;
        _email = email;
        _username = username;
        _password = password;
        _role = role;
    }

    //destructor
    ~User() {
        _name = "";
        _address = "";
        _phoneNumber = "";
        _email = "";
        _username = "";
        _password = "";
        _role = "";
    }

    //getter && setter
    std::string getName() { return _name; }
    void setName(std::string name) { _name = name; }
    std::string getAddress() { return _address; }
    void setAddress(std::string address) { _address = address; }
    std::string getPhoneNumber() { return _phoneNumber; }
    void setPhoneNumber(std::string phoneNumber) { _phoneNumber = phoneNumber; }
    std::string getEmail() { return _email; }
    void setEmail(std::string email) { _email = email; }
    std::string getUsername() { return _username; }
    void setUsername(std::string username) { _username = username; }
    std::string getPassword() { return _password; }
    void setPassword(std::string password) { _password = password; }
    std::string getRole() { return _role; }
    void setRole(std::string role) { _role = role; }
};

#endif