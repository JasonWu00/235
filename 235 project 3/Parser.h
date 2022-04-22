#pragma once
#include <vector>
#include <iostream>

class Parser {
	public:
		Parser();
		Parser(std::vector<char> separators);
		std::vector<std::string> operator()(std::string input, int state = 0) const;
		bool charInSeparator(char c) const;
		bool charInOperator(char c) const;
		//bool charInSeparator(char c, char priorityDelimiter) const;

	protected:
		std::vector<char> separators;
		std::vector<char> operators;
};