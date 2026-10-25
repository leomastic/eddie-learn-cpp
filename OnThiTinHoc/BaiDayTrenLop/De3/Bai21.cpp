#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long x;
    if (!(std::cin >> n >> x)) return 0;

    std::unordered_map<long long, long long> freq;
    long long total_pairs = 0;

    for (int i = 0; i < n; ++i) {
        long long a_i;
        std::cin >> a_i;

        long long complement = x - a_i;
        if (freq.find(complement) != freq.end()) {
            total_pairs += freq[complement];
        }

        freq[a_i]++;
    }

    std::cout << total_pairs << "\n";

    return 0;
}