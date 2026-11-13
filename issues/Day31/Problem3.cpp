#include<bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> weights(N);
    for(int i = 0; i < N; ++i) {
        cin >> weights[i]; 
    }
    vector<int> x(Q);
    for(int i = 0; i < Q; ++i) {
        cin >> x[i];
    }

    sort(weights.begin(), weights.end());

    for(int i = 0; i < Q; ++i) {
        
    }

    return 0;
}