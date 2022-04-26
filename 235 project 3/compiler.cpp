#include "compiler.h"

//

//

Compiler::Compiler(std::string filename) {
    fileToBeRead = filename;
    std::vector<std::string> vec;
    //push empty vectors into names
    names.push_back(vec);
    names.push_back(vec);

    //these words and symbols cannot be used as names
    reservedKeywords.push_back("NUMBER");
    reservedKeywords.push_back("STRING");
    reservedKeywords.push_back("PRINT");
    reservedKeywords.push_back("=");
    reservedKeywords.push_back("+");
    reservedKeywords.push_back("-");
    reservedKeywords.push_back("*");
}

std::string Compiler::returnFileName() const {
    return fileToBeRead;
}

//helper functions begin here

bool Compiler::isNum(std::string input) const {
    for (char c : input) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

ErrorCode Compiler::createNewVar(std::string type, std::string name) {
    ErrorCode state = ErrorCode::Continue;

    if (isNum(name)) {
        return ErrorCode::NameReserved;
        //you can't have a var named 12
    }

    for (std::string keyword : reservedKeywords) {
        if (name == keyword) {
            return ErrorCode::NameReserved;
            //you can't have a var named "PRINT"
        }
    }

    //makes new var
    if (type == "STRING") {
        StrVar myString{name};
        StrMemory.push_back(myString);
        //StrNames.push_back(name);
        names[strNameIndex].push_back(name);
        //replaced magic number with a static const declared at initialization

        //std::cout << "Making a string var of name " << StrMemory.back().returnName() << std::endl;
    }
    else if (type == "NUMBER") {
        NumVar myNum{name};
        NumMemory.push_back(myNum);
        //NumNames.push_back(name);
        names[numNameIndex].push_back(name);
        //std::cout << "Making a number var of name " << NumMemory.back().returnName() << std::endl;
    }
    return state;
}

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

std::string Compiler::removeQuotes(std::string input) {
    std::string cleanedToken = "";
    for (char c : input) {
        if (c != '\"') {
            cleanedToken += c;
        }
    }
    return cleanedToken;
}

void Compiler::printValueByName(VarData data) {
    //std::cout << "print variable function broken, have this" << std::endl;
    if (data.type == VarType::String) {
        std::string output = removeQuotes(StrMemory[data.placeInMemory].returnValue());
        std::cout << output << std::endl;
    }
    else if (data.type == VarType::Number) {
        std::cout << NumMemory[data.placeInMemory].returnValue() << std::endl;
    }
}

void Compiler::updateStrByName(VarData data, std::string newVal) {
    StrMemory[data.placeInMemory].updateValue(newVal);
}

void Compiler::updateNumByName(VarData data, long long newVal) {
    NumMemory[data.placeInMemory].updateValue(newVal);
}

VarData Compiler::findType(std::string token) {
    VarData output{-1, VarType::Nothing};

    if (isString(token)) {
        output.type = VarType::String;
    }
    else if (isNum(token)) {
        output.type = VarType::Number;
    }

    return output;
}

bool Compiler::isString(std::string input) const {
    if (input[0] == '\"' && input[input.length()-1] == '\"') {
        return true;
    }
    return false;
}

long long Compiler::pemdas(std::vector<std::string> expression) {
    long long output = 0;
    //takes in an expression as a vector
    //and evaluates its value

    //step 0: check if it is a legitimate expression.
    //each number must be flanked by operators (except first and last)
    //and each operator must be flanked by numbers.

    //step 1: replace all var names with literal values.
    //throw error if quote or unrecognized varname detected.

    //step 2: find every instance of * and replace it,
    //the number before, and the number after with one token
    //containing the result of multiplication

    //step 3: do the same with + and -

    //step 4: cast singular remaining str as long and parse into output.
    //step 5:
    return output;
}

//helper functions end here
//interpreter function begins here

ErrorCode Compiler::interpretLine(std::vector<std::string> line) {
    ErrorCode error = ErrorCode::Continue;
    //takes in one line, analyzes what it is supposed to do, then calls a helper
    //types of lines: variable declaration, print statement,
    //                value assignment, PEMDAS,
    //                comments (can be ignored), empty line

    //Variable declaration and print: 2 tokens
    //line[0] will be "STRING", "NUMBER", or "PRINT"
    //line[1] declares a variable or sends a variable or literal to print

    //assignment: 3 tokens
    //line[1] will be '=', line[0] will be the name of a variable
    //line[2] will be an appropriate value

    //number assignment with PEMDAS: > 5 tokens
    //line[0] will be var name, line[1] will be '='
    //line[2] onwards will be be alternating number literals / number var names and operators
    
    size_t lineLength = line.size();
    if (lineLength == 0) {
        return ErrorCode::Continue;
        //empty line or comment line, skip to next line
    }

    else if (lineLength == 2) {//var declaration or print
        std::string command = line[0];
        std::string name = line[1];
        //either a declaration "STRING/NUMBER var"
        //or a print "PRINT stuffhere"

        //declaration
        //std::cout << "Is this a new var?" << std::endl;
        if (command == "STRING" || command == "NUMBER") {
            //std::cout << "Creating string or number" << std::endl;
            return createNewVar(command, name);
        }
        //std::cout << "Not a new var" << std::endl;

        //print statement
        if (command == "PRINT") {
            //std::cout << "Printing thing" << std::endl;
            //check if the thing is a variable
            //if so, call its returnValue() function

            VarData data = findTypeByName(name);
            //data holds info on the location of the variable desired and its type
            bool matchingVarFound = (data.type != VarType::Nothing);
            if (matchingVarFound) {
                //std::cout << "print variable function broken, have this" << std::endl;
                printValueByName(data);
                return ErrorCode::Continue;
            }

            //if not a var name, directly print as seen below

            if (! isNum(name) && ! matchingVarFound) {//not a number, not a variable name
                //if it doesn't have quotes around it, it's not a literal
                //throw an error
                bool isLiteral = isString(name);
                if (! isLiteral) {
                    //std::cout << "not literal or name" << std::endl;
                    return ErrorCode::NotLiteralOrName;
                }

                //it has quotes, it is a literal
                //print it but without quotes
                std::string cleanedToken = removeQuotes(name);
                std::cout << cleanedToken << std::endl;
            }

            else if (! matchingVarFound){//a number, but not a var name
                std::cout << name << std::endl;
            }
        }
    }
    
    else if (lineLength == 3) {//var value assignment
        if (line[1] == "=") {
            //std::cout << "Assignment line" << std::endl;
            //is an assignment line
            //line[0] should be a var name
            std::string name = line[0];

            VarData data = findTypeByName(name);
            //data holds info on the location of the variable desired and its type

            if (data.type != VarType::Nothing) {//is a recognized data type
                //std::cout << "Recognized data type" << std::endl;
                std::string token = line[2];

                VarData newDataVar = findTypeByName(token);
                //this tells us if token is a string, number, or other variable
                VarData newDataLit = findType(token);
                //this tells us if token is a string, number, or other literal

                if (newDataVar.type == data.type) {//both are same type variables
                    std::cout << "In assignment line" << std::endl;
                    //assign var referenced by data with value from var referenced by newdata

                    //due to issue with dynamically returning value of string or number in one func
                    //more if-else statements needed
                    if (data.type == VarType::String) {
                        std::string newStr = StrMemory[newDataVar.placeInMemory].returnValue();
                        updateStrByName(data, newStr);
                    }
                    else if (data.type == VarType::Number) {
                        long long newNum = NumMemory[newDataVar.placeInMemory].returnValue();
                        updateNumByName(data, newNum);
                    }
                    return ErrorCode::Continue;
                }
                else if (newDataLit.type == data.type) {//both are same types but one is lit and other is var
                    //assign var referenced by data with newdata literal
                    if (data.type == VarType::String) {
                        updateStrByName(data, token);
                    }
                    else if (data.type == VarType::Number) {
                        updateNumByName(data, stol(token));
                    }
                    return ErrorCode::Continue;
                }
            }

            else {
                return ErrorCode::NotRecognizedName;
            }

        }

        else {
            return ErrorCode::TooManyTokens;
        }
    }

    else if (lineLength >= 4) {
        //number value assignment with pemdas
        //or print pemdas expression
        //std::cout << "Line length > 4, probably an expression" << std::endl;
        
        if (line[0] == "PRINT") {
            std::vector<std::string> expression;
            for (int i = 1; i < line.size(); i++) {
                expression.push_back(line[i]);
            }
            std::cout << pemdas(expression) << std::endl;
            return ErrorCode::Continue;
        }

        else if (line[1] == "=") {
            //check if line[0] is a number var
            //if not, throw error
            //if yes, continue
            VarData numData = findTypeByName(line[0]);
            if (numData.type != VarType::Number) {
                return ErrorCode::NotNumber;
            }
            else {
                std::cout << "number value assignment placeholder" << std::endl;
            }
        }
    }

    return ErrorCode::Continue;
}