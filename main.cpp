#include <iostream>
#include "UserInterface.h"

int main() {
    UserInterface::UserInterface ui;
    ui.cBorder = '*';
    
    ui.printTitle("Hello, World!", UserInterface::YELLOW, UserInterface::CYAN);
    
    ui.printLineBreak();
    ui.printLineBreak();
    
    
    ui.input("Username: ", UserInterface::LIGHT_BLUE, false);
    std::string pass = ui.input("Password (default: 123): ", UserInterface::LIGHT_BLUE, true);
    
    std::string testPass = "123";
    if (pass == testPass) {
        ui.printTitle("Access granted!", UserInterface::GREEN, UserInterface::CYAN);
    } else {
        ui.printTitle("Access denied!", UserInterface::RED, UserInterface::CYAN);
        system("pause");
        return 0;
    }
    
    ui.clearScreen();
    
    ui.printCentered("Menu", UserInterface::YELLOW, UserInterface::CYAN, '-');
    ui.printMenu(
        {
            "1. Option 1",
            "2. Option 2",
            "3. Option 3",
            "4. Option 4"
        },
        UserInterface::LIGHT_BLUE
    );
    
    while (1 != 2) {
        std::string s;
        s = ui.input(">", UserInterface::LIGHT_YELLOW, false);
        ui.print(s, UserInterface::LIGHT_BLUE, true);
    }
    return 0;
}
