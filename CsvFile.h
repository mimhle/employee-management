#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#ifndef CTDL_GK_CSVFILE_H
#define CTDL_GK_CSVFILE_H

#include <string>
#include <vector>


/**
 * @class File
 * @brief Class for File
 * @details This class contains functions for File with CSV format
 */
class CsvFile {
private:
    std::string _strPath;
public:
    /**
     * @brief Constructor
     * @param path Path to file
     */
    explicit CsvFile(std::string path);

    /**
     * @brief Read data from file
     *
     * @param startLine Start line
     * @param endLine End line
     * @param sep Separator
     * @return Data from file
     */
    std::vector<std::vector<std::string>> read(int startLine = 0, int endLine = -1, char sep = ',') const;

    /**
     * @brief Write data to file
     * @param data Data to write
     * @param sep Separator
     * @return True if success, false if not
     */
    bool write(const std::vector<std::vector<std::string>>& data, char sep = ',') const;

    /**
     * @brief Append data to file
     * @param data Data to append
     * @param sep Separator
     * @return True if success, false if not
     */
    bool append(const std::vector<std::vector<std::string>>& data, char sep = ',') const;

    /**
     * @brief Remove line from file
     * @param line Line to remove (negative value to count from end)
     */
    void remove(int line) const;

    /**
     * @brief Rename file
     * @param newName New name
     * @return True if success, false if not
     */
    bool rename(const std::string& newName);

    /**
     * @brief Delete file
     * @return True if success, false if not
     */
    bool del();
};


#endif //CTDL_GK_CSVFILE_H

#pragma clang diagnostic pop