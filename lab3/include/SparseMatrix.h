#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
/*
Process:
init -> assign -> +/-

initSparseMatrix will make an empty sparse matrix.
assignMatrix fill the matrix by inputing a two dimensional array to assign.
+ and - overload will return a two dimensional array as result.
*/

#include <iostream>

typedef struct OLNode {
    int row, col;
    int value;
    struct OLNode *right = nullptr, *down = nullptr;
    OLNode(int r, int c): row(r), col(c) {}
} OLNode;

typedef struct SparseMatrix {
    OLNode *rowHead, *colHead;
    int rows, cols;
    int numNonZero;
} SparseMatrix;

void initSparseMatrix(SparseMatrix &matrix, int rows, int cols);
void assignMatrix(SparseMatrix &matrix, int** data, int numNonZero);
// int** operator+(const SparseMatrix &a, const SparseMatrix &b);
// int** operator-(const SparseMatrix &a, const SparseMatrix &b);
// void printMatrix(int** matrix, int rows, int cols);
void printMatrix(SparseMatrix matrix, int rows, int cols, bool withoutZeros = false);
SparseMatrix operator+(const SparseMatrix &a, const SparseMatrix &b);
SparseMatrix operator-(const SparseMatrix &a, const SparseMatrix &b);
#endif // SPARSE_MATRIX_H