#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "CsvFile.h"

CsvFile::CsvFile(std::string path) {
    _strPath = std::move(path);
}

std::vector<std::vector<std::string>> CsvFile::read(int startLine, int endLine) const {
    std::ifstream ifsFile(_strPath);
    if (!ifsFile.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }
    std::vector<std::vector<std::string>> vtResult;
    std::string strLine;
    while (std::getline(ifsFile, strLine)) {
        std::vector<std::string> vtRow;
        std::string strCell;
        for (char c: strLine) {
            if (c == ',') {
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
        endLine = vtResult.size();
    }
    if (startLine < 0 || endLine > vtResult.size()) {
        throw std::runtime_error("Invalid line!");
    }
    vtResult.erase(vtResult.begin(), vtResult.begin() + startLine);
    return vtResult;
}

void CsvFile::write(const std::vector<std::vector<std::string>>& data) const {
    std::ofstream ofsFile(_strPath, std::ios::out | std::ios::trunc);
    if (!ofsFile.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }
    for (const std::vector<std::string>& vtRow: data) {
        for (int i = 0; i < vtRow.size(); ++i) {
            ofsFile << vtRow[i];
            if (i != vtRow.size() - 1) {
                ofsFile << ",";
            }
        }
        ofsFile << "\n";
    }
    ofsFile.close();
}

void CsvFile::append(const std::vector<std::vector<std::string>>& data) const {
    std::ofstream ofsFile(_strPath, std::ios::out | std::ios::app);
    if (!ofsFile.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }
    for (const std::vector<std::string>& vtRow: data) {
        for (int i = 0; i < vtRow.size(); ++i) {
            ofsFile << vtRow[i];
            if (i != vtRow.size() - 1) {
                ofsFile << ",";
            }
        }
        ofsFile << "\n";
    }
    ofsFile.close();
}

void CsvFile::remove(int line) const {
    std::vector<std::vector<std::string>> VtData = read(0, -1);
    VtData.erase(VtData.begin() + line);
    write(VtData);
}
