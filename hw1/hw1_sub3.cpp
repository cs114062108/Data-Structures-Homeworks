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