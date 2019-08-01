#include "playground/btree.hpp"

using namespace playground::btree;
using namespace std;

void PreOrderWithoutRecursive(const TreeNode *root) {
    stack<const TreeNode *> s;
    while (!s.empty() || root) {
        while (root) {
            s.push(root);
            cout << root->val << ' ';
            root = root->left;
        }
        root = s.top()->right;
        s.pop();
    }
    cout << "<- pre order" << endl;
}

void InOrderWithoutRecursive(const TreeNode *root) {
    stack<const TreeNode *> s;
    while (root || !s.empty()) {
        while (root) {
            s.push(root);
            root = root->left;
        }
        cout << s.top()->val << ' ';
        root = s.top()->right;
        s.pop();
    }
    cout << "<- in order" << endl;
}

void PostOrderWithoutRecursive(const TreeNode *root) {
    struct env {
        const TreeNode *node;
        bool first;
    };
    stack<env> s;
    while (root || !s.empty()) {
        while (root) {
            s.push({root, true});
            root = root->left;
        }
        if (s.top().first) {
            s.top().first = false;
            root = s.top().node->right;
        } else {
            cout << s.top().node->val << ' ';
            root = nullptr;
            s.pop();
        }
    }
    cout << "<- post order" << endl;
}

void PostOrderWithoutRecursive2(const TreeNode *root) {
    stack<const TreeNode *> s;
    if (root) {
        s.push(root);
    }
    const TreeNode *pre = nullptr;
    while (!s.empty()) {
        const TreeNode *cur = s.top();
        if ((!cur->left && !cur->right) ||
            (pre && (pre == cur->left || pre == cur->right))) {
            cout << cur->val << ' ';
            s.pop();
            pre = cur;
        } else {
            if (cur->right) {
                s.push(cur->right);
            }
            if (cur->left) {
                s.push(cur->left);
            }
        }
    }
    cout << "<- post order 2" << endl;
}

void LevelOrder(const TreeNode *root) {
    queue<const TreeNode *> q;
    if (root) {
        q.push(root);
    }
    while (!q.empty()) {
        const TreeNode *cur = q.front();
        q.pop();
        cout << cur->val << ' ';
        if (cur->left) {
            q.push(cur->left);
        }
        if (cur->right) {
            q.push(cur->right);
        }
    }
    cout << "<- level order" << endl;
}

void MorrisInOrder(TreeNode *root) {
    while (root) {
        if (root->left) {
            TreeNode *tmp = root->left;
            while (tmp->right && tmp->right != root) {
                tmp = tmp->right;
            }
            if (!tmp->right) {
                tmp->right = root;
                root = root->left;
            } else {
                tmp->right = nullptr;
                cout << root->val << ' ';
                root = root->right;
            }
        } else {
            cout << root->val << ' ';
            root = root->right;
        }
    }
    cout << "<- morris in order" << endl;
}

void MorrisPreOrder(TreeNode *root) {
    while (root) {
        if (root->left) {
            TreeNode *tmp = root->left;
            while (tmp->right && tmp->right != root) {
                tmp = tmp->right;
            }
            if (!tmp->right) {
                tmp->right = root;
                cout << root->val << ' ';
                root = root->left;
            } else {
                tmp->right = nullptr;
                root = root->right;
            }
        } else {
            cout << root->val << ' ';
            root = root->right;
        }
    }
    cout << "<- morris pre order" << endl;
}

int main() {
    TreeNode *root = generateRandomTree();
    printTreeV(root);
    PreOrderWithoutRecursive(root);
    MorrisPreOrder(root);
    InOrderWithoutRecursive(root);
    MorrisInOrder(root);
    PostOrderWithoutRecursive(root);
    PostOrderWithoutRecursive2(root);
    LevelOrder(root);
}
