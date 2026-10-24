#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long K;
    if (!(std::cin >> n >> K)) return 0;

    std::vector<long long> A(n);
    std::unordered_set<long long> s;
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
        s.insert(A[i]);
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (s.count(A[i] - K) && s.count(A[i] + K)) {
            count++;
        }
    }

    std::cout << count << "\n";

    return 0;
}