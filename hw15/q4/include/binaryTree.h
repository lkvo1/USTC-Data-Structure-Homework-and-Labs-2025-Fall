#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>
#include <stack>

typedef struct TreeNode {
    int value;
    int descNum;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr), descNum(0) {}
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

    std::cout << std::endl;
}

// 递归复制树
TreeNode* recursiveCopyTree(TreeNode* src) {
    if (!src) return nullptr;
    TreeNode* dst = new TreeNode(src->value);

    dst->left = recursiveCopyTree(src->left);
    dst->right = recursiveCopyTree(src->right);

    return dst;
}

// 非递归复制树
TreeNode* nonrecursiveCopyTree(TreeNode* src) {
    if (!src) return nullptr;

    // 创建一个根节点，然后使用栈来进行非递归复制
    TreeNode* dst = new TreeNode(src->value);
    std::stack<TreeNode*> s;

    // 入栈两源节点和目标节点
    s.push(src);
    s.push(dst);

    while (!s.empty()) {
        // 每次成对弹出源节点和目标节点
        TreeNode* currentDst = s.top(); s.pop();
        TreeNode* currentSrc = s.top(); s.pop();

        // 处理当前节点的右子节点
        if (currentSrc->right) {
            currentDst->right = new TreeNode(currentSrc->right->value);
            s.push(currentSrc->right);
            s.push(currentDst->right);
        }

        // 处理当前节点的左子节点
        if (currentSrc->left) {
            currentDst->left = new TreeNode(currentSrc->left->value);
            s.push(currentSrc->left);
            s.push(currentDst->left);
        }
    }
    return dst;
}

#endif // BINARYTREE_H