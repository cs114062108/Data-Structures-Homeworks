// 15032 - RedCapeFlyingCat hates walking
#include <iostream>
#include <stack>
#include <map>
using namespace std;

map<char, char> op_map = {{'N', 'S'}, {'S', 'N'}, {'E', 'W'}, {'W', 'E'}};

bool is_opposite(char a, char b) {
    return op_map[a] == b;
}

int main() {
    string s;
    cin >> s;

    deque<char> chars;

    for (char &c: s) {
        if (!chars.empty()) {
            if (is_opposite(chars.back(), c)) {
                chars.pop_back();
                continue;
            }
        }
        chars.push_back(c);
    }

    while (!chars.empty()) {
        char c = chars.front();
        cout << c;
        chars.pop_front();
    }
    cout << endl;

    return 0;
}
