#include <iostream>
#include "compiler.h"

void printVector(std::vector<std::string> input) {
    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i] << "|";
    }
    std::cout << " ";
    //std::cout << input.size();
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    //argv[1] should contain name of file to be interpreted
    //unless none is provided, in which case argc==1, return error code
    if (argc == 1) {
        std::cout << "No file name provided" << std::endl;
        return 0;
    }

    std::string filename = argv[1];
    /*
    size_t extension = filename.find(".hun");
    if (extension == -1) {
        std::cout << "File does not have correct extension" << std::endl;
        return 0;
    }*/

    Compiler compiler{argv[1]};
    Parser parser;
    //Compiler compiler;
    //std::cout << compiler.returnFileName() << std::endl;
    //compiler.checkifParserWorks();

    std::ifstream readRecords;
    readRecords.open(compiler.returnFileName());
    if (! readRecords) {//check if the file actually exists
        std::cout << "The specified file does not exist" << std::endl;
        readRecords.close();
        return 0;
    }

    std::cout << "Readstream opened to " << compiler.returnFileName() << std::endl;
    //open read stream to specified file

    std::string line = "";//a line of code to be read
    ErrorCode isDone = ErrorCode::Continue;
    
    while (getline(readRecords, line)) {
        //std::cout << "One line read" << std::endl;
        //std::cout << line << std::endl;

        //std::vector<std::string> parsedLine = parser(line);
        std::vector<std::string> parsedLine = parser(parser.cleanLine(line));
        //line has been cleaned and parsed into a vector

        //testing: print the vector
        //printVector(parsedLine);

        //send line to compiler to be interpreted
        compiler.interpretLine(parsedLine);
        
    }

    /*
    while (getline(std::cin, line)) {
        //std::cout << "One line read" << std::endl;
        std::vector<std::string> parsedLine = parser(parser.cleanLine(line));
        //std::vector<std::string> parsedLine = parser(line);
        //line has been cleaned and parsed into a vector
        //testing: print the vector
        printVector(parsedLine);
    }*/

    readRecords.close();

    return 0;
}