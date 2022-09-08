//
// Created by Arne Haus on 08.09.22.
//

#ifndef DLAUTOGEN_EXAMPLEHEADER2_H
#define DLAUTOGEN_EXAMPLEHEADER2_H

union TestUnion {
    int d;
    int e;
};

unsigned int return69();

union TestUnion *createTestUnion();

union TestUnion* createTestUnionFromUnion(union TestUnion* testUnion);

#endif //DLAUTOGEN_EXAMPLEHEADER2_H
