#ifndef TREE_H
#define TREE_H

#include <iostream>

// 兄弟-孩子链表
typedef struct TreeNode {
    char data;
    struct TreeNode* firstChild;
    struct TreeNode* nextSibling;
    TreeNode(char d) : data(d), firstChild(nullptr), nextSibling(nullptr) {}
} TreeNode;

TreeNode* createNode(char data) {
    return new TreeNode(data);
}

// 添加孩子节点（添加到最后）
void addChild(TreeNode* parent, TreeNode* child) {
    if (parent == nullptr || child == nullptr) return;
    
    if (parent->firstChild == nullptr) {
        // 如果没有孩子，设为第一个孩子
        parent->firstChild = child;
    } else {
        // 否则找到最后一个孩子添加为兄弟
        TreeNode* sibling = parent->firstChild;
        while (sibling->nextSibling != nullptr) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = child;
    }
}

// 以凹入表形式打印树
void printRecessedTable(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }

    std::cout << root->data << std::endl;
    
    printRecessedTable(root->firstChild, depth + 1);
    printRecessedTable(root->nextSibling, depth);
}

#endif // TREE_H