#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<long long> packages(n);
    for (long long& package : packages) {
        cin >> package;
    }
    sort(packages.begin(), packages.end());

    while (q--) {
        long long requestedWeight;
        cin >> requestedWeight;

        const auto first = lower_bound(packages.begin(), packages.end(), requestedWeight);
        if (first == packages.end()) {
            cout << "-1 0\n";
            continue;
        }

        const long long weight = *first;
        const auto afterLast = upper_bound(first, packages.end(), weight);
        cout << weight << ' ' << (afterLast - first) << '\n';
    }

    return 0;
}
