## DLAutoGen

A small program to automatically generate all necessary files to link a shared library at runtime.

### Motivation and Functionality
Linking a shared library at runtime can be a quite annoying and time-consuming task because every
function must be translated to a function-pointer. Moreover, other structures must be present, too. 
This program trys to reduce the effort of runtime linking. It needs the original headers of a library
and creates from that new headers with function-pointers as well as all needed linking code. Please have a look
at the examples folder for an example of the generated code.

### Compilation
This program bases on the cppparser from satya-das, so it must be installed first.
\
Install the packages: \
`git clone https://github.com/satya-das/common.git` \
`git clone https://github.com/satya-das/CppParser.git` \
and this packet all into the same folder.

Afterwards compile the cppparser inside the build directory. 
```
cd cppparser
mkdir build
cd build
cmake ..
make
```
Afterwards compile the DLAutoGen program: 
```
cd DLAutoGen
mkdir build
cd build
cmake ..
make
```

### Usage
The program can be used via command line. It has the following command line parameters:

`-h`: Print help information \
`-i`: Path to the header files regarding the library. It can be specified more than one header. \
`-l`: Library which should be linked at runtime \
`-o`: Set the output directory of this program. If empty, the actual directory of the program is assumed. \
`--cst`: If set, the functions in the header will be matched with the symbols in the symbol table of the library

### Restrictions
The program works only on pure C functions in C libraries. The header files must be correct.

### Security
Please check the command line parameters carefully to avoid Code Injections!



