#include "Parser.h"
//#include <vector>
//#include <iostream>

//functions for Parser class

Parser::Parser() {
    separators.push_back('\"');
    separators.push_back(' ');
    separators.push_back('\t');
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

std::vector<std::string> Parser::operator()(std::string input) {
    std::vector<std::string> output;
    std::string parsedString = "";
    int quotationCounter = 0;

    for (char c : input) {
        //parse chars not in the separators list into a temp string
        //push string to output when separator detected
        bool quoteAlreadyAdded = false;
        //covers an issue where a quotation mark gets added twice
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
        if (charInSeparator(c) && quotationCounter % 2 == 0) {
            //seperator char found, no open quotation marks
            //std::cout << "DEBUG quote count: " << quotationCounter << std::endl;
            if (parsedString != "" && parsedString != " " && parsedString != "\"") {
                //std::cout << "DEBUG pushing string |" << parsedString << "| into vector" << std::endl;
                //covers an issue where sometimes parsedString gets pushed with value " " or "\""
                output.push_back(parsedString);
            }
            
            parsedString = "";
            //reset string to clear out old data
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
    if (parsedString != "" && parsedString != " " && parsedString != "\"") {
        //std::cout << "DEBUG pushing string |" << parsedString << "| into vector" << std::endl;
        //covers an issue where sometimes parsedString gets pushed with value " "
        output.push_back(parsedString);
    }
    //std::cout << "DEBUG end of for loop" << std::endl;
    //push last bit of data into output

    //the output should not be longer than 3 or 4 strings long
    //so we will pass by value
    return output;
}