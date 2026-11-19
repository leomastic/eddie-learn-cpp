#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    long long width = llabs(x1 - x2);
    long long height = llabs(y1 - y2);
    cout << (width - 1) * (height - 1) << '\n';

    return 0;
}
