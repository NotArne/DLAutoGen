//
// Created by Arne Haus on 06.09.22.
//

#include <fstream>
#include <iostream>
#include "OutputFileHelper.h"

void OutputFileHelper::writeToFile(std::string filePath, std::string content) {
    std::ofstream fileWriter(filePath);
    if (!fileWriter.is_open()) {
        throw std::runtime_error("Failed to open output file!");
    }
    fileWriter.write(content.c_str(), content.size());
    fileWriter.close();
}
