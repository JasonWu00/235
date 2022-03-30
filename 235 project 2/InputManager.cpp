//#include <iostream>
#include "InputManager.h"
//#include <string>
//#include <vector>

//functions for InputManager class

InputManager::InputManager() {
    //std::cout << "Making a manager" << std::endl;
    privateDiskMan = new DiskManager("student_data.txt");
    //std::cout << "diskMan made" << std::endl;
    privateDiskMan->getRecords(records);
    //std::cout << "Records got" << std::endl;
    //the disk man will parse the content of the file into
    //the student record vector once it is created.
    //privateParser = new Parser();
}

InputManager::~InputManager() {
    privateDiskMan->writeRecords(records);
    //write to file before self deletion
    delete privateDiskMan;
    privateDiskMan = nullptr;
    for (Student* student : records) {
        delete student;
        student = nullptr;
    }
}

RequestState InputManager::processRequest(std::vector<std::string> input) {
    //input[0] tells if it is add, find, remove, or stop
    //returns an appropriate RequestState enum indicating exit status
    if (input[0] == "STOP") {
        return RequestState::Exit;
    }
    else if (input[0] == "ADD") {
        if (! isNum(input[1]) || ! isNum(input[3])) {
            //id and age should be numbers
            return RequestState::BadFormat_IdAge;
            //no need for an else statement, return exits function
        }
        addStudent(stoi(input[1]), input[2], stoi(input[3]));
        return RequestState::AllIsWell;
    }
    else if (input[0] == "FIND") {
        //input[1] is the condition
        return findCondition(input[1]);
    }
    else if (input[0] == "REMOVE") {
        return removeCondition(input[1]);
    }
    else {
        //input[0] is not a recognized command
        return RequestState::BadFormat_Command;
    }
}

//helper function to see if a string can be turned into an int
bool InputManager::isNum(std::string input) {
    for (char c : input) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

RequestState InputManager::addStudent(int student_id, std::string name, int age) {
    Student* student = new Student(student_id, name, age);
    records.push_back(student);
    return RequestState::AllIsWell;
}

RequestState InputManager::findCondition(std::string condition) {
    std::cout << "findCondition is triggered but did nothing (incomplete)" << std::endl;
    return RequestState::AllIsWell;
}

RequestState InputManager::removeCondition(std::string condition) {
    std::cout << "removeCondition is triggered but did nothing (incomplete)" << std::endl;
    return RequestState::AllIsWell;
}
