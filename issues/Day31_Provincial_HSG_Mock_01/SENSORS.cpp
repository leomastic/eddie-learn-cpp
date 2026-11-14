#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> readings(n);
    for (long long& reading : readings) {
        cin >> reading;
    }
    sort(readings.begin(), readings.end());

    const long long lowerMedian = readings[(n - 1) / 2];
    long long mode = readings.front();
    int highestFrequency = 0;

    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && readings[j] == readings[i]) {
            ++j;
        }
        const int frequency = j - i;
        if (frequency > highestFrequency) {
            highestFrequency = frequency;
            mode = readings[i];
        }
        i = j;
    }

    int aboveMedian = 0;
    for (long long reading : readings) {
        if (reading > lowerMedian) {
            ++aboveMedian;
        }
    }

    cout << lowerMedian << ' ' << mode << ' ' << aboveMedian << '\n';
    return 0;
}
