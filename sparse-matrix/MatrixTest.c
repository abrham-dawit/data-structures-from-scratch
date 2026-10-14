// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa4
// MatrixTest.c
// Test client for the Matrix ADT

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main() {
    printf("Running MatrixTest...\n\n");

    // Create a new 5x5 matrix
    Matrix A = newMatrix(5);
    Matrix B = newMatrix(5);
    
    // Populate A and B
    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 2, 2.0);
    changeEntry(A, 2, 3, 3.0);
    changeEntry(A, 3, 4, 4.0);
    changeEntry(A, 4, 5, 5.0);
    changeEntry(A, 5, 1, 6.0);

    changeEntry(B, 1, 1, 7.0);
    changeEntry(B, 2, 2, 8.0);
    changeEntry(B, 3, 3, 9.0);
    changeEntry(B, 4, 4, 10.0);
    changeEntry(B, 5, 5, 11.0);

    // Print matrices
    printf("Matrix A:\n");
    printMatrix(stdout, A);
    printf("\nMatrix B:\n");
    printMatrix(stdout, B);

    // Test scalar multiplication
    Matrix C = scalarMult(2.0, A);
    printf("\n2 * A:\n");
    printMatrix(stdout, C);

    // Test transpose
    Matrix T = transpose(A);
    printf("\nTranspose of A:\n");
    printMatrix(stdout, T);

    // Test sum
    Matrix S = sum(A, B);
    printf("\nA + B:\n");
    printMatrix(stdout, S);

    // Test equality
    printf("\nA == A? %s\n", equals(A, A) ? "true" : "false");
    printf("A == B? %s\n", equals(A, B) ? "true" : "false");

    // Test makeZero
    makeZero(A);
    printf("\nA after makeZero():\n");
    printMatrix(stdout, A);

    // Free memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&T);
    freeMatrix(&S);

    printf("\nMatrixTest completed successfully!\n");

    return 0;
}
