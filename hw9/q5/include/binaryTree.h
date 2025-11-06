#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>
#include <stack>
#include "charStack.h"

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

// 中缀表示式转换为算术表示树
TreeNode* infixToArithmeticTree(const char* infix) {
    char* rpn = infixToRPN(infix);
    std::stack<TreeNode*> s;
    TreeNode* root = new TreeNode(rpn[strlen(rpn) - 1]); // 根节点先创建一个空节点
    s.push(root); // 根节点入栈
    // 从后到前遍历来构造树（先进后出） 按照 根-右-左 的顺序
    // 如果是变量，为栈顶的节点的叶节点。如果栈顶节点有两个叶节点，则弹出栈顶节点
    for (int i = strlen(rpn) - 2; i >= 0; i--) {
        if (rpn[i] >= 'a' && rpn[i] <= 'z') {
            TreeNode* newNode = new TreeNode(rpn[i]);
            if (!s.top()->right) s.top()->right = newNode; // 如果右边没东西，那么填到右边
            else {
                s.top()->left = newNode; // 否则填到左边
                s.pop(); // 填完左边之后弹出栈顶节点
            }
        } else { // 如果是运算符，填到栈顶节点的叶节点，然后把这个运算符入栈
            TreeNode* newNode = new TreeNode(rpn[i]);
            if (!s.top()->right) s.top()->right = newNode; // 如果右边没东西，那么填到右边
            else s.top()->left = newNode; // 否则填到左边
            s.push(newNode); // 然后把运算符入栈
        }
    }
    return root;
}

// 获取运算符优先级
int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0; // 不是运算符
}

std::string arithmeticTreeToInfix(TreeNode* root) {
    if (!root) return "";
    // 叶节点直接返回其值
    if (!root->left && !root->right) {
        return std::string(1, char(root->value));
    }

    // 递归获取左右子树的中缀表达式
    std::string leftStr = arithmeticTreeToInfix(root->left);
    std::string rightStr = arithmeticTreeToInfix(root->right);

    int rootPrec = getPrecedence(root->value);

    // 检查左子树是否需要加括号
    if (root->left) {
        int leftPrec = getPrecedence(root->left->value);
        // 如果父节点的优先级大于左子节点，则需要加括号
        if (leftPrec > 0 && leftPrec < rootPrec) {
            leftStr = "(" + leftStr + ")";
        }
    }

    // 检查右子树是否需要加括号
    if (root->right) {
        int rightPrec = getPrecedence(root->right->value);
        // 如果父节点优先级大于等于右子节点，则需要加括号
        if (rightPrec > 0 && rightPrec <= rootPrec) {
            rightStr = "(" + rightStr + ")";
        }
    }
    return leftStr + char(root->value) + rightStr;
}

int calcDescNum(TreeNode* root) {
    if (!root) return -1;

    if (!root->left && !root->right) {
        root->descNum = 0;
        return 0;
    }

    if (root->left) {
        root->descNum += (1 + calcDescNum(root->left));
    }

    if (root->right) {
        root->descNum += (1 + calcDescNum(root->right));
    }

    return root->descNum;
}

// 按层序遍历树(附带每个节点的descNum)
void levelOrderPrintTreeWithDescNum(TreeNode* root) {
    if (!root) return;

    // 创建一个队列用于存储先后各个节点，首先把根节点推进去
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        // 按照层序遍历顺序，子节点应该在父节点之后，使用队列先进先出的性质
        if (q.front()->left) q.push(q.front()->left);   // 左节点入队
        if (q.front()->right) q.push(q.front()->right); // 右节点入队
        
        // 打印队首节点的值
        std::cout << q.front()->value << "(descNum=" << q.front()->descNum << ')' <<' ';
        // 弹出队首节点
        q.pop();
    }

    std::cout << std::endl;
}

// 根据前序和中序遍历数组构建二叉树
TreeNode* getTreeFromInorderAndPreorderArray(int *in, int *pre, int size) {
    if (size <= 0) return nullptr;
    
    int rootValue = pre[0];
    TreeNode* root = new TreeNode(rootValue);
    
    if (size == 1) return root;
    
    int rootIndex = 0;
    for (int i = 0; i < size; i++) {
        if (in[i] == rootValue) {
            rootIndex = i;
            break;
        }
    }
    // 左子树的节点数量
    int leftSize = rootIndex;
    // 右子树的节点数量
    int rightSize = size - rootIndex - 1;
    
    if (leftSize > 0) {
        root->left = getTreeFromInorderAndPreorderArray(in, pre + 1, leftSize);
    }

    if (rightSize > 0) {
        root->right = getTreeFromInorderAndPreorderArray(in + rootIndex + 1, pre + leftSize + 1, rightSize);
    }
    
    return root;
}

#endif // BINARYTREE_H