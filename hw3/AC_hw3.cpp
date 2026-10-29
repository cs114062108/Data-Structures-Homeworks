#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int key, size;
    Node *left, *right;
    explicit Node(int value) : key(value), size(1), left(nullptr), right(nullptr) {}
};

int nodeSize(Node* node) { return node == nullptr ? 0 : node->size; }
void pull(Node* node) { node->size = 1 + nodeSize(node->left) + nodeSize(node->right); }

Node* insertNode(Node* node, int key) {
    if (node == nullptr) return new Node(key);
    if (key < node->key) node->left = insertNode(node->left, key);
    else if (key > node->key) node->right = insertNode(node->right, key);
    pull(node);
    return node;
}

int rankOf(Node* node, int key) {
    int passed = 0;
    while (node != nullptr) {
        if (key == node->key) return passed + nodeSize(node->left) + 1;
        if (key < node->key) node = node->left;
        else {
            passed += nodeSize(node->left) + 1;
            node = node->right;
        }
    }
    return -1;
}

int kth(Node* node, int k) {
    while (node != nullptr) {
        int leftSize = nodeSize(node->left);
        if (k == leftSize + 1) return node->key;
        if (k <= leftSize) node = node->left;
        else { k -= leftSize + 1; node = node->right; }
    }
    return 0; // Unreachable for valid k.
}

void preorder(Node* node, vector<int>& result) {
    if (node == nullptr) return;
    result.push_back(node->key);
    preorder(node->left, result);
    preorder(node->right, result);
}

void inorder(Node* node, vector<int>& result) {
    if (node == nullptr) return;
    inorder(node->left, result);
    result.push_back(node->key);
    inorder(node->right, result);
}

void printTree(Node* root, bool usePreorder) {
    vector<int> result;
    if (usePreorder) preorder(root, result); else inorder(root, result);
    for (int i = 0; i < (int)result.size(); ++i) {
        if (i) cout << ' ';
        cout << result[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> Q;
    Node* root = nullptr;
    while (Q--) {
        string command;
        cin >> command;
        if (command == "INSERT") {
            int x; cin >> x;
            root = insertNode(root, x);
        } else if (command == "RANK") {
            int x; cin >> x;
            cout << rankOf(root, x) << '\n';
        } else if (command == "KTH") {
            int k; cin >> k;
            cout << kth(root, k) << '\n';
        } else {
            int order; cin >> order;
            printTree(root, order == 0);
        }
    }
}
