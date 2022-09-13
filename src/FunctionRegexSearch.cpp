//
// Created by NotArne on 04.09.22.
//

#include <iostream>
#include <fstream>
#include <regex>
#include "FunctionRegexSearch.h"
#include "CodeGen.h"
#include "FileHelper.h"

std::pair<int, int> FunctionRegexSearch::searchParsedFunction(ParsedFunction func) {
    // Build function regex
    std::string funcRegexString;
    funcRegexString.append("(?:");
    if (func.returnValueModifier.isConst) {
        funcRegexString.append("(?:const)");
        funcRegexString.append("[[:space:]]+");
    }
    funcRegexString.append("(?:" + func.returnType + ")");
    funcRegexString.append("[[:space:]]*");
    if (func.returnValueModifier.isPointer) {
        funcRegexString.append("\\*");
    }
    funcRegexString.append("[[:space:]]*"); // Spaces
    funcRegexString.append("(?:" + func.name + ")");
    funcRegexString.append("[[:space:]]*"); // Spaces
    funcRegexString.append("\\(");
    if (func.hasParameters) {
        for (size_t i = 0; i < func.parameters.size(); i++) {
            funcRegexString.append("[[:space:]]*"); // Spaces
            FunctionParameter param = func.parameters[i];
            if (param.modifier.isConst) {
                funcRegexString.append("(?:const)");
                funcRegexString.append("[[:space:]]+");
            }
            funcRegexString.append("(?:" + param.type + ")");
            if (param.modifier.isPointer) {
                funcRegexString.append("[[:space:]]*");
                funcRegexString.append("\\*");
            }
            funcRegexString.append("[[:space:]]*"); // Void parameter needs no space
            funcRegexString.append("(?:" + param.name + ")");
            funcRegexString.append("[[:space:]]*");
            if ((i + 1) < func.parameters.size()) {
                funcRegexString.append(",");
            }
        }
    }
    funcRegexString.append("\\)");
    funcRegexString.append(")+");

    std::regex funcRegex(funcRegexString);

    std::smatch m;
    regex_search(this->internalHeaderFile, m, funcRegex);

    std::pair<int, int> result(-1, -1);
    if (m.size() == 1) {
        result.first = m.position();
        result.second = m.length();
    } else {
        std::cout << "WARNING: The function " << func.name << " could not be back-matched by the regex expression!"
                  << std::endl;
    }

    return result;
}

bool FunctionRegexSearch::replaceMatchedFunctionWithPointer(std::pair<int, int> positionsInString,
                                                            ParsedFunction func) {
    FunctionPointerCodeGen pointerCodeGen(func, !func.isExtern);
    if (positionsInString.first != -1 && positionsInString.second != -1) {
        internalHeaderFile.replace(positionsInString.first, positionsInString.second,
                                   pointerCodeGen.getGeneratedCode());
        return true;
    }
    return false;
}

bool FunctionRegexSearch::searchAndReplaceFunctionWithPointer(ParsedFunction func) {
    if (!headerFileLoaded) {
        throw std::runtime_error("Error: You must load a header before it can be converted!");
    }
    auto functionPosInHeader = searchParsedFunction(func);
    return replaceMatchedFunctionWithPointer(functionPosInHeader, func);
}

bool FunctionRegexSearch::removeFunctionFromHeader(ParsedFunction func) {
    if (!headerFileLoaded) {
        throw std::runtime_error("Error: You must load a header before it can be converted!");
    }
    auto functionPosInHeader = searchParsedFunction(func);
    if (functionPosInHeader.first != -1 && functionPosInHeader.second != -1) {
        internalHeaderFile.replace(functionPosInHeader.first, functionPosInHeader.second, "");
        return true;
    }
    return false;
}

void FunctionRegexSearch::getHeaderFromFile(std::string headerFilePath) {
    originalHeaderFile = FileHelper::readFromFile(headerFilePath);
    headerFileLoaded = true;
    internalHeaderFile = originalHeaderFile;
}

void FunctionRegexSearch::setOriginalHeaderFile(std::string header) {
    originalHeaderFile = header;
    internalHeaderFile = originalHeaderFile;
    headerFileLoaded = true;
}

std::string FunctionRegexSearch::getOriginalHeaderFile() {
    return originalHeaderFile;
}

std::string FunctionRegexSearch::getReplacedHeaderFile() {
    return internalHeaderFile;
}
