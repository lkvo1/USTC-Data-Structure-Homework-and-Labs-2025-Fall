#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

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
void initQueue(CircularQueue* queue);

// 入队操作
void enqueue(CircularQueue* queue, int value);

// 出队操作
void dequeue(CircularQueue* queue);
// 销毁队列
void destroyQueue(CircularQueue* queue);

void printQueue(CircularQueue* queue);
#endif // CIRCULARQUEUE_H