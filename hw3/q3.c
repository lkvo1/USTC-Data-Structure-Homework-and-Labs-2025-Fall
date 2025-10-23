#include "Stack.h"

int main() {
    Stack *stack = createStack();
    char str[] = "{[()asdasd]}";
    matchPairs(stack, str);
    return 0;
}