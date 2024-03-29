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

        static const int strNameIndex = 0;
        static const int numNameIndex = 1;

        ErrorCode interpretLine(std::vector<std::string> line);
        //takes in 1 line of code and does stuff with it

        //helpers
        ErrorCode createNewVar(std::string type, std::string name);
        VarData findDataByName(std::string givenName) const;
        void printValueByName(VarData data) const;

        long long returnNumByName(VarData data) const;
        std::string returnStrByName(VarData data) const;

        void updateStrByName(VarData data, std::string newVal);
        void updateNumByName(VarData data, long long newVal);

        bool isString(std::string input) const;
        bool isNum(std::string input) const;

        VarData findType(std::string token) const;
        std::string removeQuotes(std::string input) const;
        std::string replaceNewlines(std::string input) const;

        long long pemdas(std::vector<std::string> expression) const;
        ErrorCode validateExp(std::vector<std::string> expression) const;

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