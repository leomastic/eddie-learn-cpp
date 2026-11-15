#include<bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string code;
    long long k;
    if(!(cin >> code >> k)) return 0;

    long long sum = 0;
    for(int i = 0; i < static_cast<int>(code.length()); ++i) {
        int digit = code[i] - '0';
        sum += digit * (i + 1LL);
    }

    cout << sum << " ";

    if(sum % k != 0) {
        cout << "INVALID\n";
        return 0;
    }

    cout << "VALID\n";

    return 0;
}