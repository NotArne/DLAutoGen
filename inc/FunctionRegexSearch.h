//
// Created by NotArne on 04.09.22.
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
    std::pair<int, int> searchParsedFunction(ParsedFunction func);

    bool replaceMatchedFunctionWithPointer(std::pair<int, int> positionsInString, ParsedFunction func);

public:
    /**
     * Replaces a matched function which a pointer
     * @param func Function which should be replaced by a pointer
     * @return if operation was successful
     */
    bool searchAndReplaceFunctionWithPointer(ParsedFunction func);

    /**
     * Removes a function from header file
     * @param func Function, which should be removed
     * @return if operation was successful
     */
    bool removeFunctionFromHeader(ParsedFunction func);

    /**
     * Loads a header from file
     * @param headerFilePath Path of the header file
     */
    void getHeaderFromFile(std::string headerFilePath);

    /**
     * Sets the original, not edited source
     * @param header header to set
     */
    void setOriginalHeaderFile(std::string header);

    /**
     * @return Returns the original, not edited source
     */
    std::string getOriginalHeaderFile();

    /**
     * @return Returns the edited file
     */
    std::string getReplacedHeaderFile();
};

#endif //DLAUTOGEN_FUNCTIONREGEXSEARCH_H
