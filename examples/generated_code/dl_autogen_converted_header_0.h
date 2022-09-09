//
// Created by NotArne on 08.09.22.
//

#ifndef DLAUTOGEN_EXAMPLEHEADER1_H
#define DLAUTOGEN_EXAMPLEHEADER1_H

struct TestStruct {
    int a;
    int b;
    int c;
};

extern void (*hello)(void );

extern int (*add)(int a, int b);

extern int (*printAndReturn42)();

extern void (*printTestStruct)(struct TestStruct a);

#endif //DLAUTOGEN_EXAMPLEHEADER1_H
