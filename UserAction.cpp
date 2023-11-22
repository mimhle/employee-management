#include "UserAction.h"
#include "CsvFile.h"
#include "Users.h"
#include "UserData.h"


UserAction::UserAction(std::string role = "") {
	strRole = role;
	usersList.importUserData();
}

UserAction::UserAction() {
	strRole = "";
	usersList.importUserData();
}

void UserAction::addUser(UserData user) {
	if (strRole == "Admin") {
		CsvFile csvFileEmployee("Employees.txt");
		csvFileEmployee.append({
			{user.getUserName(), "," , user.getPassword()}
			});
		CsvFile newUser(user.getUserName() + ".txt");
		newUser.append({
			{user.getName()},
			{user.getDateOfBirth()},
			{user.getAddress()},
			{user.getPhoneNumber()},
			{user.getEmail()}
			});
		usersList.addUser(user);
	}
}

void UserAction::deleteUser(UserData user) {
	if (strRole == "Admin") {
		CsvFile csvFileEmployee("Employees.txt");
		std::vector<std::vector<std::string>> dataUsers = csvFileEmployee.read();
		int lineNum = 0;
		for (auto& row : dataUsers) {
			if (row[0] == user.getName()) {
				break;
			}
			else
			{
				lineNum++;
			}
		}
		csvFileEmployee.remove(lineNum);
		usersList.removeUser(user);
	}
}

UserData UserAction::findUser(std::string userName) {
	if (strRole == "Admin") {
		std::vector<UserData> vtUsersDataList = usersList.listUsers();
		int userNum = usersList.searchUser(userName);
		return vtUsersDataList[userNum];
	}
	return UserData();
}

void UserAction::updateUserInformation(std::string userName, UserData user) {
	usersList.editUser(userName, user);
	CsvFile csvFileUser(userName + ".txt");
	csvFileUser.remove(0);
	csvFileUser.remove(1);
	csvFileUser.remove(2);
	csvFileUser.remove(3);
	csvFileUser.remove(4);
	csvFileUser.append({
		{user.getName()},
		{user.getDateOfBirth()},
		{user.getAddress()},
		{user.getPhoneNumber()},
		{user.getEmail()}
		});
	CsvFile csvFileEmployee("Employees.txt");
	std::vector<std::vector<std::string>> vtEmployeeAccounts = csvFileEmployee.read();
	int intLine = 0;
	for (auto& row : vtEmployeeAccounts) {
		if (row[0] == userName) {
			break;
		}
		else {
			intLine++;
		}
	}
	csvFileEmployee.remove(intLine);
	csvFileEmployee.append({
			{user.getUserName(), "," , user.getPassword()}
		});
}

std::string UserAction::getUserInformation(std::string userName) {
	if (strRole == "Employee") {
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
	if (strRole == "Admin") {
		std::vector <UserData> vtUsersDataList = usersList.listUsers();
		for (int i = 0; i < vtUsersDataList.size(); i++) {
			if(vtUsersDataList[i].getRole() == "Admin")
				strUsers.push_back( vtUsersDataList[i].getName() + " " + vtUsersDataList[i].getDateOfBirth() + " " + vtUsersDataList[i].getAddress() + " " + vtUsersDataList[i].getPhoneNumber() + " " + vtUsersDataList[i].getEmail());
		}
		return strUsers;
	}
	else {
		strUsers[0] = "None user were found";
		return strUsers;
	}
}

bool UserAction::authenticateUser(std::string userName, std::string passWord) {
	if (strRole == "Admin") {
		CsvFile csvFileAdmin("Administrators.txt");
		std::vector<std::vector<std::string>> vtAdminAccounts = csvFileAdmin.read();
		for (auto& row : vtAdminAccounts) {
			if (row[0] == userName && row[1] == passWord) {
				return true;
			}
		}
	}
	else if (strRole == "Employee") {
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

