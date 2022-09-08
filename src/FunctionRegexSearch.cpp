//
// Created by Arne Haus on 04.09.22.
//

#include <iostream>
#include <fstream>
#include <regex>
#include "FunctionRegexSearch.h"
#include "CodeGen.h"

std::pair<int, int> FunctionRegexSearch::searchParsedFunction(ParsedFunction func) {
    // Build function regex
    /*std::string funcRegexString;
    funcRegexString.append("(?:");
    funcRegexString.append("(?:[[:space:]])*"); // Spaces
    funcRegexString.append("(?:" + func.returnType + ")");
    if(func.returnValueModifier.isPointer) {
        funcRegexString.append("\\*");
    }
    funcRegexString.append("(?:[[:space:]])+"); // Spaces
    funcRegexString.append("(?:" + func.name +")");
    funcRegexString.append("(?:[[:space:]])*"); // Spaces
    funcRegexString.append("\\(");
    if(func.hasParameters) {
        for(size_t i = 0; i < func.parameters.size(); i++) {
            funcRegexString.append("(?:[[:space:]])*"); // Spaces
            FunctionParameter param = func.parameters[i];
            funcRegexString.append("(?:"+param.type+")");
            if(param.modifier.isPointer){
                funcRegexString.append("\\*");
            }
            funcRegexString.append("(?:[[:space:]])*"); // Void parameter needs no space
            funcRegexString.append("(?:"+param.name+")");
            funcRegexString.append("(?:[[:space:]])*");
            if( (i+1) < func.parameters.size()) {
                funcRegexString.append(",");
            }
        }
    }
    funcRegexString.append("\\)");
    funcRegexString.append(")+"); */
    std::string funcRegexString;
    funcRegexString.append("(?:");
    //funcRegexString.append("[[:space:]]*"); // Spaces
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
    //funcRegexString.append("[[:space:]]*");
    //funcRegexString.append(";");
    funcRegexString.append(")+");

    std::regex funcRegex(funcRegexString);

    std::smatch m;
    regex_search(this->internalHeaderFile, m, funcRegex);

    std::pair<int, int> result(-1, -1);
    if (m.size() == 1) {
        result.first = m.position();
        result.second = m.length();
    } else {
        std::cout << "WARNING: The function " << func.name << " could not be back-matched by the regex!" << std::endl;
    }

    return result;
}

bool FunctionRegexSearch::replaceMatchedFunctionWithPointer(std::pair<int, int> positionsInString,
                                                            ParsedFunction func) {
    FunctionPointerCodeGen pointerCodeGen(func);
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
    std::ifstream headerFile(headerFilePath);
    if (!headerFile.is_open()) {
        throw std::runtime_error("Failed to open header file! Please check your file path!");
    }

    std::string line;
    while (std::getline(headerFile, line)) {
        this->originalHeaderFile.append(line);
        this->originalHeaderFile.append("\n");
    }
    headerFileLoaded = true;
    internalHeaderFile = originalHeaderFile;
    headerFile.close();
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