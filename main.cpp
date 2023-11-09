#include <iostream>
#include "UserInterface.h"

int main() {
    UserInterface::UserInterface ui;
    ui.cBorder = '*';
    
    ui.printTitle("Hello, World!", UserInterface::YELLOW, UserInterface::CYAN);
    
    ui.waitForInput("Username: ", UserInterface::LIGHT_BLUE, false);
    std::string pass = ui.waitForInput("Password: ", UserInterface::LIGHT_BLUE, true);
    
    std::string testPass = "123";
    if (pass == testPass) {
        ui.printTitle("Access granted!", UserInterface::GREEN, UserInterface::CYAN);
    } else {
        ui.printTitle("Access denied!", UserInterface::RED, UserInterface::CYAN);
        system("pause");
        return 0;
    }
    
    ui.clearScreen();
    ui.menu.emplace_back("1. Option 1");
    ui.menu.emplace_back("2. Option 2");
    ui.menu.emplace_back("3. Option 3");
    ui.menu.emplace_back("4. Option 4");
    
    ui.printTitle("Menu", UserInterface::YELLOW, UserInterface::CYAN);
    ui.printMenu(UserInterface::LIGHT_BLUE);
    
    while (1 != 2) {
        std::string s;
        s = ui.waitForInput(">", UserInterface::LIGHT_YELLOW, false);
        ui.print(s, UserInterface::LIGHT_BLUE, true);
    }
    return 0;
}
