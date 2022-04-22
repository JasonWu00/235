#include <iostream>
#include "compiler.h"

int main(int argc, char *argv[]) {
    //argv[1] should contain name of file to be interpreted
    //unless none is provided, in which case argc==1, return error code
    if (argc == 1) {
        std::cout << "No file name provided" << std::endl;
        return 0;
    }
    Compiler compiler{argv[1]};
    std::cout << compiler.returnFileName() << std::endl;
    return 0;
}