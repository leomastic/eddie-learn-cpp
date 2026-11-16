#include <bits/stdc++.h>
using namespace std;

long long chooseTwo(long long count) {
    return count * (count - 1) / 2;
}

long long chooseThree(long long count) {
    return count * (count - 1) * (count - 2) / 6;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, mod;
    if (!(cin >> n >> mod)) return 0;

    vector<long long> residueCount(mod, 0);
    for (int i = 0; i < n; ++i) {
        long long score;
        cin >> score;
        ++residueCount[score % mod];
    }

    long long answer = 0;
    for (int first = 0; first < mod; ++first) {
        for (int second = first; second < mod; ++second) {
            for (int third = second; third < mod; ++third) {
                if ((first + second + third) % mod != 0) continue;

                if (first == third) {
                    answer += chooseThree(residueCount[first]);
                } else if (first == second) {
                    answer += chooseTwo(residueCount[first]) * residueCount[third];
                } else if (second == third) {
                    answer += residueCount[first] * chooseTwo(residueCount[second]);
                } else {
                    answer += residueCount[first] * residueCount[second] *
                              residueCount[third];
                }
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
