#include <bits/stdc++.h>

int char_dist(char a, char b) {
    int d = abs(a - b);
    return std::min(d, 26 - d);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    if (!(std::cin >> s)) return 0;

    int n = s.length();
    std::vector<int> pos[26];
    for (int i = 0; i < n; ++i) {
        pos[s[i] - 'a'].push_back(i + 1);
    }

    int q;
    std::cin >> q;
    while (q--) {
        int L, R;
        std::cin >> L >> R;

        std::vector<char> present_chars;
        for (int c = 0; c < 26; ++c) {
            auto it = lower_bound(pos[c].begin(), pos[c].end(), L);
            if (it != pos[c].end() && *it <= R) {
                present_chars.push_back((char)('a' + c));
            }
        }

        int max_d = 0;
        int sz = present_chars.size();
        for (int i = 0; i < sz; ++i) {
            for (int j = i + 1; j < sz; ++j) {
                max_d = std::max(max_d, char_dist(present_chars[i], present_chars[j]));
            }
        }

        std::cout << max_d << "\n";
    }

    return 0;
}