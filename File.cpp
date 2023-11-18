#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "User.h"
#include "UserInterface.h"
#include "File.h"

User;

UserInterface ui;

void File::addEmployees(User a) {
	std::ofstream file("employees.txt", std::ios::app);
	file << a.getUserName() << "," << "111111" << "\n";
	file.close();
	std::ofstream newFile(a.getUserName() + ".txt");
    newFile << a.getName() << "," << a.getAddress() << "," << a.getPhoneNumber() << "," << a.getEmail();
	newFile.close();
}

//
void File::changePassEmployee(std::string strUserName,std::string strNewPassword) {
    // Change pass in employees.txt
    std::ifstream file("employees.txt");
    std::vector<std::vector<std::string>> data;

    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> row;
        std::string username = line.substr(0, line.find(','));
        std::string password = line.substr(line.find(',') + 1);
        row.push_back(username);
        row.push_back(password);
        data.push_back(row);
    }
    file.close();
    for (auto& row : data) {
        if (row[0] == strUserName) {
            row[1] = strNewPassword;
            break;
        }
    }

    std::ofstream file1("employees.txt", std::ios::trunc);  // Open in truncation mode
    for (const auto& row : data) {
        file1 << row[0] << "," << row[1] << "\n";
    }
    file1.close();
}

bool File::checkEmployeeExist(std::string strUserName) {
	// Mở file để đọc
	std::ifstream file("employees.txt");
	std::string line;
	// Đọc từng dòng trong file
	while (getline(file, line)) {
		// Tách username để kiểm tra
		int pos = line.find(",");
		std::string currentUser = line.substr(0, pos);
		// So sánh với username cần tìm
		if (currentUser == strUserName) {
			return true;
		}
	}
	// Không tìm thấy trong file
	return false;
}

void File::deleteEmployee(std::string strUserName) {
	std::ifstream file("employees.txt");
	std::vector<std::vector<std::string>> data;

	std::string line;
	while (getline(file, line)) {
		std::vector<std::string> row;
		std::string username = line.substr(0, line.find(','));
		std::string password = line.substr(line.find(',') + 1);
		row.push_back(username);
		row.push_back(password);
		data.push_back(row);
	}
	file.close();

	// Find and remove the user from the vector
	auto it = std::remove_if(data.begin(), data.end(),
		[&strUserName](const std::vector<std::string>& row) {
			return row[0] == strUserName;
		});
	data.erase(it, data.end());

	// Write the updated data back to the file
	std::ofstream file1("employees.txt", std::ios::trunc); // Open in truncation mode
	for (const auto& row : data) {
		file1 << row[0] << "," << row[1] << "\n";
	}
	file1.close();
    std::remove((strUserName + ".txt").c_str());
}

void File::changeInformationEmployee(std::string strUserName, int intChange, std::string change) {
    std::ifstream file(strUserName + ".txt");
    std::vector<std::string> data;
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    while (std::getline(ss, line, ',')) {
        data.push_back(line);
    }
    file.close();
	data[intChange - 1] = change;

    std::ofstream file1(strUserName + ".txt", std::ios::trunc);
    for (int i = 0; i < data.size(); i++) {
        // Write current element followed by comma
        file1 << data[i];
        // Don't write comma after last element
        if (i < data.size() - 1) {
            file1 << ",";
        }
    }
    file1.close();
}

void File::displayEmployeeInformation(std::string strUserName) {
    std::ifstream file(strUserName + ".txt");
    std::vector<std::string> data;
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    while (std::getline(ss, line, ',')) {
        data.push_back(line);
    }
    file.close();

    for (const auto& row : data) {
        ui.print(row);
    }
}

void File::displayAllEmployees() {

}