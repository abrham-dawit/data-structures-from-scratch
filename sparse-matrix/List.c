// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa4
// List.c - Implementation file for the generic List ADT

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Struct Definitions
typedef struct NodeObj {
    void* data;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors

// newNode(): Creates a new node with given data
Node newNode(void* data) {
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL) {
        fprintf(stderr, "List Error: newNode() failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return N;
}

// freeNode(): Frees a node
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// newList(): Creates and returns a new empty list
List newList(void) {
    List L = malloc(sizeof(ListObj));
    if (L == NULL) {
        fprintf(stderr, "List Error: newList() failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

// freeList(): Frees all heap memory associated with *pL and sets *pL to NULL
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access Functions
int length(List L) {
    return (L != NULL) ? L->length : 0;
}
int index(List L) {
    return (L->cursor != NULL) ? L->index : -1;
}
void* front(List L) {
    if (L == NULL || L->length == 0) {
        fprintf(stderr, "List Error: front() called on an empty list\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}
void* back(List L) {
    if (L == NULL || L->length == 0) {
        fprintf(stderr, "List Error: back() called on an empty list\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}
void* get(List L) {
    if (L == NULL || L->cursor == NULL) {
        fprintf(stderr, "List Error: get() called on an empty list or undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Manipulation Procedures
void clear(List L) {
    if (L == NULL) return;
    while (L->length > 0) deleteFront(L);
    L->cursor = NULL;
    L->index = -1;
}
void moveFront(List L) {
    if (L != NULL && L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}
void moveBack(List L) {
    if (L != NULL && L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}
void movePrev(List L) {
    if (L != NULL && L->cursor != NULL) {
        L->cursor = L->cursor->prev;
        L->index = (L->cursor == NULL) ? -1 : L->index - 1;
    }
}
void moveNext(List L) {
    if (L != NULL && L->cursor != NULL) {
        L->cursor = L->cursor->next;
        L->index = (L->cursor == NULL) ? -1 : L->index + 1;
    }
}
void prepend(List L, void* data) {
    if (L == NULL) return;
    Node N = newNode(data);
    if (L->length == 0) {
        L->front = L->back = N;
    } else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    L->length++;
    if (L->cursor != NULL) L->index++;
}
void append(List L, void* data) {
    if (L == NULL) return;
    Node N = newNode(data);
    if (L->length == 0) {
        L->front = L->back = N;
    } else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}
void insertBefore(List L, void* data) {
    if (L == NULL || L->cursor == NULL) return;
    if (L->cursor == L->front) {
        prepend(L, data);
    } else {
        Node N = newNode(data);
        N->prev = L->cursor->prev;
        N->next = L->cursor;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->length++;
        L->index++;
    }
}
void insertAfter(List L, void* data) {
    if (L == NULL || L->cursor == NULL) return;
    if (L->cursor == L->back) {
        append(L, data);
    } else {
        Node N = newNode(data);
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next->prev = N;
        L->cursor->next = N;
        L->length++;
    }
}
void deleteFront(List L) {
    if (L == NULL || L->length == 0) return;
    Node N = L->front;
    if (L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    if (L->cursor == N) L->cursor = NULL;
    freeNode(&N);
    L->length--;
    L->index = (L->index > 0) ? L->index - 1 : -1;
}
void deleteBack(List L) {
    if (L == NULL || L->length == 0) return;
    Node N = L->back;
    if (L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    if (L->cursor == N) L->cursor = NULL;
    freeNode(&N);
    L->length--;
}
void delete(List L) {
    if (L == NULL || L->cursor == NULL) return;
    if (L->cursor == L->front) {
        deleteFront(L);
    } else if (L->cursor == L->back) {
        deleteBack(L);
    } else {
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&L->cursor);
        L->cursor = NULL;
        L->length--;
    }
}