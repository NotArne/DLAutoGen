//
// Created by Arne Haus on 07.09.22.
//

#include <stdio.h>
#include <regex>
#include <boost/format.hpp>
#include "SymbolTableCheck.h"


std::unordered_set<std::string> SymbolTableCheck::matchFunctionNameToSymbolTable(std::unordered_set<std::string> functionNamesToCheck,
                                                                          std::string dllPath) {
    FILE* processHandler = popen( (boost::format("nm -j --defined-only %1%") % dllPath).str().c_str(), "r");
    if(processHandler == nullptr) {
        throw std::runtime_error("Failed to call nm command while try to check symbol table!");
    }

    std::string nmCommandResult;
    char buf[256];
    size_t readn;
    while ((readn = fread(buf, 1, sizeof(buf), processHandler)) > 0) {
        nmCommandResult.append(std::string(buf));
    }

    std::unordered_set<std::string> matchedFunctions;
    for(const std::string& functionToMatch : functionNamesToCheck) {
        //(?:%1%)+(?=[[:space:]]+)
        std::string matchRegexString = (boost::format("(?:%1%(?=[[:space:]]))+") % functionToMatch).str();
        std::regex matchRegex(matchRegexString);
        std::smatch m;
        regex_search(nmCommandResult, m, matchRegex);
        if(m.size() == 1) {
            matchedFunctions.insert(functionToMatch);
        }
        if(m.size() > 1) {
            throw std::logic_error("Internal error: Matched one function name to more than one function in nm result!");
        }
    }
    pclose(processHandler);

    return matchedFunctions;
}
