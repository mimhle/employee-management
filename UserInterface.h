//
// Created by Mingle on 008/08/11/23.
//

#ifndef CTDL_GK_USERINTERFACE_H
#define CTDL_GK_USERINTERFACE_H

#include <iostream>
#include <windows.h>

namespace UserInterface {
    struct POINT {
        int X;
        int Y;
    };

    enum Color {
        DEFAULT_COLOR = 7,
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        PURPLE = 5,
        YELLOW = 6,
        WHITE = 7,
        GRAY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_PURPLE = 13,
        LIGHT_YELLOW = 14,
        BRIGHT_WHITE = 15
    };

    class UserInterface {
    private:
        HANDLE _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE _inputHandle = GetStdHandle(STD_INPUT_HANDLE);

        POINT _getScreenSize() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(_consoleHandle, &csbi);
            int iWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            int iHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            return {iWidth, iHeight};
        }

        POINT _getCursorPosition() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(_consoleHandle, &csbi)) {
                return {-1, -1};
            }
            return {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
        }

        void _setCursorPosition(POINT pos) {
            SetConsoleCursorPosition(_consoleHandle, {static_cast<short>(pos.X), static_cast<short>(pos.Y)});
        }

        void _moveCursor(int dx = 0, int dy = 0) {
            POINT pos = _getCursorPosition();
            _setCursorPosition({pos.X + dx, pos.Y + dy});
        }

        void _hideInput() {
            DWORD mode = 0;
            GetConsoleMode(_inputHandle, &mode);
            SetConsoleMode(_inputHandle, mode & (~ENABLE_ECHO_INPUT));
        }

        void _showInput() {
            DWORD mode = 0;
            GetConsoleMode(_inputHandle, &mode);
            SetConsoleMode(_inputHandle, mode | ENABLE_ECHO_INPUT);
        }

        void _printFullLine(const std::string &text, const int color = DEFAULT_COLOR) {
            POINT screenSize = _getScreenSize();
            int iCount = (int) (screenSize.X / text.length());
            _setCursorPosition({0, _getCursorPosition().Y + 1});
            setColor(color);
            for (int i = 0; i < iCount; i++) {
                printf("%s", text.c_str());
            }
            _setCursorPosition({0, _getCursorPosition().Y + 1});
            setColor(DEFAULT_COLOR);
        }

    public:
        UserInterface() {
            clear();
            setColor(DEFAULT_COLOR);
        }

        static void clear() {
            system("cls");
        }

        static void setColor(const int color = DEFAULT_COLOR) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        }

        void printTitle(
                const std::string &text,
                const int borderColor = DEFAULT_COLOR,
                const int textColor = DEFAULT_COLOR
        ) {
            _printFullLine("-", borderColor);

            _moveCursor(static_cast<int>((_getScreenSize().X - text.length()) / 2), 0);
            setColor(textColor);
            printf("%s", text.c_str());

            _printFullLine("-", borderColor);
        }

        std::string waitForInput(
                const std::string &message = ">",
                const int color = DEFAULT_COLOR,
                bool hideInput = false
        ) {
            char szInput[255];
            setColor(color);
            printf("%s ", message.c_str());
            if (hideInput) {
                _hideInput();
            }
            scanf("%s", szInput);
            if (hideInput) {
                _showInput();
                printf("\n");
            }
            setColor(DEFAULT_COLOR);
            return szInput;
        }
    };

} // UserInterface

#endif //CTDL_GK_USERINTERFACE_H
