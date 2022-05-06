#include "HunPolynomial.h"

HunPolynomial::HunPolynomial() {

}

HunPolynomial::HunPolynomial(std::vector<int> givenValue) {
    value = givenValue;    
}

void HunPolynomial::Set(std::vector<int> setValue) {
    value = setValue;
}

std::string HunPolynomial::toString() {
    std::string output = "";
    for (int i = 0; i < value.size(); i++) {
        int coefficient = value[i];
        if (i != 0) {
            if (coefficient < 0) {
                output += "- ";
            }
            else if (coefficient > 0) {
                output += "+ ";
            }
        }
        output += std::to_string(std::abs(coefficient));
        if (i != value.size() - 1) {
            output += "*x^";
            output += std::to_string(value.size() - i-1);
        }
        output += " ";
    }
    return output;
}