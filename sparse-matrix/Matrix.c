// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa4
// Matrix.c
// Implementation file for the Matrix ADT

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"

// Struct for a single nonzero entry
typedef struct EntryObj {
    int col;
    double value;
} EntryObj;

typedef EntryObj* Entry;

// Matrix structure
typedef struct MatrixObj {
    int size;      // Number of rows/columns (n x n matrix)
    int NNZ;       // Number of nonzero entries
    List* rows;    // Array of Lists (each row contains entries)
} MatrixObj;

// Helper function to create a new Entry
Entry newEntry(int col, double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = col;
    E->value = value;
    return E;
}

// Helper function to free an Entry
void freeEntry(Entry* pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

// Constructor: Creates a new matrix of size n x n
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->NNZ = 0;
    M->rows = calloc(n + 1, sizeof(List));  // 1-based indexing
    for (int i = 1; i <= n; i++) {
        M->rows[i] = newList();
    }
    return M;
}

// Destructor: Frees all memory associated with Matrix M
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        Matrix M = *pM;
        for (int i = 1; i <= M->size; i++) {
            moveFront(M->rows[i]);
            while (index(M->rows[i]) >= 0) {
                Entry E = (Entry)get(M->rows[i]);
                freeEntry(&E);
                moveNext(M->rows[i]);
            }
            clear(M->rows[i]); // Ensure list is fully cleared
            freeList(&(M->rows[i]));
        }
        free(M->rows);
        free(M);
        *pM = NULL;
    }
}


// Returns the size of Matrix M
int size(Matrix M) {
    return M->size;
}

// Returns the number of nonzero entries in M
int NNZ(Matrix M) {
    return M->NNZ;
}

// Compares two matrices and returns true if they are equal
bool equals(Matrix A, Matrix B) {
    if (A == B) return true;
    if (A == NULL || B == NULL || A->size != B->size) return false;

    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];

        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 && index(rowB) >= 0) {
            Entry E1 = (Entry)get(rowA);
            Entry E2 = (Entry)get(rowB);

            if (E1->col != E2->col || E1->value != E2->value) {
                return false;
            }

            moveNext(rowA);
            moveNext(rowB);
        }

        if (index(rowA) >= 0 || index(rowB) >= 0) return false;
    }
    return true;
}

// Sets M to the zero matrix
void makeZero(Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        moveFront(M->rows[i]);
        while (index(M->rows[i]) >= 0) {
            Entry E = (Entry)get(M->rows[i]);
            moveNext(M->rows[i]);
            freeEntry(&E);
        }
        clear(M->rows[i]);
    }
    M->NNZ = 0;
}

// Changes the entry at (i, j) to x
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL || i < 1 || i > M->size || j < 1 || j > M->size) {
        printf("Error: changeEntry called with invalid indices.\n");
        return;
    }
    List row = M->rows[i];
    moveFront(row);

    while (index(row) >= 0) {
        Entry E = (Entry)get(row);
        if (E->col == j) {
            if (x == 0) {
                freeEntry(&E);
                delete(row);
                M->NNZ--;
            } else {
                E->value = x;
            }
            return;
        } else if (E->col > j) break;
        moveNext(row);
    }

    if (x != 0) { // Insert new entry
        Entry newE = newEntry(j, x);
        if (index(row) < 0) { // Insert at end
            append(row, newE);
        } else { // Insert before current position
            insertBefore(row, newE);
        }
        M->NNZ++;
    }
}

// Returns a copy of Matrix A
Matrix copy(Matrix A) {
    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry E = (Entry)get(row);
            changeEntry(C, i, E->col, E->value);
            moveNext(row);
        }
    }
    return C;
}

// Returns the transpose of Matrix A
Matrix transpose(Matrix A) {
    Matrix T = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry E = (Entry)get(row);
            changeEntry(T, E->col, i, E->value);
            moveNext(row);
        }
    }
    return T;
}

// Returns the scalar multiplication of Matrix A by x
Matrix scalarMult(double x, Matrix A) {
    Matrix S = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry E = (Entry)get(row);
            changeEntry(S, i, E->col, x * E->value);
            moveNext(row);
        }
    }
    return S;
}

