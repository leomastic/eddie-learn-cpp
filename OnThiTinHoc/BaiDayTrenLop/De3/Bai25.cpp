#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N, K, P;
    if (!(cin >> N >> K >> P)) return 0;

    vector<long long> a(N);
    vector<long long> pref(N + 1, 0);

    long long sum_full = 0;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
        sum_full = (sum_full + a[i]) % MOD;
        pref[i + 1] = (pref[i] + a[i]) % MOD;
    }

    long long full_cycles = K / N;
    long long rem = K % N;

    long long total_sum = (full_cycles % MOD) * sum_full % MOD;

    long long start_idx = (P - 1) % N;
    long long end_idx = start_idx + rem;

    long long rem_sum = 0;
    if (end_idx <= N) {
        rem_sum = (pref[end_idx] - pref[start_idx] + MOD) % MOD;
    } else {
        long long part1 = (pref[N] - pref[start_idx] + MOD) % MOD;
        long long part2 = pref[end_idx % N];
        rem_sum = (part1 + part2) % MOD;
    }

    total_sum = (total_sum + rem_sum) % MOD;

    cout << total_sum << "\n";

    return 0;
}