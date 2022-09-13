//
// Created by NotArne on 06.09.22.
//

#include <fstream>
#include <iostream>
#include "FileHelper.h"

void FileHelper::writeToFile(std::string filePath, std::string content) {
    std::ofstream fileWriter(filePath);
    if (!fileWriter.is_open()) {
        throw std::runtime_error("Failed to open output file!");
    }
    fileWriter.write(content.c_str(), content.size());
    fileWriter.close();
}

std::string FileHelper::readFromFile(std::string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + filePath + "! Please check your file path!");
    }
    std::string result;
    std::string line;
    while (std::getline(file, line)) {
        result.append(line);
        result.append("\n");
    }
    file.close();
    return result;
}
