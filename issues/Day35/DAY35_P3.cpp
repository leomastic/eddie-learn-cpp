#include <bits/stdc++.h>

using namespace std;
#define ll long long

bool ok(const vector<ll>& a, int k, ll x) {
    int groups = 1;
    ll sum = 0;

    for(ll v : a) {
        if(v > x) return false;

        if(sum + v <= x) {
            sum += v;
        } else {
            groups += 1;
            sum = v;
        }
    }

    return groups <= k;
}

ll solve(const vector<ll>& a, int k) {
    ll L = *max_element(a.begin(), a.end());
    ll R = 0;
    for(ll v : a) R += v;

    while(L < R) {
        ll mid = L + ((R - L) / 2);
        
        if(ok(a, k, mid)) {
            R = mid;
        } else {
            L = mid + 1;
        }
    }

    return L;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if(!(cin >> n >> k)) return 1;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll ans = solve(a, k);

    cout << ans;

    return 0;
}