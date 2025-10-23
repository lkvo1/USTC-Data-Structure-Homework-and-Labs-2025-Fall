#include "CircularQueue.h"

int testCircularQueue() {
    CircularQueue queue;
    initQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    printQueue(&queue);

    dequeue(&queue);
    printQueue(&queue);

    destroyQueue(&queue);

    return 0;
}