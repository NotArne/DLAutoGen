//
// Created by NotArne on 07.09.22.
//

#ifndef DLAUTOGEN_CHECKHEADERFUNCTION_H
#define DLAUTOGEN_CHECKHEADERFUNCTION_H

#include <string>
#include <unordered_set>

class CheckHeaderFunction {
private:
    void *libraryHandler;
public:
    /**
     * @param dll Library name
     */
    CheckHeaderFunction(const char *dll);

    ~CheckHeaderFunction();

    /**
     * Checks for a function, if it can be dynamically linked to a library on the system
     * @param functionName Name of the function
     * @return True, if no error occured and false, if one occured
     */
    bool checkFunction(const char *functionName);
};

#endif //DLAUTOGEN_CHECKHEADERFUNCTION_H
