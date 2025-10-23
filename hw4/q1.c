#include "RPN.h"

int main() {
    const char* infix = "a+b*c-d/e";
    char* rpn = infixToRPN(infix);
    printf("%s\n", infix);
    printf("%s\n", rpn);
    float values[26] = {5, 3, 4, 10, 2}; // a=5, b=3, c=4, d=10, e=2
    printf("%.2f\n", calculateRPN(rpn, values)); // 12.00
    
    return 0;
}