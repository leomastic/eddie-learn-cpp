#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string s;
    cin >> n >> k >> s;

    if(k == 0) {
        cout << "0 0";
        return 0;
    }

    int bestlen = 1;
    int ssp = 1;
    int i = 0;

    while(i < n) {
        set<char> chars = {s[i]};
        for(int j = i; j < n; ++j) {
            chars.insert(s[j]);
            int len = j - i + 1;
            if(len > bestlen && chars.size() <= k) {
                bestlen = len;
                ssp = i + 1;
            }
            else if(chars.size() > k) {
                break;
            }
        }
        ++i;
    }

    cout << bestlen << " " << ssp;
    return 0;
}