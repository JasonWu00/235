#include "compiler.h"

std::string Var::returnName() {
    return name;
}

std::string StrVar::returnValue() {
    return value;
}

long long NumVar::returnValue() {
    return value;
}

void NumVar::updateValue(long long input) {
    value = input;
}

void StrVar::updateValue(std::string input) {
    value = input;
}

Compiler::Compiler(std::string filename) {
    fileToBeRead = filename;
}

std::string Compiler::returnFileName() {
    return fileToBeRead;
}