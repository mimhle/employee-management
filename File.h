//#pragma once

#include <iostream>
#include <fstream>
#include "User.h"

class File {
public:
	void addEmployees(User a);
	void deleteEmployee(std::string strUserName);
	void changePassEmployee(std::string strUserName,std::string newPassword);
	bool checkEmployeeExist(std::string strUserName);
	// intChange = 1  change Name; = 2 change Adress; = 3 change sdt; = 4 change Email
	void changeInformationEmployee(std::string strUserName, int intChange, std::string change);
	void displayEmployeeInformation(std::string strUserName);
	void displayAllEmployees();
};