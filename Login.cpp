#include <iostream>
#include "Login.h"

Login::Login(std::string user, std::string pass) {
	_strUser = user;
	_strPass = pass;
}

Login::~Login() {
	_strUser = "";
	_strPass = "1111";
}

std::string Login::getUser() const { return _strUser; }

void Login::setUser(std::string user) { _strUser = user;  }

std::string Login::getPass() const { return _strPass; }

void Login::setPass(std::string pass) { _strPass = pass;  }

bool Login::authenticate() const {
	std::ifstream file("data.txt");

	if (!file.is_open()) {
		std::cerr << "Error opening file.\n";
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
	return false; // Authentication failed
}