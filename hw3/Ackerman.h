#ifndef ACKERMAN_H
#define ACKERMAN_H

#include "IntStack.h"
#include <stdio.h>

int akm_recursion(int m, int n) {
    if(m == 0) {
        return n + 1;
    } else if(m != 0 && n == 0) {
        return akm_recursion(m - 1, 1);
    } else if(m != 0 && n != 0) {
        return akm_recursion(m - 1, akm_recursion(m, n - 1));
    }

    return -1;
}

int akm_human(int m, int n) {
    IntStack* s = createIntStack();
    push(s, m);

    while(!isEmpty(s)) {
        m = peek(s);
        pop(s);

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            push(s, m - 1); 
            n = 1;
        } else {
            push(s, m - 1);
            push(s, m);
            n = n - 1;
        }
    }
    return n;
}

#endif // ACKERMAN_H