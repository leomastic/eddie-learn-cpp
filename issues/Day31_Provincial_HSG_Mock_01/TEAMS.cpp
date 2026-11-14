#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long limit;
    if (!(cin >> n >> limit)) return 0;

    vector<long long> skill(n);
    for (long long& value : skill) {
        cin >> value;
    }
    sort(skill.begin(), skill.end());

    long long teams = 0;
    for (int first = 0; first < n - 2; ++first) {
        int left = first + 1;
        int right = n - 1;

        while (left < right) {
            if (skill[first] + skill[left] + skill[right] <= limit) {
                teams += right - left;
                ++left;
            } else {
                --right;
            }
        }
    }

    cout << teams << '\n';
    return 0;
}
