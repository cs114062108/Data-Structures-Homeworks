# Lab2 Cheatsheet

### `lab2.cpp`
```cpp
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

```

<div style="page-break-after: always;"></div>

### `hw2.cpp`
```cpp
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

```

<div style="page-break-after: always;"></div>

### `hw2_AC_array.cpp`
```cpp
#include <iostream>
using namespace std;

const int MAX_N = 500000;
char s[MAX_N + 1];
char st[MAX_N + 1];

bool opposite(char a, char b) {
    return (a == 'N' && b == 'S') || (a == 'S' && b == 'N') ||
           (a == 'E' && b == 'W') || (a == 'W' && b == 'E');
}

int main() {
    cin >> s;

    int top = -1;  // The stack is empty when top == -1.
    for (int i = 0; s[i] != '\0'; ++i) {
        char d = s[i];
        if (top >= 0 && opposite(st[top], d)) {
            --top;          // Pop the opposite step.
        } else {
            st[++top] = d;  // Push the current step.
        }
    }

    st[top + 1] = '\0';
    cout << st << '\n';
    //printf("%s\n", st);
}

```

<div style="page-break-after: always;"></div>

### `hw2_AC_std_stack.cpp`
```cpp
#include <iostream>
#include <stack>
using namespace std;

const int MAX_N = 500000;
char s[MAX_N + 1];
char answer[MAX_N + 1];

bool opposite(char a, char b) {
    return (a == 'N' && b == 'S') || (a == 'S' && b == 'N') ||
           (a == 'E' && b == 'W') || (a == 'W' && b == 'E');
}

int main() {
    cin >> s;

    stack<char> st;
    for (int i = 0; s[i] != '\0'; ++i) {
        char d = s[i];
        bool cancel = !st.empty() && opposite(st.top(), d);
        if (cancel) {
            st.pop();
        } else {
            st.push(d);
        }
    }

    int length = st.size();
    for (int i = length - 1; i >= 0; --i) {
        answer[i] = st.top();
        st.pop();
    }
    answer[length] = '\0';
    cout << answer << '\n';
}

```

<div style="page-break-after: always;"></div>

