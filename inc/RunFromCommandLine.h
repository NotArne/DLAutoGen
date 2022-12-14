//
// Created by NotArne on 07.09.22.
//

#ifndef DLAUTOGEN_RUNFROMCOMMANDLINE_H
#define DLAUTOGEN_RUNFROMCOMMANDLINE_H

#include "ParsedFunction.h"

struct ParsedCommandLineParameters {
    ParsedCommandLineParameters(std::vector<std::string> commandLineHeaders, std::string commandLineLibrary,
                                std::string outputDirectory, std::string functionListPath, bool checkHeaderFunction, bool checkCommandLineInput,
                                bool abortOnDlSymFailure) :
            commandLineHeaders(commandLineHeaders), commandLineLibrary(commandLineLibrary),
            outputDirectory(outputDirectory), functionListPath(functionListPath), checkHeaderFunction(checkHeaderFunction),
            checkCommandLineInput(checkCommandLineInput),
            abortOnDlSymFailure(abortOnDlSymFailure) {}

    const std::vector<std::string> commandLineHeaders;
    const std::string commandLineLibrary;
    const std::string outputDirectory;
    const std::string functionListPath;
    const bool checkHeaderFunction;
    const bool checkCommandLineInput;
    const bool abortOnDlSymFailure;
};

class RunFromCommandLine {
private:
    /**
     * Checks if a headerfile exists
     * @param headerFile header file which should be checked
     * @return if header exists or not
     */
    bool isHeaderFileExistent(std::string headerFile);

    /**
     * Checks, if the library exists
     * @param library library to check
     * @return if library exists or not
     */
    bool isLibraryExistent(std::string library);

    /**
     * Parses the specified command line parameters
     * @param argc argc input from command line
     * @param argv argv input from command line
     * @return parsed command line parameters
     */
    ParsedCommandLineParameters parseCommandLineParameters(int argc, char *argv[]);

public:
    /**
     * Runs the program
     * @param argc argc input from command line
     * @param argv argv input from command line
     */
    void runFromCommandLine(int argc, char *argv[]);
};

#endif //DLAUTOGEN_RUNFROMCOMMANDLINE_H
