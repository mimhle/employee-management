#include "UserInterface.h"

using namespace UserInterface;

bool UserInterfaceWindows::isElevated() {
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

COORD UserInterfaceWindows::_getScreenSize() {
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(_consoleHandle, &consoleScreenBufferInfo);
    int iWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;
    int iHeight = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top + 1;
    return {static_cast<SHORT>(iWidth), static_cast<SHORT>(iHeight)};
}

COORD UserInterfaceWindows::_getCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    if (!GetConsoleScreenBufferInfo(_consoleHandle, &consoleScreenBufferInfo)) {
        return {-1, -1};
    }
    return {consoleScreenBufferInfo.dwCursorPosition.X, consoleScreenBufferInfo.dwCursorPosition.Y};
}

void UserInterfaceWindows::_setCursorPosition(int x, int y) {
    SetConsoleCursorPosition(_consoleHandle, {static_cast<short>(x), static_cast<short>(y)});
}

void UserInterfaceWindows::_moveCursor(int dx, int dy) {
    COORD pos = _getCursorPosition();
    _setCursorPosition(pos.X + dx, pos.Y + dy);
}

void UserInterfaceWindows::_hideInput() {
    DWORD mode = 0;
    GetConsoleMode(_inputHandle, &mode);
    SetConsoleMode(_inputHandle, mode & (~ENABLE_ECHO_INPUT));
}

void UserInterfaceWindows::_showInput() {
    DWORD mode = 0;
    GetConsoleMode(_inputHandle, &mode);
    SetConsoleMode(_inputHandle, mode | ENABLE_ECHO_INPUT);
}

UserInterfaceWindows::UserInterfaceWindows() {
    if (!isElevated()) {
        printf("Please run this program as administrator!\n");
        system("pause");
        exit(0);
    }
    _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    clearScreen();
    
    // disable wrap
    DWORD mode;
    GetConsoleMode(_consoleHandle, &mode);
    mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
    SetConsoleMode(_consoleHandle, mode);
    
    setColor(DEFAULT_COLOR);
}

void UserInterfaceWindows::clearScreen() {
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(_consoleHandle, &consoleScreenBufferInfo);
    FillConsoleOutputCharacterA(_consoleHandle, ' ', consoleScreenBufferInfo.dwSize.X * consoleScreenBufferInfo.dwSize.Y,
                               coord, &count);
    SetConsoleCursorPosition(_consoleHandle, coord);
}

void UserInterfaceWindows::setColor(const int color) {
    SetConsoleTextAttribute(_consoleHandle, color);
}

void UserInterfaceWindows::print(const std::string &text, const int color, const bool newLine) {
    setColor(color);
    printf("%s", text.c_str());
    if (newLine) {
        printf("\n");
    }
    setColor(DEFAULT_COLOR);
}

void UserInterfaceWindows::printCentered(const std::string &text, int color, bool newLine, char padding, char cap,
                                         int capColor
) {
    COORD screenSize = _getScreenSize();
    int paddingLengthLeft = static_cast<int>((screenSize.X - text.length()) / 2);
    int paddingLengthRight = (int) (screenSize.X - text.length()) - paddingLengthLeft;
    std::string paddingLeft(paddingLengthLeft, padding);
    std::string paddingRight(paddingLengthRight, padding);
    paddingLeft[0] = cap;
    paddingRight[paddingRight.length() - 1] = cap;
    print(paddingLeft, capColor, false);
    print(text, color, false);
    print(paddingRight, capColor, newLine);
}

void UserInterfaceWindows::printLineBreak(const char c, const int color, bool newLine) {
    COORD screenSize = _getScreenSize();
    setColor(color);
    for (int i = 0; i < screenSize.X; i++) {
        printf("%c", c);
    }
    if (newLine) {
        _setCursorPosition(0, _getCursorPosition().Y + 1);
    }
    setColor(DEFAULT_COLOR);
}

void UserInterfaceWindows::printTitle(const std::string &text, const int textColor, const int borderColor,
                                      bool cap
) {
    printLineBreak(cBorder, borderColor);
    if (cap) {
        printCentered(" ", textColor, true, ' ', cBorder, borderColor);
        printCentered(text, textColor, true, ' ', cBorder, borderColor);
        printCentered(" ", textColor, true, ' ', cBorder, borderColor);
    } else {
        printLineBreak();
        printCentered(text, textColor, true);
        printLineBreak();
    }
    printLineBreak(cBorder, borderColor);
}

void UserInterfaceWindows::printMultiLine(const std::vector<std::string> &items, int color) {
    int i = 0;
    for (const std::string &item: items) {
        print(item, color, false);
        if (i == 0) {
            print(" (default)", color, false);
        }
        printLineBreak();
        i++;
    }
}

std::string UserInterfaceWindows::input(const std::string &message, int color, bool hideInput) {
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
