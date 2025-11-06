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

#endif // CHARSTACK_H