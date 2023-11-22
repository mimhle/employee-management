#include "UserAction.h"
#include "CsvFile.h"
#include "Users.h"
#include "UserData.h"


UserAction::UserAction(std::string role = "") {
	strRole = role;
	list.importUserData();
}

UserAction::UserAction() {
	strRole = "";
	list.importUserData();
}

void UserAction::setUserRole(std::string role) {
	strRole = role;
}

std::string UserAction::getUserRole() {
	return strRole;
}

void UserAction::addUser(UserData user) {
	if (strRole == "admin") {
		CsvFile usersFile("Employees.txt");
		usersFile.append({
			{user.getUserName(), "," , user.getPassword()}
			});
		usersFile.addNewFile(user.getUserName());
		CsvFile newUser(user.getUserName() + ".txt");
		newUser.append({
			{user.getName()},
			{user.getAddress()},
			{user.getPhoneNumber()},
			{user.getEmail()}
			});
		list.addUser(user);
	}
}

void UserAction::deleteUser(UserData user) {
	if (strRole == "admin") {
		CsvFile usersFile("Employees.txt");
		std::vector<std::vector<std::string>> dataUsers = usersFile.read();
		int lineNum = 0;
		for (auto& row:dataUsers) {
			if (row[0] == user.getName()) {
				break;
			}
			else
			{
				lineNum++;
			}
		}
		usersFile.remove(lineNum);
		list.removeUser(user);
	}
}

UserData UserAction::findUser(std::string userName) {
	if (strRole == "admin") {
		std::vector<UserData> usersList = list.listUsers();
		int userNum = list.searchUser(userName);
		return usersList[userNum];
	}
	return UserData();
}

void UserAction::editUser(std::string userName, UserData editedUser) {
	list.editUser(userName, editedUser);
	CsvFile userData(userName + ".txt");
	userData.remove(0);
	userData.append({
		{editedUser.getName()},
		{editedUser.getAddress()},
		{editedUser.getPhoneNumber()},
		{editedUser.getEmail()}
		});
}

std::string UserAction::displayUser(std::string userName) {
	if (strRole == "employee") {
		std::string userDataTmp;
		CsvFile userData(userName + ".txt");
		std::vector<std::vector<std::string>> dataUser = userData.read();
		for (auto& v : dataUser) {
			for (auto& s : v) userDataTmp += s + " ";
		}
		return userDataTmp;
	}
	return "";
}

std::vector<std::string> UserAction::displayUsers() {
	std::vector <std::string> strUser;
	if (strRole == "admin") {
		std::vector <UserData> listUser = list.listUsers();
		for (int i = 0; i < listUser.size(); i++) {
			strUser[i] += listUser[i].getName() + " " + listUser[i].getAddress() + " " + listUser[i].getPhoneNumber() + " " + listUser[i].getEmail();
		}
		return strUser;
	}
	else {
		strUser[0] = "None user were found";
		return strUser;
	}
}

bool UserAction::authentication(std::string userName, std::string passWord) {
	if (strRole == "admin") {
		CsvFile adminLogin("Administrators.txt");
		std::vector<std::vector<std::string>> adminData = adminLogin.read();
		for (auto& row : adminData) {
			if (row[0] == userName && row[1] == passWord) {
				return true;
			}
		}
	}
	else if (strRole == "employee") {
		CsvFile userLogin("Employees.txt");
		std::vector<std::vector<std::string>> userData = userLogin.read();
		for (auto& row : userData) {
			if (row[0] == userName && row[1] == passWord) {
				return true;
			}
			
		}
	}

	return false;
}

