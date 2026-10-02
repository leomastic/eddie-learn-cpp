#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("CHOXUAN.INP");
    ofstream fout("CHOXUAN.OUT");

    long long N, K;
    if (fin >> N >> K) {
        long long total_cost = 7 * K;
        if (N < total_cost) {
            fout << -1 << "\n";
        } else {
            fout << N - total_cost << "\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}