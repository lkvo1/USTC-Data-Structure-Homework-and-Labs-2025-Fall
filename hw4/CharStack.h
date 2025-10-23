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

// 提取出一个字符串的括号部分, 并判断括号是否匹配
void matchPairs(Stack *stack, char* str) {
    if(!isEmpty(stack)) {
        perror("Stack is not empty, cannot deal.");
        return;
    }

    // 遇遇到() [] {} 就入栈, 如果匹配到了对应的反括号则Pop, 如果括号是匹配的, 那么最内层会被消掉, 进一步的外层括号也会逐层被消掉
    for(char* p = str; *p != '\0'; p++) {
        if(*p == '(' || *p == '[' || *p == '{') {
            push(stack, *p);
        } else if(*p == ')') {
            if(!isEmpty(stack) && peek(stack) == '(') {
                pop(stack);
            } else {
                printf("失败啦! ");
                return;
            }
        } else if(*p == ']') {
            if(!isEmpty(stack) && peek(stack) == '[') {
                pop(stack);
            } else {
                printf("失败啦! ");
                return;
            }
        } else if(*p == '}') {
            if(!isEmpty(stack) && peek(stack) == '{') {
                pop(stack);
            } else {
                printf("失败啦! ");
                return;
            }
        }
    }
    
    // 如果栈为空, 则说明匹配成功
    if(isEmpty(stack)) {
        printf("成功啦! ");
        return;
    } else {
        printf("失败啦! ");
    }
}
#endif // CHARSTACK_H