#ifndef DOUBLY_CIRCULAR_LINKED_LIST_H
#define DOUBLY_CIRCULAR_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int freq; // 访问频率
    struct Node *prev;
    struct Node *next;
} Node;

// 创建链表头节点
Node *CreateList() {
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = head;
    head->prev = head;
    head->data = 0; // 用于存储链表长度
    head->freq = 0; // 用于存储访问频率
    return head;
}

void InsertNode(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->freq = 0; // 访问频率初始化为0
    newNode->prev = head->prev;
    newNode->next = head;
    head->prev->next = newNode;
    head->prev = newNode;
    head->data++; 
}

Node *LocateNode(Node* head, int data) {
    Node *cur = head->next;
    while (cur != head) {
        if (cur->data == data) {
            cur->freq++; // 更新访问频率

            // 每访问一次, 按频率对链表进行排序
            while(cur->prev != head && cur->freq > cur->prev->freq) {
                // 交换一次节点(冒泡排序)
                Node *prevNode = cur->prev;
                Node *nextNode = cur->next;
                
                nextNode->prev = prevNode;
                prevNode->next = nextNode;
                cur->prev = prevNode->prev;
                cur->next = prevNode;
                prevNode->prev->next = cur;
                prevNode->prev = cur;
            }
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void PrintList(Node* head) {
    Node* cur = head->next;
    while (cur != head) {
        printf("Data: %d, Freq: %d\n", cur->data, cur->freq);
        cur = cur->next;
    }
}

#endif // DOUBLY_CIRCULAR_LINKED_LIST_H