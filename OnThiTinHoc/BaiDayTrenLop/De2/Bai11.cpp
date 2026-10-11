#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long k;
    if(!(std::cin >> k)) return 0;

    long long count = 0;
    for(int i = 1; i*i <= k; ++i) {
        for(int j = i + 1; j*i <= k; ++j) {
            ++count;
        }
    }

    std::cout << count << std::endl;

    return 0;
}