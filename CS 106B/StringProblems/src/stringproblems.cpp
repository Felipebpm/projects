// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

// Please feel free to add any other #includes you need!
#include "stringproblems.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

/*
 * recursively determines and returns the letters in a string. (case insensitive)
 * args: string s
 * return: string store (letters in string s)
 */
string lettersOnly(string s) {   
    string store = "";
    if (s.empty()){
        return store;
    }
    else {
        if (isalpha(s[0])){
            store += s[0];
        }
        store += lettersOnly(s.substr(1, s.length()));
    }
    return store;
}

/*
 * recursively determines if string is balanced.
 * args: string s
 * return: true if balanced, false if not
 */
bool isBalanced(string s) {
    // isn't working
    if (s.empty()) {
        return true;
    }
    else {
        if (s.find("<>") != string::npos) {
            s.erase(s.find("<>"), 2);
            return isBalanced(s);
        }
        else if (s.find("()") != string::npos) {
            s.erase(s.find("()"), 2);
            return isBalanced(s);
        }
        else if (s.find("{}") != string::npos) {
            s.erase(s.find("{}"), 2);
            return isBalanced(s);
        }
        else if (s.find("[]") != string::npos) {
            s.erase(s.find("[]"), 2);
            return isBalanced(s);
        }
        else {
            return false;
        }
    }
}

/*
 * recursively determines and prints binary form of an int. (sign insensitive)
 * args: int n
 */
void printBinary(int n) {
    if (n < 0){
        cout << "-";
        n *= -1;
    }
    if (n == 0 || n == 1){
        cout << n;
    }
    else {
        printBinary(n / 2);
        cout << n - 2 * (n / 2);
    }
}

/*
 * recursively determines and returns if string s1 contains s2.
 * args: string s1, string s2
 * return: true if s1 contains s2, false if not.
 */
bool contains(string s1, string s2) {
    if (s1.length() < s2.length()) {
        return false;
    }
    if (s2.empty()) {
        return true;
    }
    else {
        if (s1[0] == s2[0]) {
            if (s1.substr(0, s2.length()) == s2) {
                return true;
            }
            else {
                return contains(s1.substr(1, s1.length()), s2);
            }
        }
        else {
            return contains(s1.substr(1, s1.length()), s2);
        }
    }
}


