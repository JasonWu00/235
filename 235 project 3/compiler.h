#pragma once
#include "parser.h"
#include <fstream>
#include <iostream>
#include <string>

enum ErrorCode {
    None,
    Continue,
    Exit,
    NoVarFound,
};

enum Action {
    Print,
    Modify,
};

template <typename T> class HunVar {
    public:
        std::string returnName() const;
        HunVar(std::string name);
    protected:
        std::string name;
        T value;
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
        bool interactWithVar(std::string name, Action action, long long num = -1, std::string str = "");//helper
        void printError(ErrorCode code);
    private:
        std::vector<StrVar> StrMemory;
        std::vector<NumVar> NumMemory;
        std::string fileToBeRead;
};