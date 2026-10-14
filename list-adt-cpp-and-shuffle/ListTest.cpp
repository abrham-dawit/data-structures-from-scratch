// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa5
// ListTest.cpp 
// Test client for the List ADT

#include <iostream>
#include <cassert>
#include "List.h"

using namespace std;

void testFindNext() {
    cout << "Testing findNext()...\n";
    List L;
    
    // Insert values
    L.insertBefore(10);
    L.insertBefore(20);
    L.insertBefore(30);
    L.insertBefore(40);
    L.insertBefore(50); // List: [50, 40, 30, 20, 10]
    
    L.moveFront();
    assert(L.findNext(30) == 2); // Move to position of 30
    assert(L.findNext(50) == -1); // 50 not found in remaining elements
    assert(L.findNext(10) == 4); // Move to 10 (end)
    
    L.moveFront();
    assert(L.findNext(100) == -1); // Element not in list
    
    cout << "findNext() passed all tests!\n";
}

void testFindPrev() {
    cout << "Testing findPrev()...\n";
    List L;
    
    // Insert values
    L.insertBefore(10);
    L.insertBefore(20);
    L.insertBefore(30);
    L.insertBefore(40);
    L.insertBefore(50); // List: [50, 40, 30, 20, 10]
    
    L.moveBack();
    assert(L.findPrev(30) == 2);  // Move to position of 30
    assert(L.findPrev(50) == -1); // 50 not found when moving back
    assert(L.findPrev(40) == 1);  // Move to 40
    
    L.moveBack();
    assert(L.findPrev(100) == -1); // Element not in list
    
    cout << "findPrev() passed all tests!\n";
}

void testCleanup() {
    cout << "Testing cleanup()...\n";
    
    List L;
    
    // Test with no duplicates
    L.insertBefore(1);
    L.insertBefore(2);
    L.insertBefore(3);
    L.insertBefore(4);
    L.insertBefore(5); // [5, 4, 3, 2, 1]
    
    L.cleanup(); // No change expected
    assert(L.length() == 5);
    
    // Test with duplicates
    L.insertBefore(3);
    L.insertBefore(2);
    L.insertBefore(4);
    L.insertBefore(1); // [1, 4, 2, 3, 5, 4, 3, 2, 1]
    
    L.cleanup(); // Should remove second occurrences of 1, 2, 3, 4
    assert(L.length() == 5);
    
    cout << "cleanup() passed all tests!\n";
}

void testEqualityOperator() {
    cout << "Testing equality operator...\n";
    List A, B;
    
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    
    assert(A == B); // Lists are the same
    
    B.insertBefore(4);
    assert(!(A == B)); // Lists are now different
    
    cout << "Equality operator passed all tests!\n";
}

void testCopyConstructor() {
    cout << "Testing copy constructor...\n";
    
    List A;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    
    List B(A); // Copy A into B
    assert(A == B);
    
    B.insertBefore(4);
    assert(!(A == B)); // Lists should be different now
    
    cout << "Copy constructor passed all tests!\n";
}

int main() {
    testFindNext();
    testFindPrev();
    testCleanup();
    testEqualityOperator();
    testCopyConstructor();
    
    cout << "All ListTest cases passed successfully!\n";
    return 0;
}