cmake_minimum_required(VERSION 3.23)
#project(example_library C)

set(CMAKE_C_STANDARD 99)

add_library(example_library SHARED src/ExampleSource1.c src/ExampleSource2.c)
target_include_directories(example_library PRIVATE inc)