// Returns A + B
Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || A->size != B->size) {
        printf("Matrix sum error: invalid matrix dimensions\n");
        return NULL;
    }
    if (A == B) {
        return scalarMult(2, A);
    }
    
    Matrix S = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        moveFront(rowA);
        moveFront(rowB);
        while (index(rowA) >= 0 || index(rowB) >= 0) {
            int col;
            double sumVal = 0.0;
            
            if (index(rowA) >= 0 && index(rowB) >= 0) {
                Entry entryA = (Entry)get(rowA);
                Entry entryB = (Entry)get(rowB);
                int colA = entryA->col;
                int colB = entryB->col;
                if (colA == colB) {
                    sumVal = entryA->value + entryB->value;
                    col = colA;
                    moveNext(rowA);
                    moveNext(rowB);
                } else if (colA < colB) {
                    sumVal = entryA->value;
                    col = colA;
                    moveNext(rowA);
                } else { // colB < colA
                    sumVal = entryB->value;
                    col = colB;
                    moveNext(rowB);
                }
            } else if (index(rowA) >= 0) {
                Entry entryA = (Entry)get(rowA);
                sumVal = entryA->value;
                col = entryA->col;
                moveNext(rowA);
            } else {  // Only rowB has entries left
                Entry entryB = (Entry)get(rowB);
                sumVal = entryB->value;
                col = entryB->col;
                moveNext(rowB);
            }
            if (sumVal != 0) {
                changeEntry(S, i, col, sumVal);
            }
        }
    }
    return S;
}

// Returns A - B
Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || A->size != B->size) {
        printf("Matrix diff error: invalid matrix dimensions\n");
        return NULL;
    }
    if (A == B) {
        return newMatrix(A->size);
    }

    Matrix D = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 || index(rowB) >= 0) {
            int col;
            double newValue = 0.0;

            if (index(rowA) >= 0 && index(rowB) >= 0) {
                Entry entryA = (Entry)get(rowA);
                Entry entryB = (Entry)get(rowB);
                int colA = entryA->col;
                int colB = entryB->col;
                if (colA == colB) {
                    col = colA;
                    newValue = entryA->value - entryB->value;
                    moveNext(rowA);
                    moveNext(rowB);
                } else if (colA < colB) {
                    col = colA;
                    newValue = entryA->value;
                    moveNext(rowA);
                } else {  // colB < colA
                    col = colB;
                    newValue = -entryB->value;
                    moveNext(rowB);
                }
            } else if (index(rowA) >= 0) {
                Entry entryA = (Entry)get(rowA);
                col = entryA->col;
                newValue = entryA->value;
                moveNext(rowA);
            } else {  // Only rowB has entries left
                Entry entryB = (Entry)get(rowB);
                col = entryB->col;
                newValue = -entryB->value;
                moveNext(rowB);
            }

            // Only insert nonzero differences.
            if (newValue != 0) {
                changeEntry(D, i, col, newValue);
            }
        }
    }
    return D;
}

// Prints Matrix M
void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        List row = M->rows[i];
        if (length(row) > 0) {
            fprintf(out, "%d:", i);
            moveFront(row);
            while (index(row) >= 0) {
                Entry E = (Entry)get(row);
                fprintf(out, " (%d, %.1f)", E->col, E->value);
                moveNext(row);
            }
            fprintf(out, "\n");
        }
    }
}

Matrix product(Matrix A, Matrix B) {
    if (A->size != B->size) return NULL;
    int n = A->size;
    Matrix C = newMatrix(n);
    Matrix B_T = transpose(B);

    for (int i = 1; i <= n; i++) {
        List rowA = A->rows[i];
        if (length(rowA) == 0) continue;
        for (int j = 1; j <= n; j++) {
            List rowB_T = B_T->rows[j];
            if (length(rowB_T) == 0) continue;

            double dot = 0.0;
            moveFront(rowA);
            moveFront(rowB_T);
            while (index(rowA) >= 0 && index(rowB_T) >= 0) {
                Entry E_A = (Entry)get(rowA);
                Entry E_B = (Entry)get(rowB_T);
                if (E_A->col == E_B->col) {
                    dot += E_A->value * E_B->value;
                    moveNext(rowA);
                    moveNext(rowB_T);
                } else if (E_A->col < E_B->col) {
                    moveNext(rowA);
                } else { // E_A->col > E_B->col
                    moveNext(rowB_T);
                }
            }
            if (dot != 0) {
                changeEntry(C, i, j, dot);
            }
        }
    }

    freeMatrix(&B_T);
    return C;
}