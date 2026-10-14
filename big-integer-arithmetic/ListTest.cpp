// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa6
// ListTest.cpp
// Test suite for the List ADT

#include <iostream>
#include <stdexcept>
#include <string>
#include "List.h"

using namespace std;

// Test that an empty list has length 0 and throws exceptions for front/back
void testEmptyList() {
    List L;
    if (L.length() != 0)
        throw runtime_error("testEmptyList: Expected length 0.");
    try {
        L.front();
        throw runtime_error("testEmptyList: front() should throw on empty list.");
    } catch (runtime_error&) { }
    try {
        L.back();
        throw runtime_error("testEmptyList: back() should throw on empty list.");
    } catch (runtime_error&) { }
}

// Test insertAfter, insertBefore, and basic cursor movement
void testInsertAndMove() {
    List L;
    L.insertAfter(10);
    if (L.length() != 1)
        throw runtime_error("testInsertAndMove: Expected length 1 after insertAfter.");
    if (L.to_string() != "(10)")
        throw runtime_error("testInsertAndMove: Expected (10), got " + L.to_string());
    
    L.insertBefore(5);
    if (L.to_string() != "(5, 10)")
        throw runtime_error("testInsertAndMove: Expected (5, 10), got " + L.to_string());
    
    L.moveFront();
    int pos1 = L.moveNext();
    if (pos1 != 1)
        throw runtime_error("testInsertAndMove: moveNext did not update position correctly (first call).");
    int pos2 = L.moveNext(); 
    if (pos2 != 2)
        throw runtime_error("testInsertAndMove: moveNext did not update position correctly (second call).");
    int pos3 = L.movePrev();
    if (pos3 != 2)
        throw runtime_error("testInsertAndMove: movePrev did not update position correctly.");
}

// Test erasing elements with eraseAfter and eraseBefore
void testErase() {
    List L;
    // Build list: (10, 20, 30)
    L.insertAfter(10);  
    L.insertAfter(20);
    L.insertAfter(30);

    L.moveFront();  
    L.moveNext();

    L.eraseAfter();
    if (L.length() != 2)
        throw runtime_error("testErase: Expected length 2 after eraseAfter.");
        
    L.moveBack();   
    L.eraseBefore(); 
    if (L.length() != 1)
        throw runtime_error("testErase: Expected length 1 after eraseBefore.");
}

// Test findNext, findPrev, and cleanup functions
void testFindCleanup() {
    List L;

    L.insertAfter(1);
    L.insertAfter(2);
    L.insertAfter(2);
    L.insertAfter(3);
    L.insertAfter(2);

    L.moveFront();
    int pos = L.findNext(2);
    if (pos < 0)
        throw runtime_error("testFindCleanup: findNext failed to locate element 2.");
    
    int posPrev = L.findPrev(2);
    if (posPrev < 0)
        throw runtime_error("testFindCleanup: findPrev failed to locate element 2.");
    
    L.cleanup();
    if (L.to_string() != "(1, 2, 3)")
        throw runtime_error("testFindCleanup: cleanup failed, expected (1, 2, 3), got " + L.to_string());
}

// Test the concatenation of two lists
void testConcat() {
    List L1;
    L1.insertAfter(1);
    L1.insertAfter(2);
    L1.insertAfter(3);
    List L2;
    L2.insertAfter(4);
    L2.insertAfter(5);
    List L3 = L1.concat(L2);
    // Expected concatenated list: (1, 2, 3, 4, 5)
    if (L3.to_string() != "(1, 2, 3, 4, 5)")
        throw runtime_error("testConcat: Expected (1, 2, 3, 4, 5), got " + L3.to_string());
}

// Test equality (operator==) and assignment (operator=)
void testEqualityAssignment() {
    List L1;
    L1.insertAfter(10);
    L1.insertAfter(20);
    L1.insertAfter(30);
    List L2 = L1;
    if (!(L1 == L2))
        throw runtime_error("testEqualityAssignment: Copy constructor failed (operator==).");
    List L3;
    L3 = L1;
    if (!(L1 == L3))
        throw runtime_error("testEqualityAssignment: Assignment operator failed (operator==).");
}

int main() {
    try {
        testEmptyList();
        cout << "testEmptyList passed" << endl;
        testInsertAndMove();
        cout << "testInsertAndMove passed" << endl;
        testErase();
        cout << "testErase passed" << endl;
        testFindCleanup();
        cout << "testFindCleanup passed" << endl;
        testConcat();
        cout << "testConcat passed" << endl;
        testEqualityAssignment();
        cout << "testEqualityAssignment passed" << endl;
    } catch (const exception& e) {
        cerr << "ListTest failed: " << e.what() << endl;
        return 1;
    }
    cout << "All List tests passed successfully!" << endl;
    return 0;
}