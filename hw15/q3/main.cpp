#include "binaryTree.h"
#include <climits>

bool isBST(TreeNode* root, int minVal, int maxVal) {
    if (root == nullptr) {
        return true;
    }

    // 检查当前结点的关键字
    if (root->value <= minVal || root->value >= maxVal) {
        return false;
    }

    // 递归检查左子树和右子树
    // 左子树的所有结点值必须小于当前结点值
    // 右子树的所有结点值必须大于当前结点值
    return isBST(root->left, minVal, root->value) && 
           isBST(root->right, root->value, maxVal);
}

bool checkBST(TreeNode* root) {
    return isBST(root, INT_MIN, INT_MAX);
}

int main() {
    TreeNode* root1 = new TreeNode(5);
    root1->left = new TreeNode(3);
    root1->right = new TreeNode(7);
    root1->left->left = new TreeNode(2);
    root1->left->right = new TreeNode(4);
    root1->right->right = new TreeNode(8);

    std::cout << "Test1: " << (checkBST(root1) ? "Yes" : "No") << std::endl;

    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(7);
    root2->right->left = new TreeNode(4);

    std::cout << "Test2: " << (checkBST(root2) ? "Yes" : "No") << std::endl;

    return 0;
}
