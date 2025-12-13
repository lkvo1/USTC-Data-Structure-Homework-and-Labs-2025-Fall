#include <iostream>
#include "SparseMatrix.h"

// 初始化稀疏矩阵
void initSparseMatrix(SparseMatrix &matrix, int rows, int cols) {
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.numNonZero = 0;
    matrix.rowHead = new OLNode(0, 0);
    matrix.colHead = new OLNode(0, 0);
}

void addNodeAtRowEnd(OLNode *head, OLNode *newNode) {
    OLNode* current = head;
    while (current->right != nullptr) {
        current = current->right;
    }
    current->right = newNode;
}

void addNodeAtColEnd(OLNode *head, OLNode *newNode) {
    OLNode* current = head;
    while (current->down != nullptr) {
        current = current->down;
    }
    current->down = newNode;
}

void assignMatrix(SparseMatrix &matrix, int** data, int numNonZero) {
    matrix.numNonZero = numNonZero;
    // 如果找到新的非0元素，第一种情况是上一个元素在同一行，第二种情况是新的一行
    OLNode* lastNonNullRowHead = nullptr;
    OLNode* lastNonZeroNode = nullptr;
    OLNode* currentRowHead = nullptr;
    
    for (int i = 0; i < matrix.rows; i++) {
        currentRowHead = nullptr;  // 每行开始时重置当前行头
        
        for(int j = 0; j < matrix.cols; j++) {
            if (data[i][j] != 0) {
                // 创建新节点
                OLNode* newNode = new OLNode(i, j);
                newNode->value = data[i][j];
                newNode->right = nullptr;
                newNode->down = nullptr;
                
                // 如果是当前行的第一个非零元素
                if (currentRowHead == nullptr) {
                    currentRowHead = newNode;
                    
                    // 如果有上一个非全零行，将上一行的头结点的down指向当前行头
                    if (lastNonNullRowHead != nullptr) {
                        lastNonNullRowHead->down = newNode;
                    } else {
                        // 如果这是第一个非全零的行
                        matrix.rowHead = newNode;
                    }
                    
                    lastNonNullRowHead = newNode;  // 更新上一个非全零行的头结点
                } else {
                    // 如果是同一行的后续元素
                    lastNonZeroNode->right = newNode;
                }
                
                lastNonZeroNode = newNode;  // 更新最后一个非零节点
            }
        }
    }
}

SparseMatrix operator+(const SparseMatrix &a, const SparseMatrix &b) {
    SparseMatrix result;
    initSparseMatrix(result, a.rows, a.cols);
    if (a.cols != b.cols || a.rows != b.rows) {
        std::cout << "Dimension not match." << std::endl;
        return result;
    }
    
    // 创建临时的二维数组来存储结果
    int** tempResult = new int*[a.rows];
    for (int i = 0; i < a.rows; i++) {
        tempResult[i] = new int[a.cols];
        for (int j = 0; j < a.cols; j++) {
            tempResult[i][j] = 0;
        }
    }
    
    // 遍历矩阵a，将非零元素加入结果
    OLNode* rowNodeA = a.rowHead;
    while (rowNodeA != nullptr) {
        OLNode* colNode = rowNodeA;
        while (colNode != nullptr) {
            tempResult[colNode->row][colNode->col] += colNode->value;
            colNode = colNode->right;
        }
        rowNodeA = rowNodeA->down;
    }
    
    // 遍历矩阵b，将非零元素加入结果
    OLNode* rowNodeB = b.rowHead;
    while (rowNodeB != nullptr) {
        OLNode* colNode = rowNodeB;
        while (colNode != nullptr) {
            tempResult[colNode->row][colNode->col] += colNode->value;
            colNode = colNode->right;
        }
        rowNodeB = rowNodeB->down;
    }
    
    // 计算非零元素个数
    int numNonZero = 0;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (tempResult[i][j] != 0) {
                numNonZero++;
            }
        }
    }
    
    // 使用assignMatrix函数构建结果稀疏矩阵
    assignMatrix(result, tempResult, numNonZero);
    
    // 释放临时数组
    for (int i = 0; i < a.rows; i++) {
        delete[] tempResult[i];
    }
    delete[] tempResult;
    
    return result;
}

