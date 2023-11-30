#include <string>
#include "UserInterface.h"
#include "CsvFile.h"
#include "UserAction.h"
#include "UserData.h"

int g_maxLoginAttempts = 0;

std::string g_userAccount;
std::string g_userPassword;
UserAction g_user("Admin");

UserInterface g_ui;


void adminMenu();

void employeeMenu();

void loginMenu();

void loginAdmin();

void loginEmployee();

void adminMenuProcessing(char cOption);

void employeeMenuProcessing(char cOption);

UserData updateMenu(std::string userName);

UserData inputInformation();

void displayUserInformation(const UserData user);

void displayAllUserInformation(const std::vector<std::string> user);

bool isValidDateFormat(const std::string& date);

void changePassword();

int main() {
    g_ui.cBorder = '*';
    loginMenu();
    return 0;
}

// TODO: Change all recursive functions to using loop

void adminMenu() {
    g_ui.printCentered("MENU", LIGHT_YELLOW, true, '-');
    g_ui.print(
        {
            "1. Add Employee",
            "2. Delete Employee",
            "3. Find Employee",
            "4. Update Employee",
            "5. Display Employee Information",
            "6. Exit"
        },
        LIGHT_YELLOW
    );
    g_ui.printCentered("", LIGHT_YELLOW, true, '-');
    g_ui.printCentered("", LIGHT_YELLOW, true, ' ');
    adminMenuProcessing(g_ui.input(">", LIGHT_GREEN, false)[0]);
}

void employeeMenu() {
    g_ui.cBorder = '*';
    g_ui.printCentered("EMPLOYEE MENU", LIGHT_YELLOW, true, '-');
    g_ui.print(
        {
            "1. View Account Information",
            "2. Change Password",
            "3. Exit"
        },
        LIGHT_YELLOW
    );
    g_ui.printCentered("", LIGHT_YELLOW, true, '-');
    g_ui.printCentered("", LIGHT_YELLOW, true, ' ');
    employeeMenuProcessing(g_ui.input(">", LIGHT_GREEN, false)[0]);
}

void loginMenu() {
    g_ui.cBorder = '*';
    g_ui.printTitle("LOGIN", LIGHT_GREEN, BRIGHT_WHITE, true);
    g_ui.printLineBreak();
    g_ui.print(
        {
            "SELECT ACCOUNT TYPE:",
            "1. ADMIN",
            "2. EMPLOYEE",
            "3. EXIT"
        },
        LIGHT_GREEN
    );
    g_ui.printLineBreak();
    std::string strOption = g_ui.input(">", BRIGHT_WHITE, false);
    g_ui.clearScreen();
    if (strOption == "1") {
        g_user.setRole("Admin");
        loginAdmin();
    } else if (strOption == "2") {
        g_user.setRole("Employee");
        loginEmployee();
    } else if (strOption == "3") {
        exit(0);
    } else {
        g_ui.printTitle("INVALID CHOICE", LIGHT_YELLOW, LIGHT_RED, true);
        g_ui.printCentered("Return", LIGHT_PURPLE, false);
        g_ui.input();
        g_ui.clearScreen();
        loginMenu();
    }
}

