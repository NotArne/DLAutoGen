//
// Created by Arne Haus on 11.09.22.
//

#ifndef DLAUTOGEN_CSVPARSER_H
#define DLAUTOGEN_CSVPARSER_H

#include <vector>
#include <string>

class CsvParser {
public:
    /**
     * Parse a comma-separated (,) .csv string to a list of strings
     * @param csv Csv string
     * @return List of strings
     */
    static std::vector<std::string> parseCsv(std::string csv);
    /**
     * Parse a comma-separated (,) .csv file to a list of strings
     * @param csv Csv path
     * @return List of strings
     */
    static std::vector<std::string> parseCsvFromFile(std::string csvPath);
};

#endif //DLAUTOGEN_CSVPARSER_H
