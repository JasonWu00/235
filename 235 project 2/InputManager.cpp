//#include <iostream>
#include "InputManager.h"
//#include <string>
//#include <vector>
#include <climits>

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
    if (input.empty()) {
        //input empty, nonsensical request
        return RequestState::BadFormatMissingArgs;
    }

    std::string order = input[0];
    /*for (char c : input[0]) {
        order += c - 32;
        //"add" becomes "ADD", etc
    }*/
    //functionality to cover for lowercase entries such as "find"
    //not implemented due to project requirements
    //std::cout << order << std::endl;

    std::string sanitizedInput = "";
    for (int i = 1; i < input.size(); i++) {
        if (i < input.size()) {
            sanitizedInput += input[i];
        }
        //to cover for cases where the condition section is inconsistently spaced
        //e.g. "id > 4", "id> 4", "id >4", "id>4"
        //this will compact them all into "id>4"
        //used for findCondition and removeCondition
    }
    if (order == "STOP") {
        return RequestState::Exit;
    }
    else if (order == "ADD") {
        if (input.size() < 4) {
            return RequestState::BadFormatMissingArgs;
        }
        else if (! isNum(input[1]) || ! isNum(input[3]) || input[2] == "BAD_NAME_FORMAT") {
            //id and age should be numbers
            return RequestState::BadFormatIdAgeName;
            //no need for an else statement, return exits function
        }
        addStudent(stoi(input[1]), input[2], stoi(input[3]));
        return RequestState::AllIsWell;
    }
    else if (order == "FIND") {
        //input[1] is the condition
        return findCondition(sanitizedInput);
    }
    else if (order == "REMOVE") {
        return removeCondition(sanitizedInput);
    }
    else {
        //input[0] is not a recognized command
        return RequestState::BadFormatCommand;
    }
}

