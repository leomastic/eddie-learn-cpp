#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string signal;
    if (!(cin >> n >> signal)) return 0;

    char bestCharacter = signal[0];
    int bestLength = 1;
    int bestStart = 0;

    for (int start = 0; start < n;) {
        int end = start + 1;
        while (end < n && signal[end] == signal[start]) {
            ++end;
        }

        int length = end - start;
        if (length > bestLength) {
            bestCharacter = signal[start];
            bestLength = length;
            bestStart = start;
        }
        start = end;
    }

    cout << bestCharacter << ' ' << bestLength << ' ' << bestStart + 1 << '\n';
    return 0;
}
