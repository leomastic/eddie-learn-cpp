#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    if (!(std::cin >> s)) return 0;

    std::vector<char> digits;
    for (char c : s) {
        if (isdigit(c)) {
            digits.push_back(c);
        }
    }

    sort(digits.begin(), digits.end());

    int idx = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (isdigit(s[i])) {
            s[i] = digits[idx++];
        }
    }

    std::cout << s << "\n";

    return 0;
}