//helper function to see if a string can be turned into an int
bool InputManager::isNum(std::string input) const {
    for (char c : input) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

RequestState InputManager::addStudent(long studentId, std::string name, int age) {
    if (studentId > UINT_MAX || studentId < 0) {
        return RequestState::BadFormatOverflow;
    }
    else if (age > USHRT_MAX || age < 0) {
        return RequestState::BadFormatOverflow;
    }
    Student* student = new Student(studentId, name, age);
    records.push_back(student);

    std::string studentAsString = student->toString();
    //std::cout << "The following student has been added:" << std::endl;
    //std::cout << studentAsString << std::endl << std::endl;

    return RequestState::AllIsWell;
}

RequestState InputManager::fitsCondition(std::string condition, Student* student) const {
    //helper function
    //confirms if the student fits the condition
    //returns Match if matches, NoMatch otherwise

    std::vector<std::string> parsedCondition = privateParser(condition, 1);
    
    /*std::cout << "DEBUG ";
    for (std::string str : parsedCondition) {
        std::cout << str << "|";
    }*/
    //std::cout << std::endl;
    //pC[0] refers to the field (id, age, name)
    //pc[1] is either <, >, or =
    //pc[2] is an int of some sort or a string
    if (parsedCondition.size() < 2) {
        //not enough inputs
        return RequestState::BadFormatMissingArgs;
    }

    std::string field = parsedCondition[0];
    /*
    for (char c : parsedCondition[0]) {
        field += c + 32;
        //"ID" becomes "id", etc
    }*/
    
    std::string studentValue;
    if (field == "id") {
        studentValue = std::to_string(student->getID());
    }
    else if (field == "age") {
        studentValue = std::to_string(student->getAge());
    }
    else if (field == "name") {
        for (char c : student->getName()) {
            if (c != '\"') {
                studentValue += c;
                //deals with quotation marks used in the storage file
            }
        }
    }
    else {//field is neither age nor id nor name
        return RequestState::BadFormatCondition;
    }
    //std::cout << "DEBUG studentValue populated" << std::endl;

    std::string fieldValue;
    for (char c : parsedCondition[1]) {
        if (c != '\"') {
            fieldValue += c;
            //deals with quotation marks used in the storage file
        }
    }

    char op = ' '; //parsedCondition is missing operator symbol, we must find it
    int opCounter = 0;
    for (char c : condition) {
        if (c == '<' || c == '>' || c == '=') {
            op = c;
            opCounter++;
            if (opCounter >= 2) {
                op = '!';//generic nonsensical operator
                break;//stop the loop, this input is nonsensical
            }
        }
    }
    //std::cout << "DEBUG condition is " << condition << std::endl;
    //std::cout << "DEBUG operator char is " << op << std::endl;

    //now for the comparison
    bool isCorrectStudent;
    if (op == '<') {
        if (! isNum(fieldValue)) {//fieldValue cannot be convered to int
            return RequestState::BadFormatCondition;
        }
        isCorrectStudent = (stoi(studentValue) < stoi(fieldValue));

        // std::cout << "DEBUG fieldValue is: " << fieldValue << std::endl;
        // std::cout << "DEBUG studentValue is: " << studentValue << std::endl;
        // std::cout << "DEBUG isCorrectStudent value (<): " << isCorrectStudent << std::endl;
        //> and < only applies for id and age
        //so we automatically convert the strings to ints
    }
    else if (op == '>') {
        if (! isNum(fieldValue)) {//fieldValue cannot be convered to int
            return RequestState::BadFormatCondition;
        }
        isCorrectStudent = (stoi(studentValue) > stoi(fieldValue));

        // std::cout << "DEBUG fieldValue is: " << fieldValue << std::endl;
        // std::cout << "DEBUG studentValue is: " << studentValue << std::endl;
        // std::cout << "DEBUG isCorrectStudent value (>): " << isCorrectStudent << std::endl;
    }
    else if (op == '=') {
        isCorrectStudent = (fieldValue == studentValue);

        // std::cout << "DEBUG fieldValue is: " << fieldValue << std::endl;
        // std::cout << "DEBUG studentValue is: " << studentValue << std::endl;
        // std::cout << "DEBUG isCorrectStudent value (=): " << isCorrectStudent << std::endl;
        //= can apply to name
        //we directly compare strings
    }
    else {//operator is not <, >, or =
        return RequestState::BadFormatCondition;
    }

    if (isCorrectStudent) {
        return RequestState::Match;
    }
    else {
        return RequestState::NoMatch;
    }
    
    //return RequestState::AllIsWell;
}

RequestState InputManager::findCondition(std::string condition) const {
    //std::cout << "findCondition is triggered but did nothing (incomplete)" << std::endl;
    bool somethingFound = false;

    for (Student* student : records) {
        RequestState matchFound = fitsCondition(condition, student);

        if (matchFound == RequestState::Match) {//if student fits condition, print student
            somethingFound = true;

            std::string studentAsString = student->toString();
            //uses Student helper function to generate a string representation
            std::cout << studentAsString << std::endl;
        }
        else if (matchFound != RequestState::NoMatch) {
            //some kind of an error state returned
            return matchFound;
        }
        //if matchFound == noMatch, for loop moves on
    }
    
    if (! somethingFound) {
        //std::cout << "No Student matching this condition found" << std::endl;
    }
    //std::cout << std::endl;
    return RequestState::AllIsWell;
}

RequestState InputManager::removeCondition(std::string condition) {
    //std::cout << "removeCondition is triggered but did nothing (incomplete)" << std::endl;
    bool somethingFound = false;
    //std::cout << "DEBUG: size of records: " << records.size() << std::endl;

    for (int i = 0; i < records.size(); i++) {
        RequestState matchFound = fitsCondition(condition, records[i]);

        std::string studentAsString = records[i]->toString();
        // std::cout << studentAsString << std::endl;
        // std::cout << "DEBUG: this student iterated onto" << std::endl;
        // std::cout << "DEBUG: value of i is: " << i << std::endl;

        if (matchFound == RequestState::Match) {//if student fits condition, remove student
            somethingFound = true;

            //delete student pointer and remove it from array

            //uses Student helper function to generate a string representation
            //std::cout << studentAsString << std::endl;
            //std::cout << "DEBUG: this student should be deleted" << std::endl;

            delete records[i];
            records.erase(records.begin() + i);
            i--;//otherwise it will skip the next student

            //std::cout << "The following student has been removed:" << std::endl;
            //std::cout << studentAsString << std::endl << std::endl;
        }
        else if (matchFound != RequestState::NoMatch) {
            //some kind of an error state returned
            return matchFound;
        }
        //if matchFound == NoMatch, for loop goes on
    }

    
    if (! somethingFound) {
        //std::cout << "No Student matching this condition found" << std::endl;
    }
    return RequestState::AllIsWell;
}