void loginAdmin() {
    g_ui.clearScreen();
    g_ui.cBorder = '*';
    g_ui.printTitle("ADMIN LOGIN", LIGHT_YELLOW, LIGHT_CYAN, true);
    g_ui.printLineBreak();
    g_userAccount = g_ui.input("Username: ", LIGHT_PURPLE, false);
    g_userPassword = g_ui.input("Password (default: 123): ", LIGHT_PURPLE, true);
    if (g_user.authenticateUser(g_userAccount, g_userPassword)) {
        g_maxLoginAttempts = 0;
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
    g_ui.cBorder = '*';
    g_ui.printTitle("EMPLOYEE LOGIN", LIGHT_YELLOW, LIGHT_CYAN, true);
    g_ui.printLineBreak();
    g_userAccount = g_ui.input("Username: ", LIGHT_PURPLE, false);
    g_userPassword = g_ui.input("Password (default: 123): ", LIGHT_PURPLE, true);
    if (g_user.authenticateUser(g_userAccount, g_userPassword)) {
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
    g_ui.clearScreen();
    std::string username;
    switch (cOption) {
        case '1':
            if (g_user.addUser(inputInformation())) {
                g_ui.clearScreen();
                g_ui.printTitle("Successful", LIGHT_GREEN, GREEN);
            } else
                g_ui.printTitle("Unsuccessful", LIGHT_YELLOW, YELLOW);
            break;
        case '2':
            if (g_user.deleteUser(g_ui.input("Enter username:", LIGHT_CYAN, false))) {
                g_ui.clearScreen();
                g_ui.printTitle("Successful", LIGHT_GREEN, GREEN);
            } else
                g_ui.printTitle("Unsuccessful", LIGHT_YELLOW, YELLOW);
            break;
        case '3':
            displayUserInformation(g_user.findUser(g_ui.input("Enter username:", LIGHT_CYAN, false)));
            break;
        case '4':
            username = g_ui.input("Enter username:", LIGHT_CYAN, false);
            if (g_user.updateUserInformation(username, updateMenu(username))) {
                g_ui.clearScreen();
                g_ui.printTitle("Successful", LIGHT_GREEN, GREEN);
            } else
                g_ui.printTitle("Unsuccessful", LIGHT_YELLOW, YELLOW);
            break;
        case '5':
            displayAllUserInformation(g_user.getAllUsersInformation());
            break;
        case '6':
            loginMenu();
            break;
        default:
            g_ui.printTitle("INVALID CHOICE", LIGHT_YELLOW, LIGHT_RED, true);
            break;
    }
    g_ui.input("Return");
    g_ui.clearScreen();
    adminMenu();
}

void employeeMenuProcessing(char cOption) {
    g_ui.clearScreen();
    switch (cOption) {
        case '1':
            g_ui.print(
                {
                    g_user.getUserInformation(g_userAccount)
                },
                LIGHT_YELLOW
            );
            break;
        case '2':
            changePassword();
            break;
        case '3':
            loginMenu();
            break;
        default:
            g_ui.printTitle("INVALID CHOICE", LIGHT_YELLOW, LIGHT_RED, true);
            break;
    }
    g_ui.input("Return");
    g_ui.clearScreen();
    employeeMenu();
}

UserData updateMenu(std::string userName) {
    g_ui.print(
        {
            "1. Update Name",
            "2. Update Date of Birth",
            "3. Update Address",
            "4. Update Phone Number",
            "5. Update Email",
        },
        LIGHT_YELLOW
    );
    std::string strChange = g_ui.input("Enter number to change: ");
    std::string strChangeStuff = g_ui.input("Enter new value: ");
    UserData user = g_user.findUser(userName);
    if (strChange == "1") {
        user.setName(strChangeStuff);
        return user;
    } else if (strChange == "2") {
        user.setDateOfBirth(strChangeStuff);
        return user;
    } else if (strChange == "3") {
        user.setAddress(strChangeStuff);
        return user;
    } else if (strChange == "4") {
        user.setPhoneNumber(strChangeStuff);
        return user;
    } else if (strChange == "5") {
        user.setEmail(strChangeStuff);
        return user;
    } else {
        updateMenu(userName);
    }
    return user;
}

UserData inputInformation() {
    std::string strName;
    std::string strBirth;

    do {
        strName = g_ui.input("Enter name: ");
        strBirth = g_ui.input("Enter Date of birth(dd/mm/yy): ");
        if (!isValidDateFormat(strBirth)) {
            g_ui.clearScreen();
            g_ui.printTitle("Invalid date of birth!", LIGHT_YELLOW, LIGHT_RED, true);
            g_ui.input("Retry");
            g_ui.clearScreen();
        }
    } while (!isValidDateFormat(strBirth));

    std::string strAddress = g_ui.input("Enter Address: ");
    std::string strPhoneNumber = g_ui.input("Enter phone: ");
    std::string strEmail = g_ui.input("Enter email: ");
    std::string strUsername = g_ui.input("Enter UserName: ");
    std::string strPass = "111111";
    return UserData(strName, strBirth, strAddress, strPhoneNumber, strEmail, strUsername, strPass, "Employee");
}

void displayUserInformation(const UserData user) {
    g_ui.print(
        {
            user.getName(),
            user.getDateOfBirth(),
            user.getPassword(),
            user.getPhoneNumber(),
            user.getEmail()
        },
        LIGHT_PURPLE
    );
}

void displayAllUserInformation(const std::vector<std::string> user) {
    //g_ui.print(user, LIGHT_CYAN, true, '\n');
    for (auto& row: user) {
        g_ui.printCentered(row, BLUE);
        g_ui.printLineBreak();
    }
}

void changePassword() {
    std::string strNewPass1 = g_ui.input("Enter a new password: ", LIGHT_PURPLE, true);
    std::string strNewPass2 = g_ui.input("Confirm the new password again: ", LIGHT_PURPLE, true);

    if (g_user.authenticateUser(g_userAccount, g_ui.input("Enter current password: ", LIGHT_CYAN, true))) {
        g_maxLoginAttempts = 0;
        g_ui.clearScreen();
        if (strNewPass1 == strNewPass2) {
            g_user.setRole("Admin");
            UserData user = g_user.findUser(g_userAccount);
            user.setPassword(strNewPass1);
            if (g_user.updateUserInformation(g_userAccount, user)) {
                g_ui.printTitle("Successful", LIGHT_GREEN, GREEN);
                g_ui.clearScreen();
                loginMenu();
            } else {
                g_ui.printTitle("Unsuccessful", RED, RED);
                employeeMenu();

            }
        } else {
            g_ui.clearScreen();
            g_ui.printTitle("The new passwords do not match. Please try again.", LIGHT_CYAN, LIGHT_RED);
        }
    } else {
        if (g_maxLoginAttempts == 2) {
            g_maxLoginAttempts = 0;
            g_ui.clearScreen();
            g_ui.printTitle("Access is blocked!", LIGHT_RED, LIGHT_RED);
            g_ui.input();
            exit(0);
        }
        g_ui.clearScreen();
        g_ui.printTitle("Incorrect curent password", LIGHT_CYAN, LIGHT_RED);
        g_maxLoginAttempts++;
        g_ui.input();
    }
}

bool isValidDateFormat(const std::string& date) {
    if (date.length() != 10) return false;

    if (date[2] != '/' || date[5] != '/') return false;

    int iDay, iMonth, iYear;
    sscanf(date.c_str(), "%d/%d/%d", &iDay, &iMonth, &iYear);

    if (iYear < 1900 || iYear > 2100) return false;

    if (iMonth < 1 || iMonth > 12) return false;

    if (iMonth == 2) {
        if (iYear % 4 == 0 && (iYear % 100 != 0 || iYear % 400 == 0)) {
            if (iDay < 1 || iDay > 29) return false;
        } else {
            if (iDay < 1 || iDay > 28) return false;
        }
    } else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11) {
        if (iDay < 1 || iDay > 30) return false;
    } else {
        if (iDay < 1 || iDay > 31) return false;
    }
    return true;
}
