#include <bits/stdc++.h>

using namespace std;

int simplifyNumerator(int numerator, int denominator) {
    return numerator / (gcd(numerator, denominator));
}

int simplifyDenominator(int numerator, int denominator) {
    return denominator / (gcd(numerator, denominator));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    if(!(cin >> a)) return 0;
    if(!(cin >> b)) return 0;
    if(!(cin >> c)) return 0;
    if(!(cin >> d)) return 0;

    int x = (a*d) - (c*b);
    int y = b*d;

    int z = simplifyNumerator(x, y);
    y = simplifyDenominator(x, y);

    cout << z << " " << y << '\n';

    return 0;
}