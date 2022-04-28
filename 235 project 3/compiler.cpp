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
    reservedKeywords.push_back("#");
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

    std::string first = "";
    first += name[0];
    if (isNum(first)) {
        //std::cout << "badname" << std::endl;
        return ErrorCode::BadName;
    }

    for (std::string keyword : reservedKeywords) {
        if (name == keyword) {
            return ErrorCode::NameReserved;
            //you can't have a var named "PRINT"
        }
    }

    //makes new var
    if (type == "STRING") {
        std::string quoteless = removeQuotes(name);
        StrVar myString{quoteless};
        StrMemory.push_back(myString);
        //StrNames.push_back(name);
        names[strNameIndex].push_back(quoteless);
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

VarData Compiler::findDataByName(std::string givenName) const {
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

std::string Compiler::removeQuotes(std::string input) const {
    std::string cleanedToken = "";
    for (char c : input) {
        if (c != '\"') {
            cleanedToken += c;
        }
    }
    return cleanedToken;
}

void Compiler::printValueByName(VarData data) const {
    //std::cout << "print variable function broken, have this" << std::endl;
    if (data.type == VarType::String) {
        std::string str = returnStrByName(data);
        std::string cleaned = removeQuotes(str);
        std::cout << cleaned << std::endl;
    }
    else if (data.type == VarType::Number) {
        std::cout << returnNumByName(data);// << std::endl;
    }
}

void printStrPerChar(std::string input) {
    //local debug function for seeing if newline chars are implemented properly
    for (char c : input) {
        if (c != '\n') {
            std::cout << c << "|";
        }
        else {
            std::cout << "NL" << "|";
        }
    }
    std::cout << std::endl;
}

std::string Compiler::replaceNewlines(std::string input) const {
    //Helper function intended to clear out bad newlines '\\n'
    //Obsoleted due to implementation of a simpler cleaning functionality
    //in the parser

    std::string output = input;
    bool newlinesReplaced = false;
    std::vector<int> newlineLocations;
    std::string badNewline = "\\n";

    std::cout << "before replacing" << std::endl;
    //printStrPerChar(output);
    std::cout << std::endl;
    
    while (! newlinesReplaced) {
        size_t newlinePlace = output.find(badNewline);
        if (newlinePlace != std::string::npos) {//there is >=1 instance of a bad newline
            output.replace(newlinePlace, newlinePlace + badNewline.size()-1, "\n");
            newlineLocations.push_back(newlinePlace);
        }
        else {
            newlinesReplaced = true;
        }
    }

    std::cout << "after replacing" << std::endl;
    //printStrPerChar(output);
    std::cout << std::endl;

    /*
    for (int i : newlineLocations) {
        if (output[i] == 'n') {
            output.erase(i, 1);
            //deals with an issue where sometimes there's a random n left at the start due to bad cropping
        }
    }*/

    return output;
}

void Compiler::updateStrByName(VarData data, std::string newVal) {
    //std::string cleanedStr = replaceNewlines(newVal);
    StrMemory[data.placeInMemory].updateValue(newVal);
}

void Compiler::updateNumByName(VarData data, long long newVal) {
    NumMemory[data.placeInMemory].updateValue(newVal);
}

long long Compiler::returnNumByName(VarData data) const {
    return NumMemory[data.placeInMemory].returnValue();
}

std::string Compiler::returnStrByName(VarData data) const {
    return StrMemory[data.placeInMemory].returnValue();
}

VarData Compiler::findType(std::string token) const {
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

ErrorCode Compiler::validateExp(std::vector<std::string> expression) const {
    std::vector<std::string> myExp = expression;

    std::vector<std::string> operators;
    operators.push_back("*");
    operators.push_back("+");
    operators.push_back("-");

    //number of tokens must be odd (x operators and x+1 literals)
    if ((myExp.size() % 2) != 1) {//even tokens
        //std::cout << "Too many tokens" << std::endl;
        return ErrorCode::TooManyTokensInExp;
    }

    //step 1: parse through every non-number and non-operator
    //and see if they are number vars
    //if not: throw an error

    for (int i = 0; i < myExp.size(); i+=2) {
        if (! isNum(myExp[i])) {
            VarData data = findDataByName(myExp[i]);
            if (data.type != VarType::Number) {
                //std::cout << "Not Number" << std::endl;
                return ErrorCode::NotNumber;
            }
            else {
                long long actualVal = returnNumByName(data);
                myExp[i] = std::to_string(actualVal);
                //temp replaces vars with literals to facilitate next for loop
            }
        }
    }

    //each number must be flanked by operators (except first and last)
    //and each operator must be flanked by numbers
    //also ensure only recognized operators present

    for (int i = 1; i < myExp.size(); i+=2) {
        if (! (isNum(myExp[i-1]) && isNum(myExp[i+1]))) {//not nums
            //std::cout << "Not number 2" << std::endl;
            return ErrorCode::NotNumber;
        }

        bool badOp = false;
        for (std::string op : operators) {
            if (op == myExp[i]) {
                badOp = true;
                //return ErrorCode::IncorrectOperator;
            }
        }

        if (! badOp) {
            //std::cout << "Bad operator" << std::endl;
            return ErrorCode::IncorrectOperator;
        }
    }

    //if all tests pass, return errorcode continue
    return ErrorCode::Continue;
}

long long Compiler::pemdas(std::vector<std::string> expression) const {
    long long output = 0;
    std::vector<std::string> myExp = expression;
    //takes in an expression as a vector
    //and evaluates its value

    //step 1: replace all var names with literal values.

    for (int i = 0; i < myExp.size(); i+=2) {
        if (! isNum(myExp[i])) {
            VarData data = findDataByName(myExp[i]);
            long long actualVal = returnNumByName(data);
            myExp[i] = std::to_string(actualVal);
            //temp replaces vars with literals to facilitate next for loop
        }
    }

    //step 2: find every instance of * and replace it,
    //the number before, and the number after with one token
    //containing the result of multiplication

    for (int i = 1; i < myExp.size(); i+=2) {
        if (myExp[i] == "*") {
            long long multiplied = stoll(myExp[i-1]) * stoll(myExp[i+1]);

            //replace myExp[i] with multiplied, erase nums before and after it
            myExp[i] = std::to_string(multiplied);
            myExp.erase(myExp.begin() + i + 1);
            myExp.erase(myExp.begin() + i - 1);
            i -= 2;

            //suppose we are looking at token 3 of 0 1 2 3 4 5 6 (4th token)
            //after we remove #2 and #4, we are left with 0 1 3 5 6 (3rd token)
            //size dropped by 2, so we must decrease i by 2
        }
    }

    //step 3: do the same with + and -

    for (int i = 1; i < myExp.size(); i+=2) {
        long long sum = stoll(myExp[i-1]);

        if (myExp[i] == "+") {
            sum += stoll(myExp[i+1]);
        }

        else if (myExp[i] == "-") {
            sum -= stoll(myExp[i+1]);
        }
        myExp[i] = std::to_string(sum);
        myExp.erase(myExp.begin() + i + 1);
        myExp.erase(myExp.begin() + i - 1);
        i -= 2;
    }

    //step 4: cast singular remaining str as long and parse into output.
    output = stoll(myExp[0]);

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

    //Variable declaration and simple print: 2 tokens
    //line[0] will be "STRING", "NUMBER", or "PRINT"
    //line[1] declares a variable or sends a variable or literal to print

    //assignment: 3 tokens
    //line[1] will be '=', line[0] will be the name of a variable
    //line[2] will be an appropriate value

    //number assignment with PEMDAS: > 5 tokens
    //line[0] will be var name, line[1] will be '='
    //line[2] onwards will be be alternating number literals / number var names and operators

    //print with PEMDAS: > 4 tokens
    //line[0] will be PRINT
    //line[1] onwards will be the expression
    
    size_t lineLength = line.size();

    for (int i = 0; i < lineLength; i++) {
        if (line[i] == "BAD_NAME_FORMAT") {
            return ErrorCode::BadQuoteFormatting;
        }
    }

    if (lineLength == 0) {
        return ErrorCode::Continue;
        //empty line or comment line, skip to next line
    }

    if (lineLength == 1) {
        return ErrorCode::None;
        //the user may have put any number of unsupported things here
        //using errorcode none as a standin for now
    }

    if (lineLength == 2) {//var declaration or print
        std::string command = line[0];
        std::string name = line[1];
        //std::cout << "line length 2" << std::endl;
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
        else if (command == "PRINT") {
            //std::cout << "Printing thing" << std::endl;
            //check if the thing is a variable
            //if so, call its returnValue() function

            VarData data = findDataByName(name);
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
                //std::string fixedNewlines = replaceNewlines(cleanedToken);
                //printStrPerChar(cleanedToken);
                std::cout << cleanedToken;// << std::endl;
            }

            else if (! matchingVarFound){//a number, but not a var name
                std::cout << name;// << std::endl;
                return ErrorCode::Continue;
            }
        }

        else {
            return ErrorCode::UnknownVarType;
        }
    }
    
    if (lineLength == 3) {//var value assignment
        if (line[1] == "=") {
            //std::cout << "Assignment line" << std::endl;
            //is an assignment line
            //line[0] should be a var name
            std::string name = line[0];

            VarData data = findDataByName(name);
            //data holds info on the location of the variable desired and its type

            if (data.type != VarType::Nothing) {//is a recognized data type
                //std::cout << "Recognized data type" << std::endl;
                std::string token = line[2];

                VarData newDataVar = findDataByName(token);
                //this tells us if token is a string, number, or other variable
                VarData newDataLit = findType(token);
                //this tells us if token is a string, number, or other literal

                if (data.type != newDataLit.type && data.type != newDataVar.type) {
                    return ErrorCode::BadVarLitCombo;
                }

                if (newDataVar.type == data.type) {//both are same type variables
                    //std::cout << "In assignment line" << std::endl;
                    //assign var referenced by data with value from var referenced by newdata

                    //due to issue with dynamically returning value of string or number in one func
                    //more if-else statements needed
                    if (data.type == VarType::String) {
                        std::string newStr = returnStrByName(newDataVar);
                        updateStrByName(data, newStr);
                        
                    }
                    else if (data.type == VarType::Number) {
                        long long newNum = returnNumByName(newDataVar);
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
                        updateNumByName(data, stoll(token));
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

    if (lineLength >= 4) {
        //number value assignment with pemdas
        //or print pemdas expression
        //std::cout << "Line length > 4, probably an expression" << std::endl;

        if (line[0] == "PRINT") {

            std::vector<std::string> expression;
            for (int i = 1; i < line.size(); i++) {
                expression.push_back(line[i]);
            }

            ErrorCode correctExp = validateExp(expression);
            if (correctExp != ErrorCode::Continue) {
                //std::cout << "incorrectExp" << std::endl;
                return correctExp;
            }

            std::cout << pemdas(expression) << std::endl;
            return ErrorCode::Continue;
        }

        else if (line[1] == "=") {
            //check if line[0] is a number var
            //if not, throw error
            //if yes, continue

            VarData numData = findDataByName(line[0]);
            if (numData.type != VarType::Number) {
                //not a number var
                return ErrorCode::NotNumber;
            }

            else {//is a number var
                //std::cout << "number value assignment placeholder" << std::endl;
                //pass everything to right of equal sign to pemdas

                std::vector<std::string> expression;
                for (int i = 2; i < line.size(); i++) {
                    expression.push_back(line[i]);
                }

                ErrorCode correctExp = validateExp(expression);
                if (correctExp != ErrorCode::Continue) {//check if pemdas function is legal
                    //std::cout << "incorrectExp" << std::endl;
                    return correctExp;
                }

                //it is legal, now send it to pemdas() to be evaluated
                long long output = pemdas(expression);
                updateNumByName(numData, output);
                return ErrorCode::Continue;
            }
        }
    }

    return ErrorCode::Continue;
    //in case something goes wrong
}