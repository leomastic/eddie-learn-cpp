#include <bits/stdc++.h>

using namespace std;

int readIntInRange(string prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cout << "Invalid value. Please enter a valid value." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (value < minValue || value > maxValue) {
            cout << "Invalid value. Please enter a value between "
                 << minValue << " and " << maxValue << endl;
            continue;
        }
        return value;
    }
}

double readDoubleInRange(string prompt, double minValue, double maxValue) {
    double value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cout << "Invalid value. Please enter a valid value." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (value < minValue || value > maxValue) {
            cout << "Invalid value. Please enter a value between "
                 << minValue << " and " << maxValue << endl;
            continue;
        }
        return value;
    }
}

vector<double> calculateFinishTimes(int n, double d) {
    vector<double> t_finish(n);
    for (int i = 0; i < n; i++) {
        double v;
        cin >> v;
        t_finish[i] = i + (d / v);
    }
    return t_finish;
}

int countOvertakes(int n, const vector<double>& t_finish) {
    int count = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (t_finish[i] < t_finish[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n = readIntInRange("Nhap so luong Robot n: ", 1, 1000);
    double d = readDoubleInRange("Nhap do dai duong dua d: ", 1.0, 1000000000.0);

    cout << "Nhap van toc cac robot: ";
    vector<double> t_finish = calculateFinishTimes(n, d);

    int totalOvertakes = countOvertakes(n, t_finish);

    cout << "So lan vuot nhau: " << totalOvertakes << endl;

    return 0;
}