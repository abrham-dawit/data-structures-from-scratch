// Name: Abrham Dawit
// Cruzid: asdawit
// Winter 25 - 101
// Assignment: pa1
// List.c
// Implementation file for the List ADT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

// Private Node type
typedef struct NodeObj* Node;

typedef struct NodeObj {
    int data;
    Node next;
    Node prev;
} NodeObj;

// Private List type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors -----------------------------------------------------------
// Creates and returns a new empty List.
List newList(void) {
    List L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
    if (pL == NULL || *pL == NULL) {
        return;
    }
    // Clear the list before freeing the ListObj
    clear(*pL);
    
    free(*pL);
    *pL = NULL;
}

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L) {
    if(L == NULL ){
        fprintf(stderr, "List Error: length() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: index() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: front() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: front() called on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// Returns back element of L. Pre: length()>0
int back(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: back() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: back() called on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: get() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: get() called on empty List\n");
         exit(EXIT_FAILURE);
    }
     if (L->index < 0) {
        fprintf(stderr, "List Error: get() called with undefined cursor\n");
         exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Returns true iff Lists A and B contain the same sequence of elements, returns false otherwise.
bool equals(List A, List B){
   if( A == NULL || B == NULL ){
        fprintf(stderr, "List Error: equals() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

   if (length(A) != length(B)) {
        return false;
    }
    Node currA = A->front;
    Node currB = B->front;
    while (currA != NULL) {
        if (currA->data != currB->data) {
            return false;
        }
        currA = currA->next;
        currB = currB->next;
    }
    return true;
}


// Manipulation procedures -----------------------------------------------------------
// Resets L to its original empty state.
void clear(List L) {
    if( L == NULL ){
        fprintf(stderr, "List Error: clear() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node temp;
    while (L->front != NULL) {
        temp = L->front;
        L->front = L->front->next;
        free(temp);
    }
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
    if( L == NULL ){
        fprintf(stderr, "List Error: set() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: set() called on empty List\n");
         exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
         fprintf(stderr, "List Error: set() called with undefined cursor\n");
         exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if( L == NULL ){
        fprintf(stderr, "List Error: moveFront() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: moveBack() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: movePrev() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->index > 0) {
        L->cursor = L->cursor->prev;
        L->index--;
    } else if (L->cursor != NULL && L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
    }
}

// If cursor is defined and not at back, move cursor one step toward the back of L;
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: moveNext() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->index < L->length - 1) {
        L->cursor = L->cursor->next;
        L->index++;
    } else if (L->cursor != NULL && L->index == L->length - 1) {
        L->cursor = NULL;
        L->index = -1;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {
    if( L == NULL ){
        fprintf(stderr, "List Error: prepend() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = malloc(sizeof(NodeObj));
    assert(newNode != NULL);
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = L->front;
    if (L->front != NULL) {
        L->front->prev = newNode;
    }
    L->front = newNode;
    if (L->back == NULL) {
        L->back = newNode;
    }
    L->length++;
    if (L->cursor != NULL){
        L->index++;
    }
}

// Insert new element into L.  If L is non-empty, insertion takes place after back element.
void append(List L, int x) {
    if( L == NULL ){
        fprintf(stderr, "List Error: append() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = malloc(sizeof(NodeObj));
    assert(newNode != NULL);
    newNode->data = x;
    newNode->next = NULL;
     newNode->prev = L->back;

    if (L->back != NULL) {
        L->back->next = newNode;
    }
    L->back = newNode;
    if (L->front == NULL) {
        L->front = newNode;
    }

    L->length++;
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
     if( L == NULL ){
        fprintf(stderr, "List Error: insertBefore() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
         fprintf(stderr, "List Error: insertBefore() called on empty List\n");
         exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List Error: insertBefore() called with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = malloc(sizeof(NodeObj));
    assert(newNode != NULL);
    newNode->data = x;
     if (L->cursor->prev != NULL){
        newNode->prev = L->cursor->prev;
         L->cursor->prev->next = newNode;
     } else { //cursor at front
        L->front = newNode;
         newNode->prev = NULL;
     }

    newNode->next = L->cursor;
    L->cursor->prev = newNode;
    L->index++;
    L->length++;
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if( L == NULL ){
        fprintf(stderr, "List Error: insertAfter() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: insertAfter() called on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List Error: insertAfter() called with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = malloc(sizeof(NodeObj));
    assert(newNode != NULL);
    newNode->data = x;
    newNode->next = L->cursor->next;
    newNode->prev = L->cursor;
    if (L->cursor->next != NULL) {
        L->cursor->next->prev = newNode;
    } else { //cursor at back
        L->back = newNode;
    }
    L->cursor->next = newNode;
    L->length++;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: deleteFront() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
       fprintf(stderr, "List Error: deleteFront() called on empty List\n");
       exit(EXIT_FAILURE);
    }
    Node temp = L->front;
    if (L->length == 1) {
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->front = L->front->next;
        L->front->prev = NULL;
        if (L->cursor != NULL && L->index != -1){
        L->index--;
        }
    }

    free(temp);
    L->length--;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if( L == NULL ){
        fprintf(stderr, "List Error: deleteBack() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
         fprintf(stderr, "List Error: deleteBack() called on empty List\n");
         exit(EXIT_FAILURE);
    }
    Node temp = L->back;
      if (L->length == 1) {
        L->front = NULL;
        L->back = NULL;
         L->cursor = NULL;
        L->index = -1;
    } else {
        L->back = L->back->prev;
        L->back->next = NULL;
         if (L->cursor == temp){
            L->cursor = NULL;
             L->index = -1;
         }
    }
    free(temp);
    L->length--;
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
     if( L == NULL ){
        fprintf(stderr, "List Error: delete() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: delete() called on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List Error: delete() called with undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    Node temp = L->cursor;

    if (L->length == 1){
          L->front = NULL;
          L->back = NULL;
    } else if (L->cursor == L->front){
          L->front = L->front->next;
          if (L->front != NULL){
              L->front->prev = NULL;
          }
    } else if (L->cursor == L->back){
          L->back = L->back->prev;
          if (L->back != NULL){
               L->back->next = NULL;
          }
     } else {
           L->cursor->prev->next = L->cursor->next;
           L->cursor->next->prev = L->cursor->prev;
     }

    L->cursor = NULL;
    L->index = -1;
    free(temp);
    L->length--;
}

// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left
void printList(FILE* out, List L) {
     if( L==NULL ){
        fprintf(stderr, "List Error: printList() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node current = L->front;
    while (current != NULL) {
        fprintf(out, "%d ", current->data);
        current = current->next;
    }
}


// Returns a new List representing the same integer sequence as L
List copyList(List L){
    if( L == NULL ){
        fprintf(stderr, "List Error: copyList() called on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List copiedList = newList();
    Node current = L->front;
    while(current != NULL){
        append(copiedList, current->data);
        current = current->next;
    }
    return copiedList;
}
