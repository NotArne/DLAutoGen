//
// Created by Arne Haus on 03.09.22.
//
#ifndef DLAUTOGEN_PARSEDFUNCTION_H
#define DLAUTOGEN_PARSEDFUNCTION_H

#include <string>
#include <vector>

#include "ParsedObject.h"

struct FunctionReturnValueModifier {
    FunctionReturnValueModifier(bool isConst, bool isPointer) : isConst(isConst), isPointer(isPointer) {};
    const bool isConst; // Probably not needed due to C restrictions
    const bool isPointer;
};

struct FunctionParameterModifier {
    FunctionParameterModifier(bool isConst, bool isPointer) : isConst(isConst), isPointer(isPointer) {};
    const bool isConst; // Probably not needed due to C restrictions
    const bool isPointer;
};

struct FunctionParameter {
    FunctionParameter(std::string name, std::string type, FunctionParameterModifier modifier) : name(name), type(type),
        modifier(modifier) {};
    const std::string name;
    const std::string type;
    const FunctionParameterModifier modifier;
};

struct ParsedFunction : public ParsedObject {

public:

    ParsedFunction(std::string name, std::string returnType, FunctionReturnValueModifier returnValueModifier, bool hasDefinition,
                   bool isExtern,
                   bool hasParameters = false,
                   std::vector<FunctionParameter> parameters = std::vector<FunctionParameter>()) :
                   name(name),
                   returnType(returnType),
                   returnValueModifier(returnValueModifier),
                   hasParameters(hasParameters),
                   parameters(parameters),
                   hasDefinition(hasDefinition),
                   isExtern(isExtern){};

    // Name of the function
    const std::string name;

    // Return type
    const std::string returnType;
    const FunctionReturnValueModifier returnValueModifier;

    // Parameters
    const bool hasParameters;
    const std::vector<FunctionParameter > parameters;

    // Definition
    const bool hasDefinition;

    // IsExtern
    const bool isExtern;

    AllParsableItems getParsableObjectType() override {
        return AllParsableItems::PARSED_FUNCTION;
    }
};

#endif //DLAUTOGEN_PARSEDFUNCTION_H
