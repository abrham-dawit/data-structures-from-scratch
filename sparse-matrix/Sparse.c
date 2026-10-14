// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa4
// Sparse.c
// A program that reads two matrices from a file, performs operations, and prints the results.

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file for reading
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for reading.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file for writing
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for writing.\n", argv[2]);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    int n, a, b;
    // Read matrix size and the number of nonzero entries for A and B
    fscanf(in, "%d %d %d", &n, &a, &b);

    // Create matrices A and B
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // Read and populate Matrix A
    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    // Read and populate Matrix B
    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(in, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    // Print matrices A and B
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    // Scalar multiplication: 1.5 * A
    Matrix scalarA = scalarMult(1.5, A);
    fprintf(out, "(1.5) * A =\n");
    printMatrix(out, scalarA);
    fprintf(out, "\n");

    // Sum: A + B
    Matrix sumAB = sum(A, B);
    fprintf(out, "A + B =\n");
    printMatrix(out, sumAB);
    fprintf(out, "\n");

    // Sum: A + A
    Matrix sumAA = sum(A, A);
    fprintf(out, "A + A =\n");
    printMatrix(out, sumAA);
    fprintf(out, "\n");

    // Difference: B - A
    Matrix diffBA = diff(B, A);
    fprintf(out, "B - A =\n");
    printMatrix(out, diffBA);
    fprintf(out, "\n");

    // Difference: A - A 
    Matrix diffAA = diff(A, A);
    fprintf(out, "A - A =\n");
    printMatrix(out, diffAA);
    fprintf(out, "\n");

    // Transpose of A
    Matrix transposeA = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, transposeA);
    fprintf(out, "\n");

    // Product: A * B
    Matrix productAB = product(A, B);
    fprintf(out, "A * B =\n");
    printMatrix(out, productAB);
    fprintf(out, "\n");

    // Product: B*B
    Matrix productBB = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, productBB);
    fprintf(out, "\n");

    // Free allocated memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalarA);
    freeMatrix(&sumAB);
    freeMatrix(&sumAA);
    freeMatrix(&diffBA);
    freeMatrix(&diffAA);
    freeMatrix(&transposeA);
    freeMatrix(&productAB);
    freeMatrix(&productBB);

    // Close files
    fclose(in);
    fclose(out);

    return 0;
}
