#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <regex>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::string;
using std::map;
using std::set;
using std::transform;
using std::regex;
using std::regex_replace;
using std::sregex_iterator;
using std::any_of;
using std::regex_search;
using std::tolower;
using std::regex_iterator;

// remove punctuation from start and end of word
string trimPunctuation(const string& word) {
    size_t start = 0, end = word.length();
    while (start < end && ispunct(word[start])) ++start;
    while (end > start && ispunct(word[end - 1])) --end;
    return word.substr(start, end - start);
}

// check for unwanted characters
bool containsUnwantedCharacters(const string& word) {
    string unwanted = "\\/|:*+=@!?#$%^&~`<>\";,[]{}";
    for (char c : word) {
        if (unwanted.find(c) != string::npos)
            return true;
    }
    return false;
}

string toLower(const string& word) {
    string result = word;

    transform(result.begin(), result.end(), result.begin(),
          [](unsigned char c){ return tolower(c); });
    return result;
}

// check for URLs
bool isURL(const string& word) {
    string w = toLower(trimPunctuation(word));

    if (w.find("http://") == 0 || w.find("https://") == 0 || w.find("www.") == 0) {
        return w.find('.') != string::npos && w.length() > 7;
    }

    // 
    size_t dotPos = w.find('.');
    if (dotPos != string::npos && dotPos > 0 && dotPos < w.length() - 1) {
        string ext = w.substr(dotPos + 1);
        if (ext.length() >= 2 && ext.length() <= 6 && all_of(ext.begin(), ext.end(), ::isalpha)) {
            return true;
        }
    }

    return false;
}

#endif