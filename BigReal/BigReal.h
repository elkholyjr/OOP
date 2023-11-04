#ifndef BIGREAL_H
#define BIGREAL_H
// File: BigReal.cpp
// Purpose: making basic operations but on very big numbers
// Author: Ahmed Elkholy , youssef nabeh , anas elessily
// Section: S1
// ID: 20220037 , 20220410 , 20220071
// TA: Nardeen mokhless
// Date: 4 Nov 2023
#include <bits/stdc++.h>
using namespace std;

class BigReal {
private:
    string realNumber;
    int sign;
    bool isValidReal(string realNumber);
    void strip(string &text);

public:
    BigReal(double realNumber = 0.0);

    BigReal(string realNumber);

    void setNum(string realNumber);

    int size();

    int Sign();

    BigReal operator+ (const BigReal& other);

    string addIntegers(string num1, string num2);

    string addStrings(string num1, string num2);

    BigReal operator- (const BigReal& other);

    string MinusStrings(string num1, string num2);
    
    string subtractIntegers(string num1, string num2);
    
    bool operator< (const BigReal& other);

    bool operator> (const BigReal& other);

    bool operator== (const BigReal& other);

    BigReal& operator= (const BigReal& other);

friend ostream& operator << (std::ostream& out, const BigReal& num);
friend istream &operator>>(istream &in,BigReal &num);
};
#endif
