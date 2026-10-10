#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if(!(std::cin >> N)) return 0;

    int largestNum = 0;
    for(int i = 0; i < N; ++i) {
        int c;
        if(!(std::cin >> c)) return 0;

        largestNum = std::max(largestNum, c);
    }

    std::cout << largestNum << std::endl;

    return 0;
}