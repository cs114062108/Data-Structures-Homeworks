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
