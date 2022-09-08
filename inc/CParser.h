//
// Created by Arne Haus on 03.09.22.
//

#ifndef DLAUTOGEN_CPARSER_H
#define DLAUTOGEN_CPARSER_H

#include <vector>
#include <cppparser.h>
#include "ParsedObject.h"
#include "ParsedFunction.h"

class CParser {

private:
    CppParser cppParser;

    /**
     * Parse a function
     * @param ast The compound object, in this case the root of the ast
     * @param astFunction Function in the cppparser library
     * @return
     */
    std::shared_ptr<ParsedObject> parsedFunction(std::unique_ptr<CppCompound> &ast, CppFunctionEPtr &astFunction);

public:
    /**
     * Parses all functions in the specified header
     * @param header Header, in which the functions will be parsed
     * @return vector of ParsedObject. In this case ParsedFunctions
     */
    std::vector<std::shared_ptr<ParsedObject>> parseFunctionsInHeader(std::string header);
};

#endif //DLAUTOGEN_CPARSER_H
