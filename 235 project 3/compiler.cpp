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
    value = 0;//intialized to default value
}

StrVar::StrVar(std::string name) : Var(name) {
    value = "Default StrVar value";
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
        StrMemory.push_back(myString);
        //std::cout << "Making a string var of name " << StrMemory.back().returnName() << std::endl;
    }
    else if (type == "NUMBER") {
        NumVar myNum{name};
        NumMemory.push_back(myNum);
        //std::cout << "Making a number var of name " << NumMemory.back().returnName() << std::endl;
    }
    return state;
}

bool Compiler::interactWithVar(std::string name, Action action, long long num, std::string str) {
    bool matchingVarFound = false;
    
    for (NumVar myNumVar : NumMemory) {
        if (name == myNumVar.returnName()) {
            matchingVarFound = true;
            std::cout << "NumVar found" << std::endl;
            //found the number, now to assign it a value or print something
            if (action == Action::Print) {
                std::cout << myNumVar.returnValue() << std::endl;
            }
        }
    }

    if (! matchingVarFound) {
        for (StrVar myStrVar : StrMemory) {
            if (name == myStrVar.returnName()) {
                matchingVarFound = true;
                std::cout << "StrVar found" << std::endl;
                if (action == Action::Print) {
                    std::cout << myStrVar.returnValue() << std::endl;
                }
                
            }
        }
    }
    /*
    
    for (i = 0; i < StrMemory.size(); i++) {//iterate through memory
        matchingVarFound = (name == StrMemory[i].returnName());
        if (matchingVarFound) {
            //std::cout << StrMemory[i].returnValue() << std::endl;
            std::cout << "StrVar found" << std::endl;
            return StrMemory[i].returnValue();
            //return matchingVarFound;
        }
    }

    if (! matchingVarFound) {
        for (i = 0; i < NumMemory.size(); i++) {//iterate through memory
            matchingVarFound = (name == NumMemory[i].returnName());
            if (matchingVarFound) {
                //std::cout << NumMemory[i].returnValue() << std::endl;
                std::cout << "NumVar found" << std::endl;
                return NumMemory[i].returnValue();
                //return matchingVarFound;
            }
        }
    }*/

    return matchingVarFound;
}

ErrorCode Compiler::interpretLine(std::vector<std::string> line) {
    ErrorCode error = ErrorCode::None;
    //takes in one line, analyzes what it is supposed to do, then calls a helper
    //types of lines: variable declaration, print statement,
    //                value assignment (with or without PEMDAS),
    //                comments (can be ignored), empty line

    //Variable declaration and print
    //line[0] will be "STRING", "NUMBER", or "PRINT"
    //line[1] declares a variable or sends a variable or literal to print
    
    size_t lineLength = line.size();
    if (lineLength == 0) {
        return ErrorCode::None;
        //empty line, skip to next line
    }
    if (lineLength == 2) {

        //declaration
        if (line[0] == "STRING" || line[0] == "NUMBER") {
            //std::cout << "Creating string or number" << std::endl;
            error = createNewVar(line[0], line[1]);
        }

        //print statement
        else if (line[0] == "PRINT") {
            std::cout << "Printing thing" << std::endl;
            //check if the thing is a variable
            //if so, call its returnValue() function

            bool matchingVarFound = interactWithVar(line[1], Action::Print);

            //if not, directly print as seen below

            if (! isNum(line[1]) && ! matchingVarFound) {//not a number, not a variable name
                std::string cleanedToken = "";
                for (char c : line[1]) {
                    if (c != '\"') {
                        cleanedToken += c;
                    }
                }
                std::cout << cleanedToken << std::endl;
            }

            else if (! matchingVarFound){//a number, but not a var name
                std::cout << line[1] << std::endl;
            }
        }
    }

    return error;
}