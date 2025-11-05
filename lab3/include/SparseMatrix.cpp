#include <iostream>
#include "SparseMatrix.h"

// 初始化稀疏矩阵
void initSparseMatrix(SparseMatrix &matrix, int rows, int cols) {
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.numNonZero = 0;
    matrix.rowHead = new OLNode*[rows];
    matrix.colHead = new OLNode*[cols];
    for (int i = 0; i < rows; i++) {
        matrix.rowHead[i] = nullptr;
    }
    for (int j = 0; j < cols; j++) {
        matrix.colHead[j] = nullptr;
    }
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
    for (int i = 0; i < matrix.rows; i++) {
        for(int j = 0; j < matrix.cols; j++) {
            if (data[i][j] != 0) {
                // 创建新节点
                OLNode* newNode = new OLNode();
                newNode->row = i;
                newNode->col = j;
                newNode->value = data[i][j];
                newNode->right = nullptr;
                newNode->down = nullptr;

                // 插入行链表
                if(matrix.rowHead[i] == nullptr) {
                    matrix.rowHead[i] = newNode;
                } else {
                    addNodeAtRowEnd(matrix.rowHead[i], newNode);
                }

                // 插入列链表
                if(matrix.colHead[j] == nullptr) {
                    matrix.colHead[j] = newNode;
                } else {
                    addNodeAtColEnd(matrix.colHead[j], newNode);
                }
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
    // 行遍历矩阵a和矩阵b的所有元素来构造行链表
    OLNode* curA;
    OLNode* curB;

    for (int i = 0; i < a.rows; i++) {
        curA = a.rowHead[i];
        curB = b.rowHead[i];
        while (curA != nullptr && curB != nullptr) {
            if (curA->col == curB->col) {
                OLNode* newNode = new OLNode();
                newNode->row = curA->row;
                newNode->col = curA->col;
                newNode->value = curA->value + curB->value;

                // 插入行链表
                if (newNode->value != 0) {
                    if (result.rowHead[i] == nullptr) {
                        result.rowHead[i] = newNode;
                    } else {
                        addNodeAtRowEnd(result.rowHead[i], newNode);
                    }
                // 插入列链表
                    if (result.colHead[newNode->col] == nullptr) {
                        result.colHead[newNode->col] = newNode;
                    } else {
                        addNodeAtColEnd(result.colHead[newNode->col], newNode);
                    }
                } else {
                    delete(newNode);
                }

                curA = curA->right;
                curB = curB->right;
            } else if (curA->col < curB->col) {
                OLNode* newNode = new OLNode();
                newNode->row = curA->row;
                newNode->col = curA->col;
                newNode->value = curA->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curA = curA->right;
            } else if (curA->col > curB->col) {
                OLNode* newNode = new OLNode();
                newNode->row = curB->row;
                newNode->col = curB->col;
                newNode->value = curB->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curB = curB->right;
            }
        }

        // 如果还有剩余节点，再进行处理
        if (curA != nullptr) {
            while (curA != nullptr) {
                OLNode* newNode = new OLNode();
                newNode->row = curA->row;
                newNode->col = curA->col;
                newNode->value = curA->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curA = curA->right;
            }
        }

        if (curB != nullptr) {
            while (curB != nullptr) {
                OLNode* newNode = new OLNode();
                newNode->row = curB->row;
                newNode->col = curB->col;
                newNode->value = curB->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curB = curB->right;
            }
        }
    }

    return result;
}

SparseMatrix operator-(const SparseMatrix &a, const SparseMatrix &b) {
    SparseMatrix result;
    initSparseMatrix(result, a.rows, a.cols);
    if (a.cols != b.cols || a.rows != b.rows) {
            std::cout << "Dimension not match." << std::endl;
            return result;
    }
    // 行遍历矩阵a和矩阵b的所有元素来构造行链表
    OLNode* curA;
    OLNode* curB;

    for (int i = 0; i < a.rows; i++) {
        curA = a.rowHead[i];
        curB = b.rowHead[i];
        while (curA != nullptr && curB != nullptr) {
            if (curA->col == curB->col) {
                OLNode* newNode = new OLNode();
                newNode->row = curA->row;
                newNode->col = curA->col;
                newNode->value = curA->value - curB->value;

                // 插入行链表
                if (newNode->value != 0) {
                    if (result.rowHead[i] == nullptr) {
                        result.rowHead[i] = newNode;
                    } else {
                        addNodeAtRowEnd(result.rowHead[i], newNode);
                    }
                // 插入列链表
                    if (result.colHead[newNode->col] == nullptr) {
                        result.colHead[newNode->col] = newNode;
                    } else {
                        addNodeAtColEnd(result.colHead[newNode->col], newNode);
                    }
                } else {
                    delete(newNode);
                }

                curA = curA->right;
                curB = curB->right;
            } else if (curA->col < curB->col) {
                OLNode* newNode = new OLNode();
                newNode->row = curA->row;
                newNode->col = curA->col;
                newNode->value = curA->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curA = curA->right;
            } else if (curA->col > curB->col) {
                OLNode* newNode = new OLNode();
                newNode->row = curB->row;
                newNode->col = curB->col;
                newNode->value = -1 * curB->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curB = curB->right;
            }
        }

        // 如果还有剩余节点，再进行处理
        if (curA != nullptr) {
            while (curA != nullptr) {
                OLNode* newNode = new OLNode();
                newNode->row = curA->row;
                newNode->col = curA->col;
                newNode->value = curA->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curA = curA->right;
            }
        }

        if (curB != nullptr) {
            while (curB != nullptr) {
                OLNode* newNode = new OLNode();
                newNode->row = curB->row;
                newNode->col = curB->col;
                newNode->value = -1 * curB->value;
                // 插入行链表
                if (result.rowHead[newNode->row] == nullptr) {
                    result.rowHead[newNode->row] = newNode;
                } else {
                    addNodeAtRowEnd(result.rowHead[newNode->row], newNode);
                }
                // 插入列链表
                if (result.colHead[newNode->col] == nullptr) {
                    result.colHead[newNode->col] = newNode;
                } else {
                    addNodeAtColEnd(result.colHead[newNode->col], newNode);
                }
                curB = curB->right;
            }
        }
    }

    return result;
}

void printMatrix(SparseMatrix matrix, int rows, int cols, bool withoutZeros) {
    for (int i = 0; i < rows; i++) {
        OLNode* current = matrix.rowHead[i];
        int currentCol = 0;
        for (int j = 0; j < cols; j++) {
            if (current != nullptr && current->col == j) {
                std::cout << '\t' << current->value << " ";
                current = current->right;
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