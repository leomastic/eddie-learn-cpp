#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    if(!(cin >> S)) return 0;

    int sum = 0;
    for(int i = 0; i < S.length(); ++i) {
        if(isdigit(S[i])) {
            sum += S[i] - '0';
            continue;
        }

        return 0;
    }

    cout << sum << " ";

    int digitalRoot = 0;
    for(int i = 0; i < to_string(sum).length(); ++i) {
        digitalRoot += to_string(sum)[i] - '0';
    }

    while(digitalRoot >= 10) {
        int x = 0;
        for(int i = 0; i < to_string(digitalRoot).length(); ++i) {
            x += to_string(digitalRoot)[i] - '0';
        }
        digitalRoot = x;
    }

    cout << digitalRoot;

    return 0;
}