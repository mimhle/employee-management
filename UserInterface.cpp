#include "UserInterface.h"

bool UserInterface::isElevated() {
    BOOL bRet = FALSE;
    HANDLE hToken = nullptr;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION teElevation;
        DWORD lSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &teElevation, sizeof(teElevation), &lSize)) {
            bRet = (bool) teElevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle(hToken);
    }
    return bRet;
}

COORD UserInterface::_getScreenSize() const {
    CONSOLE_SCREEN_BUFFER_INFO csbiConsoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(_hConsoleHandle, &csbiConsoleScreenBufferInfo);
    int iWidth = csbiConsoleScreenBufferInfo.srWindow.Right - csbiConsoleScreenBufferInfo.srWindow.Left + 1;
    int iHeight = csbiConsoleScreenBufferInfo.srWindow.Bottom - csbiConsoleScreenBufferInfo.srWindow.Top + 1;
    return {static_cast<SHORT>(iWidth), static_cast<SHORT>(iHeight)};
}

COORD UserInterface::_getCursorPosition() const {
    CONSOLE_SCREEN_BUFFER_INFO csbiConsoleScreenBufferInfo;
    if (!GetConsoleScreenBufferInfo(_hConsoleHandle, &csbiConsoleScreenBufferInfo)) {
        return {-1, -1};
    }
    return {csbiConsoleScreenBufferInfo.dwCursorPosition.X, csbiConsoleScreenBufferInfo.dwCursorPosition.Y};
}

void UserInterface::_setCursorPosition(int x, int y) const {
    SetConsoleCursorPosition(_hConsoleHandle, {static_cast<short>(x), static_cast<short>(y)});
}

void UserInterface::_moveCursor(int dx, int dy) const {
    COORD coordPos = _getCursorPosition();
    _setCursorPosition(coordPos.X + dx, coordPos.Y + dy);
}

void UserInterface::_hideInput() const {
    DWORD lMode = 0;
    GetConsoleMode(_hInputHandle, &lMode);
    SetConsoleMode(_hInputHandle, lMode & (~ENABLE_ECHO_INPUT));
}

void UserInterface::_showInput() const {
    DWORD lMode = 0;
    GetConsoleMode(_hInputHandle, &lMode);
    SetConsoleMode(_hInputHandle, lMode | ENABLE_ECHO_INPUT);
}

UserInterface::UserInterface() {
    if (!isElevated()) {
        printf("Please run this program as administrator!\n");
        system("pause");
        exit(0);
    }
    _hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _hInputHandle = GetStdHandle(STD_INPUT_HANDLE);
    clearScreen();

    // disable wrap
    DWORD lMode;
    GetConsoleMode(_hConsoleHandle, &lMode);
    lMode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
    SetConsoleMode(_hConsoleHandle, lMode);

    setColor(DEFAULT_COLOR);
}

UserInterface::~UserInterface() {
    CloseHandle(_hConsoleHandle);
    CloseHandle(_hInputHandle);
}

void UserInterface::clearScreen() const {
    COORD coordTopLeft = {0, 0};
    DWORD lCount;
    CONSOLE_SCREEN_BUFFER_INFO csbiConsoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(_hConsoleHandle, &csbiConsoleScreenBufferInfo);
    FillConsoleOutputCharacterA(_hConsoleHandle, ' ',
                                csbiConsoleScreenBufferInfo.dwSize.X * csbiConsoleScreenBufferInfo.dwSize.Y,
                                coordTopLeft, &lCount);
    SetConsoleCursorPosition(_hConsoleHandle, coordTopLeft);
}

void UserInterface::setColor(const int color) const {
    SetConsoleTextAttribute(_hConsoleHandle, color);
}

void UserInterface::print(const std::string& text, const int color, const bool newLine) const {
    setColor(color);
    printf("%s", text.c_str());
    if (newLine) {
        printf("\n");
    }
    setColor(DEFAULT_COLOR);
}

void UserInterface::print(const std::vector<std::string>& items, int color, bool newLine, char separator) const {
    for (const std::string& strItem: items) {
        print(strItem, color, false);
        if (strItem != items.back() && items.size() > 1) {
            print(std::string(1, separator), color, false);
        }
    }
    if (newLine) {
        printLineBreak();
    }
}

void UserInterface::printCentered(const std::string& text, int color, bool newLine, char padding, char cap,
                                  int capColor
) const {
    COORD coordScreenSize = _getScreenSize();
    int iPaddingLengthLeft = static_cast<int>((coordScreenSize.X - text.length()) / 2);
    int iPaddingLengthRight = (int) (coordScreenSize.X - text.length()) - iPaddingLengthLeft;
    std::string strPaddingLeft(iPaddingLengthLeft, padding);
    std::string strPaddingRight(iPaddingLengthRight, padding);
    strPaddingLeft[0] = cap;
    strPaddingRight[strPaddingRight.length() - 1] = cap;
    print(strPaddingLeft, capColor, false);
    print(text, color, false);
    print(strPaddingRight, capColor, newLine);
}

void UserInterface::printLineBreak(const char c, const int color, bool newLine) const {
    COORD coordScreenSize = _getScreenSize();
    setColor(color);
    for (int i = 0; i < coordScreenSize.X; i++) {
        printf("%c", c);
    }
    if (newLine) {
        _setCursorPosition(0, _getCursorPosition().Y + 1);
    }
    setColor(DEFAULT_COLOR);
}

void UserInterface::printTitle(const std::string& text, int textColor, int borderColor,
                               bool cap
) const {
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

void UserInterface::printMultiLine(const std::vector<std::string>& items, int color) const {
    for (const std::string& strItem: items) {
        print(strItem, color, false);
        printLineBreak();
    }
}

std::string UserInterface::input(const std::string& message, int color, bool hideInput) const {
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
