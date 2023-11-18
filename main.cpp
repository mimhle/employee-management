#include <iostream>
#include "UserInterface.h"

int main() {
    UserInterface ui;
    ui.cBorder = '*';
    
    ui.printTitle("No cap!", YELLOW, CYAN);
    ui.printLineBreak();
    ui.printTitle("With cap!  " + std::to_string(1), YELLOW, CYAN, true);
    
    ui.printLineBreak();
    ui.printLineBreak();
    
    ui.input("Username: ", LIGHT_BLUE, false);
    std::string pass = ui.input("Password (default: 123): ", LIGHT_BLUE, true);
    
    if (pass == "123") {
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
    return 0;
}
