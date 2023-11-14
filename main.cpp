#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "UserInterface.h"
#include "Login.h"

UserInterface;
Login;
/*
bool authenticate(const std::string& username, const std::string& password) {
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
			if (storedUsername == username && storedPassword == password) {
				return true; // Authentication successful
			}
		}
	}
	return false;
}
*/
bool checkUsername(const std::string& username) {
	std::ifstream file("data.txt");

	if (!file.is_open()) {
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string storedUsername;
		if (std::getline(iss, storedUsername)) {
			if (storedUsername == username) {
				return true;
			}
		}
	}
}



int main() {
	UserInterface ui;
	Login cu;
	int cnt = 0;
	std::string user;
	std::string pass;
	bool login = false;
	//login
	while (cnt != 4) {
		//ui.cBorder = '*';
		ui.printLineBreak();
		ui.printTitle("Login Admin  ", GREEN, CYAN, true);

		ui.printLineBreak();
		ui.printLineBreak();

		user = ui.input("Username: ", LIGHT_BLUE, false);
		pass = ui.input("Password (default: 123): ", LIGHT_BLUE, true);
		cu.setUser(user);
		cu.setPass(pass);
		login = cu.authenticate();
		if (login) {
			ui.printTitle("Access granted!", GREEN, CYAN);
			break;
		}
		else if (cnt != 3) {
			ui.printTitle("You have been denied " + std::to_string(cnt + 1) + " please press Enter to continue!", RED, CYAN);
			std::cin.get();
			//system("pause");
			ui.clearScreen();
			cnt++;
		}
		else {
			ui.printTitle("Access denied you have 4 time, please try again!", RED, CYAN);
			std::cin.get();
			break;
		}
	}


	//after_login
	if (login) {
		while (1 != 2) {
			ui.clearScreen();
			if (login) {
				ui.printCentered("Menu", YELLOW, CYAN, '-');
				ui.printMultiLine(
					{
						"1. Add employee",
						"2. Delete employee",
						"3. Find employee",
						"4. Edit employee",
						"5. Show employee information",
						"6. Return!"
					},
					LIGHT_BLUE
				);


			}
			std::string s;
			s = ui.input(">", LIGHT_YELLOW, false);
			if (s == "1") {
				ui.clearScreen();
				std::ofstream file("data.txt", std::ios::app);
				std::string _user = ui.input("UserName: ");
				std::string _pass = ui.input("Password: ");
				std::string _vpass = ui.input("Verify Password: ");
				//check_xem_ten_co_ton_tai_khum
				if (checkUsername(_user)) {
					ui.print("Username already exists, please press enter to return menu!!");
					std::cin.get();
				}
				else if (_pass != _vpass) {
					ui.print("Please verify your password again");
				}
				else {
					//file << _user << "," << _pass << "\n";
					ui.print("Sign up successfully");
				}
				file.close();

			}
			else if (s == "2") {
				ui.clearScreen();
				ui.printTitle("Xoa Nhan vien");
				std::cin.get();
			}
			else if (s == "3") {
			}
			else if (s == "4") {

			}
			else if (s == "6") {
				ui.clearScreen();
				ui.printTitle("Thanks for using us", RED);
				break;
			}
		}
	}
	return 0;
}
