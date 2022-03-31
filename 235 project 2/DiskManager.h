#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Parser.h"

class Student {
	public: 
		Student(unsigned int id, std::string name, unsigned short age);
		unsigned int getID() const;
		std::string getName() const;
		unsigned short getAge() const;
		std::string toString() const;

	protected:
		unsigned int studentId;
		std::string name;
		unsigned short age;

};

class DiskManager {
	public:
		DiskManager(std::string userGivenFileName);
		bool getRecords(std::vector<Student*> &records); 
		//reads from file and writes data into records
		bool writeRecords(std::vector<Student*> &records); 
		//takes records and writes daya into file
		~DiskManager();

	protected:
		std::string storageFileName;
		Parser privateParser;
};
