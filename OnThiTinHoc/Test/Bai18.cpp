#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    int P;
    int M;
    std::cin >> N;
    std::cin >> P;

    if(P > N) {
        M = 1;
    }

    int calc;
    int i = 1;
    while(std::pow(P, i) < N) {
        calc = N / std::pow(P, i);
        M = std::max(M, calc);
        ++i;
    }

    std::cout << M << std::endl;
}