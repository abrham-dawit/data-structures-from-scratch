// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa8
// Order.cpp
// Top-level client for the Red-Black Tree Dictionary ADT (unchanged from pa7)

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        exit(EXIT_FAILURE);
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Error: Could not open input file " << argv[1] << endl;
        exit(EXIT_FAILURE);
    }

    ofstream outfile(argv[2]);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open output file " << argv[2] << endl;
        exit(EXIT_FAILURE);
    }

    Dictionary dict;

    string line;
    int lineNumber = 1;

    while (getline(infile, line)) {
        dict.setValue(line, lineNumber);
        lineNumber++;
    }

    outfile << dict.to_string() << endl;

    outfile << endl;

    outfile << dict.pre_string();

    infile.close();
    outfile.close();

    return 0;
}