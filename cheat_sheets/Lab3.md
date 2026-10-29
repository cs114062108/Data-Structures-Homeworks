# Lab3 Cheatsheet

### `AC_hw3.cpp`
```cpp
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

```

<div style="page-break-after: always;"></div>

### `hw3.cpp`
```cpp
// 15056 - RedCapeFlyingCat and BST
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class vT>
struct Node {
    vT val;
    int size;
    Node *left, *right;
    explicit Node(vT value) : val(value), size(1), left(nullptr), right(nullptr) {}
};

template<class T>
class BST{
    private:
        Node<T> *root;

        int nodeSize(Node<T> *node) {
            return node != nullptr ? node->size : 0;
        }

        void pull(Node<T> *node) {
            node->size = 1 + nodeSize(node->left) + nodeSize(node->right);
        }

        // Pre: root -> left -> right
        void preorder(Node<T> *node, vector<T> &result) {
            if (node == nullptr) return;
            result.push_back(node->val);
            preorder(node->left, result);
            preorder(node->right, result);
        }

        // In: left -> root -> right
        void inorder(Node<T> *node, vector<T> &result) {
            if (node == nullptr) return;
            inorder(node->left, result);
            result.push_back(node->val);
            inorder(node->right, result);
        }

        Node<T> *insertNode(Node<T> *node, T x) {
            if (!node) return new Node<T>(x);
            if (x < node->val) {
                node->left = insertNode(node->left, x);
            } else {
                node->right = insertNode(node->right, x);
            }
            pull(node);
            return node;
        }
    public:
        explicit BST(): root(nullptr) {}

        void insert(T x) {
            root = insertNode(root, x);
        }

        int rank(T x) {
            int passed = 0;
            Node<T> *node = root;
            while (node != nullptr) {
                int leftSize = nodeSize(node->left);
                if (x == node->val) return passed + leftSize + 1;
                if (x < node->val) {
                    node = node->left;
                } else {
                    passed += leftSize + 1;
                    node = node->right;
                }
            }
            return -1;
        }

        T* kth(T k) {
            Node<T> *node = root;
            while (node != nullptr) {
                int leftSize = nodeSize(node->left);
                if (k == leftSize + 1) return &(node->val);
                if (k <= leftSize) {
                    node = node->left;
                } else {
                    k -= leftSize + 1;
                    node = node->right;
                }
            }
            return nullptr;
        }

        void printTree(bool usePre) {
            vector<T> result;
            if (usePre) {
                preorder(root, result);
            } else {
                inorder(root, result);
            }
            int tree_size = (int) result.size();
            for (int i = 0; i < tree_size; i++) {
                if (i > 0) cout << ' ';
                cout << result[i];
            }
            cout << endl;
        }
};

int main() {
    int Q;
    cin >> Q;
    
    BST<int> tree;

    for (int _ = 0; _ < Q; _++) {
        string cmd;
        cin >> cmd;
        
        if (cmd == "INSERT") {
            int x; cin >> x;
            tree.insert(x);
        } else if (cmd == "RANK") {
            int x; cin >> x;
            cout << tree.rank(x) << endl;
        } else if (cmd == "KTH") {
            int k; cin >> k;
            int *kth = tree.kth(k);
            if (kth == nullptr) continue;
            cout << *kth << endl;
        } else if (cmd == "PRINT") {
            int order; cin >> order;
            tree.printTree(order == 0);
        }
    }

    return 0;
}

```

<div style="page-break-after: always;"></div>

