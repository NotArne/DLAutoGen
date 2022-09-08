//
// Created by Arne Haus on 08.09.22.
//

#include <printf.h>
#include "ExampleHeader1.h"

void hello(void) {
    printf("Hello!\n");
}

int add(int a, int b) {
    return a + b;
}

int printAndReturn42() {
    printf("42\n");
    return 42;
}

void printTestStruct(struct TestStruct a) {
    printf("A: %i, B: %i, C: %i\n", a.a, a.b, a.c);
}