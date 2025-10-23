#ifndef INTSTACK_H
#define INTSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10000
typedef struct IntStack {
    int top; 
    int data[MAXSIZE]; 
} IntStack;

IntStack* createIntStack();
bool isFull(IntStack *stack);
bool isEmpty(IntStack *stack);
void push(IntStack *stack, int value);
void pop(IntStack *stack);
int peek(IntStack *stack);

IntStack* createIntStack() {
    IntStack *stack = (IntStack*)malloc(sizeof(IntStack));
    stack->top = -1;
    return stack;
}

bool isFull(IntStack *stack) {
    return stack->top == MAXSIZE - 1;
}

bool isEmpty(IntStack *stack) {
    return stack->top == -1;
}

void push(IntStack *stack, int value) {
    if(!isFull(stack)) {
        stack->data[stack->top + 1] = value;
        stack->top++;
    } else {
        perror("StackOverflow");
    }
}

void pop(IntStack *stack) {
    if(!isEmpty(stack)) {
        stack->top--;
    } else {
        perror("Stack is Empty"); 
    }
}

int peek(IntStack *stack) {
    if(!isEmpty(stack)) {
        return stack->data[stack->top];
    } else {
        perror("Stack is Empty");
        return '\0';
    }
}

#endif // STACK_H