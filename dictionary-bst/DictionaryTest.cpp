// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa7
// DictionaryTest.cpp
// A test client for the Dictionary ADT

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void testEmptyDictionary() {
    cout << "Test 1: Empty Dictionary" << endl;
    Dictionary dict;

    if(dict.size() != 0)
        cout << "Error: size should be 0, got " << dict.size() << endl;
    
    try {
        dict.currentKey();
        cout << "Error: currentKey() should throw exception for empty dictionary." << endl;
    } catch (const logic_error& e) {
        cout << "Passed: currentKey() correctly threw exception." << endl;
    }
}

void testSetValueAndContains() {
    cout << "\nTest 2: setValue, contains, and getValue" << endl;
    Dictionary dict;
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    dict.setValue("cherry", 3);

    if (!dict.contains("apple") || !dict.contains("banana") || !dict.contains("cherry"))
        cout << "Error: contains() failed to detect keys." << endl;
    else
        cout << "Passed: contains() correctly found all keys." << endl;

    dict.setValue("apple", 10);
    if (dict.getValue("apple") != 10)
        cout << "Error: setValue() did not update 'apple' to 10." << endl;
    else
        cout << "Passed: setValue() correctly updated key 'apple'." << endl;
}

void testIteratorFunctions() {
    cout << "\nTest 3: Iterator Functions" << endl;
    Dictionary dict;

    dict.setValue("d", 4);
    dict.setValue("a", 1);
    dict.setValue("c", 3);
    dict.setValue("b", 2);

    dict.begin();
    if (dict.currentKey() != "a" || dict.currentVal() != 1)
        cout << "Error: begin() did not set current to 'a'." << endl;
    else
        cout << "Passed: begin() correctly set iterator to smallest key 'a'." << endl;

    dict.next();
    if (dict.currentKey() != "b")
        cout << "Error: next() did not move to 'b'." << endl;
    dict.next();
    if (dict.currentKey() != "c")
        cout << "Error: next() did not move to 'c'." << endl;
    dict.next();
    if (dict.currentKey() != "d")
        cout << "Error: next() did not move to 'd'." << endl;
    
    try {
        dict.next();
        cout << "Error: next() should have resulted in an undefined iterator at end." << endl;
    } catch (const logic_error& e) {
        cout << "Passed: next() correctly handled reaching the end." << endl;
    }

    dict.end();
    if (dict.currentKey() != "d")
        cout << "Error: end() did not set current to 'd'." << endl;
    dict.prev();
    if (dict.currentKey() != "c")
        cout << "Error: prev() did not move to 'c'." << endl;
    dict.prev();
    if (dict.currentKey() != "b")
        cout << "Error: prev() did not move to 'b'." << endl;
    dict.prev();
    if (dict.currentKey() != "a")
        cout << "Error: prev() did not move to 'a'." << endl;

    try {
        dict.prev();
        cout << "Error: prev() should have resulted in an undefined iterator at beginning." << endl;
    } catch (const logic_error& e) {
        cout << "Passed: prev() correctly handled reaching the beginning." << endl;
    }
}

void testRemove() {
    cout << "\nTest 4: remove()" << endl;
    Dictionary dict;
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    dict.setValue("cherry", 3);

    dict.remove("banana");
    if (dict.contains("banana"))
        cout << "Error: remove() did not delete 'banana'." << endl;
    else
        cout << "Passed: remove() correctly removed 'banana'." << endl;

    if (dict.size() != 2)
        cout << "Error: size should be 2 after removal, got " << dict.size() << endl;

    dict.begin();
    if (dict.currentKey() != "apple")
        cout << "Error: begin() did not set iterator to 'apple'." << endl;
    dict.remove("apple");
    try {
        dict.currentKey();
        cout << "Error: currentKey() should throw exception after removal of current element." << endl;
    } catch (const logic_error& e) {
        cout << "Passed: removal of current element correctly undefined the iterator." << endl;
    }
}

void testToStringAndPreString() {
    cout << "\nTest 5: to_string() and pre_string()" << endl;
    Dictionary dict;
    
    dict.setValue("b", 2);
    dict.setValue("a", 1);
    dict.setValue("c", 3);

    string expected = "a : 1\nb : 2\nc : 3\n";
    string result = dict.to_string();
    if (result != expected) {
        cout << "Error: to_string() output mismatch." << endl;
        cout << "Expected:\n" << expected << endl;
        cout << "Got:\n" << result << endl;
    } else {
        cout << "Passed: to_string() produced correct output." << endl;
    }

    string expectedPre = "b\na\nc\n";
    string resultPre = dict.pre_string();
    if (resultPre != expectedPre) {
        cout << "Error: pre_string() output mismatch." << endl;
        cout << "Expected:\n" << expectedPre << endl;
        cout << "Got:\n" << resultPre << endl;
    } else {
        cout << "Passed: pre_string() produced correct output." << endl;
    }
}

void testEqualsAndAssignment() {
    cout << "\nTest 6: equals() and Assignment Operator" << endl;
    Dictionary dict1;
    dict1.setValue("apple", 1);
    dict1.setValue("banana", 2);

    Dictionary dict2;
    dict2.setValue("apple", 1);
    dict2.setValue("banana", 2);

    if (!dict1.equals(dict2))
        cout << "Error: equals() should return true for identical dictionaries." << endl;
    else
        cout << "Passed: equals() correctly identified identical dictionaries." << endl;

    Dictionary dict3 = dict1;
    if (!dict1.equals(dict3))
        cout << "Error: Copy constructor did not create an identical dictionary." << endl;
    else
        cout << "Passed: Copy constructor works correctly." << endl;

    Dictionary dict4;
    dict4.setValue("dummy", 0);
    dict4 = dict1;
    if (!dict4.equals(dict1))
        cout << "Error: Assignment operator did not correctly copy dictionary state." << endl;
    else
        cout << "Passed: Assignment operator works correctly." << endl;
}

int main() {
    cout << "Running Dictionary ADT Tests..." << endl;

    testEmptyDictionary();
    testSetValueAndContains();
    testIteratorFunctions();
    testRemove();
    testToStringAndPreString();
    testEqualsAndAssignment();

    cout << "\nAll tests completed." << endl;
    return 0;
}