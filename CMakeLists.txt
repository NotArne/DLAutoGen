cmake_minimum_required(VERSION 3.16)
project(DLAutoGen)

set(CMAKE_CXX_STANDARD 20)

# Link Boost
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED )

include(../common/cmake/conf.cmake)

add_executable(dlautogen
        main.cpp
        src/CParser.cpp
        src/CodeGen.cpp
        src/FunctionRegexSearch.cpp
        src/FileHelper.cpp
        src/CheckHeaderFunction.cpp
        src/RunFromCommandLine.cpp
        src/CsvParser.cpp)

target_include_directories(dlautogen PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(dlautogen PRIVATE parse_items inc)
# Include CPPParser
target_include_directories(dlautogen PUBLIC ../cppparser/pub ../common/third_party)

# Link dl
target_link_libraries(dlautogen dl)

# Link CPPParser
target_link_libraries(dlautogen ${CMAKE_CURRENT_LIST_DIR}/../cppparser/build/libcppparser.a)
target_link_libraries(dlautogen ${CMAKE_CURRENT_LIST_DIR}/../cppparser/build/boost/libboost_system.a)
target_link_libraries(dlautogen ${CMAKE_CURRENT_LIST_DIR}/../cppparser/build/boost/libboost_filesystem.a)
target_link_libraries(dlautogen ${CMAKE_CURRENT_LIST_DIR}/../cppparser/build/boost/libboost_program_options.a)

# Link Boost
target_link_libraries(dlautogen ${Boost_LIBRARIES})
