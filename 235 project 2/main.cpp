#include <iostream>
//#include <fstream>
#include "InputManager.h"
//#include "Parser.h"
//#include "DiskManager.h"

int main() {
    InputManager engine;
    std::vector<char> separators {' ', '\t'};
    Parser parser{separators};

    std::string input;
    RequestState stopNow = RequestState::AllIsWell;

    std::cout << "This is a program for storing and modifying student data." << std::endl;
    std::cout << "Force exiting this program may result in your progress being lost." << std::endl;
    std::cout << "The program is ready for use. Enter your commands below." << std::endl;
    while (stopNow != RequestState::Exit) {
        //main code goes here
        getline(std::cin, input);
        stopNow = engine.processRequest(parser(input));
        if (stopNow == RequestState::BadFormat) {
            std::cout << "Your command is incorrectly formatted. Please try again." << std::endl;
        }
    }

    //when program goes out of scope, manager and parser should be deleted
    return 0;
}