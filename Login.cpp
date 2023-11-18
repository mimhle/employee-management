#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Login.h"

Login::Login(std::string user, std::string pass, int type) {
	_strUser = user;
	_strPass = pass;
	_intTypeUser = 0;
}

Login::~Login() {
	_strUser = "";
	_strPass = "1111";
	_intTypeUser = 0;
}

std::string Login::getUser() const { return _strUser; }

void Login::setUser(std::string user) { _strUser = user;  }

std::string Login::getPass() const { return _strPass; }

void Login::setPass(std::string pass) { _strPass = pass;  }

int Login::getIntTypeUser() const { return _intTypeUser; }

std::string Login::getStrTypeUser() const{
	if (_intTypeUser == 1)
		return "Administrators";
	if (_intTypeUser == 2)
		return "Employees";
}
void Login::setTypeUser(int type) { _intTypeUser = type; }

bool Login::authenticate() const {
	std::ifstream file( getStrTypeUser() + ".txt");

	if (!file.is_open()) {
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string storedUsername, storedPassword;

		// Read the fields from the CSV line
		if (std::getline(iss, storedUsername, ',') && std::getline(iss, storedPassword)) {
			if (storedUsername == _strUser && storedPassword == _strPass) {
				return true; // Authentication successful
			}
		}
	}
	file.close();
	return false; // Authentication failed
}