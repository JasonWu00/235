#pragma once
#include <vector>
#include <string>
#include "Parser.h"
#include "DiskManager.h"

enum RequestState {
	AllIsWell,
	Match,
	NoMatch,
	BadFormat,
	BadFormatMissingArgs,
	BadFormatOverflow,
	BadFormatIdAgeName,
	BadFormatCommand,
	BadFormatCondition,
	Exit
};
//reports on if user input has errors or not

class InputManager {
	public:
		InputManager();
		RequestState processRequest(std::vector<std::string> input);
		//figures out what kind of a command it is, then invokes
		//one of the three functions below
		RequestState addStudent(long studentId, std::string name, int age);
		RequestState findCondition(std::string condition) const;
		RequestState removeCondition(std::string condition);
		//helper
		RequestState fitsCondition(std::string condition, Student* student) const;

		bool isNum(std::string input) const;
		//helper
		~InputManager();

	protected:
		std::vector<Student*> records;
		//a vector containing lesser vectors representing students
		DiskManager* privateDiskMan;
		//the disk manager is available to the input manager
		//but not to the user
		Parser privateParser;
		//declaring directly rather than using a pointer
		//otherwise it doesn't work with operator()
};

