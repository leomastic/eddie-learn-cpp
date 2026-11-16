#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, minLength, maxLength;
    if (!(cin >> n >> minLength >> maxLength)) return 0;

    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long value;
        cin >> value;
        prefix[i] = prefix[i - 1] + value;
    }

    deque<int> candidates;
    long long best = LLONG_MIN;

    for (int end = minLength; end <= n; ++end) {
        int newStart = end - minLength;
        while (!candidates.empty() && prefix[candidates.back()] >= prefix[newStart]) {
            candidates.pop_back();
        }
        candidates.push_back(newStart);

        int earliestStart = end - maxLength;
        while (candidates.front() < earliestStart) {
            candidates.pop_front();
        }

        best = max(best, prefix[end] - prefix[candidates.front()]);
    }

    cout << best << '\n';
    return 0;
}
