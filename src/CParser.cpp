//
// Created by Arne Haus on 03.09.22.
//
#include <iostream>
#include "CParser.h"
#include "ParsedFunction.h"

std::vector<std::shared_ptr<ParsedObject>> CParser::parseFunctionsInHeader(std::string header) {
    std::vector<std::shared_ptr<ParsedObject>> parseObjects;

    std::unique_ptr<CppCompound> rootCompoundUnique = cppParser.parseFile(header);
    CppCompoundEPtr easyCompoundPtr = rootCompoundUnique;
    parseFunctionsInCompound(easyCompoundPtr, parseObjects);

    return parseObjects;
}

void CParser::parseFunctionsInCompound(CppCompoundEPtr &compound,
                                       std::vector<std::shared_ptr<ParsedObject>>& parsedObjects) {
    if (compound.get() == nullptr) {
        throw std::runtime_error("Failed to build a compound in AST! Please check the input header!");
    }
    for (const auto &member: compound->members()) {
        if (member->objType_ == CppObjType::kCompound) {
            CppCompoundEPtr newCompound = member;
            parseFunctionsInCompound(newCompound, parsedObjects);
        }
        if (member->objType_ == CppObjType::kFunction) { // Is a function declaration
            // Fill in values from AST
            CppFunctionEPtr astFunction = member;
            parsedObjects.push_back(std::move(parseFunction(compound, astFunction)));
        }
    }
}

std::shared_ptr<ParsedObject> CParser::parseFunction(CppCompoundEPtr &ast, CppFunctionEPtr &astFunction) {
    const auto astFunctionReturnModifier = astFunction->retType_->typeModifier();
    FunctionReturnValueModifier parsedReturnValueModifier(astFunctionReturnModifier.constBits_,
                                                          astFunctionReturnModifier.ptrLevel_);
    std::vector<FunctionParameter> allFunctionParameters;
    if (astFunction->hasParams()) {
        for (const auto &param: *astFunction->params()) {
            if (param->objType_ == CppObjType::kVar) {
                CppVarEPtr var = param;
                FunctionParameterModifier parameterModifier(var->varType()->typeModifier().constBits_,
                                                            var->varType()->typeModifier().ptrLevel_);
                FunctionParameter functionParameter(var->name(), var->varType()->baseType(), parameterModifier);
                allFunctionParameters.push_back(functionParameter);
            }
        }
    }

    // Create parse result
    std::shared_ptr<ParsedObject> ptr(new ParsedFunction(astFunction->name_,
                                                         astFunction->retType_->baseType(),
                                                         parsedReturnValueModifier,
                                                         astFunction->defn() != nullptr,
                                                         astFunction->hasAttr(CppIdentifierAttrib::kExtern),
                                                         astFunction->hasParams(),
                                                         allFunctionParameters));
    return ptr;
}
