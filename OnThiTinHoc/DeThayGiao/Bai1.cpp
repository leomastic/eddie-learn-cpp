#include <iostream>
#include <cmath>
using namespace std;

struct PhanSo {
    int tu;
    int mau;
};

int ucln(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b; 
        a = temp;
    }
    return a;
}

void rutGon(PhanSo &p) {
    int uc = ucln(p.tu, p.mau);
    p.tu /= uc;
    p.mau /= uc;
    if (p.mau < 0) {
        p.tu = -p.tu;
        p.mau = -p.mau;
    }
}

PhanSo hieuPhanSo(PhanSo p1, PhanSo p2) {
    PhanSo ketQua;
    ketQua.tu = p1.tu * p2.mau - p2.tu * p1.mau;
    ketQua.mau = p1.mau * p2.mau;
    rutGon(ketQua);
    return ketQua;
}

void xuatPhanSo(PhanSo p) {
    if (p.mau == 1) {
        cout << p.tu << endl;
    } else {
        cout << p.tu << "/" << p.mau << endl;
    }
}

int main() {
    PhanSo p1, p2;

    cout << "Nhap phan so 1 (tu va mau): ";
    cin >> p1.tu >> p1.mau;

    cout << "Nhap phan so 2 (tu va mau): ";
    cin >> p2.tu >> p2.mau;

    PhanSo hieu = hieuPhanSo(p1, p2);

    cout << "Hieu hai phan so la: ";
    xuatPhanSo(hieu);

    return 0;
}    