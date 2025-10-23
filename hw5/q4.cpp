#include "CircularQueue.h"
#include <iostream>
using namespace std;

int testkFib() {
	int k, max;
	cout << "k =  ";
	cin >> k;
	cout << "max = ";
	cin >> max;

	CircularQueue queue;
	initQueue(&queue);

	// 将前k项入队，均为1
	for (int i = 0; i < k; ++i) {
		enqueue(&queue, 1);
	}

    std::cout << "k-Fib: ";
	int fn = 1; // 队尾项
	while (true) {
		// 计算下一项
		int sum = 0;
		QueueNode* cur = queue.dummyHead->next;
		for (int i = 0; i < k; ++i) {
			sum += cur->data;
			cur = cur->next;
		}
		// sum为f_{n+1}
		if (fn <= max && sum > max) {
			break;
		}
		// 队列弹出最早的，加入新项
		dequeue(&queue);
        // dequeue之前输出队首的值，表示出整个数列
        cout << queue.dummyHead->next->data << ' ';
		enqueue(&queue, sum);
		fn = sum;
	}

	// 输出循环队列中的k项
	QueueNode* cur = queue.dummyHead->next;
	for (int i = 0; i < k; ++i) {
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;

	destroyQueue(&queue);
	return 0;
}
