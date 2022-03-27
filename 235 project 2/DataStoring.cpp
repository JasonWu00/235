#include <iostream>
#include "DataStoring.h"
#include <fstream>
#include <string>

//functions for Parser class

Parser::Parser() {
    separators.push_back('\"');
    separators.push_back(' ');
    separators.push_back('\t');
}

Parser::Parser(std::vector<char> separators) {
    this->separators = separators;
}

//helper functions to look for a char in the seperators vector
bool Parser::charInList(char c) const {
    for (char separator : separators) {
        //checks from first element of separator to last
        //thus quotation marks have precedence over spaces and tabs
        if (c == separator) {
            return true;
        }
    }
    return false;
}

bool Parser::charInList(char c, char priorityDelimiter) const {
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
}

std::vector<std::string> Parser::readInput(std::string input, char priorityDelimiter) {
    std::vector<std::string> output;
    std::string parsedString = "";

    for (char c : input) {
        //parse chars not in the separators list into a temp string
        //push string to output when separator detected
        if (charInList(c, priorityDelimiter)) {
            //seperator char found
            output.push_back(parsedString);
            parsedString = "";
            //reset string to clear out old data
        }
        else {
            //not seperator, add to parsedString
            parsedString += c;
        }
    }
    output.push_back(parsedString);
    //push last bit of data into output

    //the output should not be longer than 3 or 4 strings long
    //so we will pass by value
    return output;
}

//functions for diskManager class

diskManager::diskManager(std::string userGivenFileName) {
    storageFileName = userGivenFileName;
    privateParser = new Parser();
}

bool diskManager::getRecords(std::vector<Student*> &records) {
    std::ifstream readRecords(storageFileName);

    if (readRecords.fail()){
        //file didn't open for whatever reason
        std::cout << "The file cannot be opened" << std::endl;
        return false;
    }

    //create a read stream leading to said file
    std::string rawData;
    //holds info on one student at a time
    while (getline(readRecords, rawData)) {
        //grab each line (each representing 1 student) at a time
        std::vector<std::string> parsedData = privateParser->readInput(rawData, ' ');
        //parsedData now holds several strings describing the student

        //element 0 is id, element 1 is name, element 2 is age
        //create new student, convering 0 and 2 from string to int
        Student* student = new Student(stoi(parsedData[0]), parsedData[1], stoi(parsedData[2]));
        //put pointer in vector
        records.push_back(student);
    }
    readRecords.close();
    return true;
}

bool diskManager::writeRecords(std::vector<Student*> &records) {
    std::ofstream writeRecords(storageFileName);
    //create a write stream leading to said file

    if (writeRecords.fail()){
        //file didn't open for whatever reason
        std::cout << "The file cannot be opened" << std::endl;
        return false;
    }

    for (Student* student : records) {
        //write each student into the file
        
        writeRecords << student->getID() 
                     << ' ' 
                     << student->getName()
                     << ' ' 
                     << student->getAge()
                     << "\n";
        //each student goes on a new line
    }
    writeRecords.close();
    return true;
}

diskManager::~diskManager() {
    delete privateParser;
    privateParser = nullptr;
}

//functions for Student class

Student::Student(int id, std::string name, int age) {
    this->id = id;
    this->name = name;
    this->age = age;
}

//since the project does not call for ability to edit Students
//setters are not implemented

//getters

int Student::getID() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

//functions for inputManager class

inputManager::inputManager() {
    privateDiskMan = new diskManager("student_data.txt");
    privateParser = new Parser();
}

inputManager::~inputManager() {
    delete privateDiskMan, privateParser;
    privateDiskMan, privateParser = nullptr;
    for (Student* student : records) {
        delete student;
        student = nullptr;
    }
}