#include "classes.h"

//contains code for lesser classes and enums.

std::string Var::returnName() const {
    return name;
}

std::string StrVar::returnValue() const {
    return value;
}

Var::Var(std::string name) {
    this->name = name;
}

//child constructors call parent constructor

NumVar::NumVar(std::string name) : Var(name) {
    value = 0;//intialized to default value
}

StrVar::StrVar(std::string name) : Var(name) {
    value = "Default StrVar value";
}

long long NumVar::returnValue() const {
    return value;
}

void NumVar::updateValue(long long input) {
    value = input;
}

void StrVar::updateValue(std::string input) {
    value = input;
}

VarData::VarData(int location, VarType type) {
    placeInMemory = location;
    this->type = type;
}