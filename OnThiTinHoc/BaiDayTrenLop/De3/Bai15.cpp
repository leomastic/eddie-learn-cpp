#include <bits/stdc++.h>

int findIndex(char Char) {
    if (Char == 'A') return 1;
    if (Char == 'C') return 2;
    if (Char == 'G') return 3;
    if (Char == 'T') return 4;
    return -1;
}

bool isValid(const std::string& S) {
    for (size_t i = 0; i < S.length(); ++i) {
        if (S[i] != 'A' && S[i] != 'C' && S[i] != 'G' && S[i] != 'T') {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string S;
    if (!(std::cin >> S) || !isValid(S)) return 0;

    std::vector<int> Index(5, 0);
    std::vector<int> history;

    for (size_t i = 0; i < S.length(); ++i) {
        int index = findIndex(S[i]);
        ++Index[index];
        
        if (i > 0 && S[i] != S[i - 1]) {
            int prev_index = findIndex(S[i - 1]);
            int I = Index[prev_index];
            history.push_back(I);
            Index[prev_index] = 0;
        }
    }

    int ans = 0;
    for (size_t i = 0; i < history.size(); ++i) {
        ans = std::max(ans, history[i]);
    }

    std::cout << ans << '\n';

    return 0;
}