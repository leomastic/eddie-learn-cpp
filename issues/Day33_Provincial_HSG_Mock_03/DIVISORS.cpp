#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;

    struct Query {
        int left;
        int right;
        int divisors;
    };

    vector<Query> queries(q);
    int maxRight = 1;
    for (Query& query : queries) {
        cin >> query.left >> query.right >> query.divisors;
        maxRight = max(maxRight, query.right);
    }

    vector<int> divisorCount(maxRight + 1, 0);
    for (int divisor = 1; divisor <= maxRight; ++divisor) {
        for (int multiple = divisor; multiple <= maxRight; multiple += divisor) {
            ++divisorCount[multiple];
        }
    }

    vector<vector<int>> positionsWithCount(101);
    for (int value = 1; value <= maxRight; ++value) {
        int count = divisorCount[value];
        if (count <= 100) {
            positionsWithCount[count].push_back(value);
        }
    }

    for (const Query& query : queries) {
        const vector<int>& positions = positionsWithCount[query.divisors];
        auto first = lower_bound(positions.begin(), positions.end(), query.left);
        auto afterLast = upper_bound(positions.begin(), positions.end(), query.right);
        cout << afterLast - first << '\n';
    }

    return 0;
}
