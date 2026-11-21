#include <bits/stdc++.h>

using namespace std;

int findIndex(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    if (!(cin >> S)) return 0;

    int N = S.length();
    string bestRotation = S;
    int bestIndex = 1;

    for (int i = 1; i < N; ++i) {
        string current = S.substr(i) + S.substr(0, i);
        if (current < bestRotation) {
            bestRotation = current;
            bestIndex = i + 1;
        }
    }

    cout << bestRotation << '\n';
    cout << bestIndex << '\n';

    return 0;
}