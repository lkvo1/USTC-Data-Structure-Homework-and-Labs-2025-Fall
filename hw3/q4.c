#include "Ackerman.h"

int main() {
    for(int m = 0; m <= 3; m++) {
        for(int n = 0; n <= 10; n++) {
            printf("re: A(%d, %d) = %d\n", m, n, akm_recursion(m, n));
            printf("hu: A(%d, %d) = %d\n", m, n, akm_human(m, n));
        }
    }

    return 0;
}