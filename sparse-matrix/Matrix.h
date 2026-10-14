// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa4
// Matrix.h
// Header file for the Matrix ADT

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include "List.h"  // Using List ADT for sparse matrix representation

// Define types
typedef struct MatrixObj* Matrix;

// Constructors-Destructors
Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);

// Access functions
int size(Matrix M);
int NNZ(Matrix M);  // Number of non-zero entries
bool equals(Matrix A, Matrix B);

// Manipulation procedures
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);

// Other operations
void printMatrix(FILE* out, Matrix M);

#endif