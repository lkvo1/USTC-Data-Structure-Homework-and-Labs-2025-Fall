#include "DoublyCircularLinkedList.h"

int main() {
    Node* list = CreateList();
    InsertNode(list, 10);
    InsertNode(list, 20);
    InsertNode(list, 30);
    InsertNode(list, 40);
    InsertNode(list, 50);
    InsertNode(list, 60);

    LocateNode(list, 30);
    LocateNode(list, 20);
    LocateNode(list, 20);
    LocateNode(list, 50);
    LocateNode(list, 50);
    LocateNode(list, 50);

    PrintList(list);

    return 0;
}