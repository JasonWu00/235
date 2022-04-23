#include "compiler.h"

std::string Var::returnName() const {
    return name;
}

std::string StrVar::returnValue() const {
    return value;
}

Var::Var(std::string name) {
    this->name = name;
}

//child constructors call parent constructor

NumVar::NumVar(std::string name) : Var(name) {

}

StrVar::StrVar(std::string name) : Var(name) {
    
}

long long NumVar::returnValue() const {
    return value;
}

void NumVar::updateValue(long long input) {
    value = input;
}

void StrVar::updateValue(std::string input) {
    value = input;
}

Compiler::Compiler(std::string filename) {
    fileToBeRead = filename;
}

std::string Compiler::returnFileName() const {
    return fileToBeRead;
}

bool Compiler::isNum(std::string input) const {
    for (char c : input) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

ErrorCode Compiler::createNewVar(std::string type, std::string name) {
    ErrorCode state = None;
    //makes new var
    if (type == "STRING") {
        StrVar myString{name};
        memory.push_back(myString);
        //std::cout << "Making a string var of name " << memory.back().returnName() << std::endl;
    }
    else if (type == "NUMBER") {
        NumVar myNum{name};
        memory.push_back(myNum);
        //std::cout << "Making a number var of name " << memory.back().returnName() << std::endl;
    }
    return state;
}

ErrorCode Compiler::interpretLine(std::vector<std::string> line) {
    ErrorCode error = ErrorCode::None;
    //takes in one line, analyzes what it is supposed to do, then calls a helper
    //types of lines: variable declaration, print statement,
    //                value assignment (with or without PEMDAS),
    //                comments (can be ignored)

    //Variable declaration and print
    //line[0] will be "STRING", "NUMBER", or "PRINT"
    //line[1] declares a variable or sends a variable or literal to print
    
    size_t lineLength = line.size();
    if (lineLength == 2) {

        //declaration
        if (line[0] == "STRING" || line[0] == "NUMBER") {
            //std::cout << "Creating string or number" << std::endl;
            error = createNewVar(line[0], line[1]);
        }

        //print statement
        else if (line[0] == "PRINT") {
            std::cout << "Printing thing" << std::endl;

            if (! isNum(line[1])) {//not a number
                std::string cleanedToken = "";
                for (char c : line[1]) {
                    if (c != '\"') {
                        cleanedToken += c;
                    }
                }
                std::cout << cleanedToken << std::endl;
            }

            else {
                std::cout << line[1] << std::endl;
            }
        }
    }

    return error;
}