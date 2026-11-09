#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int m;
    if (!(std::cin >> n >> m)) return 0;

    std::vector<long long> teamA(n);
    std::vector<long long> teamB(m);
    for (long long& score : teamA) {
        std::cin >> score;
    }
    for (long long& score : teamB) {
        std::cin >> score;
    }

    std::sort(teamA.begin(), teamA.end());
    std::sort(teamB.begin(), teamB.end());

    int i = 0;
    int j = 0;
    long long best = teamA[0] >= teamB[0]
                         ? teamA[0] - teamB[0]
                         : teamB[0] - teamA[0];

    while (i < n && j < m) {
        const long long difference = teamA[i] >= teamB[j]
                                         ? teamA[i] - teamB[j]
                                         : teamB[j] - teamA[i];
        best = std::min(best, difference);

        if (teamA[i] < teamB[j]) {
            ++i;
        } else {
            ++j;
        }
    }

    std::cout << best << '\n';
    return 0;
}
