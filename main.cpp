#include <iostream>
#include "UserInterface.cpp"

int main() {
    UserInterface::UserInterface ui;
    ui.cBorder = '*';
    
    ui.printTitle("Hello, World!", UserInterface::YELLOW, UserInterface::CYAN);
    std::string testPass = "123";
    
    ui.waitForInput("Username: ", UserInterface::LIGHT_BLUE, false);
    std::string pass = ui.waitForInput("Password: ", UserInterface::LIGHT_BLUE, true);
    
    if (pass == testPass) {
        ui.printTitle("Access granted!", UserInterface::GREEN, UserInterface::CYAN);
    } else {
        ui.printTitle("Access denied!", UserInterface::RED, UserInterface::CYAN);
        system("pause");
        return 0;
    }
    
    while (1 != 2) {
        std::string s;
        s = ui.waitForInput(">", UserInterface::LIGHT_YELLOW, false);
        ui.print(s, UserInterface::LIGHT_BLUE, true);
    }
    return 0;
}
