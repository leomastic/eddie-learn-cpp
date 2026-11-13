#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    int median = a[(n - 1) / 2];

    int mode = a[0];
    int maxFreq = 1;
    int currentFreq = 1;

    for (int i = 1; i < n; ++i) {
        if (a[i] == a[i - 1]) {
            currentFreq++;
        } else {
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
                mode = a[i - 1];
            }
            currentFreq = 1;
        }
    }

    if (currentFreq > maxFreq) {
        maxFreq = currentFreq;
        mode = a[n - 1];
    }

    auto it = upper_bound(a.begin(), a.end(), median);
    int countAboveMedian = a.end() - it;

    cout << median << " " << mode << " " << countAboveMedian << "\n";

    return 0;
}
