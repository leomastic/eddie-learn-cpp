#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    long long n;
    // Đọc input, nếu không còn dữ liệu (EOF) thì dừng
    if (!(cin >> n)) return;

    vector<long long> sequence;
    long long max_val = n;

    sequence.push_back(n);
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        sequence.push_back(n);
        if (n > max_val) {
            max_val = n;
        }
    }

    // Dòng 1: In dãy đáp án
    for (size_t i = 0; i < sequence.size(); ++i) {
        cout << sequence[i] << (i + 1 == sequence.size() ? "" : " ");
    }
    cout << "\n";

    // Dòng 2: In tổng số bước
    cout << sequence.size() - 1 << "\n";

    // Dòng 3: In giá trị lớn nhất đạt được
    cout << max_val << "\n";
}

int main() {
    // Tối ưu tốc độ Input/Output cho Online Judge
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Hỗ trợ cả trường hợp đề bài có 1 test case hoặc nhiều test cases (Multiple Testcases)
    solve();

    return 0;
}