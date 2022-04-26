#pragma once
#include <string>

enum ErrorCode {
    None,
    Continue,
    Exit,
    NoVarFound,
    NotRecognizedName,
    NotLiteralOrName,
    NotRecognizedType,
    NotNumber,
    NotString,
    NameReserved,
    TooManyTokens,
};

enum VarType {
    Number,
    String,
    Nothing,
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

class VarData {
    public:
        int placeInMemory;
        VarType type;
        VarData(int location, VarType type);
};