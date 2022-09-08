#include <iostream>

#include "RunFromCommandLine.h"

int main(int argc, char **argv) {
    std::cout << "Running DLAutoGen: " << std::endl;
    RunFromCommandLine runner;
    runner.runFromCommandLine(argc, argv);
    return 0;
}
