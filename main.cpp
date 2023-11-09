#include <iostream>
#include "UserInterface.h"

int main() {
    UserInterface::UserInterface ui;
    ui.title("Hello, World!", UserInterface::RED, UserInterface::GREEN);
    ui.title("Hello, World!", UserInterface::LIGHT_BLUE, UserInterface::LIGHT_GREEN);

    std::string testPass = "123";

    ui.waitForInput("Username: ", UserInterface::BLUE, false);
    std::string pass = ui.waitForInput("Password: ", UserInterface::BLUE, true);

    if (pass == testPass) {
        ui.title("Welcome", UserInterface::RED, UserInterface::GREEN);
    } else {
        ui.title("Wrong password!", UserInterface::RED, UserInterface::GREEN);
    }

    system("pause");
    return 0;
}
