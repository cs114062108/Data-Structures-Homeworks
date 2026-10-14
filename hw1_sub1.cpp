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