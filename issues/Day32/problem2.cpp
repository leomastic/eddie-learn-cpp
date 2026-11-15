#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string s;
    cin >> n >> k >> s;

    if(k == 0) {
        cout << "0 0\n";
        return 0;
    }

    vector<int> frequency(26, 0);
    int distinct = 0;
    int left = 0;
    int bestlen = 0;
    int beststart = 0;

    for(int right = 0; right < n; ++right) {
        int current = s[right] - 'a';
        if(frequency[current]++ == 0) ++distinct;

        while(distinct > k) {
            int removed = s[left] - 'a';
            if(--frequency[removed] == 0) --distinct;
            ++left;
        }

        int len = right - left + 1;
        if(len > bestlen) {
            bestlen = len;
            beststart = left;
        }
    }

    cout << bestlen << " " << beststart + 1 << '\n';
    return 0;
}