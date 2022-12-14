//
// Created by NotArne on 07.09.22.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include <unordered_set>
#include <boost/format.hpp>
#include "RunFromCommandLine.h"
#include "CParser.h"
#include "FunctionRegexSearch.h"
#include "CodeGen.h"
#include "CheckHeaderFunction.h"
#include "FileHelper.h"
#include "CsvParser.h"


bool RunFromCommandLine::isHeaderFileExistent(std::string headerFile) {
    std::ifstream headerFileCheck(headerFile);
    bool headerFileExists = headerFileCheck.is_open();
    headerFileCheck.close();
    return headerFileExists;
}

bool RunFromCommandLine::isLibraryExistent(std::string library) {
    void *libraryHandler = dlopen(library.c_str(), RTLD_LAZY);
    bool libraryExistent = (libraryHandler != nullptr);
    if (libraryExistent) {
        dlclose(libraryHandler);
    }
    return libraryExistent;
}

ParsedCommandLineParameters RunFromCommandLine::parseCommandLineParameters(int argc, char **argv) {

    boost::program_options::options_description optionsDescription("Allowed parameters");
    optionsDescription.add_options()
            ("help,h", "Print help information")
            ("version,v", "Print version information")
            ("header,i", boost::program_options::value<std::vector<std::string>>()->multitoken(),
             "Input header of the library. It can be specified several header files.")
            ("library,l", boost::program_options::value<std::string>(), "Library which should be linked at runtime.")
            ("chf", boost::program_options::bool_switch(),
             "If set, the functions found in the header files will testwise linked and checked on errors.")
            ("output,o", boost::program_options::value<std::string>()->default_value(""),
             "Output directory. Specifies where to write the generated files.")
            ("cl", boost::program_options::bool_switch(),
             "Check if the specified library exists on the system.")
            ("adsf", boost::program_options::bool_switch(),
             "Add the abort command to generated files, if dlsym fails.")
            ("flp", boost::program_options::value<std::string>()->default_value(""),
             "Function list path: Specify via a .csv file path function names, which should be linked.");

    boost::program_options::variables_map vm;
    store(parse_command_line(argc, argv, optionsDescription), vm);
    notify(vm);

    std::vector<std::string> parsedHeaders;
    std::string parsedLibrary;
    std::string parsedOutputDirectory;
    std::string parsedFunctionListPath;
    bool parsedCheckHeaderFunction;
    bool parsedCheckInputs;
    bool parsedAbortOnFailure;

    if (vm.count("help")) {
        std::cout << optionsDescription << std::endl;
        exit(0);
    } else if (vm.count("version")) {
        std::cout << "DLAutoGen version: " << "1.0.0" << std::endl;
        exit(0);
    } else {
        parsedCheckInputs = vm.at("cl").as<bool>();
        parsedAbortOnFailure = vm.at("adsf").as<bool>();
        parsedCheckHeaderFunction = vm.at("chf").as<bool>();
        // Parse command line include headers
        if (vm.count("header")) {
            std::vector<std::string> commandLineHeaders = vm.at("header").as<std::vector<std::string>>();
            for (std::string &includeHeader: commandLineHeaders) {
                if (isHeaderFileExistent(includeHeader)) {
                    parsedHeaders.push_back(includeHeader);
                } else {
                    std::cerr << "Error: The specified header " + includeHeader + " has not been found!" << std::endl;
                    exit(0);
                }
            }
            if (commandLineHeaders.empty()) {
                std::cerr << "Error: No headers are specified!" << std::endl;
                exit(0);
            }
        } else {
            std::cerr << "Error: No headers are specified!" << std::endl;
            exit(0);
        }

        // Parse commandline library
        if (vm.count("library")) {
            std::string commandLineLibrary = vm.at("library").as<std::string>();
            if (parsedCheckInputs) {
                if (isLibraryExistent(commandLineLibrary)) {
                    parsedLibrary = commandLineLibrary;
                } else {
                    std::cerr << "Error: The library " << commandLineLibrary << " has not been found!" << std::endl;
                    exit(0);
                }
            } else {
                parsedLibrary = commandLineLibrary;
            }
        } else {
            std::cerr << "Error: No library is specified!" << std::endl;
            exit(0);
        }

        if (vm.count("output")) {
            parsedOutputDirectory = vm.at("output").as<std::string>();
        } else {
            std::cerr << "Error: No output directory specified!" << std::endl;
        }

        if (vm.count("flp")) {
            parsedFunctionListPath = vm.at("flp").as<std::string>();
        }

    }

    ParsedCommandLineParameters result(parsedHeaders, parsedLibrary, parsedOutputDirectory, parsedFunctionListPath,
                                       parsedCheckHeaderFunction,
                                       parsedCheckInputs, parsedAbortOnFailure);
    return result;
}

