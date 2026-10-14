// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa6
// BigIntegerTest.cpp
// Test suite for the BigInteger ADT

#include <iostream>
#include <stdexcept>
#include <string>
#include "BigInteger.h"

using namespace std;

// Test the sign() function
void testSign() {
    BigInteger A("0");
    BigInteger B("12345");
    BigInteger C("-98765");
    
    if (A.sign() != 0)
        throw runtime_error("testSign: Zero test failed");
    if (B.sign() != 1)
        throw runtime_error("testSign: Positive test failed");
    if (C.sign() != -1)
        throw runtime_error("testSign: Negative test failed");
}

// Test the negate() function
void testNegate() {
    BigInteger A("12345");
    A.negate();
    if (A.sign() != -1)
        throw runtime_error("testNegate: Negation failed");
    
    // Negating zero should do nothing
    BigInteger B("0");
    B.negate();
    if (B.sign() != 0)
        throw runtime_error("testNegate: Negation on zero failed");
}

// Test the makeZero() function
void testMakeZero() {
    BigInteger A("12345");
    A.makeZero();
    if (A.sign() != 0 || A.to_string() != "0")
        throw runtime_error("testMakeZero: makeZero failed");
}

// Test addition
void testAddition() {
    BigInteger A("12345");
    BigInteger B("67890");
    BigInteger C = A.add(B);
    if (C.to_string() != "80235")
        throw runtime_error("testAddition: 12345 + 67890 failed");
    
    // Test addition with different signs
    BigInteger D("10000");
    BigInteger E("-10000");
    BigInteger F = D.add(E);
    if (F.to_string() != "0")
        throw runtime_error("testAddition: addition with canceling signs failed");
}

// Test subtraction
void testSubtraction() {
    BigInteger A("67890");
    BigInteger B("12345");
    BigInteger C = A.sub(B);
    if (C.to_string() != "55545")
        throw runtime_error("testSubtraction: 67890 - 12345 failed");
    
    // Test subtracting a larger number
    BigInteger D = B.sub(A);
    if (D.to_string()[0] != '-') // expects a negative result
        throw runtime_error("testSubtraction: subtraction negative result failed");
}

// Test multiplication
void testMultiplication() {
    BigInteger A("123");
    BigInteger B("456");
    BigInteger C = A.mult(B);
    if (C.to_string() != "56088")
        throw runtime_error("testMultiplication: 123 * 456 failed");
    
    // Multiplication by zero
    BigInteger D("0");
    BigInteger E = A.mult(D);
    if (E.to_string() != "0")
        throw runtime_error("testMultiplication: multiplication by zero failed");
}

// Test comparison operators
void testComparisons() {
    BigInteger A("1000");
    BigInteger B("1000");
    BigInteger C("999");
    BigInteger D("1001");
    
    if (!(A == B))
        throw runtime_error("testComparisons: equality failed");
    if (!(C < A))
        throw runtime_error("testComparisons: less-than failed");
    if (!(D > A))
        throw runtime_error("testComparisons: greater-than failed");
    if (!(A <= B))
        throw runtime_error("testComparisons: less-than or equal failed");
    if (!(A >= B))
        throw runtime_error("testComparisons: greater-than or equal failed");
}

int main() {
    try {
        testSign();
        cout << "testSign passed" << endl;
        testNegate();
        cout << "testNegate passed" << endl;
        testMakeZero();
        cout << "testMakeZero passed" << endl;
        testAddition();
        cout << "testAddition passed" << endl;
        testSubtraction();
        cout << "testSubtraction passed" << endl;
        testMultiplication();
        cout << "testMultiplication passed" << endl;
        testComparisons();
        cout << "testComparisons passed" << endl;
    } catch (const exception& e) {
        cerr << "A test failed: " << e.what() << endl;
        return 1;
    }
    
    cout << "All BigInteger tests passed successfully!" << endl;
    return 0;
}