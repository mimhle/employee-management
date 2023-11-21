#include <iostream>
#include "UserInterface.h"
#include "CsvFile.h"
#include "UserAction.h"

int main() {
    UserInterface ui;
    ui.cBorder = '*';
    
    ui.printTitle("No cap!", YELLOW, CYAN);
    ui.printLineBreak();
    ui.printTitle("With cap!  " + std::to_string(1), YELLOW, CYAN, true);
    
    ui.printLineBreak();
    ui.printLineBreak();
    UserAction a("admin");
    std::string user = ui.input("Username: ", LIGHT_BLUE, false);
    std::string pass = ui.input("Password: ", LIGHT_BLUE, true);
    
    if (a.authentication(user,pass)) {
        ui.printTitle("Access granted!", GREEN, CYAN);
    } else {
        ui.printTitle("Access denied!", RED, CYAN);
        system("pause");
        return 0;
    }
    
    ui.clearScreen();
    
    ui.printCentered("Menu", YELLOW, true, '-');
    ui.print(
        {
            "1. Option 1",
            "2. Option 2",
            "3. Option 3",
            "4. Option 4"
        },
        LIGHT_BLUE
    );

    
    
    
    
    while (1 != 2) {
        std::string s;
        s = ui.input(">", LIGHT_YELLOW, false);
        ui.print(s, LIGHT_BLUE, true);
    }

    //test file
    
    //only_employee
    //std::cout << a.displayUser("Donald") << std::endl;
    //std::cout << a.displayUser("Mickey");
    
    //only admin
    /*std::vector<std::string> users = a.displayUsers();
    for (auto& row : users) {
        std::cout << row << std::endl;
    }*/

    return 0;
}
