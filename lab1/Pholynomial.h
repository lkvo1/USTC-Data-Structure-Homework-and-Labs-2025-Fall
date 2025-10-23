#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Node {
    float coeff;
    int power;
    struct Node *next;
} Node;

typedef struct Polynomial {
    int size;
    Node *head;
} Polynomial;

void initPolynomial(Polynomial *poly) {
    poly->size = 0;
    poly->head = (Node *)malloc(sizeof(Node));
    if (poly->head) {
        poly->head->coeff = 0;
        poly->head->power = 0;
        poly->head->next = NULL;
    }
}

bool isValidIndex(const Polynomial *poly, int index, bool allowEnd) {
    if (!poly || !poly->head) return false;
    int size = poly->size;
    if (allowEnd) {
        return index >= 0 && index <= size;
    } else {
        return index >= 0 && index < size;
    }
}

// 添加单项式到多项式中
bool addMono(Polynomial *poly, float coeff, int power) {
    if (!poly || !poly->head) {
        fprintf(stderr, "poly not initialized\n");
        return false;
    }

    if (coeff == 0) return true; // 系数为0不添加

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }

    newNode->coeff = coeff;
    newNode->power = power;

    Node *cur = poly->head;
    
    while (cur->next != NULL && cur->next->power > power) {
        cur = cur->next;
    }
    
    // 如果发现相同幂次
    if (cur->next != NULL && cur->next->power == power) {
        cur->next->coeff += coeff;
        free(newNode);
        // 如果合并后系数为0，删除该节点
        if (cur->next->coeff == 0) {
            Node *toDelete = cur->next;
            cur->next = cur->next->next;
            free(toDelete);
            poly->size--;
        }
        return true;
    }
    
    // 插入新节点
    newNode->next = cur->next;
    cur->next = newNode;
    poly->size++;
    
    return true;
}
void printPoly(Polynomial *poly) {
    if (!poly || !poly->head) {
        printf("0 \n");
        return;
    }
    
    // 打印项数
    printf("%d ", poly->size);
    // 打印其他项
    Node* curNode = poly->head->next;
    while(curNode != NULL) {
        printf("%.2f ", curNode->coeff);
        printf("%d ", curNode->power);
        curNode = curNode->next;
    }
}

Polynomial addPoly(Polynomial *poly1, Polynomial *poly2) {
    Polynomial newPoly;
    initPolynomial(&newPoly);

    Node *cur1 = poly1->head->next; 
    Node *cur2 = poly2->head->next; 

    // 将两个多项式相加, 此时cur1为指数项较大的人
    while (cur1 != NULL && cur2 != NULL) {
        if (cur1->power == cur2->power) {
            // 发现两个人指数一样, 则创建并添加新的多项式
            float newCoeff = cur1->coeff + cur2->coeff;
            if (newCoeff != 0) {  // 只有系数不为0时才添加
                addMono(&newPoly, newCoeff, cur1->power);
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        } else if (cur1->power > cur2->power) {
            addMono(&newPoly, cur1->coeff, cur1->power);
            cur1 = cur1->next;
        } else {
            addMono(&newPoly, cur2->coeff, cur2->power);
            cur2 = cur2->next;
        }
    }
    // 之后处理没有加完的家伙
    if (cur1 == NULL) {
        while (cur2 != NULL) {
            addMono(&newPoly, cur2->coeff, cur2->power);
            cur2 = cur2->next;
        }
    } else if (cur2 == NULL) {
        while (cur1 != NULL) {
            addMono(&newPoly, cur1->coeff, cur1->power);
            cur1 = cur1->next;
        }
    }

    return newPoly;
}

// 多项式减法, 返回poly1 - poly2
Polynomial subPoly(Polynomial *poly1, Polynomial *poly2) {
    Polynomial newPoly;
    initPolynomial(&newPoly);

    Node *cur1 = poly1->head->next; 
    Node *cur2 = poly2->head->next; 

    // 将两个多项式相减
    while (cur1 != NULL && cur2 != NULL) {
        if (cur1->power == cur2->power) {
            // 发现两个人指数一样, 则创建并添加新的多项式
            int newCoeff = cur1->coeff - cur2->coeff;
            if (newCoeff != 0) {  // 只有系数不为0时才添加
                addMono(&newPoly, newCoeff, cur1->power);
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        } else if (cur1->power > cur2->power) {
            addMono(&newPoly, cur1->coeff, cur1->power);
            cur1 = cur1->next;
        } else {
            addMono(&newPoly, -cur2->coeff, cur2->power); 
            cur2 = cur2->next;
        }
    }
    // 之后处理没有减完的项
    while (cur1 != NULL) {
        addMono(&newPoly, cur1->coeff, cur1->power);
        cur1 = cur1->next;
    }
    while (cur2 != NULL) {
        addMono(&newPoly, -cur2->coeff, cur2->power); 
        cur2 = cur2->next;
    }

    return newPoly;
}

float evaluatePoly(Polynomial *poly, float x) {

    float result = 0.0;
    Node *cur = poly->head->next;

    while (cur != NULL) {
        result += cur->coeff * pow(x, cur->power);
        cur = cur->next;
    }

    return result;
}

Polynomial multiplyPoly(Polynomial *poly1, Polynomial *poly2) {
    Polynomial result;
    initPolynomial(&result);

    for (Node *node1 = poly1->head->next; node1 != NULL; node1 = node1->next) {
        for (Node *node2 = poly2->head->next; node2 != NULL; node2 = node2->next) {
            float newCoeff = node1->coeff * node2->coeff;
            int newPower = node1->power + node2->power;
            addMono(&result, newCoeff, newPower);
        }
    }

    return result;
}

Polynomial differentialPoly(Polynomial *poly) {
    Polynomial result;
    initPolynomial(&result);

    for (Node *cur = poly->head->next; cur != NULL; cur = cur->next) {
        if (cur->power > 0) { // 常数项的导数为0
            float newCoeff = cur->coeff * cur->power;
            int newPower = cur->power - 1;
            addMono(&result, newCoeff, newPower);
        }
    }

    return result;
}

void printPolyHumanReadable(Polynomial *poly) {

    Node *cur = poly->head->next;
    bool firstTerm = true;

    while (cur != NULL) {
        if (cur->coeff != 0) {
            if (!firstTerm) {
                if (cur->coeff > 0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                }
            } else {
                if (cur->coeff < 0) {
                    printf("-");
                }
                firstTerm = false;
            }

            float coeff_abs = fabs(cur->coeff);
            if (coeff_abs != 1 || cur->power == 0) {
                printf("%.2f", coeff_abs);
            }
            if (cur->power > 0) {
                printf("x");
                if (cur->power > 1) {
                    printf("^%d", cur->power);
                }
            }
        }
        cur = cur->next;
    }
    printf("\n");
}
#endif // POLYNOMIAL_H