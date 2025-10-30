#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>

typedef struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
} TreeNode;

void deleteTree(TreeNode* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

// 删除特定值的节点的子树
void deleteChildTreesWithSpecifiedValue(TreeNode* root, int value) {
    if (!root) return;

    // 判断当前节点是否匹配
    if (root->value == value) {
        // 删除左子树(如果存在的话)
        if (root->left) {
            deleteTree(root->left);
            root->left = nullptr;
        }

        // 删除右子树(如果存在的话)
        if (root->right) {
            deleteTree(root->right);
            root->right = nullptr;
        }
    } else {
        deleteChildTreesWithSpecifiedValue(root->left, value);
        deleteChildTreesWithSpecifiedValue(root->right, value);
    }
}

void preorderPrintTree(TreeNode* root) {
    if (!root) return;
    std::cout << root->value << " ";
    preorderPrintTree(root->left);
    preorderPrintTree(root->right);
}

// 按层序遍历树
void levelOrderPrintTree(TreeNode* root) {
    if (!root) return;

    // 创建一个队列用于存储先后各个节点，首先把根节点推进去
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        // 按照层序遍历顺序，子节点应该在父节点之后，使用队列先进先出的性质
        if (q.front()->left) q.push(q.front()->left);   // 左节点入队
        if (q.front()->right) q.push(q.front()->right); // 右节点入队
        
        // 打印队首节点的值
        std::cout << q.front()->value << ' ';
        // 弹出队首节点
        q.pop();
    }
}

#endif // BINARYTREE_H