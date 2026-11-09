#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    if(!(cin >> n)) return 0;
    if(!(cin >> d)) return 0;

    vector<int> A;
    for(int i = 0; i < n; ++i) {
        int a;
        if(!(cin >> a)) return 0;
        A.push_back(a);
    }

    vector<int> distFrom0 = {A[0]};
    int count = 0;

    return 0;
}