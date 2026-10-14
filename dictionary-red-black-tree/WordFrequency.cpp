//-----------------------------------------------------------------------------
// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa8
// WordFrequency.cpp
// A top-level client that counts word frequencies using a Red-Black Tree (RBT)
//-----------------------------------------------------------------------------

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>      
#include <cstdlib>     

using namespace std;

// Convert string to all lowercase
string toLowerCase(const string& word) {
    string result;
    for (char ch : word) {
        result += tolower(ch);
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    if (!inFile.is_open()) {
        cerr << "Error: Cannot open input file " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    if (!outFile.is_open()) {
        cerr << "Error: Cannot open output file " << argv[2] << endl;
        return EXIT_FAILURE;
    }

    Dictionary dict;

    string line;
    string delim = " \t\\\"',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    while (getline(inFile, line)) {
        size_t begin = line.find_first_not_of(delim);
        while (begin != string::npos) {
            size_t end = line.find_first_of(delim, begin);
            string word = line.substr(begin, end - begin);
            word = toLowerCase(word);
            if (word != "") {
                if (dict.contains(word)) {
                    dict.getValue(word) += 1;
                } else {
                    dict.setValue(word, 1);
                }
            }
            begin = line.find_first_not_of(delim, end);
        }
    }

    outFile << dict.to_string();

    inFile.close();
    outFile.close();

    return EXIT_SUCCESS;
}