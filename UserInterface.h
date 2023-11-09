//
// Created by Mingle on 008/08/11/23.
//

#ifndef CTDL_GK_USERINTERFACE_H
#define CTDL_GK_USERINTERFACE_H

#include <iostream>
#include <windows.h>

namespace UserInterface {

    struct Coordinate {
        int x;
        int y;
    };

    const int DEFAULT_COLOR = 7;
    const int BLACK = 0;
    const int BLUE = 1;
    const int GREEN = 2;
    const int CYAN = 3;
    const int RED = 4;
    const int PURPLE = 5;
    const int YELLOW = 6;
    const int WHITE = 7;
    const int GRAY = 8;
    const int LIGHT_BLUE = 9;
    const int LIGHT_GREEN = 10;
    const int LIGHT_CYAN = 11;
    const int LIGHT_RED = 12;
    const int LIGHT_PURPLE = 13;
    const int LIGHT_YELLOW = 14;
    const int BRIGHT_WHITE = 15;

    class UserInterface {
    private:

        HANDLE _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE _inputHandle = GetStdHandle(STD_INPUT_HANDLE);

        Coordinate _getScreenSize() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(_consoleHandle, &csbi);
            int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            return {width, height};
        }

        Coordinate _getCursorPosition() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(_consoleHandle, &csbi)) {
                return {-1, -1};
            }
            return {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
        }

        void _setCursorPosition(Coordinate pos) {
            SetConsoleCursorPosition(_consoleHandle,
                                     {static_cast<short>(pos.x), static_cast<short>(pos.y)});
        }

        void _moveCursor(int dx = 0, int dy = 0) {
            auto pos = _getCursorPosition();
            _setCursorPosition({pos.x + dx, pos.y + dy});
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
            auto screenSize = _getScreenSize();
            auto count = (int) (screenSize.x / text.length());
            _setCursorPosition({0, _getCursorPosition().y + 1});
            setColor(color);
            for (int i = 0; i < count; i++) {
                printf("%s", text.c_str());
            }
            _setCursorPosition({0, _getCursorPosition().y + 1});
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

        void title(
                const std::string &text,
                const int borderColor = DEFAULT_COLOR,
                const int textColor = DEFAULT_COLOR
        ) {
            _printFullLine("-", borderColor);

            _moveCursor(static_cast<int>((_getScreenSize().x - text.length()) / 2), 0);
            setColor(textColor);
            printf("%s", text.c_str());

            _printFullLine("-", borderColor);
        }

        std::string waitForInput(
                const std::string &message = ">",
                const int color = DEFAULT_COLOR,
                bool hideInput = false
        ) {
            char input[255];
            setColor(color);
            printf("%s ", message.c_str());
            if (hideInput) {
                _hideInput();
            }
            scanf("%s", input);
            if (hideInput) {
                _showInput();
                printf("\n");
            }
            setColor(DEFAULT_COLOR);
            return input;
        }
    };

} // UserInterface

#endif //CTDL_GK_USERINTERFACE_H
