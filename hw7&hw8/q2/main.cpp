#include <iostream>

// 只使用一个temp的空间.
int temp;

void printArr(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// 翻转数组arr从index left到right的元素
void reverse(int arr[], int left, int right) {
    while(left < right) {
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

// 将数组arr[0..n-1]循环右移k个位置（只用一个元素的额外空间）
int main() {
    int n, k;
    std::cin >> n >> k;
    int arr[n];

    for(int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    k = k % n; // 防止 k > n

    std::cout << "Original array: ";
    printArr(arr, n);

    reverse(arr, 0, n-1);
    reverse(arr, 0, k-1);
    reverse(arr, k, n-1);

    std::cout << "Result array:   ";
    printArr(arr, n);
    return 0;
}