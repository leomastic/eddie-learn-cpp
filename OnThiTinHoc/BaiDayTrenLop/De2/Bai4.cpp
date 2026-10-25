#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if (!(std::cin >> N) || N <= 0) {
        std::cout << "N khong hop le!" << std::endl;
        return 0;
    }

    // Mảng đánh dấu các số từ 1 đến N (khởi tạo ban đầu là false)
    std::vector<bool> visited(N + 1, false);
    bool isValid = true;

    for (int i = 0; i < N - 1; ++i) {
        int number;
        std::cin >> number;

        // Kiểm tra số có nằm trong [1, N] và chưa từng xuất hiện không
        if (number < 1 || number > N || visited[number]) {
            isValid = false; // Dữ liệu sai (trùng lặp hoặc ngoài phạm vi)
        } else {
            visited[number] = true;
        }
    }

    if (!isValid) {
        std::cout << "Du lieu nhap vao sai quy tac!" << std::endl;
        return 0;
    }

    // Tìm số chưa được đánh dấu (chưa xuất hiện)
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            std::cout << i << std::endl;
            break;
        }
    }

    return 0;
}