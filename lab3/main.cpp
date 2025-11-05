#include "SparseMatrix.h"

int main() {
    SparseMatrix matA, matB, matC;
    initSparseMatrix(matA, 3, 5);
    initSparseMatrix(matB, 3, 5);
    initSparseMatrix(matC, 5, 7);

    assignMatrix(matA, new int*[3] {
        new int[5]{0, 0, 3, 0, 4},
        new int[5]{0, 0, 5, 7, 0},
        new int[5]{0, 0, 0, 0, 0}
    }, 4);

    assignMatrix(matB, new int*[3] {
        new int[5]{0, 2, -3, 0, 0},
        new int[5]{0, 0, 0, 3, 0},
        new int[5]{0, 1, 4, 0, 5}
    }, 6);

    assignMatrix(matC, new int*[5] {
        new int[7]{0, 0, 0, 0, 0, 0, 0},
        new int[7]{0, 0, 0, 0, 0, 0, 0},
        new int[7]{0, 0, 0, 0, 0, 0, 0},
        new int[7]{0, 0, 0, 0, 0, 0, 0},
        new int[7]{0, 0, 0, 0, 0, 0, 6}
    }, 1);

    printf("Matrix A:\n");
    printMatrix(matA, matA.rows, matA.cols);
    printf("Matrix B:\n");
    printMatrix(matB, matB.rows, matB.cols);
    printf("Matrix C:\n");
    printMatrix(matC, matC.rows, matC.cols);

    SparseMatrix resultAdd = matA + matB;
    SparseMatrix resultSub = matA - matB;

    SparseMatrix resultError0 = matA + matC;
    SparseMatrix resultError1 = matA - matC;

    std::cout << "A + B =" << std::endl;
    printMatrix(resultAdd, matA.rows, matA.cols, true);
    std::cout << "A - B =" << std::endl;
    printMatrix(resultSub, matA.rows, matA.cols, true);

    return 0;
}