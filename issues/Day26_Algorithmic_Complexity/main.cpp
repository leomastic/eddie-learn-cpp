#include <iostream>
#include <vector>

long long linearWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        ++operations;
    }

    return operations;
}

long long quadraticWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ++operations;
        }
    }

    return operations;
}

int findMaximum(const std::vector<int>& numbers) {
    int maximum = numbers[0];

    for (int i = 1; i < static_cast<int>(numbers.size()); ++i) {
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }

    return maximum;
}

long long countEqualPairs(const std::vector<int>& a) {
    long long count = 0;
    const int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    int choice;
    if (!(std::cin >> choice)) return 0;

    if (choice == 1) {
        const std::vector<int> testSizes = {10, 100, 1000, 10000};

        for (int n : testSizes) {
            std::cout << "N = " << n
                      << ", linear = " << linearWork(n)
                      << ", quadratic = " << quadraticWork(n) << '\n';
        }
        return 0;
    }

    int n;
    if (!(std::cin >> n) || n < 0) return 0;
    if (choice == 2 && n == 0) return 0;

    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    if (choice == 2) {
        std::cout << findMaximum(numbers) << '\n';
    } else if (choice == 3) {
        std::cout << countEqualPairs(numbers) << '\n';
    }

    return 0;
}