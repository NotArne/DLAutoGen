//
// Created by Arne Haus on 07.09.22.
//

#ifndef DLAUTOGEN_RUNFROMCOMMANDLINE_H
#define DLAUTOGEN_RUNFROMCOMMANDLINE_H

struct ParsedCommandLineParameters {
    ParsedCommandLineParameters(std::vector<std::string> commandLineHeaders, std::string commandLineLibrary, std::string outputDirectory, bool checkSymbolTable) :
        commandLineHeaders(commandLineHeaders), commandLineLibrary(commandLineLibrary), outputDirectory(outputDirectory), checkSymbolTable(checkSymbolTable) {}

    const std::vector<std::string> commandLineHeaders;
    const std::string commandLineLibrary;
    const std::string outputDirectory;
    const bool checkSymbolTable;
};

class RunFromCommandLine {
private:
    bool isHeaderFileExistent(std::string headerFile);
    bool isLibraryExistent(std::string library);
    ParsedCommandLineParameters parseCommandLineParameters(int argc, char *argv[]);
public:
    void runFromCommandLine(int argc, char *argv[]);
};

#endif //DLAUTOGEN_RUNFROMCOMMANDLINE_H
