#include "LinearList.h"
#include <stdio.h>

int main() {
    LinearList list1, list2, list3;
    initList(&list1);
    initList(&list2);
    initList(&list3);

    addToEnd(&list1, 10);
    addToEnd(&list1, 20);
    addToEnd(&list1, 30);
    addToEnd(&list1, 40);
    addToEnd(&list1, 50);

    addToEnd(&list2, 10);
    addToEnd(&list2, 20);
    addToEnd(&list2, 30);
    addToEnd(&list2, 40);
    addToEnd(&list2, 50);
    
    addToEnd(&list3, 10);
    addToEnd(&list3, 25);
    addToEnd(&list3, 35);
    addToEnd(&list3, 40);

    deleteFrom1WhoBothAppearIn2and3(&list1, &list2, &list3);
    printList(&list1);
    return 0;
}