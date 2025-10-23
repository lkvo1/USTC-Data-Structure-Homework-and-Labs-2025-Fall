#include <stdio.h>

int fib (int k, int m) {
    if (m < k - 1) return 0;
    if (m == k - 1) return 1;
    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += fib(k, m - 1 - i);
    }
    return sum;
}

int main() {
    int k = 2;
    int m = 3;
    printf("%d\n", fib(k, m));
    return 0;
}