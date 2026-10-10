#include <bits/stdc++.h>

bool checkOdd(int num) {
    return num % 2 != 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    int k = 0;
    if(!(std::cin >> N) || N <= 2) return 0;

    int a = 0;
    for(int i = 2; i <= N; i += 2) {
        a = i/2;
        ++k;
        while(!checkOdd(a)){
            a /= 2;
            ++k;
        }
    }

    std::cout << k << std::endl;

    return 0;
}