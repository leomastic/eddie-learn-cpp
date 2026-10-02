#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("XOADOAN.INP");
    ofstream fout("XOADOAN.OUT");

    int N;
    if (!(fin >> N)) return 0;

    vector<long long> A(N + 1);
    vector<long long> P(N + 1, 0);
    long long total_sum = 0;

    for (int i = 1; i <= N; ++i) {
        fin >> A[i];
        total_sum += A[i];
        P[i] = P[i - 1] + A[i];
    }

    long long S;
    fin >> S;

    long long T = total_sum - S;

    if (T <= 0) {
        fout << 0 << "\n";
        return 0;
    }

    // Tim do dai R - L + 1 nho nhat sao cho P[R] - P[L-1] >= T
    int min_len = N + 1;
    deque<int> dq;

    for (int i = 0; i <= N; ++i) {
        // Lay cac chi so j tu deque sao cho P[i] - P[j] >= T
        while (!dq.empty() && P[i] - P[dq.front()] >= T) {
            min_len = min(min_len, i - dq.front());
            dq.pop_front();
        }

        // Duy tri deque gia tri P giam dan
        while (!dq.empty() && P[i] <= P[dq.back()]) {
            dq.pop_back();
        }

        dq.push_back(i);
    }

    if (min_len <= N) {
        fout << min_len << "\n";
    } else {
        fout << -1 << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}