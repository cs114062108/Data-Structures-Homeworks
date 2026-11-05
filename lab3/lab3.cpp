// 14051
#include <iostream>
#include <string>
#include <vector>

#include <queue>

using namespace std;

template<class vT>
struct Node{
    vT val;
    int size;
    Node *left, *right;
    explicit Node(vT value): val(value), size(1), left(nullptr), right(nullptr) {}
};

class BST{
    private:
        Node<int> *root;
        
        int nodeSize(Node<int> *node) {
            return node != nullptr ? node->size : 0;
        }
        
        void pull(Node<int> *node) {
            node->size = 1 + nodeSize(node->left) + nodeSize(node->right);
        }
        
        // Pre:
        void preOrder(Node<int> *node, vector<int> &result) {
            if (node == nullptr) return;
            result.push_back(node->val);
            preOrder(node->left, result);
            preOrder(node->right, result);
        }
        
        // In:
        void inOrder(Node<int> *node, vector<int> &result) {
            if (node == nullptr) return;
            inOrder(node->left, result);
            result.push_back(node->val);
            inOrder(node->right, result);
        }
        
        Node<int> *insertNode(Node<int> *node, int x) {
            if (!node) return new Node<int>(x);
            if (x < node->val) {
                node->left = insertNode(node->left, x);
            } else {
                node->right = insertNode(node->right, x);
            }
            pull(node);
            return node;
        }

        int del_smallest(Node<int> *node) {
            int sval = 0;
            if (node->left == nullptr) {
                sval = node->val;
                if (node->right != nullptr) {
                    Node<int> *rnode = node->right;
                    free(node);
                    node = rnode;
                } else {
                    free(node);
                    node = nullptr;
                }
            } else {
                sval = del_smallest(node->left);
                pull(node);
            }
            return sval;
        }

        void deleteNode(Node<int> *node, int x) {
            if (x == node->val) {
                if (node->right != nullptr) {
                    node->val = del_smallest(node->right);
                    if (node->right->val == node->val) {
                        node->right = nullptr;
                        pull(node);
                    }
                } else {
                    delete node;
                }
                return;
            } else if (x < node->val) {
                deleteNode(node->left, x);
            } else {
                deleteNode(node->right, x);
            }
            pull(node);
        }
    
    public:
        explicit BST(): root(nullptr) {}
        
        // ----------------------------------------------------
        // Debug: Level order
        // ----------------------------------------------------
        void levelOrder() {
            Node<int> *node = root;
            int cnt, next_cnt;
            int counter = 0;
            queue<Node<int>*> nodes;
            nodes.push(node);
            cnt = 1; next_cnt = 0;
            while (!nodes.empty()) {
                node = nodes.front();
                counter++;
                nodes.pop();
                if (node->left != nullptr) {
                    nodes.push(node->left);
                    next_cnt++;
                }
                if (node->right != nullptr) {
                    nodes.push(node->right);
                    next_cnt++;
                }

                int leftSize = nodeSize(node->left);
                int rightSize = nodeSize(node->right);
                if (rightSize == 0) rightSize = 1;

                for (int __ = 0; __ < leftSize; __++) cout << " ";
                cout << node->val;

                if (counter == cnt) {
                    cnt = next_cnt;
                    counter = 0;
                    next_cnt = 0;
                    cout << endl;
                } else {
                    for (int __ = 0; __ < rightSize; __++) cout << " ";
                }
            }
        }

        void insert(int x) {
            root = insertNode(root, x);
        }

        void del(int x) {
            deleteNode(root, x);
        }

        int rank(int x) {
            int passed = 0;
            Node<int> *node = root;
            while (node != nullptr) {
                int leftSize = nodeSize(node->left);
                if (x == node->val) return passed + leftSize + 1;
                if (x < node->val) {
                    node = node->left;
                } else {
                    node = node->right;
                    passed += leftSize + 1;
                }
            }
            return -1;
        }

        int kth(int k) {
            Node<int> *node = root;
            while (node != nullptr) {
                int leftSize = nodeSize(node->left);
                if (k == leftSize + 1) return node->val;
                if (k <= leftSize) {
                    node = node->left;
                } else {
                    node = node->right;
                    k -= leftSize + 1;
                }
            }
            return 0;
        }
        
        void printTree(bool usePre) {
            vector<int> result;
            if (usePre) {
                preOrder(root, result);
            } else {
                inOrder(root, result);
            }
            int tree_size = (int) result.size();
            for (int i = 0; i < tree_size; i++) {
                if (i > 0) cout << ' ';
                cout << result[i];
            }
            cout << endl;
        }
};

#define DEBUG 1

int main() {
    int Q;
    cin >> Q;

    BST tree;

    for (int _ = 0; _ < Q; _++) {
        string cmd;
        cin >> cmd;

        if (cmd == "INSERT") {
            int x; cin >> x;
            tree.insert(x);
            if (DEBUG) tree.levelOrder();
        } else if (cmd == "RANK") {
            int x; cin >> x;
            cout << tree.rank(x) << endl;
        } else if (cmd == "KTH") {
            int k; cin >> k;
            cout << tree.kth(k) << endl;
        } else if (cmd == "PRINT") {
            int order; cin >> order;
            tree.printTree(order == 0);
        } else if (cmd == "DELETE") {
            int x; cin >> x;
            tree.del(x);
            if (DEBUG) tree.levelOrder();
        }
    }

    return 0;
}
