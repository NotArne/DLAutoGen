#include <iostream>

#include "OutputFileHelper.h"
#include "ParsedFunction.h"
#include "CParser.h"
#include "CodeGen.h"
#include "FunctionRegexSearch.h"
#include "SymbolTableCheck.h"
#include "RunFromCommandLine.h"

int main(int argc, char **argv) {
    std::cout << "Running DLAutoGen: " << std::endl;
    RunFromCommandLine runner;
    runner.runFromCommandLine(argc, argv);
    return 0;
}
