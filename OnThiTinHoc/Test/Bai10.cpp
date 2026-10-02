#include <bits/stdc++.h>

long long solve(const std::vector<long long>& a) {
    int n = a.size();
    if (n < 4) return 0;

    long long total_sum = 0;
    for (long long x : a) {
        total_sum += x;
    }

    long long max_value = 0;

    for (int i = 0; i < n - 2; ++i) {
        long long prod3 = a[i] * a[i+1] * a[i+2];
        long long current_val = total_sum - (a[i] + a[i+1] + a[i+2]) + prod3;
        max_value = std::max(max_value, current_val);
    }

    std::vector<long long> gain(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        gain[i] = (a[i] * a[i+1]) - (a[i] + a[i+1]);
    }

    std::vector<long long> prefix_max(n - 1);
    prefix_max[0] = gain[0];
    for (int i = 1; i < n - 1; ++i) {
        prefix_max[i] = std::max(prefix_max[i - 1], gain[i]);
    }

    for (int j = 2; j < n - 1; ++j) {
        long long gain_two_pairs = gain[j] + prefix_max[j - 2];
        long long current_val = total_sum + gain_two_pairs;
        max_value = std::max(max_value, current_val);
    }

    return max_value;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (std::cin >> n) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }

        std::cout << solve(a) << "\n";
    }

    return 0;
}