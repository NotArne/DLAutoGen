//
// Created by Arne Haus on 11.09.22.
//

#include "CsvParser.h"
#include "FileHelper.h"

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>

std::vector<std::string> CsvParser::parseCsv(std::string csv) {
    boost::replace_all(csv, "\n", ""); // Remove all linebreaks
    boost::replace_all(csv, " ", ""); // Remove whitespace, not allowed in functions
    std::vector<std::string> split;
    boost::split(split, csv,boost::is_any_of(","));
    return split;
}

std::vector<std::string> CsvParser::parseCsvFromFile(std::string csvPath) {
    return parseCsv(FileHelper::readFromFile(csvPath));
}
