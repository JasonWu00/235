#include <iostream>
//#include <fstream>
#include "InputManager.h"
//#include "Parser.h"
//#include "DiskManager.h"


void returnErrorMessage(RequestState state) {
    if (state == RequestState::BadFormat) {
        std::cout << "Entry incorrectly formatted" << std::endl;
    }
    else if (state == RequestState::BadFormatCommand) {
        std::cout << "Command is incorrectly formatted (not ADD, FIND, REMOVE, or STOP)" << std::endl;
    }
    else if (state == RequestState::BadFormatIdAgeName) {
        std::cout << "ID, Age, or Name is incorrectly formatted " << std::endl;
        std::cout << "(ID/Age not int or Name has too many quotes)" << std::endl;
    }
    else if (state == RequestState::BadFormatCondition) {
        std::cout << "Condition is incorrectly formatted" << std::endl;
        std::cout << "(missing or wrong condition operator or non-int age or id)" << std::endl;
    }
    else if (state == RequestState::BadFormatMissingArgs) {
        std::cout << "Command is incorrectly formatted" << std::endl;
        std::cout << "(too few entries)" << std::endl;
    }
    else if (state == RequestState::BadFormatOverflow) {
        std::cout << "ID, Age, or Name is incorrectly formatted " << std::endl;
        std::cout << "(ID/Age values cause overflow)" << std::endl;
    }
    else if (state == RequestState::Exit) {
        std::cout << "Saving your progress and exiting the program now" << std::endl;
    }
}
//functionality for returning error messages
//not implemented due to project requirements

int main() {
    InputManager engine;
    std::vector<char> separators {' ', '\t'};
    Parser parser{separators};

    std::string input;
    RequestState stopNow = RequestState::AllIsWell;

    // std::cout << std::endl;
    // std::cout << "This is a program for storing and modifying student data." << std::endl;
    // std::cout << "Force exiting this program may result in your progress being lost." << std::endl;
    // std::cout << "The program is ready for use. Enter your commands below." << std::endl;
    // std::cout << std::endl;

    
    while (stopNow != RequestState::Exit) {
        //main code goes here
        getline(std::cin, input);
        stopNow = engine.processRequest(parser(input));
        returnErrorMessage(stopNow);
    }
    /*
    std::cout << "DEBUG mode" << std::endl;
    
    int i = 0;
    while (i == 0) {
        getline(std::cin, input);
        std::vector<std::string> parsed_command;
        parsed_command = parser(input);
        std::cout << "{";
        for (std::string thing : parsed_command) {
            std::cout << thing << " ";
        }
        std::cout << "}" << std::endl;
    }*/

    //when program goes out of scope, manager and parser should be deleted
    return 0;
}