//
// Created by Arne Haus on 04.09.22.
//

#ifndef DLAUTOGEN_CODEGEN_H
#define DLAUTOGEN_CODEGEN_H

#include <string>
#include <vector>
#include <unordered_set>
#include "ParsedFunction.h"

namespace CodeGenConstants {
    static std::string libraryHandlerPrefix = "library_handler";
    static std::string replacedHeaderFilePrefix = "dl_autogen_converted_header_%1%.h"; // Insert header index here
    static std::string generatedSourceFileName = "dl_autogen_generated.c"; // Insert dll name here
    static std::string generatedHeaderFileName = "dl_autogen_generated.h"; // Insert dll name here
}

class CodeGen{
protected:
    std::string generatedCode;

public:
    std::string getGeneratedCode() const;
};

class FunctionPointerCodeGen : public CodeGen {

public:
    FunctionPointerCodeGen(ParsedFunction func);
};

class FunctionPointerCastCodeGen : public CodeGen {

public:
    FunctionPointerCastCodeGen(ParsedFunction func);
};

class DLLHeaderCodeGen : public CodeGen {

public:
    DLLHeaderCodeGen(std::string dll);
};

class DLLSourceCodeGen : public CodeGen {
private:
    std::string generateHeaderInclude(std::vector<std::string> dllLibraryHeader, std::string dll);
    std::string generateDLOpenCommand(std::string dll);
    std::string generateDLSymCommand(std::vector<std::shared_ptr<ParsedObject>> funcToLink, std::string dll, std::unordered_set<std::string> replacedFunctions);
    std::string generateDLCloseCommand(std::string dll);
    std::string generateDLSource(std::vector<std::string> dllLibraryHeader, std::string dll, std::vector<std::shared_ptr<ParsedObject>> funcToLink, std::unordered_set<std::string> replacedFunctions);

public:
    DLLSourceCodeGen(std::vector<std::string> dllLibraryHeader, std::string dll, std::vector<std::shared_ptr<ParsedObject>> funcToLink, std::unordered_set<std::string> replacedFunctions);
};


#endif //DLAUTOGEN_CODEGEN_H
