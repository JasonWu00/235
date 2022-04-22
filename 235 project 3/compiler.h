#pragma once
#include "parser.h"

class Var {
    public:
        std::string name;
        std::string returnName();
};

class NumVar : public Var {
    public:
        long long returnValue();
        void updateValue(long long input);
    private:
        long long value;
};

class StrVar : public Var {
    public:
        std::string returnValue();
        void updateValue(std::string input);
    private:
        std::string value;
};

class Compiler {
    public:
        std::vector<Var> memory;
        Compiler(std::string filename);
        std::string returnFileName();
    private:
        std::string fileToBeRead;
        Parser privateParser;
};