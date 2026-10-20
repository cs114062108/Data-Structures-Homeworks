# Lab1 Cheatsheet

### `hw1.cpp`
```cpp
// 15025 - RedCapeFlyingCat Plays on the Grass
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    Node *prev, *next;

    Node(int _id): id(_id), prev(NULL), next(NULL) {}
};

int nodeCnt = 0;
vector<Node *> nodes;
Node *flag;

int main(void) {
    // input
    int n, q;
    cin >> n >> q;

    // init
    nodeCnt = n;
    nodes.resize(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node(i+1);
    }

    // form circular linked list
    for (int i = 0; i < n; i++) {
        nodes[i]->prev = nodes[(i - 1 + n) % n];
        nodes[i]->next = nodes[(i + 1) % n];
    }
    flag = nodes[0];

    // queries
    for (int i = 0; i < q; i++) {
        string op;
        cin >> op;

        if (op == "insert") {
            int k, id;
            cin >> k >> id;
            
            // pass flag to next k times
            for (int _ = 0; _ < k; _++) flag = flag->next;

            // new node
            nodeCnt++;
            nodes.push_back(new Node(id));
            
            // linked list insert
            nodes.back()->prev = flag;
            nodes.back()->next = flag->next;
            flag->next->prev = nodes.back();
            flag->next = nodes.back();

            // pass flag to new person
            flag = flag->next;
        } else if (op == "erase") {
            int k;
            cin >> k;

            // pass flag k times
            for (int _ = 0; _ < k; _++) flag = flag->next;

            // erase node
            nodeCnt--;
            cout << flag->id << endl;
            flag->prev->next = flag->next;
            flag->next->prev = flag->prev;

            // pass flag to next person
            flag = flag->next;
        } else if (op == "print") {
            Node *iter = flag;
            for (int j = 0; j < nodeCnt; j++) {
                cout << iter->id << ((j < nodeCnt-1) ? " " : "\n");
                //cout << iter->id << " \n"[j==nodeCnt-1];
                iter = iter->next;
            }
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

### `hw1_sub1.cpp`
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int flag = 0;

void pass_flag(int k) {
    flag = (flag + k) % v.size();
}

int main() {
    // input
    int n, q;
    cin >> n >> q;
    v.resize(n);
    iota(v.begin(), v.end(), 1); // v = {1, 2, 3, ...}

    // queries
    for (int i = 0; i < q; i++) {
        n = v.size();
        string op;
        cin >> op;

        if (op == "insert") {
            int k, id;
            cin >> k >> id;

            pass_flag(k + 1);
            v.insert(v.begin() + flag, id);
        }
        else if (op == "erase") {
            int k;
            cin >> k;
            pass_flag(k);
            cout << v[flag] << "\n";
            v.erase(v.begin() + flag);
            pass_flag(0);
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

### `hw1_sub2.cpp`
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int flag = 0;

void pass_flag(int k) {
    flag = (flag + k) % v.size();
}

int main() {
    // input
    int n, q;
    cin >> n >> q;
    v.resize(n);
    iota(v.begin(), v.end(), 1);

    // queries
    for (int i = 0; i < q; i++) {
        n = v.size();
        string op;
        cin >> op;

        if (op == "insert") {
            int k, id;
            cin >> k >> id;

            pass_flag(k + 1);
            v.insert(v.begin() + flag, id);
        } else if (op == "erase") {
            int k;
            cin >> k;
            pass_flag(k);
            cout << v[flag] << "\n";
            v.erase(v.begin() + flag);
            pass_flag(0);
        } else if (op == "print") {
            for (int j = 0; j < n; j++) {
                cout << v[(j + flag) % n] << " \n"[j == n - 1];
            }
        }
    }
}

```

<div style="page-break-after: always;"></div>

### `hw1_sub3.cpp`
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    Node *pre, *nxt;

    Node(int _id) : id(_id), pre(NULL), nxt(NULL) {}
};

int nodeCnt = 0;
vector<Node *> v;
Node *flag;

int main() {
    // input
    int n, q;
    cin >> n >> q;
    
    // init
    nodeCnt = n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i] = new Node(i + 1);
    }
    for (int i = 0; i < n; i++) {
        v[i]->pre = v[(i + n - 1) % n];
        v[i]->nxt = v[(i + 1) % n];
    }
    flag = v[0];

    // queries
    for (int i = 0; i < q; i++) {
        string op;
        cin >> op;

        if (op == "insert") {
            int k, id;
            cin >> k >> id;
            
            nodeCnt++;
            for (int _=0 ; _<k ; _++) flag = flag->nxt;
            v.push_back(new Node(id));
            v.back()->pre = flag;
            v.back()->nxt = flag->nxt;
            flag->nxt->pre = v.back();
            flag->nxt = v.back();
            flag = flag->nxt;
        } else if (op == "erase") {
            int k;
            cin >> k;
            
            nodeCnt--;
            for (int _=0 ; _<k ; _++) flag = flag->nxt;
            cout << flag->id << "\n";
            flag->pre->nxt = flag->nxt;
            flag->nxt->pre = flag->pre;
            flag = flag->nxt;
        } else if (op == "print") {
            Node* now = flag;
            for (int j = 0; j < nodeCnt; j++) {
                cout << now->id << " \n"[j==nodeCnt-1];
                now = now->nxt;
            }
        }
    }
}
```

<div style="page-break-after: always;"></div>

