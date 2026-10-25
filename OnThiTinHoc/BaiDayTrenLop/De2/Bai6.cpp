#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if(!(std::cin >> N)) return 0;

    int countZeros = 0;
    while(N > 0) {
        countZeros += N / 5;
        N /= 5;
    }

    std::cout << countZeros << std::endl;

    return 0;
}