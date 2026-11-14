#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long limit;
    if (!(cin >> n >> limit)) return 0;

    vector<long long> values(n);
    for (long long& value : values) {
        cin >> value;
    }

    deque<int> minimums;
    deque<int> maximums;
    int left = 0;
    int longest = 0;

    for (int right = 0; right < n; ++right) {
        while (!minimums.empty() && values[minimums.back()] >= values[right]) {
            minimums.pop_back();
        }
        minimums.push_back(right);

        while (!maximums.empty() && values[maximums.back()] <= values[right]) {
            maximums.pop_back();
        }
        maximums.push_back(right);

        while (values[maximums.front()] - values[minimums.front()] > limit) {
            if (minimums.front() == left) {
                minimums.pop_front();
            }
            if (maximums.front() == left) {
                maximums.pop_front();
            }
            ++left;
        }

        longest = max(longest, right - left + 1);
    }

    cout << longest << '\n';
    return 0;
}
