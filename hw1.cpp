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