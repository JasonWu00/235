//#include <iostream>
#include "DiskManager.h"
//#include <fstream>
//#include <string>

//functions for DiskManager class

DiskManager::DiskManager(std::string userGivenFileName) {
    storageFileName = userGivenFileName;
    //privateParser = new Parser();
}

DiskManager::~DiskManager() {
    //covers an issue with "undefined reference to ~DiskManager()"
}

bool DiskManager::getRecords(std::vector<Student*> &records) {
    //std::cout << "Start getting records" << std::endl;
    std::ifstream readRecords(storageFileName);
    //create a read stream leading to said file

    if (readRecords.fail()){
        //file didn't open for whatever reason
        std::cout << "The file cannot be opened" << std::endl;
        return false;
    }
    //std::cout << "Success in opening file" << std::endl;

    std::string rawData;
    //holds info on one student at a time
    while (getline(readRecords, rawData)) {
        //std::cout << "Getting line" << std::endl;
        //grab each line (each representing 1 student) at a time
        std::vector<std::string> parsedData = privateParser(rawData);
        //parsedData now holds several strings describing the student

        //element 0 is id, element 1 is name, element 2 is age
        //create new student, convering 0 and 2 from string to int
        Student* student = new Student(stoi(parsedData[0]), parsedData[1], stoi(parsedData[2]));
        //put pointer in vector
        records.push_back(student);
    }
    //std::cout << "All data parsed" << std::endl;
    readRecords.close();
    return true;
}

bool DiskManager::writeRecords(std::vector<Student*> &records) {
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

/*
DiskManager::~DiskManager() {
    delete privateParser;
    privateParser = nullptr;
}*/

//functions for Student class

Student::Student(unsigned int studentId, std::string name, unsigned short age) {
    this->studentId = studentId;
    this->name = name;
    this->age = age;
}

//since the project does not call for ability to edit Students
//setters are not implemented

//getters

unsigned int Student::getID() const {
    return studentId;
}

std::string Student::getName() const {
    return name;
}

unsigned short Student::getAge() const {
    return age;
}

std::string Student::toString() const {
    std::string output = "";

    std::string id = "";//no more than 10 chars long since unsigned int limit is 10 digits long
    id += std::to_string(getID());
    int length = id.length();
    for (int i = 0; i < 10 - length; i++) {
        id += " ";
    }

    std::string name;
    for (char c : getName()) {
        if (c != '\"') {//removes quotation marks
            name += c;
        }
    }

    std::string age = std::to_string(getAge());

    output += id;
    output += " | ";
    output += name;
    output += " | ";
    output += age;
    return output;
}