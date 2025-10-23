#include "LinearList.h"
#include <stdio.h>

int main() {
    LinearList list1, list2;
    initList(&list1);
    initList(&list2);

    addToEnd(&list1, 10);
    addToEnd(&list1, 20);
    addToEnd(&list1, 30);
    addToEnd(&list1, 40);
    addToEnd(&list1, 50);
    addToEnd(&list1, 60);

    addToEnd(&list2, 10);
    addToEnd(&list2, 20);
    addToEnd(&list2, 30);
    addToEnd(&list2, 40);
    addToEnd(&list2, 50);
    addToEnd(&list2, 60);
    
    // deleteFrom1WhoBothAppearIn2and3(&list1, &list2, &list3);
    LinearList list3 = mergeListsByIncrease(&list1,  &list2);
    printList(&list3);
    return 0;
}