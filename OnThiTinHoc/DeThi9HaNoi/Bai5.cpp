#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
long long K;
vector<long long> A;

// Ham kiem tra voi suc cong pha X co the pha huy het bia trong <= K lan ban khong
bool check(long long X) {
    vector<long long> hp = A;
    long long shots = 0;
    int curr = 0;
    long long max_range = sqrt(X); // Khoang anh huong toi da

    while (curr < N) {
        // Tim tam bia dau tien chua bi pha huy
        while (curr < N && hp[curr] <= 0) {
            curr++;
        }
        if (curr >= N) break;

        // Ban vao tam bia curr
        shots++;
        if (shots > K) return false;

        // Tinh so lan ban can thiet neu ban lien tuc vao curr de ha guc no
        long long cnt = (hp[curr] + X - 1) / X; 
        if (shots + cnt - 1 > K) return false;

        shots += (cnt - 1);

        // Cap nhat do ben cho cac tam bia phia sau bi anh huong
        int limit = min((long long)N - 1, curr + max_range);
        for (int j = curr; j <= limit; ++j) {
            long long dist = j - curr;
            long long dmg = max(0LL, X - dist * dist);
            if (dmg > 0) {
                hp[j] -= dmg * cnt;
            }
        }
    }

    return shots <= K;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("BANSUNG.INP");
    ofstream fout("BANSUNG.OUT");

    if (fin >> N >> K) {
        A.resize(N);
        long long max_A = 0;
        for (int i = 0; i < N; ++i) {
            fin >> A[i];
            max_A = max(max_A, A[i]);
        }

        // Tim kiem nhi phan gia tri X
        long long low = 1, high = max_A + 1000000LL, ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid - 1; // Tim X nho hon
            } else {
                low = mid + 1;  // Tang X
            }
        }

        fout << ans << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}