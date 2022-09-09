//
// Created by NotArne on 08.09.22.
//
#include "ExampleHeader2.h"
#include <stdlib.h>
unsigned int return69() {
    return 69;
}


union TestUnion *createTestUnion() {
    union TestUnion* created = malloc(sizeof (union TestUnion));
    created->e = 69;
    return created;
}

union TestUnion* createTestUnionFromUnion(union TestUnion* testUnion) {
    testUnion->d = 69;
    return testUnion;
}
