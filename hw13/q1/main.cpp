#include <iostream>

// 递归形式的二分查找

// 顺序数组
int arr[] = {1,2,3,4,4,5,5,5,6,6,6,6,6,6,6,7,7,7,7,8,9};

int binarySearch_recursive(int* arr, int l, int r, int target) {
    if (l > r) return -1; // 查找失败
    int mid = (l + r) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] > target) {
        return binarySearch_recursive(arr, l, mid - 1, target);
    } else {
        return binarySearch_recursive(arr, mid + 1, r, target);
    }
}

int main() {
    std::cout << binarySearch_recursive(arr, 0, sizeof(arr) / sizeof(int) - 1, 6);

    return 0;
}