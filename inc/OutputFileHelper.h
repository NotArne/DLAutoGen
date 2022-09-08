//
// Created by Arne Haus on 06.09.22.
//

#ifndef DLAUTOGEN_OUTPUTFILEHELPER_H
#define DLAUTOGEN_OUTPUTFILEHELPER_H

#include <string>

class OutputFileHelper {
public:

    /**
     * Writes the string to a file
     * @param filePath File to write
     * @param content Content to write in file
     */
    static void writeToFile(std::string filePath, std::string content);
};

#endif //DLAUTOGEN_OUTPUTFILEHELPER_H
