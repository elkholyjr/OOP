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

BigReal BigReal::operator- (const BigReal& other) {
    string subtract = MinusStrings(this->realNumber, other.realNumber);
    if (!isValidReal(subtract)) {
        throw invalid_argument("Sum is not a valid real number");
    }
    return BigReal(subtract);
}

string BigReal::subtractIntegers(string num1, string num2) {
    // Check if num1 is smaller than num2
    if (num1.size() < num2.size()) {
        swap(num1, num2);
    }

    // Reverse the strings to make subtraction easier
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    string result = "";
    int carry = 0;

    // Loop through each digit, starting from the least significant
    for (int i = 0; i < num1.size(); i++) {
        int sub = ((num1[i]-'0') - (i < num2.size() ? (num2[i]-'0') : 0) - carry);

        // If the subtraction is less than 0, we add 10 to handle borrowing
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result.push_back(sub + '0');
    }

    // Reverse the result to get the final answer
    reverse(result.begin(), result.end());

    // Remove leading zeros
    result.erase(0, min(result.find_first_not_of('0'), result.size()-1));

    return result;
}

string BigReal::MinusStrings(string num1, string num2) {
        // Check if the numbers are negative
        bool negative1 = num1[0] == '-';
        bool negative2 = num2[0] == '-';

        // Remove the negative signs for subtraction
        if (negative1) num1 = num1.substr(1);
        if (negative2) num2 = num2.substr(1);

        // Find the decimal points
        int decimal1 = num1.find('.');
        int decimal2 = num2.find('.');

        // If there are no decimal points, add them at the end
        if (decimal1 == string::npos) {
            decimal1 = num1.size();
            num1 += '.';
        }
        if (decimal2 == string::npos) {
            decimal2 = num2.size();
            num2 += '.';
        }

        // Add trailing zeros to make the fractional parts the same size
        int fractionalSize = max(num1.size() - decimal1 - 1, num2.size() - decimal2 - 1);
        num1 += string(fractionalSize - (num1.size() - decimal1 - 1), '0');
        num2 += string(fractionalSize - (num2.size() - decimal2 - 1), '0');

        // Remove the decimal points for subtraction
        num1.erase(decimal1, 1);
        num2.erase(decimal2, 1);

        // Subtract the numbers as before
        string difference;

        if ((negative1 && negative2) || (!negative1 && !negative2)) {
            difference = subtractIntegers(num1, num2);
            if (negative1 && negative2) {
                difference = '-' + difference;
            }
        } else {
            difference = addIntegers(num1, num2);
            if (negative1) {
                difference = '-' + difference;
            }
        }

        // Add the decimal point back in
        difference.insert(difference.end() - fractionalSize, '.');
        if(difference.back()=='.'){
            difference.pop_back();
        }
        return difference;
}

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
