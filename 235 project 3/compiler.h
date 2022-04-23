#pragma once
#include "parser.h"
#include <fstream>
#include <iostream>
#include <string>

enum ErrorCode {
    None,
    Continue,
    Exit,
};

class Var {
    public:
        std::string returnName() const;
        Var(std::string name);
    protected:
        std::string name;
};

class NumVar: public Var {
    public:
        long long returnValue() const;
        void updateValue(long long input);
        NumVar(std::string name);
    private:
        long long value;
};

class StrVar: public Var {
    public:
        std::string returnValue() const;
        void updateValue(std::string input);
        StrVar(std::string name);
    private:
        std::string value;
};

class Compiler {
    public:
        Compiler(std::string filename);
        std::string returnFileName() const;
        bool isNum(std::string input) const;

        ErrorCode interpretLine(std::vector<std::string> line);
        //takes in 1 line of code and does stuff with it
        ErrorCode createNewVar(std::string type, std::string name);
        void printError(ErrorCode code);
    private:
        std::vector<Var> memory;
        std::string fileToBeRead;
};