//
// Created by Arne Haus on 04.09.22.
//
#include <boost/format.hpp>

#include "CodeGen.h"

std::string CodeGen::getGeneratedCode() const {
    return generatedCode;
}

// Generate FunctionPointer
FunctionPointerCodeGen::FunctionPointerCodeGen(ParsedFunction func) {
    generatedCode.append(func.returnType);
    // Check for Pointer
    if(func.returnValueModifier.isPointer) {
        generatedCode.append("*");
    }
    generatedCode.append(" (*");
    generatedCode.append(func.name);
    generatedCode.append(")(");
    if(func.hasParameters) {
        for(size_t i = 0; i < func.parameters.size(); i++) {
            FunctionParameter param = func.parameters[i];
            generatedCode.append(param.type);
            if(param.modifier.isPointer){
                generatedCode.append("*");
            }
            generatedCode.append(" ");
            generatedCode.append(param.name);
            if( (i+1) < func.parameters.size()) {
                generatedCode.append(", ");
            }
        }
    }
    generatedCode.append(")");
}

FunctionPointerCastCodeGen::FunctionPointerCastCodeGen(ParsedFunction func) {
    ParsedFunction emptyName("",func.returnType,
                             func.returnValueModifier,
                             func.hasDefinition,
                             func.hasParameters,
                             func.parameters);
    FunctionPointerCodeGen emptyPointerCodeGen(emptyName);
    generatedCode = emptyPointerCodeGen.getGeneratedCode();
}

DLLHeaderCodeGen::DLLHeaderCodeGen(std::string dll) {
    generatedCode.append("#pragma once\n");
    generatedCode.append("\n");
    generatedCode.append((boost::format("void* %1%;\n") % CodeGenConstants::libraryHandlerPrefix).str());
    generatedCode.append((boost::format("void autogen_dlopen();\n")).str());
    generatedCode.append((boost::format("void autogen_dlclose();\n")).str());
}

std::string DLLSourceCodeGen::generateHeaderInclude(std::vector<std::string> dllLibraryHeader, std::string dll) {
    std::string includeComponent;
    includeComponent.append("#include <dlfcn.h> \n");
    includeComponent.append("#include <stdio.h> \n");
    includeComponent.append("#include <stdlib.h> \n");
    includeComponent.append("#include \""+CodeGenConstants::generatedHeaderFileName+"\"\n");

    int index = 0;
    for(const std::string& fileToInclude : dllLibraryHeader) {
        includeComponent.append((boost::format("#include \""+CodeGenConstants::replacedHeaderFilePrefix+"\"\n") % index).str());
        index++;
    }
    return includeComponent;
}

std::string DLLSourceCodeGen::generateDLOpenCommand(std::string dll) {
    std::string dlOpenComponent;
    dlOpenComponent.append((boost::format("%1% = dlopen(\"%2%\", RTLD_LAZY);\n")
    % CodeGenConstants::libraryHandlerPrefix % dll).str());
    dlOpenComponent.append((boost::format("if(!%3%) {\n"
                                          "  perror(\"Failed to dlopen %2%\"); \n"
                                          "  abort();"
                                          "\n} \n") % CodeGenConstants::libraryHandlerPrefix % dll % CodeGenConstants::libraryHandlerPrefix).str());

    return dlOpenComponent;
}

std::string DLLSourceCodeGen::generateDLSymCommand(std::vector<std::shared_ptr<ParsedObject>> funcToLink,
                                                   std::string dll,
                                                   std::unordered_set<std::string> replacedFunctions) {
    std::string dlSymComponent;
    dlSymComponent.append("char* dlSymErrorMessage; \n");
    for(const auto& parsedObject : funcToLink) {
        ParsedFunction* func = (ParsedFunction*) parsedObject.get();
        if(replacedFunctions.find(func->name) != replacedFunctions.end()) { // Create dlsym only, if function has been converted to function pointer
            FunctionPointerCastCodeGen pointerCastCode(*func);
            dlSymComponent.append(
                    (boost::format("%1% = (%2%) dlsym(%3%, \"%4%\");\n") % func->name %
                     pointerCastCode.getGeneratedCode() %
                     CodeGenConstants::libraryHandlerPrefix % func->name).str());
            dlSymComponent.append((boost::format(
                    "if((dlSymErrorMessage = dlerror())) {\n  perror(\"Error: dlsym on function %1% failed!\");"
                    "\n  perror(dlSymErrorMessage); \n}\n") % func->name).str());
        }
    }
    return dlSymComponent;
}

std::string DLLSourceCodeGen::generateDLCloseCommand(std::string dll) {
    std::string dlCloseComponent;
    dlCloseComponent.append((boost::format("dlclose(%1%);\n") % CodeGenConstants::libraryHandlerPrefix).str());
    return dlCloseComponent;
}

std::string
DLLSourceCodeGen::generateDLSource(std::vector<std::string> dllLibraryHeader,
                                   std::string dll,
                                   std::vector<std::shared_ptr<ParsedObject>> funcToLink,
                                   std::unordered_set<std::string> replacedFunctions) {
    std::string dlSourceComponent;
    dlSourceComponent.append(generateHeaderInclude(dllLibraryHeader, dll));
    dlSourceComponent.append("\n");
    dlSourceComponent.append((boost::format("void autogen_dlopen(){\n"
                                            "%1%\n"
                                            "%2%"
                                            "\n}")  % generateDLOpenCommand(dll) % generateDLSymCommand(funcToLink, dll, replacedFunctions)).str());
    dlSourceComponent.append("\n");
    dlSourceComponent.append((boost::format("void autogen_dlclose(){\n "
                                            "%1%"
                                            "\n}") % generateDLCloseCommand(dll)).str());
    return dlSourceComponent;
}

DLLSourceCodeGen::DLLSourceCodeGen(std::vector<std::string> dllLibraryHeader,
                                   std::string dll,
                                   std::vector<std::shared_ptr<ParsedObject>> funcToLink,
                                   std::unordered_set<std::string> replacedFunctions) {
    generatedCode.append(generateDLSource(dllLibraryHeader, dll, funcToLink, replacedFunctions));
}
