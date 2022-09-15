//
// Created by NotArne on 07.09.22.
//

#include <dlfcn.h>
#include <iostream>
#include "CheckHeaderFunction.h"

CheckHeaderFunction::CheckHeaderFunction(const char *dll) {
    libraryHandler = dlopen(dll, RTLD_LAZY);
    if (!libraryHandler) {
        std::cerr << "Failed to open library " << dll << "!" << std::endl;
        exit(0);
    }
}

CheckHeaderFunction::~CheckHeaderFunction() {
    int ret = dlclose(libraryHandler);
    if (ret != 0) {
        std::cerr << "Failed to close library!" << std::endl;
    }
}

bool CheckHeaderFunction::checkFunction(const char *functionName) {
    dlsym(libraryHandler, functionName);
    char *errorMessage;
    if ((errorMessage = dlerror())) {
        std::cout << "WARNING: Function " << functionName << " cannot be linked to the library!" << std::endl;
        return false;
    }
    return true;
}

