#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Hàm tính khoảng cách vòng tròn giữa 2 ký tự
inline int char_dist(char c1, char c2) {
    int diff = abs(c1 - c2);
    return min(diff, 26 - diff);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("KHOANGCACH.INP");
    ofstream fout("KHOANGCACH.OUT");

    string S;
    if (fin >> S) {
        int N = S.length();
        
        // Mảng mảng cộng dồn lưu tần suất xuất hiện của 26 ký tự
        vector<vector<int>> pref(N + 1, vector<int>(26, 0));
        for (int i = 0; i < N; ++i) {
            for (int c = 0; c < 26; ++c) {
                pref[i + 1][c] = pref[i][c];
            }
            pref[i + 1][S[i] - 'a']++;
        }

        int Q;
        fin >> Q;
        while (Q--) {
            int L, R;
            fin >> L >> R;

            // Tìm các ký tự xuất hiện trong đoạn S[L..R]
            vector<char> present_chars;
            for (int c = 0; c < 26; ++c) {
                if (pref[R][c] - pref[L - 1][c] > 0) {
                    present_chars.push_back('a' + c);
                }
            }

            int max_dist = 0;
            int num_chars = present_chars.size();
            for (int i = 0; i < num_chars; ++i) {
                for (int j = i + 1; j < num_chars; ++j) {
                    max_dist = max(max_dist, char_dist(present_chars[i], present_chars[j]));
                }
            }

            fout << max_dist << "\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}