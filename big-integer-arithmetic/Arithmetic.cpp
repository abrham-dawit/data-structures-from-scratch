// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa6
// Arithmetic.cpp
// Top-level client for the BigInteger ADT

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BigInteger.h"

using namespace std;

// Helper function: computes base^exp for BigIntegers (exp >= 0)
BigInteger power(const BigInteger& base, int exp) {
    BigInteger result("1"); // Identity
    for (int i = 0; i < exp; i++) {
        result = result * base;
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }
    
    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: Could not open input file " << argv[1] << endl;
        return 1;
    }
    
    ofstream fout(argv[2]);
    if (!fout) {
        cerr << "Error: Could not open output file " << argv[2] << endl;
        return 1;
    }
    
    string line;

    getline(fin, line);
    BigInteger A(line);
    
    getline(fin, line);
    
    getline(fin, line);
    BigInteger B(line);
    
    fout << A << "\n\n";
    fout << B << "\n\n";
    fout << (A + B) << "\n\n";
    fout << (A - B) << "\n\n";
    fout << (A - A) << "\n\n";
    fout << ((BigInteger("3") * A) - (BigInteger("2") * B)) << "\n\n";
    fout << (A * B) << "\n\n";
    fout << power(A, 2) << "\n\n";
    fout << power(B, 2) << "\n\n";
    BigInteger term1 = BigInteger("9") * power(A, 4);
    BigInteger term2 = BigInteger("16") * power(B, 5);
    fout << (term1 + term2) << "\n\n";
    
    fin.close();
    fout.close();
    return 0;
}