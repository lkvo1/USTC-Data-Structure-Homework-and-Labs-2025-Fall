#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "CircularQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct CircularQueue {
    QueueNode* dummyHead;
    QueueNode* tail;
    int size;
} CircularQueue;

// 初始化循环队列
void initQueue(CircularQueue* queue) {
    queue->dummyHead = (QueueNode*)malloc(sizeof(QueueNode));
    // 让dummyHead->next 指向自身
    queue->dummyHead->next = queue->dummyHead;
    queue->tail = queue->dummyHead;
    queue->size = 0;
}

// 入队操作
void enqueue(CircularQueue* queue, int value) {
    // 创建新的节点
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = value;

    // 将新节点插入到 tail 之后
    newNode->next = queue->dummyHead;

    if (queue->size == 0) {
        queue->dummyHead->next = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++; // 更新队列的大小
}

// 出队操作
void dequeue(CircularQueue* queue) {
    // 检测队列为空的情况
    if (queue->size == 0) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

    QueueNode* toDeleteNode = queue->dummyHead->next;
    queue->dummyHead->next = toDeleteNode->next;
    free(toDeleteNode);
    queue->size--;

    // 如果出队后队列为空，恢复到空队列初始状态
    if (queue->size == 0) {
        queue->tail = queue->dummyHead;
        queue->dummyHead->next = queue->dummyHead;
    }
}

// 销毁队列
void destroyQueue(CircularQueue* queue) {
    // 销毁所有节点
    while (queue->size > 0) {
        dequeue(queue);
    }
    // 释放dummyHead节点
    free(queue->dummyHead);
    queue->dummyHead = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

void printQueue(CircularQueue* queue) {
    QueueNode* current = queue->dummyHead->next;
    std::cout << "Queue: ";
    for (int i = 0; i < queue->size; i++) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
#endif // CIRCULARQUEUE_H