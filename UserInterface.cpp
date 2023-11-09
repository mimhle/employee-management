#include "UserInterface.h"

bool UserInterface::UserInterface::isElevated() {
    BOOL fRet = FALSE;
    HANDLE hToken = nullptr;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            fRet = (bool) Elevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle(hToken);
    }
    return fRet;
}

UserInterface::COORD UserInterface::UserInterface::_getScreenSize() {
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(_consoleHandle, &consoleScreenBufferInfo);
    int iWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;
    int iHeight = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top + 1;
    return {iWidth, iHeight};
}

UserInterface::COORD UserInterface::UserInterface::_getCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    if (!GetConsoleScreenBufferInfo(_consoleHandle, &consoleScreenBufferInfo)) {
        return {-1, -1};
    }
    return {consoleScreenBufferInfo.dwCursorPosition.X, consoleScreenBufferInfo.dwCursorPosition.Y};
}

void UserInterface::UserInterface::_setCursorPosition(int x, int y) {
    SetConsoleCursorPosition(_consoleHandle, {static_cast<short>(x), static_cast<short>(y)});
}

void UserInterface::UserInterface::_moveCursor(int dx, int dy) {
    COORD pos = _getCursorPosition();
    _setCursorPosition(pos.X + dx, pos.Y + dy);
}

void UserInterface::UserInterface::_hideInput() {
    DWORD mode = 0;
    GetConsoleMode(_inputHandle, &mode);
    SetConsoleMode(_inputHandle, mode & (~ENABLE_ECHO_INPUT));
}

void UserInterface::UserInterface::_showInput() {
    DWORD mode = 0;
    GetConsoleMode(_inputHandle, &mode);
    SetConsoleMode(_inputHandle, mode | ENABLE_ECHO_INPUT);
}

UserInterface::UserInterface::UserInterface() {
    if (!isElevated()) {
        printf("Please run this program as administrator!\n");
        system("pause");
        exit(0);
    }
    clearScreen();
    setColor(DEFAULT_COLOR);
}

void UserInterface::UserInterface::clearScreen() {
    system("cls");
}

void UserInterface::UserInterface::setColor(const int color) {
    SetConsoleTextAttribute(_consoleHandle, color);
}

void UserInterface::UserInterface::print(const std::string &text, const int color, const bool newLine) {
    setColor(color);
    printf("%s", text.c_str());
    if (newLine) {
        printf("\n");
    }
    setColor(DEFAULT_COLOR);
}

void UserInterface::UserInterface::printCentered(const std::string &text, int color, bool newLine, char padding) {
    COORD screenSize = _getScreenSize();
    int paddingLengthLeft = static_cast<int>((screenSize.X - text.length()) / 2);
    int paddingLengthRight = (int) (screenSize.X - text.length()) - paddingLengthLeft;
    std::string paddingLeft(paddingLengthLeft, padding);
    std::string paddingRight(paddingLengthRight, padding);
    print(paddingLeft + text + paddingRight, color, newLine);
}

void UserInterface::UserInterface::printFullLine(const char c, const int color) {
    COORD screenSize = _getScreenSize();
    _setCursorPosition(0, _getCursorPosition().Y + 1);
    setColor(color);
    for (int i = 0; i < screenSize.X; i++) {
        printf("%c", c);
    }
    _setCursorPosition(0, _getCursorPosition().Y + 1);
    setColor(DEFAULT_COLOR);
}

void UserInterface::UserInterface::printTitle(const std::string &text, const int borderColor, const int textColor) {
    printFullLine(cBorder, borderColor);
    printCentered(text, textColor, false);
    printFullLine(cBorder, borderColor);
}

void UserInterface::UserInterface::printMenu(const int color) {
    int i = 0;
    for (const std::string &item: menu) {
        print(item, color, false);
        if (i == 0) {
            print(" (default)", color, false);
        }
        print("");
        i++;
    }
}

std::string UserInterface::UserInterface::waitForInput(const std::string &message, const int color, bool hideInput) {
    char szInput[255];
    setColor(color);
    printf("%s ", message.c_str());
    if (hideInput) {
        _hideInput();
    }
    fgets(szInput, 255, stdin);
    szInput[strlen(szInput) - 1] = '\0'; // Remove \n
    if (hideInput) {
        _showInput();
        printf("\n");
    }
    setColor(DEFAULT_COLOR);
    return szInput;
}
