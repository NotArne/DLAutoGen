//
// Created by NotArne on 08.09.22.
//

#ifndef DLAUTOGEN_EXAMPLEHEADER2_H
#define DLAUTOGEN_EXAMPLEHEADER2_H

union TestUnion {
    int d;
    int e;
};

extern unsigned int (*return69)();

extern union TestUnion* (*createTestUnion)();

extern union TestUnion* (*createTestUnionFromUnion)(union TestUnion* testUnion);

#endif //DLAUTOGEN_EXAMPLEHEADER2_H
