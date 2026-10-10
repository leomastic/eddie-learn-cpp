#include <bits/stdc++.h>

int findBestNumber(int number) {
    int bestNumber = 0;
    while(number > 0){
        bestNumber = std::max(bestNumber, number % 10);
        number /= 10;
    }

    return bestNumber;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int number;
    if(!(std::cin >> number)) return 0;

    int bestNumber = findBestNumber(number);

    std::cout << bestNumber << std::endl;

    return 0;
}