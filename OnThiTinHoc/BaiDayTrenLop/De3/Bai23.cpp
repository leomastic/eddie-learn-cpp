#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    // A[1] = S[1] = B[1] * 1
    long long prev_sum = b[1];
    cout << prev_sum;

    for (int i = 2; i <= n; ++i) {
        long long curr_sum = b[i] * i;
        long long a_i = curr_sum - prev_sum;
        cout << " " << a_i;
        prev_sum = curr_sum;
    }
    cout << "\n";

    return 0;
}