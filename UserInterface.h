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

    class UserInterface {
    private:
        static Coordinate _getScreenSize() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            return {width, height};
        }

        static Coordinate _getCursorPosition() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                return {-1, -1};
            }
            return {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
        }

        static void _setCursorPosition(Coordinate pos) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                     {static_cast<short>(pos.x), static_cast<short>(pos.y)});
        }

        static void _moveCursor(int dx = 0, int dy = 0) {
            auto pos = _getCursorPosition();
            _setCursorPosition({pos.x + dx, pos.y + dy});
        }

        static void _printFullLine(const std::string &text, const std::string &colorCode = "07") {
            auto screenSize = _getScreenSize();
            auto count = (int) (screenSize.x / text.length());
            _setCursorPosition({0, _getCursorPosition().y + 1});
            for (int i = 0; i < count; i++) {
                printf("%s", text.c_str());
            }
            _setCursorPosition({0, _getCursorPosition().y + 1});
        }

    public:
        UserInterface() {
            clear();
        }

        static void clear() {
            system("cls");
        }

        static void title(const std::string &text, const std::string &colorCode = "07") {
            _printFullLine("-", colorCode);
            _moveCursor(static_cast<int>((_getScreenSize().x - text.length()) / 2), 0);
            printf("%s", text.c_str());
            _printFullLine("-", colorCode);
        }
    };

} // UserInterface

#endif //CTDL_GK_USERINTERFACE_H
