#ifndef CTDL_GK_USERINTERFACE_CPP
#define CTDL_GK_USERINTERFACE_CPP

#include <iostream>
#include <windows.h>
#include <vector>

/**
 * @namespace UserInterface
 * @brief Namespace for UserInterface
 * @details This namespace contains classes and functions for UserInterface
 * @note This namespace is only for Windows
 */
namespace UserInterface {
    struct COORD {
        int X;
        int Y;
    };
    
    enum [[maybe_unused]] Color {
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
    
    /**
     * @class UserInterface
     * @brief Class for UserInterface
     * @details This class contains functions for UserInterface
     * @note This class is only for Windows
     */
    class UserInterface {
    private:
        HANDLE _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE _inputHandle = GetStdHandle(STD_INPUT_HANDLE);
        
        COORD _getScreenSize() {
            CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
            GetConsoleScreenBufferInfo(_consoleHandle, &consoleScreenBufferInfo);
            int iWidth = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1;
            int iHeight = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top + 1;
            return {iWidth, iHeight};
        }
        
        COORD _getCursorPosition() {
            CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
            if (!GetConsoleScreenBufferInfo(_consoleHandle, &consoleScreenBufferInfo)) {
                return {-1, -1};
            }
            return {consoleScreenBufferInfo.dwCursorPosition.X, consoleScreenBufferInfo.dwCursorPosition.Y};
        }
        
        void _setCursorPosition(int x, int y) {
            SetConsoleCursorPosition(_consoleHandle, {static_cast<short>(x), static_cast<short>(y)});
        }
        
        void _moveCursor(int dx = 0, int dy = 0) {
            COORD pos = _getCursorPosition();
            _setCursorPosition(pos.X + dx, pos.Y + dy);
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
    
    public:
        char cBorder = '#';
        std::vector<std::string> menu;
        
        UserInterface() {
            clear();
            setColor(DEFAULT_COLOR);
        }
        
        /**
         * @description Clear console
         *
         * @return void
         */
        static void clear() {
            system("cls");
        }
        
        /**
         * @description Set color for subsequent output
         *
         * @param color: Color to set
         * @return void
         */
        void setColor(const int color = DEFAULT_COLOR) {
            SetConsoleTextAttribute(_consoleHandle, color);
        }
        
        /**
         * @description Print text to console
         *
         * @param text Text to print
         * @param color Color of text
         * @param newLine Print new line after text
         * @return void
         */
        void print(const std::string &text, const int color = DEFAULT_COLOR, const bool newLine = true) {
            setColor(color);
            printf("%s", text.c_str());
            if (newLine) {
                printf("\n");
            }
            setColor(DEFAULT_COLOR);
        }
        /**
         * @description Print text to console, centered
         *
         * @param text
         * @param color
         * @param newLine
         * @return void
         */
        void centeredPrint(const std::string &text, const int color = DEFAULT_COLOR, const bool newLine = true) {
            _moveCursor(static_cast<int>((_getScreenSize().X - text.length()) / 2), 0);
            print(text, color, newLine);
        }
        
        /**
         * @description Print full line of character to console
         *
         * @param c Character to print
         * @param color Color of character
         * @return void
         */
        void printFullLine(const char c, const int color = DEFAULT_COLOR) {
            COORD screenSize = _getScreenSize();
            _setCursorPosition(0, _getCursorPosition().Y + 1);
            setColor(color);
            for (int i = 0; i < screenSize.X; i++) {
                printf("%c", c);
            }
            _setCursorPosition(0, _getCursorPosition().Y + 1);
            setColor(DEFAULT_COLOR);
        }
        
        /**
         * @description Print title to console (text with border and centered)
         *
         * @param text Text to print
         * @param borderColor Border color
         * @param textColor Text color
         * @return void
         */
        void printTitle(
                const std::string &text,
                const int borderColor = DEFAULT_COLOR,
                const int textColor = DEFAULT_COLOR
        ) {
            printFullLine(cBorder, borderColor);
            centeredPrint(text, textColor, false);
            printFullLine(cBorder, borderColor);
        }
        
        /**
         * @description Print menu to console
         *
         * @param color Color of menu
         * @return void
         */
        void printMenu(const int color = DEFAULT_COLOR) {
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
        
        /**
         * @description Wait for user input
         *
         * @param message Message to print
         * @param color Color of message
         * @param hideInput Hide input (for password)
         * @return std::string
         */
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
            fgets(szInput, 255, stdin);
            szInput[strlen(szInput) - 1] = '\0'; // Remove \n
            if (hideInput) {
                _showInput();
                printf("\n");
            }
            setColor(DEFAULT_COLOR);
            return szInput;
        }
    };
    
} // UserInterface

#endif //CTDL_GK_USERINTERFACE_CPP
