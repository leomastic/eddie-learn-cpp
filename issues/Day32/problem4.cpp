#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if(!(cin >> n >> q)) return 0;

    vector<long long> prefix(n + 1, 0);
    for(int i = 1; i <= n; ++i) {
        long long energy;
        cin >> energy;
        prefix[i] = prefix[i - 1] + energy;
    }

    for(int i = 0; i < q; ++i) {
        int L, R;
        long long T;
        cin >> L >> R >> T;

        long long total = prefix[R] - prefix[L - 1];
        cout << total << ' ' << (total >= T ? "YES" : "NO") << '\n';
    }

    return 0;
}