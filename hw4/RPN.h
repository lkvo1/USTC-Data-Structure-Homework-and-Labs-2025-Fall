#ifndef RPN_H
#define RPN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CharStack.h"

int strlen(const char* str) {
    int len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;
}


char* infixToRPN(const char* infix) {
    // 将单字母变量和双目四则运算符的正常表示式转换为逆波兰表示式
    // 使用CharStack.h中的栈
    Stack* stack = createStack();
    char *output = (char*)malloc(strlen(infix) + 1);
    int j = 0;
    for(int i = 0; infix[i] != '\0'; i++) {
        if(int(infix[i]) >= int('a') && int(infix[i] <= int('z'))) {
            output[j++] = infix[i];
        } else if(infix[i] == '(') {
            push(stack, infix[i]);
        } else if(infix[i] == ')') {
            while(!isEmpty(stack) && peek(stack) != '(') {
                output[j++] = peek(stack);
                pop(stack);
            }
            pop(stack); // 弹出左括号
        } else { // 如果是运算符
            if(infix[i] == '+' || infix[i] == '-') {
                while(!isEmpty(stack) && peek(stack) != '(') {
                    output[j++] = peek(stack);
                    pop(stack);
                }
                push(stack, infix[i]);
            } else if(infix[i] == '*' || infix[i] == '/') {
                while(!isEmpty(stack) && peek(stack) != '(' && peek(stack) != '+' && peek(stack) != '-') {
                    output[j++] = peek(stack);
                    pop(stack);
                }
                push(stack, infix[i]);
            }
        }
    }
    while(!isEmpty(stack)) {
        output[j++] = peek(stack);
        pop(stack);
    }
    output[j] = '\0';
    return output;
}

// 计算逆波兰表示式，values数组存储变量a-z的值
float calculateRPN(char* rpn, float* values) {
    int j = 0;
    float *result = (float*)malloc(strlen(rpn) * sizeof(float)); // 用数组模拟栈
    char *p = rpn; // p指向rpn的开头
    while(*p != '\0') {
        if(int(*p) >= int('a') && int(*p) <= int('z')) {
            result[j++] = values[int(*p) - int('a')]; // 如果是变量就入栈
        } else {
            float op2 = result[--j];
            float op1 = result[--j];
            switch(*p) {
                case '+':
                    result[j++] = op1 + op2;
                    break;
                case '-':
                    result[j++] = op1 - op2;
                    break;
                case '*':
                    result[j++] = op1 * op2;
                    break;
                case '/':
                    result[j++] = op1 / op2;
                    break;
            }
        }
        p++;
    }
    return result[0];
}

#endif // RPN_H