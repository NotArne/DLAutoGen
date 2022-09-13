## DLAutoGen

A small program to automatically generate all necessary files to link a shared library at runtime.

### Motivation and Functionality:
Linking a shared library at runtime can be a quite annoying and time-consuming task because every
function must be translated to a function-pointer. Moreover, other structures must be present, too. 
This program trys to reduce the effort of runtime linking. It needs the original headers of a library
and creates from that new headers with function-pointers as well as all needed linking code. Please have a look
at the examples folder for an example of the generated code. \
The generated files should work under Linux and MacOs. 
Windows will definitive not work!

### Compilation:
This program bases on the cppparser from satya-das, so it must be installed first.
\
Install the packages: \
`git clone https://github.com/satya-das/common.git` \
`git clone https://github.com/satya-das/CppParser.git` \
and this packet all into the same folder.
Moreover, `boost` is required. \
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

### Usage:
The program can be used via command line. It has the following command line parameters:

`-h`: (help) Print help information \
`-i`: (include) Path to the header files regarding the library. It can be specified more than one header. \
`-l`: (library) Library which should be linked at runtime \
`-o`: (output) Set the output directory of this program. If empty, the actual directory of the program is assumed. \
`--cst`: (check symbol table) If set, the functions in the header will be matched with the symbols in the symbol table of the library \
`--cl`: (check library) Check if the specified library exists on the system. \
`--adsf`: (abort on dlsym failure) Add the abort command to generated files, iff dlsym fails. \
`--fml`: (function list path) Specify the path to a comma(,) separated .csv file which contains the names of the functions which should be linked.
        Functions which are in the header but not mentioned in the .csv list will be removed from the generated header.

### Restrictions:
The program works only on pure C functions in C libraries. The `extern "C"` construct in C++ might work. The header files must be correct.

### Known issues:
- If the program prints weird .gcda warnings you can delete the problematic files by running `find . -name "*.gcda" -print0 | xargs -0 rm`
in the build directory. Despite this warnings, the files will be generated.
- In my case running gcc version 12 the compilation of the cppparser library fails while building tests. This seems to be through an old
version of the catch library. Despite this, the relevant targets for this project will be generated.

### Security:
Please check the command line parameters carefully to avoid Code Injections!



