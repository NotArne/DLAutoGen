//
// Created by Arne Haus on 06.09.22.
//

#ifndef DLAUTOGEN_OUTPUTFILEHELPER_H
#define DLAUTOGEN_OUTPUTFILEHELPER_H

#include <string>

class OutputFileHelper {
public:
    static void writeToFile(std::string filePath, std::string content);
};

#endif //DLAUTOGEN_OUTPUTFILEHELPER_H
