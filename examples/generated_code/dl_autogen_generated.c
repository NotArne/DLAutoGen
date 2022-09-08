#include <dlfcn.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include "dl_autogen_generated.h"
#include "dl_autogen_converted_header_0.h"
#include "dl_autogen_converted_header_1.h"

void autogen_dlopen(){
library_handler = dlopen("libexample_library.dylib", RTLD_LAZY);
if(!library_handler) {
  perror("Failed to dlopen libexample_library.dylib");
  abort();
} 

char* dlSymErrorMessage; 
hello = (void (*)(void )) dlsym(library_handler, "hello");
if((dlSymErrorMessage = dlerror())) {
  perror("Error: dlsym on function hello failed!");
  perror(dlSymErrorMessage); 
}
add = (int (*)(int a, int b)) dlsym(library_handler, "add");
if((dlSymErrorMessage = dlerror())) {
  perror("Error: dlsym on function add failed!");
  perror(dlSymErrorMessage); 
}
printAndReturn42 = (int (*)()) dlsym(library_handler, "printAndReturn42");
if((dlSymErrorMessage = dlerror())) {
  perror("Error: dlsym on function printAndReturn42 failed!");
  perror(dlSymErrorMessage); 
}
printTestStruct = (void (*)(struct TestStruct a)) dlsym(library_handler, "printTestStruct");
if((dlSymErrorMessage = dlerror())) {
  perror("Error: dlsym on function printTestStruct failed!");
  perror(dlSymErrorMessage); 
}
return69 = (unsigned int (*)()) dlsym(library_handler, "return69");
if((dlSymErrorMessage = dlerror())) {
  perror("Error: dlsym on function return69 failed!");
  perror(dlSymErrorMessage); 
}
createTestUnion = (union TestUnion* (*)()) dlsym(library_handler, "createTestUnion");
if((dlSymErrorMessage = dlerror())) {
  perror("Error: dlsym on function createTestUnion failed!");
  perror(dlSymErrorMessage); 
}
createTestUnionFromUnion = (union TestUnion* (*)(union TestUnion* testUnion)) dlsym(library_handler, "createTestUnionFromUnion");
if((dlSymErrorMessage = dlerror())) {
  perror("Error: dlsym on function createTestUnionFromUnion failed!");
  perror(dlSymErrorMessage); 
}

}
void autogen_dlclose(){
 dlclose(library_handler);

}