#include <iostream>
#include <string>

void printTitle() {
    std::cout << "=====Space Training Simulator=====" << std::endl;
}

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

int calculateBonus(double oxygenLevel, int batteryLevel) {
    if (oxygenLevel >= 95.0 && batteryLevel >= 90) {
        return 5;
    }

    return 0;
}

void printFailReasons(double oxygenLevel, int batteryLevel) {
    std::cout << "Reasons:" << std::endl;

    if (oxygenLevel < 80.0) {
        std::cout << "- Oxygen level is too low" << std::endl;
    }

    if (batteryLevel < 50) {
        std::cout << "- Battery level is too low" << std::endl;
    }
}

void printFinalRating(int totalScore, int maxScore) {
    std::cout << "===== Final Rating =====" << std::endl;

    if (maxScore <= 0) {
        std::cout << "Rating: No completed training." << std::endl;
    } else if (totalScore >= maxScore * 1.1) {
        std::cout << "Rating: Super Duper!" << std::endl;
    } else if (totalScore >= maxScore * 0.8) {
        std::cout << "Rating: Excellent!" << std::endl;
    } else if (totalScore >= maxScore * 0.5) {
        std::cout << "Rating: Good!" << std::endl;
    } else {
        std::cout << "Rating: Need more training." << std::endl;
    }
}


int main() {
    printTitle();
    std::cout << "Enter your name (No space): ";
    std::string name;
    std::cin >> name;

    int age = readIntInRange("Enter your age (0-120): ", 0, 120);

    int trainingRounds = readIntInRange("Enter the training rounds (1-10): ", 1, 10);

    int passedRounds = 0;
    int failedRounds = 0;
    int totalScore = 0;

    int completedRounds = 0;

    for(int i = 1; i <= trainingRounds; ++i) {
        completedRounds++;
        std::cout << "Round " << i << std::endl;
        double oxygenLevel = readDoubleInRange("Enter oxygen level (0-100): ", 0, 100);

        int batteryLevel = readIntInRange("Enter battery level (0-100): ", 0, 100);
 
        if (isRoundPassed(oxygenLevel, batteryLevel)) {
            std::cout << "Round result: PASS" << std::endl;

            ++passedRounds;
            totalScore += 10;

            int bonus = calculateBonus(oxygenLevel, batteryLevel);
            if (bonus > 0) {
                std::cout << "Excellent round! Bonus +" << bonus << "." << std::endl;
                totalScore += bonus;
            }

        } else {
            std::cout << "Round result: FAIL" << std::endl;
            printFailReasons(oxygenLevel, batteryLevel);

            failedRounds++;
        }
        if (failedRounds >= 3) {
            std::cout << "Training stopped early. Too many failed rounds." << std::endl;
            break;
        }
    }

    std::cout << "=====Training Report=====" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Planned rounds: " << trainingRounds << std::endl;
    std::cout << "Completed rounds: " << completedRounds << std::endl;
    std::cout << "Passed rounds: " << passedRounds << std::endl;
    std::cout << "Failed rounds: " << failedRounds << std::endl;
    std::cout << "Total score: " << totalScore << std::endl;

    int maxScore = completedRounds * 10;
    printFinalRating(totalScore, maxScore);
    
    return 0;
}