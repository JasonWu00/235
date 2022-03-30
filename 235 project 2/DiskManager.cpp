//#include <iostream>
#include "DiskManager.h"
//#include <fstream>
//#include <string>

//functions for DiskManager class

DiskManager::DiskManager(std::string userGivenFileName) {
    storageFileName = userGivenFileName;
    //privateParser = new Parser();
}

bool DiskManager::getRecords(std::vector<Student*> &records) {
    std::ifstream readRecords(storageFileName);
    //create a read stream leading to said file

    if (readRecords.fail()){
        //file didn't open for whatever reason
        std::cout << "The file cannot be opened" << std::endl;
        return false;
    }

    std::string rawData;
    //holds info on one student at a time
    while (getline(readRecords, rawData)) {
        //grab each line (each representing 1 student) at a time
        std::vector<std::string> parsedData = privateParser(rawData);
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

Student::Student(unsigned int student_id, std::string name, unsigned short age) {
    this->student_id = student_id;
    this->name = name;
    this->age = age;
}

//since the project does not call for ability to edit Students
//setters are not implemented

//getters

unsigned int Student::getID() const {
    return student_id;
}

std::string Student::getName() const {
    return name;
}

unsigned short Student::getAge() const {
    return age;
}