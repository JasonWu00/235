#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

class HunPolynomial {
    public:
        HunPolynomial();
        HunPolynomial(std::vector<int> givenValue);
        void Set(std::vector<int> setValue);

        //helpers
        std::string toString() const;
        int getSize() const;
        std::vector<int> returnValue() const;

        //operator overloads
        float operator () (float xValue) const;
        HunPolynomial operator + (const HunPolynomial& otherPoly);
        HunPolynomial operator - (const HunPolynomial& otherPoly);
        HunPolynomial operator * (const HunPolynomial& otherPoly);
        friend std::ostream& operator << (std::ostream& outputStream, const HunPolynomial& poly);

    protected:
        std::vector<int> returnPreparedValue(int otherValueSize) const;
        std::vector<int> value;
};