#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("TBC1.INP", "r", stdin);
    freopen("TBC1.OUT", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if(!(cin >> n)) return 0;
    vector<int> B;
    for(int i = 0; i < n; ++i) {
        int x;
        if(!(cin >> x)) return 0;
        B.push_back(x);
    }
    
    int lastNum = 0;
    int num = B[0];
    cout << num << " ";
    lastNum = num;
    for(int i = 1; i < B.size(); ++i) {
        num = B[i]*(i+1) - lastNum;
        cout << num << " ";
        lastNum += num;
    }
    
    cout << '\n';

    return 0;
}