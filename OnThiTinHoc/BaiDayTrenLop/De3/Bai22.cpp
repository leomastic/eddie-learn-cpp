#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m, n;
    long long k;
    if (!(std::cin >> m >> n >> k)) return 0;

    long long total_fruits = 4 * k;
    std::vector<int> row_count(m + 1, 0);
    std::vector<int> col_count(n + 1, 0);
    std::vector<std::pair<int, int>> fruits(total_fruits);

    for (int i = 0; i < total_fruits; ++i) {
        int r, c;
        std::cin >> r >> c;
        fruits[i] = {r, c};
        row_count[r]++;
        col_count[c]++;
    }

    int r_min = -1, r_max = -1;
    long long current_row_sum = 0;
    for (int r = 1; r < m; ++r) {
        current_row_sum += row_count[r];
        if (current_row_sum == 2 * k) {
            if (r_min == -1) r_min = r;
            r_max = r;
        }
    }

    int c_min = -1, c_max = -1;
    long long current_col_sum = 0;
    for (int c = 1; c < n; ++c) {
        current_col_sum += col_count[c];
        if (current_col_sum == 2 * k) {
            if (c_min == -1) c_min = c;
            c_max = c;
        }
    }

    if (r_min == -1 || c_min == -1) {
        std::cout << 0 << "\n";
        return 0;
    }

    long long top_left_count = 0;
    for (int i = 0; i < total_fruits; ++i) {
        if (fruits[i].first <= r_min && fruits[i].second <= c_min) {
            top_left_count++;
        }
    }

    if (top_left_count == k) {
        long long valid_rows = r_max - r_min + 1;
        long long valid_cols = c_max - c_min + 1;
        std::cout << valid_rows * valid_cols << "\n";
    } else {
        std::cout << 0 << "\n";
    }

    return 0;
}