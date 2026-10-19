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
