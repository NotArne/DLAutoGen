//
// Created by Arne Haus on 04.09.22.
//

#ifndef DLAUTOGEN_CODEGEN_H
#define DLAUTOGEN_CODEGEN_H

#include <string>
#include <vector>
#include <unordered_set>
#include "ParsedFunction.h"

/**
 * Basic constants regarding CodeGeneration
 */
namespace CodeGenConstants {
    static std::string libraryHandlerPrefix = "library_handler";
    static std::string replacedHeaderFilePrefix = "dl_autogen_converted_header_%1%.h"; // Insert header index here
    static std::string generatedSourceFileName = "dl_autogen_generated.c"; // Insert dll name here
    static std::string generatedHeaderFileName = "dl_autogen_generated.h"; // Insert dll name here
}

/**
 * Base class for code generation sub-classes
 */
class CodeGen {
protected:
    std::string generatedCode;

public:
    std::string getGeneratedCode() const;
};

class FunctionPointerCodeGen : public CodeGen {

public:
    /**
     * Creates from a function the responding function-pointer representation
     * @param func Function, from which the pointer will be
     * @param generateExternKeyword Specifies, if the extern keyword should be generated
     */
    FunctionPointerCodeGen(ParsedFunction func, bool generateExternKeyword);
};

class FunctionPointerCastCodeGen : public CodeGen {

public:
    /**
     * Creates from a function the responding function-pointer cast needed to cast the void* pointer from dlsym
     * @param func Function, from which the function-pointer cast will be created
     */
    FunctionPointerCastCodeGen(ParsedFunction func);
};

class DLHeaderCodeGen : public CodeGen {

public:
    /**
     * Creates the header file regarding to the generated source code file
     */
    DLHeaderCodeGen();
};

class DLSourceCodeGen : public CodeGen {
private:

    /**
     * Generates all header includes needed for the generated source file
     * @param dllLibraryHeader List of all headers specified with the command line parameters
     * @return string with all needed C header includes
     */
    std::string generateHeaderInclude(std::vector<std::string> dllLibraryHeader);

    /**
     * Generates the dlopen command needed for the generated source file
     * @param dll Library, which should be linked at runtime
     * @return string with the dlopen command
     */
    std::string generateDLOpenCommand(std::string dll);


    std::string generateDLPointerDefinition(std::vector<std::shared_ptr<ParsedObject>> funcToLink,
                                            std::unordered_set<std::string> replacedFunctions);

    /**
     * Generates the dlsym command(s) for all parsed libraries. If --cst is set, than for all libraries,
     * which has been matched to the symbol table of the library
     * @param funcToLink All parsed functions of all headers
     * @param dll Library, which should be linked at runtime
     * @param replacedFunctions Function which has been matched. If --cst is not set, than it contains all function names
     * @return string with the dlsym command(s)
     */
    std::string generateDLSymCommand(std::vector<std::shared_ptr<ParsedObject>> funcToLink, std::string dll,
                                     std::unordered_set<std::string> replacedFunctions);

    /**
     * Generates the dlclose command for the library, which should be linked at runtime
     * @param dll Library, which should be linked at runtime
     * @return string with the dlclose command
     */
    std::string generateDLCloseCommand(std::string dll);

    /**
     * Combines the sub-functions and generates the source file
     * @param dllLibraryHeader List of all headers specified with the command line parameters
     * @param dll Library, which should be linked at runtime
     * @param funcToLink All parsed functions of all headers
     * @param replacedFunctions Function which has been matched. If --cst is not set, than it contains all function names
     * @return
     */
    std::string generateDLSource(std::vector<std::string> dllLibraryHeader, std::string dll,
                                 std::vector<std::shared_ptr<ParsedObject>> funcToLink,
                                 std::unordered_set<std::string> replacedFunctions);

public:
    /**
     * Constructs the code generation object of the source file
     * @param dllLibraryHeader List of all headers specified with the command line parameters
     * @param dll Library, which should be linked at runtime
     * @param funcToLink All parsed functions of all headers
     * @param replacedFunctions Function which has been matched. If --cst is not set, than it contains all function names
     */
    DLSourceCodeGen(std::vector<std::string> dllLibraryHeader, std::string dll,
                    std::vector<std::shared_ptr<ParsedObject>> funcToLink,
                    std::unordered_set<std::string> replacedFunctions);
};


#endif //DLAUTOGEN_CODEGEN_H
