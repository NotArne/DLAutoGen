//
// Created by NotArne on 07.09.22.
//

#ifndef DLAUTOGEN_SYMBOLTABLECHECK_H
#define DLAUTOGEN_SYMBOLTABLECHECK_H

#include <string>
#include <unordered_set>

class SymbolTableCheck {
public:

    /**
     * Checks a set (C has no function overloading) of functions if a library contains it in function table
     * @param functionNamesToCheck Names of the functions, which should be found in the symbol table
     * @param dllPath shared library
     * @return Functions, which has been matched
     */
    static std::unordered_set<std::string>
    matchFunctionNameToSymbolTable(std::unordered_set<std::string> functionNamesToCheck, std::string dllPath);
};

#endif //DLAUTOGEN_SYMBOLTABLECHECK_H
