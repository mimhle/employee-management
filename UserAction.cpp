#include "UserAction.h"
#include "CsvFile.h"
#include "Users.h"
#include "UserData.h"


UserAction::UserAction(std::string role = "") {
	_strRole = role;
	_usersList.importUserData();
}

UserAction::UserAction() {
	_strRole = "";
	_usersList.importUserData();
}

void UserAction::addUser(UserData user) {
	if (_strRole == "Admin") {
		CsvFile csvFileEmployee("Employees.txt");
		csvFileEmployee.append({
				{user.getUserName(), "," , user.getPassword()}
				});
		CsvFile newUser(user.getUserName() + ".txt");
		newUser.write(
		{
			{user.getName()},
			{user.getDateOfBirth()},
			{user.getAddress()},
			{user.getPhoneNumber()},
			{user.getEmail()}
		});
		_usersList.addUser(user);
	}
}

void UserAction::deleteUser(UserData user) {
	if (_strRole == "Admin") {
		CsvFile csvFileEmployee("Employees.txt");
		std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
		int iLine = -1;
		for (int i = 0; i < vtEmployeeAccounts.size(); i++) {
			if (vtEmployeeAccounts[i][0] == user.getName()) {
				iLine = i;
				break;
			}
		}
		csvFileEmployee.remove(iLine);
		_usersList.removeUser(user);
	}
}

UserData UserAction::findUser(std::string userName) {
	if (_strRole == "Admin") {
		std::vector<UserData> vtUsersDataList = _usersList.listUsers();
		int userNum = _usersList.searchUser(userName);
		return vtUsersDataList[userNum];
	}
	return UserData();
}

void UserAction::updateUserInformation(std::string userName, UserData user) {
	_usersList.editUser(userName, user);
	CsvFile csvFileUser(userName + ".txt");
	csvFileUser.write(
		{
			{user.getName()},
			{user.getDateOfBirth()},
			{user.getAddress()},
			{user.getPhoneNumber()},
			{user.getEmail()}
		});
	CsvFile csvFileEmployee("Employees.txt");
	std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
	int iLine = -1;
	for (int i = 0; i < vtEmployeeAccounts.size(); i++) {
		if (vtEmployeeAccounts[i][0] == user.getName()) {
			iLine = i;
			break;
		}
	}
	csvFileEmployee.remove(iLine);
	csvFileEmployee.append({
			{user.getUserName(), "," , user.getPassword()}
			});
}

std::string UserAction::getUserInformation(std::string userName) {
	if (_strRole == "Employee") {
		std::string strUserData;
		CsvFile csvFileUser(userName + ".txt");
		std::vector<std::vector<std::string>> vtDataUser = csvFileUser.read();
		for (auto& v : vtDataUser) {
			for (auto& s : v) strUserData += s + " ";
		}
		return strUserData;
	}
	return "";
}

std::vector<std::string> UserAction::getAllUsersInformation() {
	std::vector <std::string> strUsers;
	if (_strRole!= "Admin") {
		strUsers[0] = "None user were found";
		return strUsers;
	} else {
		std::vector <UserData> vtUsersDataList = _usersList.listUsers();
		for (int i = 0; i < vtUsersDataList.size(); i++) {
			if (vtUsersDataList[i].getRole() == "Employee")
				strUsers.push_back(vtUsersDataList[i].getName() + " " + vtUsersDataList[i].getDateOfBirth() + " " + vtUsersDataList[i].getAddress() + " " + vtUsersDataList[i].getPhoneNumber() + " " + vtUsersDataList[i].getEmail());
		}
		return strUsers;
	}
}

bool UserAction::authenticateUser(std::string userName, std::string passWord) {
	if (_strRole == "Admin") {
		CsvFile csvFileAdmin("Administrators.txt");
		std::vector<std::vector<std::string>> vtAdminAccounts = csvFileAdmin.read();
		for (auto& row : vtAdminAccounts) {
			if (row[0] == userName && row[1] == passWord) {
				return true;
			}
		}
	} else {
		CsvFile csvFileEmployee("Employees.txt");
		std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
		for (auto& row : vtEmployeeAccounts) {
			if (row[0] == userName && row[1] == passWord) {
				return true;
			}

		}
	}
	return false;
}

