#pragma once
#include <vector>

class parser {
	public:
		parser();
		parser(std::vector<char> separators);
		std::vector<std::string> readInput(std::string input);
		bool charInList(char c) const;

	protected:
		std::vector<char> separators;
};

class inputManager {
	public:
		inputManager();
		bool processRequest(std::vector<std::string> input);
		//figures out what kind of a command it is, then invokes
		//one of the four functions below
		bool addStudent(int id, std::string first, std::string last, int age);
		bool findCondition(std::string condition);
		bool removeCondition(std::string condition);
		bool stop();
		~inputManager();

	protected:
		std::vector<std::vector<std::string>> records;
		//a vector containing lesser vectors representing students
		diskManager* privateDiskMan;
		//the disk manager is available to the input manager
		//but not to the user
		parser* privateParser;
};

class diskManager {
	public:
		diskManager(std::string userGivenFileName);
		bool getRecords(std::vector<std::vector<std::string>> &records); 
		//reads from file and writes data into records
		bool writeRecords(std::vector<std::vector<std::string>> &records); 
		//takes records and writes daya into file
		~diskManager();

	protected:
		std::string storageFileName;
		parser* privateParser;
};