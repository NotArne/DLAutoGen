//
// Created by Arne Haus on 08.09.22.
//

#ifndef DLAUTOGEN_EXAMPLEHEADER1_H
#define DLAUTOGEN_EXAMPLEHEADER1_H

struct TestStruct {
    int a;
    int b;
    int c;
} TestStruct;

void (*hello)(void );

int (*add)(int a, int b);

int (*printAndReturn42)();

void (*printTestStruct)(struct TestStruct a);

#endif //DLAUTOGEN_EXAMPLEHEADER1_H
