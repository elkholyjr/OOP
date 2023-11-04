// File: BigReal.cpp
// Purpose: making basic operations but on very big numbers
// Author: ahmed elkholy , youssef nabeh , anas elessily
// Section: S1
// ID: 20220037 , 20220410 , 20220071
// TA: Nardeen mokhless
// Date: 4 Nov 2023
#include "BigReal.h"
#include <bits/stdc++.h>
using namespace std;
bool BigReal::isValidReal(string realNumber) {
    int pointCount = 0,non=0;
    if (realNumber[0]=='0'){
        non=1;
    }else if (realNumber[0]=='-'&&realNumber[1]=='0'){
        return false;
    }
    if(realNumber[0]=='+'&&realNumber[1]=='-'||realNumber[1]=='+'&&realNumber[0]=='-'){
        return false;
    }
    for (char c : realNumber) {
        if (c == '.') {
            pointCount++;
            if (pointCount > 1) return false; // More than one decimal point is not valid
        } else if (!isdigit(c)&&c!='+'&&c!='-') { // has zero before num and dec point 0009.1 invalid
            if(pointCount==0 && non==1){
                return false;
            }
        }
    }
    return true; // If no invalid conditions are met, the number is valid
}

BigReal::BigReal(double realNumber) {
    realNumber=0.0;
}

BigReal::BigReal(string realNumber) {
    if (!isValidReal(realNumber)) {
        throw invalid_argument("Invalid number");
    }

    // Assuming you have a setNum function to set the number
    setNum(realNumber);
}

void BigReal::setNum(string realNumber) {
    this ->realNumber=realNumber;
}

int BigReal::size() {
    return this->realNumber.size();
}

int BigReal::Sign() {
    return (this->realNumber[0] == '-') ? -1 : 1;
}

//plus operator

//minus operator

bool BigReal::operator< (const BigReal& other) {
        // If the signs are different
        if (this->realNumber[0] != other.realNumber[0]&&this->realNumber[0]=='-'||other.realNumber[0]=='-') {
            // If this number is positive and the other is negative, then this number is less
            if (this->realNumber[0] == '-') {
                return true;
            }
                // If this number is negative and the other is positive, then this number is not less
            else {
                return false;
            }
        }
            // If the signs are the same
        else {
            // Compare the absolute values of the numbers
            string absThis = (this->sign == -1) ? this->realNumber.substr(1) : this->realNumber;
            string absOther = (other.sign == -1) ? other.realNumber.substr(1) : other.realNumber;
            // Find the decimal points
            int decimal1 = absThis.find('.');
            int decimal2 = absOther.find('.');

            // If there are no decimal points, add them at the end
            if (decimal1 == string::npos) {
                decimal1 = absThis.size();
                absThis += '.';
            }
            if (decimal2 == string::npos) {
                decimal2 = absOther.size();
                absOther += '.';
            }

            strip(absThis);
            strip(absOther);

            if (decimal1 != decimal2) {
                return decimal1 < decimal2;
            } else {
                return absThis < absOther;
            }
        }
}

bool BigReal::operator> (const BigReal& other) {
    // If the signs are different
    if (this->realNumber[0] != other.realNumber[0]&&this->realNumber[0]=='-'||other.realNumber[0]=='-') {
        // If this number is positive and the other is negative, then this number is greater
        if (this->realNumber[0] != '-') {
            return true;
        }
        // If this number is negative and the other is positive, then this number is not greater
        else {
            return false;
        }
    }
        // If the signs are the same
    else {
        // Compare the absolute values of the numbers
        string absThis = (this->sign == -1) ? this->realNumber.substr(1) : this->realNumber;
        string absOther = (other.sign == -1) ? other.realNumber.substr(1) : other.realNumber;

        // Find the decimal points
        int decimal1 = absThis.find('.');
        int decimal2 = absOther.find('.');

        // If there are no decimal points, add them at the end
        if (decimal1 == string::npos) {
            decimal1 = absThis.size();
            absThis += '.';
        }
        if (decimal2 == string::npos) {
            decimal2 = absOther.size();
            absOther += '.';
        }

        strip(absThis);
        strip(absOther);

        if (decimal1 != decimal2) {
            return decimal1 > decimal2;
        } else {
            return absThis > absOther;
        }
    }
}

bool BigReal::operator== (const BigReal& other) {
        // If the signs are different
        if (this->realNumber[0] != other.realNumber[0]&&this->realNumber[0]=='-'||other.realNumber[0]=='-') {
                return false;
        }
        else {
            // Compare the absolute values of the numbers
            string absThis = (this->sign == -1) ? this->realNumber.substr(1) : this->realNumber;
            if(absThis.find('.')!=-1){
                strip(absThis);
                if(absThis.back()=='.'){
                    absThis.pop_back();
                }
            }
            string absOther = (other.sign == -1) ? other.realNumber.substr(1) : other.realNumber;
            if(absOther.find('.')!=-1){
                strip(absOther);
                if(absOther.back()=='.'){
                    absOther.pop_back();
                }
            }
                return absThis == absOther;
        }
}

BigReal& BigReal::operator= (const BigReal& other) {
    // Check for self-assignment
    if (this != &other) {
        // Assign the value of the other number to this number
        this->realNumber = other.realNumber;
    }
    return *this;
}

istream &operator>>(istream &in,BigReal &num) {
    string text ; in >> text ;
    num = BigReal(text) ;
    return in ;
}

ostream& operator << (ostream& out, const BigReal& num) {
    out << num.realNumber ;
    return out;
}

void BigReal::strip(string &text) {
    int k = 0 ;
    while ( text[k] == '0' ) k++ ;
    if ( k ) text = text.substr( k ) ;
    if ( text.front() == '.' ) text = '0' + text ;
    while (text.back() == '0' ) text.pop_back() ;
}
