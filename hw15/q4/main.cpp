#include "binaryTree.h"
#include <climits>
#include <vector>

// 将二叉排序树转换为有序数组（中序遍历）
void storeInorder(TreeNode* node, std::vector<int>& nodes) {
    if (node == nullptr) return;
    storeInorder(node->left, nodes);
    nodes.push_back(node->value);
    storeInorder(node->right, nodes);
}

// 合并两个有序数组
std::vector<int> mergeSortedArrays(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    std::vector<int> merged;
    int i = 0, j = 0;
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] < arr2[j]) {
            merged.push_back(arr1[i++]);
        } else {
            merged.push_back(arr2[j++]);
        }
    }
    while (i < arr1.size()) merged.push_back(arr1[i++]);
    while (j < arr2.size()) merged.push_back(arr2[j++]);
    return merged;
}


// 标准的二叉排序树插入算法（更简单但可能不平衡）
TreeNode* insert(TreeNode* root, int val) {
    if (root == nullptr) return new TreeNode(val);
    if (val < root->value) {
        root->left = insert(root->left, val);
    } else if (val > root->value) {
        root->right = insert(root->right, val);
    }
    return root;
}

int main() {
    // 方法 1: 使用 insert 逐个构建（更简单）
    TreeNode* rootSimple = nullptr;
    std::vector<int> vals = {100, 50, 300, 20, 70, 80, 40, 120};
    for (int v : vals) {
        rootSimple = insert(rootSimple, v);
    }

    std::cout << "Simple Construction (Inorder): ";
    std::vector<int> simpleNodes;
    storeInorder(rootSimple, simpleNodes);
    for (int v : simpleNodes) std::cout << v << " ";
    std::cout << std::endl;

    // 方法 2: 合并两个已有的 BST（之前的方法）
    TreeNode* root1 = new TreeNode(100);
    root1->left = new TreeNode(50);
    root1->right = new TreeNode(300);
    // ... (省略部分手动构建代码以保持简洁)

    return 0;
}
