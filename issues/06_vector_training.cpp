//Space Training History
#include <iostream>
#include <string>
#include <vector>

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    std::cout << prompt;
    while (!(std::cin >> value) || value < minValue || value > maxValue) {
        std::cout << "Invalid input. Enter a number from "
                  << minValue << " to " << maxValue << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    return value;
}

double readDoubleInRange(std::string prompt, double minValue, double maxValue) {
    double value;

    std::cout << prompt;
    while (!(std::cin >> value) || value < minValue || value > maxValue) {
        std::cout << "Invalid input. Enter a number from "
                  << minValue << " to " << maxValue << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    return value;
}

bool isRoundPassed(double oxygenLevel, int batteryLevel) {
    return oxygenLevel >= 80.0 && batteryLevel >= 50;
}

int calculateRoundScore(double oxygenLevel, int batteryLevel) {
    if (oxygenLevel >= 80.0 && batteryLevel >= 50) {
        int score = 10;

        if (oxygenLevel >= 95.0 && batteryLevel >= 90) {
            score += 5;
        }

        return score;
    }

    return 0;
}

int calculateTotalScore(std::vector<int> scores) {
    int total = 0;

    for (int score : scores) {
        total += score;
    }

    return total;
}

double calculateAverageScore(std::vector<int> scores) {
    if (scores.size() == 0) {
        return 0.0;
    }

    int total = calculateTotalScore(scores);
    return static_cast<double>(total) / scores.size();
}

int findBestScore(std::vector<int> scores) {
    if (scores.size() == 0) {
        return 0;
    }

    int bestScore = scores[0];

    for (int score : scores) {
        if (score > bestScore) {
            bestScore = score;
        }
    }

    return bestScore;
}

int findWorstScore(std::vector<int> scores) {
    if (scores.size() == 0) {
        return 0;
    }

    int worstScore = scores[0];

    for (int score : scores) {
        if (score < worstScore) {
            worstScore = score;
        }
    }

    return worstScore;
}

void printRoundHistory(
    std::vector<double> oxygenHistory,
    std::vector<int> batteryHistory,
    std::vector<int> scoreHistory
) {
    std::cout << std::endl;
    std::cout << "===== Round History =====" << std::endl;

    for (int i = 0; i < scoreHistory.size(); i++) {
        std::cout << "Round " << i + 1
                  << " | Oxygen: " << oxygenHistory[i]
                  << " | Battery: " << batteryHistory[i]
                  << " | Score: " << scoreHistory[i]
                  << std::endl;
    }
}

int main() {
    std::cout << "===== Space Training History =====" << std::endl;

    std::cout << "Enter your name (No space): ";
    std::string name;
    std::cin >> name;

    int trainingRounds = readIntInRange("Enter training rounds (1-10): ", 1, 10);

    std::vector<double> oxygenHistory;
    std::vector<int> batteryHistory;
    std::vector<int> scoreHistory;

    for (int round = 1; round <= trainingRounds; round++) {
        std::cout << std::endl;
        std::cout << "Round " << round << std::endl;

        double oxygenLevel = readDoubleInRange("Enter oxygen level (0-100): ", 0.0, 100.0);
        int batteryLevel = readIntInRange("Enter battery level (0-100): ", 0, 100);

        int roundScore = calculateRoundScore(oxygenLevel, batteryLevel);

        oxygenHistory.push_back(oxygenLevel);
        batteryHistory.push_back(batteryLevel);
        scoreHistory.push_back(roundScore);

        if (isRoundPassed(oxygenLevel, batteryLevel)) {
            std::cout << "Round result: PASS" << std::endl;
        } else {
            std::cout << "Round result: FAIL" << std::endl;
        }

        std::cout << "Round score: " << roundScore << std::endl;
    }

    int totalScore = calculateTotalScore(scoreHistory);
    double averageScore = calculateAverageScore(scoreHistory);
    int bestScore = findBestScore(scoreHistory);
    int worstScore = findWorstScore(scoreHistory);

    std::cout << std::endl;
    std::cout << "===== Training Report =====" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Rounds: " << trainingRounds << std::endl;
    std::cout << "Total score: " << totalScore << std::endl;
    std::cout << "Average score: " << averageScore << std::endl;
    std::cout << "Best score: " << bestScore << std::endl;
    std::cout << "Worst score: " << worstScore << std::endl;

    printRoundHistory(oxygenHistory, batteryHistory, scoreHistory);

    return 0;
}