#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<long long, long long> prefixCount;
    prefixCount.reserve(n * 2 + 1);
    prefixCount[0] = 1;

    long long prefix = 0;
    long long answer = 0;

    for (int i = 0; i < n; ++i) {
        long long value;
        cin >> value;
        prefix += value;
        answer += prefixCount[prefix];
        ++prefixCount[prefix];
    }

    cout << answer << '\n';
    return 0;
}
