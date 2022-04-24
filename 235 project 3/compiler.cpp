#include "compiler.h"

//

//

Compiler::Compiler(std::string filename) {
    fileToBeRead = filename;
    std::vector<std::string> vec;
    names.push_back(vec);
    names.push_back(vec);
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
    ErrorCode state = ErrorCode::None;
    //makes new var
    if (type == "STRING") {
        StrVar myString{name};
        StrMemory.push_back(myString);
        //StrNames.push_back(name);
        names[0].push_back(name);
        //magic number will have to be replaced with a variable in the future
        //kept as is right now due to a lack of time
        //std::cout << "Making a string var of name " << StrMemory.back().returnName() << std::endl;
    }
    else if (type == "NUMBER") {
        NumVar myNum{name};
        NumMemory.push_back(myNum);
        //NumNames.push_back(name);
        names[1].push_back(name);
        //std::cout << "Making a number var of name " << NumMemory.back().returnName() << std::endl;
    }
    return state;
}

/*
bool Compiler::interactWithVar(std::string name, Action action, VarType type, long long num, std::string str) {
    bool matchingVarFound = false;

    if (type = VarType::String) {

    }
    
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

    return matchingVarFound;
}
*/
VarData Compiler::findTypeByName(std::string givenName) {
    bool varFound = false;
    int nameListIterator = 0;
    for (std::vector<std::string> nameList : names) {
        for (int i = 0; i < nameList.size(); i++) {
            varFound = (nameList[i] == givenName);
            if (varFound) {
                if (nameListIterator == 0) {
                    //name found in string section
                    VarData output{i, VarType::String};
                    return output;
                }
                else if (nameListIterator == 1) {
                    //found in num section'
                    VarData output{i, VarType::Number};
                    return output;
                }
            }
        }
        nameListIterator++;
    }
    //nothing found
    VarData output{-1, VarType::Nothing};
    return output;
}

void Compiler::printValueByName(VarData data) {
    //std::cout << "print variable function broken, have this" << std::endl;
    if (data.type == VarType::String) {
        std::cout << StrMemory[data.placeInMemory].returnValue() << std::endl;
    }
    else if (data.type == VarType::Number) {
        std::cout << NumMemory[data.placeInMemory].returnValue() << std::endl;
    }
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
        std::string command = line[0];
        std::string name = line[1];
        //either a declaration "STRING/NUMBER var"
        //or a print "PRINT stuffhere"

        //declaration
        //std::cout << "Is this a new var?" << std::endl;
        if (command == "STRING" || command == "NUMBER") {
            //std::cout << "Creating string or number" << std::endl;
            error = createNewVar(command, name);
            return error;
        }
        //std::cout << "Not a new var" << std::endl;

        //print statement
        if (command == "PRINT") {
            //std::cout << "Printing thing" << std::endl;
            //check if the thing is a variable
            //if so, call its returnValue() function

            VarData data = findTypeByName(name);
            //bool matchingVarFound = interactWithVar(name, Action::Print, type);
            bool matchingVarFound = (data.type != VarType::Nothing);
            if (matchingVarFound) {
                //std::cout << "print variable function broken, have this" << std::endl;
                printValueByName(data);
            }
            //if not, directly print as seen below

            if (! isNum(name) && ! matchingVarFound) {//not a number, not a variable name
                std::string cleanedToken = "";
                for (char c : name) {
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