#ifndef CHARSTACK_H
#define CHARSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100
typedef struct Stack {
    int top; 
    char data[MAXSIZE]; 
} Stack;

Stack* createStack();
bool isFull(Stack *stack);
bool isEmpty(Stack *stack);
void push(Stack *stack, char value);
void pop(Stack *stack);
char peek(Stack *stack);

Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

bool isFull(Stack *stack) {
    return stack->top == MAXSIZE - 1;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, char value) {
    if(!isFull(stack)) {
        stack->data[stack->top + 1] = value;
        stack->top++;
    } else {
        perror("StackOverflow");
    }
}

void pop(Stack *stack) {
    if(!isEmpty(stack)) {
        stack->top--;
    } else {
        perror("Stack is Empty"); 
    }
}

char peek(Stack *stack) {
    if(!isEmpty(stack)) {
        return stack->data[stack->top];
    } else {
        perror("Stack is Empty");
        return '\0';
    }
}

int strlen(const char* str) {
    int len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;
}

char* infixToRPN(const char* infix) {
    // 将单字母变量和双目四则运算符的正常表示式转换为逆波兰表示式
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


#endif // CHARSTACK_H