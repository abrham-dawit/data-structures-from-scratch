// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa4
// List.h - Header file for the generic List ADT

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

// Exported type
typedef struct ListObj* List;

// Constructors-Destructors
List newList(void);
void freeList(List* pL);

// Access Functions
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

// Manipulation Procedures
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* data);
void append(List L, void* data);
void insertBefore(List L, void* data);
void insertAfter(List L, void* data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

#endif