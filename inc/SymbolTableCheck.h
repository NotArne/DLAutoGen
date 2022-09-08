//
// Created by Arne Haus on 07.09.22.
//

#ifndef DLAUTOGEN_SYMBOLTABLECHECK_H
#define DLAUTOGEN_SYMBOLTABLECHECK_H

#include <string>
#include <unordered_set>

class SymbolTableCheck {
public:
    static std::unordered_set<std::string> matchFunctionNameToSymbolTable(std::unordered_set<std::string> functionNamesToCheck, std::string dllPath);
};

#endif //DLAUTOGEN_SYMBOLTABLECHECK_H
