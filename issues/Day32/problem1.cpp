#include<bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if(!(cin >> n >> k)) return 0;

    string s = to_string(n);

    int sum = 0;
    for(int i = 0; i < s.length(); ++i) {
        int x = s[i] - '0';
        sum += x * (i + 1);
    }

    cout << sum << " ";

    if(sum % k != 0) {
        cout << "INVALID";
        return 0;
    }

    cout << "VALID";

    return 0;
}