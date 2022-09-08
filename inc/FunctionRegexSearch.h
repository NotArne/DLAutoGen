//
// Created by Arne Haus on 04.09.22.
//

#ifndef DLAUTOGEN_FUNCTIONREGEXSEARCH_H
#define DLAUTOGEN_FUNCTIONREGEXSEARCH_H

#include <string>
#include "ParsedFunction.h"

class FunctionRegexSearch {

private:
    bool headerFileLoaded{false};
    std::string internalHeaderFile; // Header, in which the functions will be replaced with function pointers step by step
    std::string originalHeaderFile; // Base header got by the user
    std::pair<int,int> searchParsedFunction(ParsedFunction func);
    bool replaceMatchedFunctionWithPointer(std::pair<int,int> positionsInString, ParsedFunction func);

public:
    bool searchAndReplaceFunctionWithPointer(ParsedFunction func);
    bool removeFunctionFromHeader(ParsedFunction func);
    void getHeaderFromFile(std::string headerFilePath);
    void setOriginalHeaderFile(std::string header);
    std::string getOriginalHeaderFile();
    std::string getReplacedHeaderFile();
};

#endif //DLAUTOGEN_FUNCTIONREGEXSEARCH_H
