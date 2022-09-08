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

    std::shared_ptr<ParsedObject> parsedFunction(std::unique_ptr<CppCompound> &ast, CppFunctionEPtr &astFunction);
public:
    std::vector<std::shared_ptr<ParsedObject>> parseHeader(std::string file);
};

#endif //DLAUTOGEN_CPARSER_H
