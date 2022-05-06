#pragma once
#include <vector>
#include <string>
#include <iostream>

class HunPolynomial {
    public:
        HunPolynomial();
        HunPolynomial(std::vector<int> givenValue);
        void Set(std::vector<int> setValue);
        std::string toString();//helper function

        //operator overloads
        float operator () (float xValue);
        HunPolynomial& operator + (const HunPolynomial& otherPoly);
        HunPolynomial& operator - (const HunPolynomial& otherPoly);
        HunPolynomial& operator * (const HunPolynomial& otherPoly);
        friend std::ostream& operator << (std::ostream& outputStream, const HunPolynomial& poly);

    protected:
        std::vector<int> value;
};