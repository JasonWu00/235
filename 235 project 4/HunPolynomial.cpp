#include "HunPolynomial.h"

HunPolynomial::HunPolynomial() {

}

HunPolynomial::HunPolynomial(std::vector<int> givenValue) {
    value = givenValue;    
}

void HunPolynomial::Set(std::vector<int> setValue) {
    value = setValue;
}

std::string HunPolynomial::toString() const {
    std::string output = "";
    if (value.empty()) {
        return "0";
    }
    int monomialCount = 0;

    for (int i = 0; i < value.size(); i++) {
        int coefficient = value[i];
        int power = value.size() - i - 1;

        if (coefficient == 0) {//no monomial here, skip it
            continue;
        }
        else {
            monomialCount++;
        }

        //adds + or - before monomial
        if (coefficient < 0) {
            output += "- ";
        }
        else if (coefficient > 0 && monomialCount >= 2) {
            output += "+ ";
        }
        

        if (coefficient != 1 && coefficient != -1) {//adds the coefficient value itself
            output += std::to_string(std::abs(coefficient));
        }
        else if (power == 0) {
            output += std::to_string(std::abs(coefficient));
        }

        if (power >= 1) {//adds the *x^ thing for all power >= 2
            if (coefficient < -1 || coefficient > 1) {//for 1 or -1, omit coefficient and *
                output += "*";
            }
            output += "x";
            if (power != 1) {
                output += "*";
                output += std::to_string(power);
            }
        }

        else if (power == 1) {
            output += "x";
        }

        output += " ";
    }
    return output;
}

float HunPolynomial::operator () (float xValue) const {
    float yValue = 0.0;
    for (int i = 0; i < value.size(); i++) {
        int coefficient = value[i];
        yValue += coefficient * std::pow(xValue, value.size() - i - 1);
        //std::cout << yValue << std::endl;
    }
    return yValue;
}

int HunPolynomial::getSize() const {
    return value.size();
}

std::vector<int> HunPolynomial::returnValue() const {
    return value;
}

std::vector<int> HunPolynomial::returnPreparedValue(int otherValueSize) {
    std::vector<int> outputVec;
    int size = std::max(getSize(), otherValueSize);

    outputVec = value;

    if (size == otherValueSize) {//other value is bigger
        int difference = otherValueSize - getSize();
        for (int i = 0; i < difference; i++) {//accounting for leading zero monomials
            outputVec.insert(outputVec.begin(), 0);
        }
    }
    /*
    std::cout << "returnPreparedValue test: " << std::endl;
    for (int i = 0; i < outputVec.size(); i++) {
        std::cout << outputVec[i] << " ";
    }
    std::cout << std::endl;
    */
    return outputVec;
}

std::ostream& operator << (std::ostream& outputStream, const HunPolynomial& poly) {
    outputStream << poly.toString();
    return outputStream;
}

HunPolynomial HunPolynomial::operator + (const HunPolynomial& otherPoly) {
    std::vector<int> outputVec = returnPreparedValue(otherPoly.getSize());
    //initiates outputVec with appropriate leading zeros via helper

    //now go backwards from the end of the array to add in value of other poly
    std::vector<int> otherValue = otherPoly.returnValue();

    for (int i = otherValue.size() - 1; i >= 0; i--) {
        int difference = otherValue.size() - i;
        int outputSize = outputVec.size();
        //std::cout << "Adding " << otherValue[i] << " to " << outputVec[outputSize - difference] << std::endl;
        outputVec[outputSize - difference] += otherValue[i];//adds value 
    }

    HunPolynomial output;
    output.Set(outputVec);
    return output;
}

HunPolynomial HunPolynomial::operator - (const HunPolynomial& otherPoly) {
    std::vector<int> outputVec = returnPreparedValue(otherPoly.getSize());
    //initiates outputVec with appropriate leading zeros via helper

    //now go backwards from the end of the array to add in value of other poly
    std::vector<int> otherValue = otherPoly.returnValue();

    for (int i = otherValue.size() - 1; i >= 0; i--) {
        int difference = otherValue.size() - i;
        int outputSize = outputVec.size();
        //std::cout << "Adding " << otherValue[i] << " to " << outputVec[outputSize - difference] << std::endl;
        outputVec[outputSize - difference] -= otherValue[i];//adds value 
    }

    HunPolynomial output;
    output.Set(outputVec);
    return output;
}

HunPolynomial HunPolynomial::operator * (const HunPolynomial& otherPoly) {
    std::vector<int> outputVec;
    std::vector<int> otherValue = otherPoly.returnValue();

    //total size of outputVec should be = to otherValue.size() + value.size()
    int highestPower = otherValue.size() + value.size() - 1;
    for (int i = 0; i < highestPower; i++) {
        outputVec.insert(outputVec.begin(), 0);
    }

    //now that we are done preparing outputVec, we can start multiplying
    //iterate through each element of value
    //for each element, multiply it with every element on otherValue
    //calculate the power and coefficient of each multiplied value
    //add each to the appropriate vector element

    for (int i = 0; i < value.size(); i++) {
        //for each element of value
        for (int j = 0; j < otherValue.size(); j++) {
            int sum = value[i] * otherValue[j];
            int totalPower = i + j;
            outputVec[totalPower] += sum;
        }
    }

    HunPolynomial output;
    output.Set(outputVec);
    return output;
}