void RunFromCommandLine::runFromCommandLine(int argc, char **argv) {
    ParsedCommandLineParameters parsedCommandLineParameters = parseCommandLineParameters(argc, argv);

    std::vector<std::shared_ptr<ParsedObject>> allFunctionsInAllHeaders; // All functions in the header
    std::unordered_set<std::string> headerReplacedFunctions; // Functions has been replaced while running the program

    std::string outputDirectory = parsedCommandLineParameters.outputDirectory;
    // Try to build valid output path
    if (!outputDirectory.empty()) {
        if (outputDirectory.at(outputDirectory.length() - 1) != '/') {
            outputDirectory.append("/");
        }
    }

    for (size_t i = 0; i < parsedCommandLineParameters.commandLineHeaders.size(); i++) {
        std::string headerFilePath = parsedCommandLineParameters.commandLineHeaders[i];
        CParser cParser;
        const auto result = cParser.parseFunctionsInHeader(headerFilePath);
        std::cout << "Functions in header(s): " << result.size() << std::endl;
        FunctionRegexSearch functionRegexMatch;
        functionRegexMatch.getHeaderFromFile(headerFilePath);

        bool functionListSet = (parsedCommandLineParameters.functionListPath != "");
        std::vector<std::string> functionList;
        if (functionListSet) {
            functionList = CsvParser::parseCsvFromFile(parsedCommandLineParameters.functionListPath);
        }

        if (parsedCommandLineParameters.checkHeaderFunction) {
            CheckHeaderFunction checkHeaderFunction(parsedCommandLineParameters.commandLineLibrary.c_str());
            for (const auto &res: result) {
                auto f = (ParsedFunction *) res.get();
                allFunctionsInAllHeaders.push_back(res);
                if (!f->hasDefinition) {
                    if (((std::find(functionList.begin(), functionList.end(), f->name) != functionList.end()) ||
                         !functionListSet) && (checkHeaderFunction.checkFunction(f->name.c_str()))) {
                        bool success = functionRegexMatch.searchAndReplaceFunctionWithPointer(*f);
                        if (success) {
                            headerReplacedFunctions.insert(f->name);
                        }
                    } else {
                        bool success = functionRegexMatch.removeFunctionFromHeader(*f);
                        if (!success) {
                            std::cout << "WARNING: Failed to remove the function " << f->name
                                      << " from converted header file!" << std::endl;
                        }
                    }
                }
            }
        } else {
            for (const auto &res: result) {
                auto f = (ParsedFunction *) res.get();
                allFunctionsInAllHeaders.push_back(res);
                if (!f->hasDefinition) {
                    if ((std::find(functionList.begin(), functionList.end(), f->name) != functionList.end()) ||
                        !functionListSet) {
                        bool success = functionRegexMatch.searchAndReplaceFunctionWithPointer(*f);
                        if (success) {
                            headerReplacedFunctions.insert(f->name);
                        }
                    } else {
                        bool success = functionRegexMatch.removeFunctionFromHeader(*f);
                        if (!success) {
                            std::cout << "WARNING: Failed to remove the function " << f->name
                                      << " from converted header file!" << std::endl;
                        }
                    }
                }
            }
        }

        // Write replaced header to file
        std::string convertedHeaderFile =
                outputDirectory + (boost::format(CodeGenConstants::replacedHeaderFilePrefix) % i).str();
        FileHelper::writeToFile(convertedHeaderFile, functionRegexMatch.getReplacedHeaderFile());
        std::cout << "INFO: The converted header file " << convertedHeaderFile << " has been created!" << std::endl;
    }

    DLHeaderCodeGen dllHeaderCodeGen;
    DLSourceCodeGen dllSourceCodeGen(parsedCommandLineParameters.commandLineHeaders,
                                     parsedCommandLineParameters.commandLineLibrary, allFunctionsInAllHeaders,
                                     headerReplacedFunctions, parsedCommandLineParameters.abortOnDlSymFailure);
    // Write generated header to file
    FileHelper::writeToFile(outputDirectory + CodeGenConstants::generatedHeaderFileName,
                            dllHeaderCodeGen.getGeneratedCode());
    std::cout << "INFO: The generated header file " << outputDirectory + CodeGenConstants::generatedHeaderFileName
              << " has been created!" << std::endl;
    // Write generated source to file
    FileHelper::writeToFile(outputDirectory + CodeGenConstants::generatedSourceFileName,
                            dllSourceCodeGen.getGeneratedCode());
    std::cout << "INFO: The generated source file " << outputDirectory + CodeGenConstants::generatedSourceFileName
              << " has been created!" << std::endl;
}

