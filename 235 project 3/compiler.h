#pragma once
#include "parser.h"
#include "classes.h"
#include <fstream>
#include <iostream>
#include <string>

class Compiler {
    public:
        Compiler(std::string filename);
        std::string returnFileName() const;

        ErrorCode interpretLine(std::vector<std::string> line);
        //takes in 1 line of code and does stuff with it

        ErrorCode createNewVar(std::string type, std::string name);

        //helpers
        VarData findTypeByName(std::string givenName);
        void printValueByName(VarData data);
        void updateStrByName(VarData data, std::string newVal);
        void updateNumByName(VarData data, long long newVal);
        bool isString(std::string input) const;
        bool isNum(std::string input) const;
        VarData findType(std::string token);
        std::string removeQuotes(std::string input);

        void printError(ErrorCode code);
    private:
        std::vector<StrVar> StrMemory;
        //std::vector<std::string> StrNames;
        std::vector<NumVar> NumMemory;
        //std::vector<std::string> NumNames;
        std::vector<std::vector<std::string>> names;
        std::vector<std::string> reservedKeywords;
        //[0] == str; [1] == num
        std::string fileToBeRead;
};