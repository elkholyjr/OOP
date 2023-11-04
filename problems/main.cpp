#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class StringSplitter {   // problem 3
public:
   vector<string> split(const string& target, const string& delimiter) {
   vector<string> result;
   istringstream iss(target);
   string token;
        while (getline(iss, token, delimiter[0])) {
            result.push_back(token);
        }
        return result;
    }
    void print(const vector<string>& vec) {
        for (const auto& str : vec) {
            cout << str << std::endl;
        }
    }
};

class Binary_problem {   // problem 6
private:
    string s;
public:
     void binaryPrint(int n) {
        if (n == 0) {
            cout<<0;
            s.push_back('0');
        }
        if (n > 0) {
            binaryPrint(n / 2);
            cout<<n%2;
            s.push_back(n%2+'0');
        }
    }
     void numbers(string prefix, int k) {
        if (k == 0) {
            cout << s <<prefix << endl;
        } else {
            numbers(prefix + "0", k - 1);
            numbers(prefix + "1", k - 1);
        }
    }
};


class TeddyBearGame {  //problem 9
public:
    static bool bears(int n) {
        if (n == 42) {
            return true;
        }
        if (n < 42) {
            return false;
        }
        if (n % 2 == 0 && bears(n / 2)) {
            return true;
        }
        if ((n % 3 == 0 || n % 4 == 0) && bears(n - (n % 10) * (n / 10 % 10))) {
            return true;
        }
        if (n % 5 == 0 && bears(n - 42)) {
            return true;
        }
        return false;
    }
};

class Phishing_scanner {    //problem 12
private:
    map<string, int> words;
    map<string, int> counts;
    int totalPoints=0;
public:
    Phishing_scanner() {
        words["You won a prize!"] = 3;
        words["ebay"] = 3;
        words["facebook"] = 3;
        words["aliexpress"] = 3;
        words["instagram"] = 3;
        words["urgent"] = 3;
        words["Verify your account"] = 3;
        words["Verify your account"] = 3;
        words["Your account has been hacked"] = 3;
        words["password check required immediately"] = 3;
        words["Confirm your identity"] = 3;
        words["Reset your password immediately"] = 3;
        words["Google"] = 3;
        words["LinkedIn"] = 3;
        words["Suspicious activity"];
        words["Dear customer"] = 3;
        words["Your payment was declined"] = 3, words["Update your information"] = 3;
        words["Login attempt from a foreign IP address"] = 3;
        words["Click this link to activate"] = 3;
        words["We have noticed unusual activity"] = 3;
        words["You’re eligible for a refund"] = 3;
        words["Failure to update your records will result in account suspension"] = 3;
        words["Your order has been cancelled"] = 3;
        words["Please view the document I uploaded for you using Google Docs"] = 3;
        words["Your mailbox is full"] = 3;
        words["Reset your password immediately"] = 3;
        words["Check your statement"] = 3;
        words["Security alert for your linked Google account"] = 3;
    }
    void scan(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Unable to open file " << filename;
            exit(1);
        }

        string word;
        while (file >> word) {
            if (words.find(word) != words.end()) {
                counts[word]++;
                totalPoints += words[word];
            }
        }
    }

    void printResults() const {
        for (const auto &pair : counts) {
            std::cout << pair.first << ": " << pair.second << " occurrences, "
                      << pair.second * words.at(pair.first) << " points\n";
        }
        std::cout << "Total points: " << totalPoints << "\n";
    }
};


int main() {


//    StringSplitter splitter;         problem 3
//    vector<string> result = splitter.split("do re mi fa so la ti do", " ");
//    splitter.print(result);


//int n;                               problem 6
//cout<<"Enter the Num\n";
//cin>>n;
//Binary_problem b;
//b.binaryPrint(n);
// cout<<"\n";
//string prefix ;
//int k;
//cout<<"Enter the digits\n";
//cin>>k;
//b.numbers(prefix, k);


//    cout << "bear(250) is " << (TeddyBearGame::bears(250) ? "true" : "false") << endl;   problem 9
//    cout << "bear(42) is " << (TeddyBearGame::bears(42) ? "true" : "false") << endl;
//    cout << "bear(84) is " << (TeddyBearGame::bears(84) ? "true" : "false") << endl;
//    cout << "bear(53) is " << (TeddyBearGame::bears(53) ? "true" : "false") << endl;
//    cout << "bear(41) is " << (TeddyBearGame::bears(41) ? "true" : "false") << endl;

//    Phishing_scanner scanner;           problem 12
//    scanner.scan("test.txt");
//    scanner.printResults();

    return 0;
}
