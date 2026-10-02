#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("CANBANG.INP");
    ofstream fout("CANBANG.OUT");

    int N;
    long long K;
    if (fin >> N >> K) {
        vector<long long> A(N);
        unordered_set<long long> elements;
        elements.reserve(N);

        for (int i = 0; i < N; ++i) {
            fin >> A[i];
            elements.insert(A[i]);
        }

        int count = 0;
        for (int i = 0; i < N; ++i) {
            if (elements.count(A[i] - K) && elements.count(A[i] + K)) {
                count++;
            }
        }

        fout << count << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}