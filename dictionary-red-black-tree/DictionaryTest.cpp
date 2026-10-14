//-----------------------------------------------------------------------------
// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa8
// DictionaryTest.cpp
// A test client for the Red-Black Tree Dictionary ADT
//-----------------------------------------------------------------------------

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Test 1: Test creation and basic access
void testBasic() {
    cout << "Test 1: Basic Set & Get\n";

    Dictionary D;
    D.setValue("d", 4);
    D.setValue("b", 2);
    D.setValue("f", 6);
    D.setValue("a", 1);
    D.setValue("c", 3);
    D.setValue("e", 5);
    D.setValue("g", 7);

    if (!D.contains("a") || !D.contains("g") || D.size() != 7)
        cout << "Error: Basic insert failed.\n";
    else
        cout << "Passed: Basic insert, contains, and size.\n";

    try {
        int val = D.getValue("c");
        if (val != 3) throw logic_error("Incorrect value");
        cout << "Passed: getValue returns correct value.\n";
    } catch (...) {
        cout << "Error: getValue threw or returned wrong.\n";
    }
}

// Test 2: Test iterators (begin, next, end, prev)
void testIterators() {
    cout << "\nTest 2: Iterator Logic\n";
    Dictionary D;
    D.setValue("b", 2);
    D.setValue("a", 1);
    D.setValue("c", 3);

    D.begin();
    if (D.currentKey() != "a") cout << "Error: begin() failed.\n";
    else cout << "Passed: begin()\n";

    D.next();
    if (D.currentKey() != "b") cout << "Error: next() failed.\n";
    else cout << "Passed: next()\n";

    D.end();
    if (D.currentKey() != "c") cout << "Error: end() failed.\n";
    else cout << "Passed: end()\n";

    D.prev();
    if (D.currentKey() != "b") cout << "Error: prev() failed.\n";
    else cout << "Passed: prev()\n";
}

// Test 3: to_string and pre_string (with RED labels)
void testStringOutput() {
    cout << "\nTest 3: String Output\n";
    Dictionary D;
    D.setValue("banana", 10);
    D.setValue("apple", 5);
    D.setValue("cherry", 15);

    string inorder = D.to_string();
    cout << "In-order:\n" << inorder;

    string preorder = D.pre_string();
    cout << "Pre-order:\n" << preorder;

    if (preorder.find("(RED)") != string::npos)
        cout << "Passed: RED node labeling present in pre_string().\n";
    else
        cout << "Warning: (RED) label not detected. May still be correct.\n";
}

// Test 4: remove()
void testRemove() {
    cout << "\nTest 4: Remove()\n";
    Dictionary D;
    D.setValue("a", 1);
    D.setValue("b", 2);
    D.setValue("c", 3);
    D.setValue("d", 4);
    D.setValue("e", 5);

    D.remove("c");
    if (D.contains("c"))
        cout << "Error: remove() failed to delete key.\n";
    else
        cout << "Passed: remove() correctly deleted key.\n";

    D.begin();
    while (D.hasCurrent()) {
        cout << D.currentKey() << " ";
        D.next();
    }
    cout << endl;
}

// Test 5: equals() and assignment
void testEqualityAndCopy() {
    cout << "\nTest 5: equals() and assignment\n";
    Dictionary A, B;

    A.setValue("z", 1);
    A.setValue("y", 2);
    A.setValue("x", 3);

    B.setValue("z", 1);
    B.setValue("y", 2);
    B.setValue("x", 3);

    if (A == B)
        cout << "Passed: operator== works.\n";
    else
        cout << "Error: operator== failed.\n";

    Dictionary C = A;
    if (C == A)
        cout << "Passed: Copy constructor.\n";
    else
        cout << "Error: Copy constructor failed.\n";

    Dictionary D;
    D = A;
    if (D == A)
        cout << "Passed: Assignment operator.\n";
    else
        cout << "Error: Assignment operator failed.\n";
}

// Test 6: Exception testing
void testExceptions() {
    cout << "\nTest 6: Exception Handling\n";
    Dictionary D;
    try {
        D.currentKey();
        cout << "Error: currentKey() did not throw on undefined current.\n";
    } catch (...) {
        cout << "Passed: currentKey() threw exception.\n";
    }

    try {
        D.next();
        cout << "Error: next() did not throw on undefined current.\n";
    } catch (...) {
        cout << "Passed: next() threw exception.\n";
    }

    try {
        D.getValue("missing");
        cout << "Error: getValue() did not throw on missing key.\n";
    } catch (...) {
        cout << "Passed: getValue() threw exception.\n";
    }

    try {
        D.remove("missing");
        cout << "Error: remove() did not throw on missing key.\n";
    } catch (...) {
        cout << "Passed: remove() threw exception.\n";
    }
}

int main() {
    cout << "Running Dictionary ADT Tests for PA8...\n";
    testBasic();
    testIterators();
    testStringOutput();
    testRemove();
    testEqualityAndCopy();
    testExceptions();
    cout << "\nAll tests completed.\n";
    return 0;
}