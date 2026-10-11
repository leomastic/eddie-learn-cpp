#include <iostream>
#include <vector>

long long gcdSlow(long long a, long long b) {
    if (a == 0) return b;
    if (b == 0) return a;

    long long limit = a < b ? a : b;
    long long answer = 1;

    for (long long d = 1; d <= limit; ++d) {
        if (a % d == 0 && b % d == 0) {
            answer = d;
        }
    }

    return answer;
}

long long gcdEuclid(long long a, long long b) {
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

int gcdStepCount(long long a, long long b) {
    int steps = 0;

    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
        ++steps;
    }

    return steps;
}

long long lcmUsingGcd(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    const long long g = gcdEuclid(a, b);
    return (a / g) * b;
}

bool simplifyFraction(long long numerator, long long denominator,
                      long long& reducedNumerator, long long& reducedDenominator) {
    if (denominator == 0) {
        return false;
    }

    const long long g = gcdEuclid(numerator, denominator);
    reducedNumerator = numerator / g;
    reducedDenominator = denominator / g;
    return true;
}

long long gcdOfVector(const std::vector<long long>& numbers) {
    long long currentGcd = 0;

    for (long long value : numbers) {
        currentGcd = gcdEuclid(currentGcd, value);
    }

    return currentGcd;
}

void runSlowVsEuclidDemo() {
    const long long samples[][2] = {
        {48, 18},
        {1000, 625},
        {100000, 99999},
        {1000000, 999999}
    };

    for (const auto& sample : samples) {
        const long long a = sample[0];
        const long long b = sample[1];
        const long long slowAnswer = gcdSlow(a, b);
        const long long euclidAnswer = gcdEuclid(a, b);
        const int euclidSteps = gcdStepCount(a, b);
        const long long slowChecks = (a < b) ? a : b;

        std::cout << "a=" << a << " b=" << b
                  << " slow=" << slowAnswer
                  << " Euclid=" << euclidAnswer
                  << " slowChecks=" << slowChecks
                  << " EuclidSteps=" << euclidSteps << '\n';
    }
}

int main() {
    int choice = 0;
    if (!(std::cin >> choice)) {
        return 0;
    }

    if (choice == 0) {
        runSlowVsEuclidDemo();
        return 0;
    }

    if (choice == 1) {
        long long a = 0;
        long long b = 0;
        std::cin >> a >> b;
        std::cout << gcdEuclid(a, b) << '\n';
        return 0;
    }

    if (choice == 2) {
        long long a = 0;
        long long b = 0;
        std::cin >> a >> b;
        std::cout << ((gcdEuclid(a, b) == 1) ? "YES" : "NO") << '\n';
        return 0;
    }

    if (choice == 3) {
        long long numerator = 0;
        long long denominator = 0;
        std::cin >> numerator >> denominator;

        long long reducedNumerator = 0;
        long long reducedDenominator = 0;
        if (!simplifyFraction(numerator, denominator, reducedNumerator, reducedDenominator)) {
            std::cerr << "Denominator cannot be zero.\n";
            return 1;
        }
        std::cout << reducedNumerator << ' ' << reducedDenominator << '\n';
        return 0;
    }

    if (choice == 4) {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100000) {
            std::cerr << "N must be between 1 and 100000.\n";
            return 1;
        }
        std::vector<long long> numbers(static_cast<std::size_t>(n));
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> numbers[static_cast<std::size_t>(i)])) {
                std::cerr << "Could not read all vector values.\n";
                return 1;
            }
        }
        std::cout << gcdOfVector(numbers) << '\n';
        return 0;
    }

    if (choice == 5) {
        long long a = 0;
        long long b = 0;
        std::cin >> a >> b;
        std::cout << lcmUsingGcd(a, b) << '\n';
        return 0;
    }

    if (choice == 6) {
        long long redObjects = 0;
        long long blueObjects = 0;
        std::cin >> redObjects >> blueObjects;
        std::cout << gcdEuclid(redObjects, blueObjects) << '\n';
        return 0;
    }

    if (choice == 7) {
        long long intervalA = 0;
        long long intervalB = 0;
        std::cin >> intervalA >> intervalB;
        std::cout << lcmUsingGcd(intervalA, intervalB) << '\n';
        return 0;
    }

    return 0;
}
