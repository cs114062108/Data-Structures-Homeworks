// 15065 - RedCapeFlyingCat hates even more walking
#include <iostream>
#include <stack>
#include <map>

using namespace std;

map<char, char> op_map = {{'N', 'S'}, {'S', 'N'}, {'E', 'W'}, {'W', 'E'}};

bool is_opposite(char a, char b) {
    return op_map[a] == b;
}

// steps can be up to 1e9
#define llint long long

int main() {
    deque<pair<char, llint>> deq;

    int Q, type;
    cin >> Q >> type;

    for (int _ = 0; _ < Q; _++) {
        char d;
        llint step;
        cin >> d >> step;

        if (!deq.empty()) {
            pair<char, llint> last = deq.back();
            if (is_opposite(last.first, d)) {
                llint cancels = min(last.second, step);
                deq.back().second -= cancels;
                if (deq.back().second <= 0) {
                    deq.pop_back();
                }
                step -= cancels;
            } else if (last.first == d) {
                deq.back().second += step;
                continue;   // Only in merge case doesn't push back
            }
        }
        if (step > 0) {
            deq.push_back({d, step});
        }
    }

    while (!deq.empty()) {
        char c = deq.front().first;
        llint times = deq.front().second;
        if (type == 0) {
            for (int _ = 0; _ < times; _++) {
                cout << c;
            }
        } else if (type == 1) {
            cout << c << times;
        }
        deq.pop_front();
    }
    cout << endl;

    return 0;
}
