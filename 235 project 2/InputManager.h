#pragma once
#include <vector>
#include <string>
#include "Parser.h"
#include "DiskManager.h"

enum RequestState {
	AllIsWell,
	BadFormat,
	BadFormat_IdAge,
	BadFormat_Command,
	Exit
};

class InputManager {
	public:
		InputManager();
		RequestState processRequest(std::vector<std::string> input);
		//figures out what kind of a command it is, then invokes
		//one of the four functions below
		RequestState addStudent(int student_id, std::string name, int age);
		bool isNum(std::string input);
		RequestState findCondition(std::string condition);
		RequestState removeCondition(std::string condition);
		bool stop();
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

