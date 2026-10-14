// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa4
// ListTest.c - Test client for the List ADT

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    printf("Running ListTest...\n");

    // Create a new List
    List L = newList();

    // Test appending elements
    int a = 10, b = 20, c = 30, d = 40;
    append(L, &a);
    append(L, &b);
    append(L, &c);
    append(L, &d);

    printf("List after appending: ");
    moveFront(L);
    while (index(L) != -1) {
        printf("%d ", *(int*)get(L));
        moveNext(L);
    }
    printf("\n");

    // Test prepending elements
    int x = 5, y = 15;
    prepend(L, &x);
    prepend(L, &y);

    printf("List after prepending: ");
    moveFront(L);
    while (index(L) != -1) {
        printf("%d ", *(int*)get(L));
        moveNext(L);
    }
    printf("\n");

    // Move cursor and insertBefore, insertAfter
    moveFront(L);
    moveNext(L);
    int z = 25;
    insertBefore(L, &z);
    
    moveNext(L);
    int w = 35;
    insertAfter(L, &w);

    printf("List after insertBefore(25) and insertAfter(35): ");
    moveFront(L);
    while (index(L) != -1) {
        printf("%d ", *(int*)get(L));
        moveNext(L);
    }
    printf("\n");

    // Test delete operations
    deleteFront(L);
    deleteBack(L);
    moveFront(L);
    moveNext(L);
    delete(L);  // Deleting cursor element

    printf("List after deleteFront, deleteBack, and delete(cursor): ");
    moveFront(L);
    while (index(L) != -1) {
        printf("%d ", *(int*)get(L));
        moveNext(L);
    }
    printf("\n");

    // Test clearing the List
    clear(L);
    printf("List length after clear(): %d\n", length(L));

    // Free memory
    freeList(&L);

    printf("ListTest completed successfully!\n");

    return 0;
}