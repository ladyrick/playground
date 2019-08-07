#include "common.hpp"

#ifndef __PLAYGROUND_BTREE__
#define __PLAYGROUND_BTREE__

namespace playground {
namespace btree {
using playground::input;
struct TreeNode : public playground::__::AutoFree {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

namespace __ {
void fillMap(std::vector<const TreeNode *> &nodemap, const TreeNode *root,
             int index) {
    if (!root) {
        return;
    }
    nodemap[index] = root;
    fillMap(nodemap, root->left, index * 2 + 1);
    fillMap(nodemap, root->right, index * 2 + 2);
}

std::ostream &putsInWidth(char c, int width) {
    return std::cout << std::setw(width) << std::setfill(c) << c
                     << std::setfill(' ');
}

void printLeftToParentBranchTop(int w) {
    putsInWidth(' ', w + 1);
    putsInWidth('_', w - 3) << "/ ";
}

void printRightToParentBranchTop(int w) {
    std::cout << '\\';
    putsInWidth('_', w - 3);
    putsInWidth(' ', w + 2);
}

void printLeftToParentBranchBottom(int w) {
    putsInWidth(' ', w) << '/';
    putsInWidth(' ', w - 1);
}

void printRightToParentBranchBottom(int w) {
    putsInWidth(' ', w - 2) << '\\';
    putsInWidth(' ', w + 1);
}

void printNode(const TreeNode *node, int w) {
    std::cout << std::setw(w) << node->val;
    return;
}

void trimLeftTrailingSpaces(std::string &input) {
    input.erase(input.begin(), std::find_if(input.begin(), input.end(),
                                       [](int ch) { return !std::isspace(ch); }));
}

void trimRightTrailingSpaces(std::string &input) {
    input.erase(std::find_if(input.rbegin(), input.rend(),
                        [](int ch) { return !std::isspace(ch); })
                    .base(),
                input.end());
}
} // namespace __

std::string treeNodeToString(const TreeNode *root) {
    if (root == nullptr) {
        return "[]";
    }

    std::string output = "";
    std::queue<const TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        const TreeNode *node = q.front();
        q.pop();

        if (node == nullptr) {
            output += "null, ";
            continue;
        }

        output += std::to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

TreeNode *stringToTreeNode(std::string input) {
    __::trimLeftTrailingSpaces(input);
    __::trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    std::string item;
    std::stringstream ss;
    ss.str(input);

    std::getline(ss, item, ',');
    TreeNode *root = new TreeNode(stoi(item));
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode *node = nodeQueue.front();
        nodeQueue.pop();

        if (!std::getline(ss, item, ',')) {
            break;
        }

        __::trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!std::getline(ss, item, ',')) {
            break;
        }

        __::trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

int maxDepth(const TreeNode *root) {
    if (!root)
        return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

bool isSame(const TreeNode *root1, const TreeNode *root2) {
    if (!root1 || !root2) {
        return root1 == root2;
    }
    return root1->val == root2->val && isSame(root1->left, root2->left) &&
           isSame(root1->right, root2->right);
}

void printTreeV(const TreeNode *root, std::string prefix = "",
                bool isLeft = true) {
    if (!root) {
        std::cout << "Empty tree";
        return;
    }

    if (root->right) {
        printTreeV(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    std::cout << prefix + (isLeft ? "└── " : "┌── ") +
                     std::to_string(root->val) + "\n";

    if (root->left) {
        printTreeV(root->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}

void printTreeH(const TreeNode *root) {
    if (!root) {
        std::cout << "Empty tree";
        return;
    }
    int depth = maxDepth(root);
    std::vector<const TreeNode *> nodemap((1 << depth) - 1, nullptr);
    __::fillMap(nodemap, root, 0);
    for (int j = 0, index = 0; j < depth; j++) {
        int w = 1 << (depth - j + 1);
        if (j > 0) {
            // Top part of node to parent branch
            for (int i = 0; i < 1 << j; i++) {
                if (nodemap[index + i]) {
                    if (i % 2 == 0) {
                        __::printLeftToParentBranchTop(w);
                    } else {
                        __::printRightToParentBranchTop(w);
                    }
                } else {
                    __::putsInWidth(' ', w * 2);
                }
            }
            std::cout << std::endl;
            // Bottom part of node to parent branch
            for (int i = 0; i < 1 << j; i++) {
                if (nodemap[index + i]) {
                    if (i % 2 == 0) {
                        __::printLeftToParentBranchBottom(w);
                    } else {
                        __::printRightToParentBranchBottom(w);
                    }
                } else {
                    __::putsInWidth(' ', w * 2);
                }
            }
            std::cout << std::endl;
        }
        // Node content
        for (int i = 0; i < 1 << j; i++, index++)
            if (nodemap[index]) {
                __::printNode(nodemap[index], w);
                __::putsInWidth(' ', w * 2 - w);
            } else {
                __::putsInWidth(' ', w * 2);
            }
        std::cout << std::endl;
    }
}

TreeNode *generateRandomTree(int num_nodes = 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (!num_nodes) {
        std::uniform_int_distribution<> idis(1, 20);
        num_nodes = idis(gen);
    }
    std::uniform_real_distribution<> rdis(0, 1);
    int nums = 0;
    std::queue<TreeNode *> que;
    TreeNode *root = new TreeNode(++nums);
    que.push(root);
    double initRatio = 0.95;
    while (!que.empty() && nums < num_nodes) {
        TreeNode *p = que.front();
        que.pop();
        if (rdis(gen) < initRatio - (initRatio - 0.5) * nums / num_nodes) {
            p->left = new TreeNode(++nums);
            que.push(p->left);
        }
        if (rdis(gen) < initRatio - (initRatio - 0.5) * nums / num_nodes) {
            p->right = new TreeNode(++nums);
            que.push(p->right);
        }
    }
    return root;
}
} // namespace btree
} // namespace playground

#endif
