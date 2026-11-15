#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if(!(cin >> q)) return 0;

    vector<int> left(q), right(q), wanted(q);
    int maxR = 1;
    for(int i = 0; i < q; ++i) {
        cin >> left[i] >> right[i] >> wanted[i];
        maxR = max(maxR, right[i]);
    }

    vector<int> distinctPrimeCount(maxR + 1, 0);
    for(int prime = 2; prime <= maxR; ++prime) {
        if(distinctPrimeCount[prime] == 0) {
            for(int multiple = prime; multiple <= maxR; multiple += prime) {
                ++distinctPrimeCount[multiple];
            }
        }
    }

    vector<vector<int>> prefix(8, vector<int>(maxR + 1, 0));
    for(int k = 0; k <= 7; ++k) {
        for(int n = 1; n <= maxR; ++n) {
            prefix[k][n] = prefix[k][n - 1];
            if(distinctPrimeCount[n] == k) {
                ++prefix[k][n];
            }
        }
    }

    for(int i = 0; i < q; ++i) {
        cout << prefix[wanted[i]][right[i]] - prefix[wanted[i]][left[i] - 1] << '\n';
    }

    return 0;
}