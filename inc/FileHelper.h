//
// Created by NotArne on 06.09.22.
//

#ifndef DLAUTOGEN_FILEHELPER_H
#define DLAUTOGEN_FILEHELPER_H

#include <string>

class FileHelper {
public:

    /**
     * Writes the string to a file
     * @param filePath File to write
     * @param content Content to write in file
     */
    static void writeToFile(std::string filePath, std::string content);

    static std::string readFromFile(std::string filePath);
};

#endif //DLAUTOGEN_FILEHELPER_H
