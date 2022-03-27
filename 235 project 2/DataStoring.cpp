#include <iostream>
#include "DataStoring.h"
#include <fstream>
#include <string>

//functions for parser class

parser::parser() {
    separators.push_back('\"');
    separators.push_back(' ');
    separators.push_back('\t');
}

parser::parser(std::vector<char> separators) {
    this->separators = separators;
}

//helper function to look for a char in the seperators vector
bool parser::charInList(char c) const {
    for (char separator : separators) {
        //checks from first element of separator to last
        //thus quotation marks have precedence over spaces and tabs
        if (c == separator) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> parser::readInput(std::string input) {
    std::vector<std::string> output;
    std::string parsedString = "";

    for (char c : input) {
        //parse chars not in the separators list into a temp string
        //push string to output when separator detected
        if (charInList(c)) {
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
    privateParser = new parser();
}

bool diskManager::getRecords(std::vector<std::vector<std::string>> &records) {
    std::ifstream readRecords(storageFileName);

    if (readRecords.fail()){
        //file didn't open for whatever reason
        std::cout << "The file cannot be opened" << std::endl;
        return false;
    }

    //create a read stream leading to said file
    std::string student;
    //holds info on one student at a time
    while (getline(readRecords, student)) {
        //grab each line (each representing 1 student) at a time
        std::vector<std::string> parsed_student = privateParser->readInput(student);
        //parsed_student now holds several strings describing the student
        records.push_back(parsed_student);
        //now put the student in the record vector
    }
    return true;
}

bool diskManager::writeRecords(std::vector<std::vector<std::string>> &records) {
    std::ofstream writeRecords(storageFileName);
    //create a write stream leading to said file

    if (writeRecords.fail()){
        //file didn't open for whatever reason
        std::cout << "The file cannot be opened" << std::endl;
        return false;
    }

    for (std::vector<std::string> student : records) {
        //write each student into the file
        for (std::string dataPoint : student) {
            writeRecords << dataPoint << ' ';
            //each data point of a student is space separated
        }
        writeRecords << "\n";
        //each student goes on a new line
    }
    return true;
}

//functions for inputManager class

inputManager::inputManager() {
    privateDiskMan = new diskManager("student_data.txt");
    privateParser = new parser();
}