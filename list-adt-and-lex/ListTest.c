// Name: Abrham Dawit
// Cruzid: asdawit
// Winter 25 - 101
// Assignment: pa1
// ListTest.c
// Test client for the List ADT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// Helper function to print test status
void printTestStatus(const char* testName, bool passed) {
    printf("%s: %s\n", testName, passed ? "PASSED" : "FAILED\n");
}

// Helper function to check list state
bool checkListState(List L, int expectedLength, int expectedIndex, int expectedValue) {
    if(length(L) != expectedLength) return false;
    if(index(L) != expectedIndex) return false;
    if(expectedIndex >= 0 && get(L) != expectedValue) return false;
    return true;
}

// Helper function for testing preconditions
void testPrecondition(const char *testName, void (*func)(List)) {
    List L = newList();
    printf("%s: ", testName);
	func(L);
	printf("Manual test executed (no crash handling implemented).\n");
    freeList(&L);
}

void testNewList() {
    List L = newList();
    bool passed = checkListState(L, 0, -1, 0);
    printTestStatus("testNewList", passed);
    freeList(&L);
}

void testAppend() {
    List L = newList();
    append(L, 5);
    bool passed = checkListState(L, 1, -1, 5);
    printTestStatus("testAppend", passed);
    freeList(&L);
}


void testPrepend() {
    List L = newList();
    prepend(L, 7);
    bool passed = checkListState(L, 1, -1, 7);
    printTestStatus("testPrepend", passed);
    freeList(&L);
}

void testInsertBefore(){
    List L = newList();
    append(L, 1);
    append(L, 3);
    moveFront(L);
    insertBefore(L, 2);
    bool passed = (length(L) == 3 && index(L) == 1 && front(L) == 2);
    printTestStatus("testInsertBefore", passed);
    freeList(&L);
}
void testInsertAfter(){
    List L = newList();
    append(L, 1);
    append(L, 3);
    moveFront(L);
    insertAfter(L, 2);
    bool passed = checkListState(L, 3, 0, 1);
    printTestStatus("testInsertAfter", passed);
    freeList(&L);
}
void testDeleteFront(){
    List L = newList();
    append(L, 1);
    append(L, 2);
    moveFront(L);
    deleteFront(L);
     bool passed = checkListState(L, 1, -1, 2);
    printTestStatus("testDeleteFront", passed);
    freeList(&L);
}

void testDeleteBack(){
    List L = newList();
    append(L, 1);
    append(L, 2);
    deleteBack(L);
    bool passed = checkListState(L, 1, -1, 1);
    printTestStatus("testDeleteBack", passed);
    freeList(&L);
}
void testDelete(){
    List L = newList();
    append(L, 1);
    append(L, 2);
    moveFront(L);
    delete(L);
    bool passed = checkListState(L, 1, -1, 2);
    printTestStatus("testDelete", passed);
    freeList(&L);
}

void testMoveFront() {
    List L = newList();
    append(L, 1);
    append(L, 2);
    moveFront(L);
    bool passed = checkListState(L, 2, 0, 1);
    printTestStatus("testMoveFront", passed);
    freeList(&L);
}

void testMoveBack() {
    List L = newList();
    append(L, 1);
    append(L, 2);
    moveBack(L);
    bool passed = checkListState(L, 2, 1, 2);
    printTestStatus("testMoveBack", passed);
    freeList(&L);
}
void testMoveNext() {
    List L = newList();
    append(L, 1);
    append(L, 2);
    moveFront(L);
    moveNext(L);
    bool passed = checkListState(L, 2, 1, 2);
     printTestStatus("testMoveNext", passed);
    freeList(&L);
}

void testMovePrev() {
    List L = newList();
    append(L, 1);
    append(L, 2);
    moveBack(L);
    movePrev(L);
    bool passed = checkListState(L, 2, 0, 1);
    printTestStatus("testMovePrev", passed);
    freeList(&L);
}

void testIndex() {
    List L = newList();
    append(L, 1);
    append(L, 2);
    moveFront(L);
    moveNext(L);
    bool passed = (index(L) == 1);
    printTestStatus("testIndex", passed);
    freeList(&L);
}


void testLength() {
    List L = newList();
    append(L, 1);
    append(L, 2);
    bool passed = (length(L) == 2);
    printTestStatus("testLength", passed);
    freeList(&L);
}

void testGet() {
    List L = newList();
    append(L, 42);
    moveFront(L);
    bool passed = (get(L) == 42);
    printTestStatus("testGet", passed);
    freeList(&L);
}
void testCopyList(){
     List L = newList();
    append(L, 1);
    append(L, 2);
    List L2 = copyList(L);
    bool passed = (length(L) == length(L2));
    printTestStatus("testCopyList", passed);
    freeList(&L);
    freeList(&L2);
}
void testEquals(){
    List L = newList();
    append(L, 1);
    append(L, 2);
    List L2 = newList();
    append(L2, 1);
    append(L2, 2);
    bool passed = equals(L, L2);
    printTestStatus("testEquals", passed);
    freeList(&L);
    freeList(&L2);
}

void testIsEmpty() {
    List L = newList();
    bool passed = (length(L) == 0);
    printTestStatus("testIsEmpty", passed);
    freeList(&L);
}

void testPrintList(){
    List L = newList();
    append(L, 1);
    append(L, 2);
    printf("testPrintList: ");
    printList(stdout, L);
    printf("\n");
    printTestStatus("testPrintList", true);
    freeList(&L);
}

void testDeletePrecondition() {
    List L = newList();
    append(L, 1);
    moveFront(L);
    testPrecondition("testDeletePrecondition", delete);
}
void testGetPrecondition() {
    printf("testGetPrecondition: Manual test skipped (incompatible function pointer).\n");
}
void testDeleteFrontPrecondition(){
    testPrecondition("testDeleteFrontPrecondition", deleteFront);
}
void testDeleteBackPrecondition(){
    testPrecondition("testDeleteBackPrecondition", deleteBack);
}
int main() {
    // Run all test cases:
   testNewList();
   testAppend();
   testPrepend();
   testInsertBefore();
   testInsertAfter();
   testDeleteFront();
   testDeleteBack();
   testDelete();
   testMoveFront();
   testMoveBack();
   testMoveNext();
   testMovePrev();
   testIndex();
   testLength();
   testGet();
   testCopyList();
   testEquals();
   testIsEmpty();
   testPrintList();
   testDeletePrecondition();
   testGetPrecondition();
   testDeleteFrontPrecondition();
   testDeleteBackPrecondition();
   
   return 0;
}
