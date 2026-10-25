#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string S;
    if(!(std::cin >> S)) return false;

    std::vector<int> index;
    for(int i = 0; i < 26; ++i) {
        index.push_back(0);
    }

    for(int i = 0; i < S.length(); ++i) {
        int Index = S[i] - 'a' + 1;
        index[Index]++;
    }

    int count = 0;
    for(int i = 0; i < index.size(); ++i) {
        if(index[i] == 1) count++;
    }

    std::cout << count << '/n';

    return 0;
}