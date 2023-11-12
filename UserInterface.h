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
        HANDLE _consoleHandle;
        HANDLE _inputHandle;
        
        static bool isElevated();
        
        COORD _getScreenSize();
        
        COORD _getCursorPosition();
        
        void _setCursorPosition(int x, int y);
        
        void _moveCursor(int dx = 0, int dy = 0);
        
        void _hideInput();
        
        void _showInput();
    
    public:
        char cBorder = '#';
        std::vector<std::string> menu;
        
        UserInterface();
        
        /**
         * @description Clear console
         *
         * @return void
         */
        void clearScreen();
        
        /**
         * @description Set color for subsequent output
         *
         * @param color: Color to set
         * @return void
         */
        void setColor(int color = DEFAULT_COLOR);
        
        /**
         * @description Print text to console
         *
         * @param text Text to print
         * @param color Color of text
         * @param newLine Print new line after text
         * @return void
         */
        void print(const std::string &text, int color = DEFAULT_COLOR, bool newLine = true);
        
        /**
         * @description Print text to console, centered
         *
         * @param text Text to print
         * @param color Color of text
         * @param newLine Print new line after text
         * @param padding Padding character
         * @param cap Cap character
         * @param capColor Color of cap and padding character
         * @return void
         */
        void printCentered(const std::string &text, int color = DEFAULT_COLOR, bool newLine = true, char padding = ' ',
                           char cap = ' ', int capColor = DEFAULT_COLOR
        );
        
        /**
         * @description Print full line of character to console
         *
         * @param c Character to print
         * @param color Color of character
         * @param newLine Print new line after text
         * @return void
         */
        void printLineBreak(char c = ' ', int color = DEFAULT_COLOR, bool newLine = true);
        
        /**
         * @description Print title to console (text with border and centered)
         *
         * @param text Text to print
         * @param textColor Text color
         * @param borderColor Border color
         * @param cap Whether to cap the title
         * @return void
         */
        void printTitle(const std::string &text, int textColor = DEFAULT_COLOR, int borderColor = DEFAULT_COLOR,
                        bool cap = false
        );
        
        /**
         * @description Print menu to console
         *
         * @param items Items to print (vector of strings)
         * @param color Color of menu
         * @return void
         */
        void printMenu(const std::vector<std::string> &items, int color = DEFAULT_COLOR);
        
        /**
         * @description Wait for user input
         *
         * @param message Message to print
         * @param color Color of message
         * @param hideInput Hide input (for password)
         * @return std::string
         */
        std::string input(const std::string &message = ">", int color = DEFAULT_COLOR, bool hideInput = false);
    };
    
} // UserInterface

#endif //CTDL_GK_USERINTERFACE_CPP
