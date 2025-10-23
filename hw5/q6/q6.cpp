#include "BlockListString.h"

int main() {
    BString s;
    BString t;
    initBString(&s);
    initBString(&t);

    // Example usage: assign values, concatenate, and print
    assignBString(&s, "Hello, ");
    assignBString(&t, "world!");

    printBString(&s);
    printBString(&t);
    
    insertAfterChar(&t, &s, 'l');
    printBString(&t);
    // insertAfterChar();
    return 0;
}