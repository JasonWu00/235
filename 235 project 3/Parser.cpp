#include "Parser.h"
//#include <vector>
//#include <iostream>

//functions for Parser class
//Code taken from 235 project 2

Parser::Parser() {
    separators.push_back('\"');
    separators.push_back(' ');
    separators.push_back('\t');
    separators.push_back('\r');
    separators.push_back('\n');
    //operators vector holds some conditional operators
    //=, <, >
    operators.push_back('=');
    operators.push_back('<');
    operators.push_back('>');
}


Parser::Parser(std::vector<char> separators) : Parser::Parser() {
    this->separators = separators;
}

//helper functions to look for a char in the seperators vector
bool Parser::charInSeparator(char c) const {
    for (char separator : separators) {
        //checks from first element of separator to last
        //thus quotation marks have precedence over spaces and tabs
        if (c == separator) {
            return true;
        }
    }
    return false;
}

//same as above but for operators vector
bool Parser::charInOperator(char c) const {
    for (char op : operators) {
        //checks from first element of separator to last
        //thus quotation marks have precedence over spaces and tabs
        if (c == op) {
            return true;
        }
    }
    return false;
}

/*
bool Parser::charInSeparator(char c, char priorityDelimiter) const {
    //this overloaded version only returns true if c is also equal to 
    //the priorityDelimiter specified
    //this allows users to parse using a specific char and not have
    //this function also parse using all other possible delimiter chars

    for (char separator : separators) {
        //checks from first element of separator to last
        //thus quotation marks have precedence over spaces and tabs
        if (c == separator && c == priorityDelimiter) {
            return true;
        }
    }
    return false;
}*/

std::vector<std::string> Parser::operator()(std::string input, int state) const {
    //state = 0 -> use charInSeparator()
    //state = 1 -> use charInOperator();
    std::vector<std::string> output;
    std::string parsedString = "";
    int quotationCounter = 0;

    for (char c : input) {
        //parse chars not in the separators list into a temp string
        //push string to output when separator detected
        bool quoteAlreadyAdded = false;
        //covers an issue where a quotation mark gets added twice

        if (c == '#') {
            break;
            //rest of code to be read is a comment, can skip w/o issue
        }
        if (c == '\"') {
            //std::cout << "DEBUG quotation found" << std::endl;
            quotationCounter++;
            //std::cout << "DEBUG quote count: " << quotationCounter << std::endl;
            if (quotationCounter % 2 == 0 && parsedString[parsedString.length()] != '\"') {
                //if this is a closing quote and there isn't a quote right before that
                //add char to string
                //std::cout << "DEBUG closing quotations and no quotation before this" << std::endl;
                parsedString += c;
                quoteAlreadyAdded = true;
            }
            //if there is an open quotation mark (counter is odd)
            //ignore separator and add it 
        }

        bool charShouldBeRemoved;
        if (state) {//state == 1, use charInOperator()
            charShouldBeRemoved = charInOperator(c);
        }
        else {//state == 0, use charInSeparator()
            charShouldBeRemoved = charInSeparator(c);
        }

        if (charShouldBeRemoved && quotationCounter % 2 == 0) {
            //seperator char found, no open quotation marks
            //std::cout << "DEBUG quote count: " << quotationCounter << std::endl;
            if (parsedString != "" && parsedString != " " && parsedString != "\"") {
                //std::cout << "DEBUG pushing string |" << parsedString << "| into vector" << std::endl;
                //covers an issue where sometimes parsedString gets pushed with value " " or "\""
                output.push_back(parsedString);
                parsedString = "";
                //reset string to clear out old data
            }
        }

        else if (! quoteAlreadyAdded){
            //not seperator or open quotation mark
            //or closing quotation has already been added
            //add to parsedString
            //std::cout << "DEBUG expanding parsedString" << std::endl;
            parsedString += c;
            //std::cout << "DEBUG string value is: |" << parsedString << "|" << std::endl;
        }
        //std::cout << "DEBUG end loop" << std::endl;
    }

    if (parsedString != "" 
        && parsedString != " " 
        && parsedString != "\"" 
        && parsedString != "#"
        && parsedString != "\n"//cleaning away newlines as well
        && parsedString != "\r") {
        //std::cout << "DEBUG pushing string |" << parsedString << "| into vector" << std::endl;
        //covers an issue where sometimes parsedString gets pushed with value " "
        output.push_back(parsedString);
        //push last bit of data into output
    }

    //std::cout << "DEBUG end of for loop" << std::endl;

    if (quotationCounter >= 3 || quotationCounter == 1) {
        //assigning values to STRINGs should have 0 or 2 quotation marks
        //otherwise it is an incorrect input
        output[2] = "BAD_NAME_FORMAT";
    }
    //the output should not be longer than a few strings long
    //so we will pass by value
    return output;
}

std::string Parser::cleanLine(std::string rawline) {
    //adds spaces between +, -, *, = symbols
    std::string output = "";
    for (char c : rawline) {
        if (c == '*' || c == '+' || c == '-' || c == '=') {
            output += ' ';
            output += c;
            output += ' ';
        }
        else {
            output += c;
        }
        //std::cout << "Output is: " << std::endl;
    }
    //std::cout << "Cleaned line: " << output << std::endl;
    return output;
}