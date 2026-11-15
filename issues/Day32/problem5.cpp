#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if(!(cin >> n >> m)) return 0;

    vector<long long> remainderCount(m, 0);
    long long pairs = 0;

    for(int i = 0; i < n; ++i) {
        long long id;
        cin >> id;

        int remainder = id % m;
        int needed = (m - remainder) % m;
        pairs += remainderCount[needed];
        ++remainderCount[remainder];
    }

    cout << pairs << '\n';
    return 0;
}
