cmake_minimum_required(VERSION 3.23)
project(DLAutoGen)

set(CMAKE_CXX_STANDARD 20)

# Link Boost
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED )

include(/Users/arne/Documents/Programmierung/common/cmake/conf.cmake)

add_executable(DLAutoGen
        main.cpp
        src/CParser.cpp
        src/CodeGen.cpp
        src/FunctionRegexSearch.cpp
        src/OutputFileHelper.cpp
        src/SymbolTableCheck.cpp
        src/RunFromCommandLine.cpp)

target_include_directories(DLAutoGen PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(DLAutoGen PRIVATE parse_items inc)
# Include CPPParser
target_include_directories(DLAutoGen PUBLIC /Users/arne/Documents/Programmierung/cppparser/pub /Users/arne/Documents/Programmierung/common/third_party)

# Link CPPParser
target_link_libraries(DLAutoGen /Users/arne/Documents/Programmierung/cppparser/build/libcppparser.a)
#target_link_libraries(DLAutoGen /Users/arne/Documents/Programmierung/cppparser/build/boost/libboost_system.a)
target_link_libraries(DLAutoGen /Users/arne/Documents/Programmierung/cppparser/build/boost/libboost_filesystem.a)
#target_link_libraries(DLAutoGen /Users/arne/Documents/Programmierung/cppparser/build/boost/libboost_program_options.a)

# Link Boost
target_link_libraries(DLAutoGen ${Boost_LIBRARIES})