#include <iostream>
//#include <fstream>
#include "InputManager.h"
//#include "Parser.h"
//#include "DiskManager.h"

void returnErrorMessage(RequestState state) {
    if (state == RequestState::BadFormat) {
        std::cout << "Entry incorrectly formatted." << std::endl;
    }
    else if (state == RequestState::BadFormat_Command) {
        std::cout << "Your command is incorrectly formatted (not ADD, FIND, REMOVE, or STOP)." << std::endl;
    }
    else if (state == RequestState::BadFormat_IdAge) {
        std::cout << "ID or Age is incorrectly formatted (not an int)." << std::endl;
    }
    else if (state == RequestState::Exit) {
        std::cout << "Saving your progress and exiting the program now." << std::endl;
    }
}

int main() {
    InputManager engine;
    std::vector<char> separators {' ', '\t'};
    Parser parser{separators};

    std::string input;
    RequestState stopNow = RequestState::AllIsWell;

    std::cout << std::endl;
    std::cout << "This is a program for storing and modifying student data." << std::endl;
    std::cout << "Force exiting this program may result in your progress being lost." << std::endl;
    std::cout << "The program is ready for use. Enter your commands below." << std::endl;
    std::cout << std::endl;

    
    while (stopNow != RequestState::Exit) {
        //main code goes here
        getline(std::cin, input);
        stopNow = engine.processRequest(parser(input));
        returnErrorMessage(stopNow);
    }

    /*std::cout << "DEBUG mode" << std::endl;
    
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