SparseMatrix operator-(const SparseMatrix &a, const SparseMatrix &b) {
    SparseMatrix result;
    initSparseMatrix(result, a.rows, a.cols);
    if (a.cols != b.cols || a.rows != b.rows) {
        std::cout << "Dimension not match." << std::endl;
        return result;
    }
    
    // 创建临时的二维数组来存储结果
    int** tempResult = new int*[a.rows];
    for (int i = 0; i < a.rows; i++) {
        tempResult[i] = new int[a.cols];
        for (int j = 0; j < a.cols; j++) {
            tempResult[i][j] = 0;
        }
    }
    
    // 遍历矩阵a，将非零元素加入结果
    OLNode* rowNodeA = a.rowHead;
    while (rowNodeA != nullptr) {
        OLNode* colNode = rowNodeA;
        while (colNode != nullptr) {
            tempResult[colNode->row][colNode->col] += colNode->value;
            colNode = colNode->right;
        }
        rowNodeA = rowNodeA->down;
    }
    
    // 遍历矩阵b，将非零元素减去
    OLNode* rowNodeB = b.rowHead;
    while (rowNodeB != nullptr) {
        OLNode* colNode = rowNodeB;
        while (colNode != nullptr) {
            tempResult[colNode->row][colNode->col] -= colNode->value;
            colNode = colNode->right;
        }
        rowNodeB = rowNodeB->down;
    }
    
    // 计算非零元素个数
    int numNonZero = 0;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (tempResult[i][j] != 0) {
                numNonZero++;
            }
        }
    }
    
    // 使用assignMatrix函数构建结果稀疏矩阵
    assignMatrix(result, tempResult, numNonZero);
    
    // 释放临时数组
    for (int i = 0; i < a.rows; i++) {
        delete[] tempResult[i];
    }
    delete[] tempResult;
    
    return result;
}

void printMatrix(SparseMatrix matrix, int rows, int cols, bool withoutZeros) {
    // 创建临时数组来存储矩阵
    int** tempMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        tempMatrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            tempMatrix[i][j] = 0;
        }
    }
    
    // 遍历稀疏矩阵，填充临时数组
    OLNode* rowNode = matrix.rowHead;
    while (rowNode != nullptr) {
        OLNode* colNode = rowNode;
        while (colNode != nullptr) {
            tempMatrix[colNode->row][colNode->col] = colNode->value;
            colNode = colNode->right;
        }
        rowNode = rowNode->down;
    }
    
    // 打印矩阵
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (tempMatrix[i][j] != 0) {
                std::cout << '\t' << tempMatrix[i][j] << " ";
            } else {
                if (withoutZeros) {
                    std::cout << '\t' << " ";
                } else {
                    std::cout << '\t' << 0 << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    
    // 释放临时数组
    for (int i = 0; i < rows; i++) {
        delete[] tempMatrix[i];
    }
    delete[] tempMatrix;
}

// int** operator+(const SparseMatrix &a, const SparseMatrix &b) {
//     if (a.rows != b.rows || a.cols != b.cols) {
//         std::cout << "Matrix dimensions not match." << std::endl;
//         return nullptr;
//     }
//
//     int** result = new int*[a.rows];
//     for (int i = 0; i < a.rows; i++) {
//         result[i] = new int[a.cols];
//         for (int j = 0; j < a.cols; j++) {
//             result[i][j] = 0;
//         }
//     }
//
//     // 添加矩阵a和矩阵b的所有元素
//     for (int i = 0; i < a.rows; i++) {
//         OLNode* current = a.rowHead[i];
//         while (current != nullptr) {
//             result[current->row][current->col] += current->value;
//             current = current->right;
//         }
//     }
//     for (int i = 0; i < b.rows; i++) {
//         OLNode* current = b.rowHead[i];
//         while (current != nullptr) {
//             result[current->row][current->col] += current->value;
//             current = current->right;
//         }
//     }
//
//     return result;
// }

// int** operator-(const SparseMatrix &a, const SparseMatrix &b) {
//     if (a.rows != b.rows || a.cols != b.cols) {
//         std::cout << "Matrix dimensions not match." << std::endl;
//         return nullptr;
//     }
//
//     int** result = new int*[a.rows];
//     for (int i = 0; i < a.rows; i++) {
//         result[i] = new int[a.cols];
//         for (int j = 0; j < a.cols; j++) {
//             result[i][j] = 0;
//         }
//     }
//
//     // 添加矩阵a的元素并减去矩阵b的元素
//     for (int i = 0; i < a.rows; i++) {
//         OLNode* current = a.rowHead[i];
//         while (current != nullptr) {
//             result[current->row][current->col] += current->value;
//             current = current->right;
//         }
//     }
//     for (int i = 0; i < b.rows; i++) {
//         OLNode* current = b.rowHead[i];
//         while (current != nullptr) {
//             result[current->row][current->col] -= current->value;
//             current = current->right;
//         }
//     }
//
//     return result;
// }

// void printMatrix(int** matrix, int rows, int cols) {
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             std::cout << '\t' << matrix[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }