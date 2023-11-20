#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "CsvFile.h"

CsvFile::CsvFile(std::string path) {
    _strPath = std::move(path);
}

std::vector<std::vector<std::string>> CsvFile::read(int startLine, int endLine, char sep) const {
    std::ifstream ifsFile(_strPath);
    if (!ifsFile.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }
    std::vector<std::vector<std::string>> vtResult;
    std::string strLine;
    while (std::getline(ifsFile, strLine)) {
        std::vector<std::string> vtRow;
        std::string strCell;
        if (strLine.empty()) {
            continue;
        }
        for (char c: strLine) {
            if (c == sep) {
                if (strCell.empty()) {
                    continue;
                }
                vtRow.push_back(strCell);
                strCell = "";
            } else {
                strCell += c;
            }
        }
        vtRow.push_back(strCell);
        vtResult.push_back(vtRow);
    }
    ifsFile.close();
    if (endLine == -1) {
        endLine = (int) vtResult.size();
    }
    if (startLine < 0 || endLine > vtResult.size()) {
        throw std::runtime_error("Invalid line!");
    }
    vtResult.erase(vtResult.begin(), vtResult.begin() + startLine);
    return vtResult;
}

bool CsvFile::write(const std::vector<std::vector<std::string>>& data, char sep) const {
    std::ofstream ofsFile(_strPath, std::ios::out | std::ios::trunc);
    if (!ofsFile.is_open()) {
        return false;
    }
    for (const std::vector<std::string>& vtRow: data) {
        for (int i = 0; i < vtRow.size(); ++i) {
            ofsFile << vtRow[i];
            if (i != vtRow.size() - 1) {
                ofsFile << sep;
            }
        }
        ofsFile << "\n";
    }
    ofsFile.close();
    return true;
}

bool CsvFile::append(const std::vector<std::vector<std::string>>& data, char sep) const {
    std::ofstream ofsFile(_strPath, std::ios::out | std::ios::app);
    if (!ofsFile.is_open()) {
        return false;
    }
    for (const std::vector<std::string>& vtRow: data) {
        for (int i = 0; i < vtRow.size(); ++i) {
            ofsFile << vtRow[i];
            if (i != vtRow.size() - 1) {
                ofsFile << sep;
            }
        }
        ofsFile << "\n";
    }
    ofsFile.close();
    return true;
}

void CsvFile::remove(int line) const {
    std::vector<std::vector<std::string>> VtData = read(0, -1);
    VtData.erase(VtData.begin() + line);
    write(VtData);
}

bool CsvFile::rename(const std::string& newName) {
    bool result = std::rename(_strPath.c_str(), newName.c_str()) == 0;
    if (result) {
        _strPath = newName;
    }
    return result;
}

bool CsvFile::del() {
    return std::remove(_strPath.c_str()) == 0;
}
