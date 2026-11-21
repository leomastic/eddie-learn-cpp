#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll t;
    if(!(cin >> n >> t)) return 0;

    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int ans = -1;
    int total = 0;
    int idx;
    for(int i = 0; i < n; ++i) {
        total = 0;
        for(int j = 0; j < n - i; ++j) {
            for(int k = j; k < i - j + 1; ++k) {
                total += a[k];
            }

            if(total >= t) {
                ans = i - j + 1;
                idx = j;
                break;
            }
        }

        if(total >= t) {
            ans = i - idx + 1;
            break;
        }
    }

    cout << ans;

    return 0;
}