#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    cin >> n;

    unsigned long long result = 0;
    while (n > 0) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }

    cout << result << '\n';
    return 0;
}
