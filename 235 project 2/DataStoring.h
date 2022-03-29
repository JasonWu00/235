#pragma once
#include <vector>

class Parser {
	public:
		Parser();
		Parser(std::vector<char> separators);
		std::vector<std::string> readInput(std::string input);
		bool charInSeparator(char c) const;
		bool charInOperator(char c) const;
		//bool charInSeparator(char c, char priorityDelimiter) const;

	protected:
		std::vector<char> separators;
		std::vector<char> operators;
};

class inputManager {
	public:
		inputManager();
		bool processRequest(std::vector<std::string> input);
		//figures out what kind of a command it is, then invokes
		//one of the four functions below
		bool addStudent(int student_id, std::string name, int age);
		bool findCondition(std::vector<std::string> condition);
		bool removeCondition(std::vector<std::string> condition);
		bool stop();
		~inputManager();

	protected:
		std::vector<Student*> records;
		//a vector containing lesser vectors representing students
		diskManager* privateDiskMan;
		//the disk manager is available to the input manager
		//but not to the user
		Parser* privateParser;
};

class diskManager {
	public:
		diskManager(std::string userGivenFileName);
		bool getRecords(std::vector<Student*> &records); 
		//reads from file and writes data into records
		bool writeRecords(std::vector<Student*> &records); 
		//takes records and writes daya into file
		~diskManager();

	protected:
		std::string storageFileName;
		Parser* privateParser;
};

class Student {
	public: 
		Student(unsigned int id, std::string name, unsigned short age);
		unsigned int getID() const;
		std::string getName() const;
		unsigned short getAge() const;

	protected:
		unsigned int student_id;
		std::string name;
		unsigned short age;

};