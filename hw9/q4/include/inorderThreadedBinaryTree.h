#ifndef INORDERTHREADENDBINARYTREE_H
#define INORDERTHREADENDBINARYTREE_H

#include <iostream>
#include <queue>

typedef struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    bool ltag;  // 左线索
    bool rtag;  // 右线索
    TreeNode (int val) : value(val), left(nullptr), right(nullptr), ltag(false), rtag(false) {}
} TreeNode;

#define inorderThreadAuto(root) \
    do { \
        TreeNode* pre = nullptr; \
        inorderThread(root, pre); \
    } while(0)

void inorderThread(TreeNode* root, TreeNode*& pre) {
    if (!root) return;
    inorderThread(root->left, pre);

    // 如果左子节点为空，则可以线索化
    if (!root->left) {
        root->left = pre;
        root->ltag = true;
    }

    // 如果pre不为null而且pre的右节点不为空，则可以线索化  
    if (pre && !pre->right) {
        pre->right = root;
        pre->rtag = true;
    }

    pre = root;
    // 弄好之后处理下一个
    inorderThread(root->right, pre);
}

// 使用线索中序遍历树
void printTreeUsingThread(TreeNode* root) {
    if (!root) return;
    TreeNode* curr = root;

    // 找到最左边的节点
    while (curr && !curr->ltag) {
        curr = curr->left;
    }
    
    while (curr) {
        std::cout << curr->value << " ";
        // 如果右指针是线索，直接跟随
        if (curr->rtag) {
            curr = curr->right;
        } else {
            // 如果右指针指向真实右子树，找到右子树的最左节点
            curr = curr->right;
            while (curr && !curr->ltag) {
                curr = curr->left;
            }
        }
    }
}

void insertChildTree(TreeNode* p, TreeNode* x) {
    if (!p || !x) return;

    // 如果 p 没有左子树，把x插入，然后线索化、
    if (p->ltag) {  // p 有左线索，即没有左子树
        p->left = x;
        p->ltag = false;

        // 新插入的子树 x 已经线索化，只需要处理 p 和 x 之间的线索，由于 x 只有左子树，所以 x 的最右节点是 x 本身
        x->right = p;
        x->rtag = true;
    } else if (!p->ltag && p->rtag) { // 如果 p 有左子树并且没有右子树，则把 x 插入为 p 的右子树

        TreeNode* x_mostLeft = x;
        while (x_mostLeft && !x_mostLeft->ltag) { // 找到 x 的最左节点
            x_mostLeft = x_mostLeft->left;
        }
        x_mostLeft->left = p;
        x_mostLeft->ltag = true;

        x->right = p->right;
        x->rtag = true;

        p->right = x; // 把 x 插入为 p 的右子树
        p->rtag = false;
    } else if (!p->ltag && !p->rtag) { // 如果既有左子树， 也有右子树， 那么这是不合法的
        std::cout << "Invalid Insertion" << std::endl;
    }
}

#endif // INORDERTHREADENDBINARYTREE_H