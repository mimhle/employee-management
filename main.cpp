#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "UserInterface.h"
#include "CsvFile.h"
#include "UserAction.h"
#include "UserData.h"

int g_maxLoginAttempts = 0;

std::string g_userAccount;
std::string g_userPassword;

UserInterface g_ui;


void adminMenu();

void employeeMenu();

void loginMenu();

void loginAdmin();

void loginEmployee();

void adminMenuProcessing(char cOption);

void employeeMenuProcessing(char cOption);

UserData inputInformation();

void processing() {
    loginMenu();
}

int main() {
    g_ui.cBorder = '*';
    processing();
    return 0;
}

// TODO: Change all recursive functions to using loop

void adminMenu() {
    g_ui.printCentered("MENU", LIGHT_YELLOW, true, '-');
    g_ui.print(
        {
            "1. Them Employee",
            "2. Xoa Employee",
            "3. Tim Employee",
            "4. Cap nhat Employee",
            "5. Hien thi thong tin Employee",
            "6. Tro ve"
        },
        LIGHT_YELLOW
    );
    g_ui.printCentered("", LIGHT_YELLOW, true, '-');
    g_ui.printCentered("", LIGHT_YELLOW, true, ' ');
    std::string strOption = g_ui.input(">", LIGHT_GREEN, false);
    adminMenuProcessing(strOption[0]);
}

void employeeMenu() {
    g_ui.printCentered("MENU EMPLOYEE", LIGHT_YELLOW, true, '-');
    g_ui.print(
        {
            "1. Xem thong tin tai khoan",
            "2. Doi password",
            "3. Tro ve"
        },
        LIGHT_YELLOW
    );
    g_ui.printCentered("", LIGHT_YELLOW, true, '-');
    g_ui.printCentered("", LIGHT_YELLOW, true, ' ');
    std::string strOption = g_ui.input(">", LIGHT_GREEN, false);
    employeeMenuProcessing(strOption[0]);
}

void loginMenu() {
    g_ui.printTitle("DANG NHAP", LIGHT_GREEN, BRIGHT_WHITE, true);
    g_ui.printLineBreak();
    g_ui.print(
        {
            "CHON LOAI TAI KHOAN:",
            "1. Admin",
            "2. Employee",
            "3. Thoat"
        },
        LIGHT_GREEN
    );
    g_ui.printLineBreak();
    std::string StrOption = g_ui.input(">", BRIGHT_WHITE, false);
    g_ui.clearScreen();
    if (StrOption == "1") {
        loginAdmin();
    } else if (StrOption == "2") {
        loginEmployee();
    } else if (StrOption == "3") {
        exit(0);
    } else {
        g_ui.printTitle("KHONG HOP LE", LIGHT_YELLOW, LIGHT_RED, true);
        g_ui.printCentered("Quay lai", LIGHT_PURPLE, false);
        g_ui.input();
        g_ui.clearScreen();
        loginMenu();
    }
}

void loginAdmin() {
    g_ui.clearScreen();
    g_ui.printTitle("DANG NHAP ADMIN", LIGHT_YELLOW, LIGHT_CYAN, true);
    g_ui.printLineBreak();
    g_userAccount = g_ui.input("Username: ", LIGHT_PURPLE, false);
    g_userPassword = g_ui.input("Password (default: 111111): ", LIGHT_PURPLE, true);
    UserAction user("Admin");
    if (user.authenticateUser(g_userAccount, g_userPassword)) {
        g_ui.clearScreen();
        adminMenu();
    } else {
        if (g_maxLoginAttempts == 2) {
            g_maxLoginAttempts = 0;
            g_ui.clearScreen();
            g_ui.printTitle("Access is blocked!", LIGHT_RED, LIGHT_RED);
            g_ui.input();
            exit(0);
        }
        g_ui.clearScreen();
        g_ui.printTitle("Access denied!", LIGHT_CYAN, LIGHT_RED);
        g_maxLoginAttempts++;
        g_ui.input();
        loginAdmin();
    }
}

void loginEmployee() {
    g_ui.clearScreen();
    g_ui.printTitle("DANG NHAP EMPLOYEE", LIGHT_YELLOW, LIGHT_CYAN, true);
    g_ui.printLineBreak();
    g_userAccount = g_ui.input("Username: ", LIGHT_PURPLE, false);
    g_userPassword = g_ui.input("Password (default: 123): ", LIGHT_PURPLE, true);
    UserAction user("Employee");
    if (user.authenticateUser(g_userAccount, g_userPassword)) {
        g_ui.clearScreen();
        employeeMenu();
    } else {
        if (g_maxLoginAttempts == 2) {
            g_maxLoginAttempts = 0;
            g_ui.clearScreen();
            g_ui.printTitle("Access is blocked!", LIGHT_RED, LIGHT_RED);
            g_ui.input();
            exit(0);
        }
        g_ui.clearScreen();
        g_ui.printTitle("Access denied!", LIGHT_CYAN, LIGHT_RED);
        g_maxLoginAttempts++;
        g_ui.input();
        loginEmployee();
    }
}

void adminMenuProcessing(char cOption) {
    UserAction user("Admin");
    g_ui.clearScreen();
    switch (cOption) {
        case '1':
            if (user.addUser(inputInformation()))
                g_ui.printTitle("Thanh cong", LIGHT_GREEN, GREEN);
            else
                g_ui.printTitle("Khong thanh cong", LIGHT_YELLOW, YELLOW);
            break;
        case '2':
            if (user.deleteUser(g_ui.input("Nhap username:", LIGHT_CYAN, false)))
                g_ui.printTitle("Thanh cong", LIGHT_GREEN, GREEN);
            else
                g_ui.printTitle("Khong thanh cong", LIGHT_YELLOW, YELLOW);
            break;
        case '3':
            user.findUser(g_ui.input("Nhap username:", LIGHT_CYAN, false)); // retrun userdata
            break;
        case '4':
            // user.updateUserInformation();
            break;
        case '5':
            user.getAllUsersInformation(); // return vector <userdata>
            break;
        case '6':
            loginMenu();
            break;
        default:
            g_ui.printTitle("KHONG HOP LE", LIGHT_YELLOW, LIGHT_RED, true);
            g_ui.printCentered("Quay lai", LIGHT_PURPLE, false);
            break;
    }
    g_ui.input();
    g_ui.clearScreen();
    adminMenu();
}

void employeeMenuProcessing(char cOption) {
    UserAction user("Employee");
    g_ui.clearScreen();
    switch (cOption) {
        case '1':
            g_ui.print(
                {
                    user.getUserInformation(g_userAccount)
                },
                LIGHT_YELLOW
            );
            g_ui.input();
            break;
        case '2':
            // user.updateUserInformation(g_userAccont, user.findUser(g_userAccont));
            break;
        case '3':
            loginMenu();
            break;
        default:
            g_ui.printTitle("KHONG HOP LE", LIGHT_YELLOW, LIGHT_RED, true);
            g_ui.printCentered("Quay lai", LIGHT_PURPLE, false);
            g_ui.input();
            break;
    }
    g_ui.clearScreen();
    employeeMenu();
}

UserData inputInformation() {

    std::string strName = g_ui.input("name: ");
    std::string strBirth = g_ui.input("birth: ");
    std::string strAddress = g_ui.input("address: ");
    std::string strPhoneNumber = g_ui.input("phone: ");
    std::string strEmail = g_ui.input("email: ");
    std::string strUsername = g_ui.input("UserName: ");
    std::string strPass = "111111";
    return UserData(strName, strBirth, strAddress, strPhoneNumber, strEmail, strUsername, strPass, "Employee");
}
