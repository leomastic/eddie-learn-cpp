#include <algorithm>
#include <iostream>
#include <vector>

bool canFinish(const std::vector<long long>& work, long long hoursAvailable,
               long long speed) {
    long long hoursNeeded = 0;
    for (long long amount : work) {
        hoursNeeded += amount / speed + (amount % speed != 0);
        if (hoursNeeded > hoursAvailable) return false;
    }
    return true;
}

long long minimumSpeed(const std::vector<long long>& work,
                       long long hoursAvailable) {
    long long maximumWork = 0;
    for (long long amount : work) {
        maximumWork = std::max(maximumWork, amount);
    }

    long long left = 1;
    long long right = maximumWork;
    while (left < right) {
        const long long middle = left + (right - left) / 2;
        if (canFinish(work, hoursAvailable, middle)) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    return left;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long hoursAvailable;
    if (!(std::cin >> n >> hoursAvailable)) return 0;

    std::vector<long long> work(n);
    for (long long& amount : work) {
        std::cin >> amount;
    }

    std::cout << minimumSpeed(work, hoursAvailable) << '\n';
    return 0;
}
