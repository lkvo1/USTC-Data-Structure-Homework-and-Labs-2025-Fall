#include <iostream>
#include <vector>

using namespace std;

// 找出所有鞍点

void findSaddlePoints(int matrix[], int m, int n) {
    // m 行 n 列的矩阵
    
    bool found = false;  // 标记是否找到马鞍点
    
    // 遍历矩阵的每个元素
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int element = matrix[i * n + j];
            
            // 是否是行最小值
            bool min = true;
            for (int k = 0; k < n; k++) {
                if (matrix[i * n + k] < element) {
                    min = false;
                    break;
                }
            }
            if (!min) continue; // 不是的话直接跳过
            
            // 是否是列最大值
            bool max = true;
            for (int k = 0; k < m; k++) {
                if (matrix[k * n + j] > element) {
                    max = false;
                    break;
                }
            }
            
            // 两个条件都满足就是鞍点
            if (max) {
                cout << "Saddle point: matrix[" << i << "][" << j << "] = " << element << "\n";
                found = true;
            }
        }
    }
    
    if (!found) {
        cout << "No saddle points.\n";
    }
}

int main() {
    int m, n;
    cout << "Enter matrix size: m x n: ";
    cin >> m >> n;
    
    // 读取矩阵元素
    int matrix[m * n];

    cout << "Enter " << (m * n) << " elements:\n";
    for (int i = 0; i < m * n; i++) {
        cin >> matrix[i];
    }
 
    // 寻找并输出鞍点
    findSaddlePoints(matrix, m, n);
    
    return 0;
}
