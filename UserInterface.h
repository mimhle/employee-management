#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef CTDL_GK_USERINTERFACE_CPP
#define CTDL_GK_USERINTERFACE_CPP

#include <windows.h>
#include <vector>
#include <string>

enum [[maybe_unused]] g_Color {
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
    HANDLE _hConsoleHandle;
    HANDLE _hInputHandle;

    static bool isElevated();

    COORD _getScreenSize() const;

    COORD _getCursorPosition() const;

    void _setCursorPosition(int x, int y) const;

    void _moveCursor(int dx = 0, int dy = 0) const;

    void _hideInput() const;

    void _showInput() const;

public:
    char cBorder = '#';

    UserInterface();

    ~UserInterface();

    /**
     * @brief Clear console screen
     *
     * @return void
     */
    void clearScreen() const;

    /**
     * @brief Set color for subsequent output
     *
     * @param color: Color to set
     * @return void
     */
    void setColor(int color = DEFAULT_COLOR) const;

    /**
     * @brief Print text to console
     *
     * @param text Text to print
     * @param color Color of text
     * @param newLine Print new line after text
     * @return void
     */
    void print(const std::string& text, int color = DEFAULT_COLOR, bool newLine = true) const;

    /**
     * @brief Print text to console
     *
     * @param items Items to print (vector of strings)
     * @param color Color of text
     * @param newLine Print new line after text
     * @param separator Separator character
     * @return void
     */
    void
    print(const std::vector<std::string>& items, int color = DEFAULT_COLOR, bool newLine = true, char separator = '\n'
    ) const;

    /**
     * @brief Print text to console
     *
     * @param items Items to print (vector of strings)
     * @param color Color of text
     * @param newLine Print new line after text
     * @param separator Separator character
     * @param center Center text
     * @return void
     */
    void printTable(const std::vector<std::vector<std::string>>& items, int color = DEFAULT_COLOR, bool newLine = true,
                    char separator = ' ', bool center = false
    ) const;

    /**
     * @brief Print text to console, centered
     *
     * @param text Text to print
     * @param color Color of text
     * @param newLine Print new line after text
     * @param padding Padding character
     * @param cap Cap character
     * @param capColor Color of cap and padding character
     * @return void
     */
    void printCentered(const std::string& text, int color = DEFAULT_COLOR, bool newLine = true, char padding = ' ',
                       char cap = ' ', int capColor = DEFAULT_COLOR
    ) const;

    /**
     * @brief Print full line of character to console
     *
     * @param c Character to print
     * @param color Color of character
     * @param newLine Print new line after text
     * @return void
     */
    void printLineBreak(char c = ' ', int color = DEFAULT_COLOR, bool newLine = true) const;

    /**
     * @brief Print title to console (text with border and centered)
     *
     * @param text Text to print
     * @param textColor Text color
     * @param borderColor Border color
     * @param cap Whether to cap the title
     * @return void
     */
    void printTitle(const std::string& text, int textColor = DEFAULT_COLOR, int borderColor = DEFAULT_COLOR,
                    bool cap = false
    ) const;

    /**
     * @brief This function is deprecated, use print() instead
     *
     * @description Print multiple lines of text to console
     *
     * @param items Items to print (vector of strings)
     * @param color Color of the items
     * @return void
     */
    [[deprecated("This function is deprecated, use print() instead")]]
    void printMultiLine(const std::vector<std::string>& items, int color = DEFAULT_COLOR) const;

    /**
     * @brief Wait for user input
     *
     * @param message Message to print
     * @param color Color of message
     * @param hideInput Hide input (for password)
     * @param hideChar Character to replace input with (if hideInput is true)
     * @return User input
     */
    std::string input(const std::string& message = "", int color = DEFAULT_COLOR, bool hideInput = false,
                      char hideChar = '*'
    ) const;
};

#endif //CTDL_GK_USERINTERFACE_CPP

#pragma clang diagnostic pop