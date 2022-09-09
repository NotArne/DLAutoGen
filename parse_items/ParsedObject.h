//
// Created by NotArne on 03.09.22.
//

#ifndef DLAUTOGEN_PARSEDOBJECT_H
#define DLAUTOGEN_PARSEDOBJECT_H

enum AllParsableItems {PARSED_FUNCTION};

class ParsedObject {

public:
    virtual AllParsableItems getParsableObjectType() = 0;
};

#endif //DLAUTOGEN_PARSEDOBJECT_H
