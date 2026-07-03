#include <iostream>
#include <string>
#include <vector>

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    std::cout << prompt;
    while (!(std::cin >> value) || value < minValue || value > maxValue) {
        std::cout << "Invalid value. Please enter a value from "
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
        std::cout << "Invalid value. Please enter a value from "
                  << minValue << " to " << maxValue << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    return value;
}

bool readYesNo(std::string prompt) {
    int value;

    std::cout << prompt << "Enter 1 for yes, 0 for no: ";
    while (!(std::cin >> value) || (value != 0 && value != 1)) {
        std::cout << "Invalid value. Enter 1 for yes, 0 for no: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    return value == 1;
}

bool isMissionSuccess(
    double oxygenLevel,
    int batteryLevel,
    double distanceToTarget,
    int dangerLevel,
    bool hasShield
) {
    if (oxygenLevel < 80.0) {
        return false;
    }

    if (batteryLevel < 50) {
        return false;
    }

    if (distanceToTarget > 1000.0) {
        return false;
    }

    if (dangerLevel > 7) {
        return false;
    }

    if (dangerLevel > 5 && !hasShield) {
        return false;
    }

    return true;
}

bool isPerfectMission(
    double oxygenLevel,
    int batteryLevel,
    double distanceToTarget,
    int dangerLevel
) {
    return oxygenLevel >= 95.0 &&
           batteryLevel >= 90 &&
           distanceToTarget <= 500.0 &&
           dangerLevel <= 3;
}

int calculateMissionScore(
    double oxygenLevel,
    int batteryLevel,
    double distanceToTarget,
    int dangerLevel,
    bool hasShield
) {
    if (!isMissionSuccess(
            oxygenLevel,
            batteryLevel,
            distanceToTarget,
            dangerLevel,
            hasShield
        )) {
        return 0;
    }

    int score = 10;

    if (isPerfectMission(
            oxygenLevel,
            batteryLevel,
            distanceToTarget,
            dangerLevel
        )) {
        score += 5;
    }

    return score;
}

void printFailReasons(
    double oxygenLevel,
    int batteryLevel,
    double distanceToTarget,
    int dangerLevel,
    bool hasShield
) {
    std::cout << "Reasons:" << std::endl;

    if (oxygenLevel < 80.0) {
        std::cout << "- Oxygen level is too low" << std::endl;
    }

    if (batteryLevel < 50) {
        std::cout << "- Battery level is too low" << std::endl;
    }

    if (distanceToTarget > 1000.0) {
        std::cout << "- Target is too far" << std::endl;
    }

    if (dangerLevel > 7) {
        std::cout << "- Danger level is too high" << std::endl;
    }

    if (dangerLevel > 5 && !hasShield) {
        std::cout << "- Shield required for high danger mission" << std::endl;
    }
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

int countSuccessMissions(std::vector<bool> successHistory) {
    int count = 0;
    
    for (bool success : successHistory) {
        if (success) {
            count++;
        }
    }
    
    return count;
}

void printMissionHistory(
    std::vector<std::string> missionNames,
    std::vector<double> oxygenHistory,
    std::vector<int> batteryHistory,
    std::vector<double> distanceHistory,
    std::vector<int> dangerHistory,
    std::vector<bool> shieldHistory,
    std::vector<int> scoreHistory,
    std::vector<bool> successHistory
) {
    std::cout << "===== Mission History =====" << std::endl;

    for (std::size_t i = 0; i < scoreHistory.size(); i++) {
        std::cout << "Mission " << i + 1
                  << " | Name: " << missionNames[i]
                  << " | Oxygen: " << oxygenHistory[i]
                  << " | Battery: " << batteryHistory[i]
                  << " | Distance: " << distanceHistory[i]
                  << " | Danger: " << dangerHistory[i]
                  << " | Shield: " << (shieldHistory[i] ? "Yes" : "No")
                  << " | Result: " << (successHistory[i] ? "SUCCESS" : "FAIL")
                  << " | Score: " << scoreHistory[i]
                  << std::endl;
    }

}

int main() {
    std::cout << "===== Space Academy Mission Log =====" << std::endl;

    std::cout << "Commander name: ";
    std::string commanderName;
    std::cin >> commanderName;

    int missionCount = readIntInRange("Number of missions (1-10): ", 1, 10);

    std::vector<std::string> missionNames;
    std::vector<double> oxygenHistory;
    std::vector<int> batteryHistory;
    std::vector<double> distanceHistory;
    std::vector<int> dangerHistory;
    std::vector<bool> shieldHistory;
    std::vector<int> scoreHistory;
    std::vector<bool> successHistory;

    for (int mission = 1; mission <= missionCount; mission++) {
        std::cout << std::endl;
        std::cout << "Mission " << mission << std::endl;

        std::cout << "Mission name (no space): ";
        std::string missionName;
        std::cin >> missionName;

        double oxygenLevel = readDoubleInRange("Oxygen level (0-100): ", 0.0, 100.0);
        int batteryLevel = readIntInRange("Battery level (0-100): ", 0, 100);
        double distanceToTarget = readDoubleInRange("Distance to target (0-2000): ", 0.0, 2000.0);
        int dangerLevel = readIntInRange("Danger level (1-10): ", 1, 10);
        bool hasShield = readYesNo("Has shield? ");

        bool success = isMissionSuccess(
            oxygenLevel,
            batteryLevel,
            distanceToTarget,
            dangerLevel,
            hasShield
        );

        int score = calculateMissionScore(
            oxygenLevel,
            batteryLevel,
            distanceToTarget,
            dangerLevel,
            hasShield
        );

        missionNames.push_back(missionName);
        oxygenHistory.push_back(oxygenLevel);
        batteryHistory.push_back(batteryLevel);
        distanceHistory.push_back(distanceToTarget);
        dangerHistory.push_back(dangerLevel);
        shieldHistory.push_back(hasShield);
        scoreHistory.push_back(score);
        successHistory.push_back(success);

        if (success) {
            std::cout << "Mission result: SUCCESS" << std::endl;
        } else {
            std::cout << "Mission result: FAIL" << std::endl;
            printFailReasons(
                oxygenLevel,
                batteryLevel,
                distanceToTarget,
                dangerLevel,
                hasShield
            );

        }

        std::cout << "Mission score: " << score << std::endl;
    }

    int totalScore = calculateTotalScore(scoreHistory);
    double averageScore = calculateAverageScore(scoreHistory);
    int bestScore = findBestScore(scoreHistory);
    int worstScore = findWorstScore(scoreHistory);
    int successCount = countSuccessMissions(successHistory);
    int completedMissions = scoreHistory.size();
    int failCount = completedMissions - successCount;

    std::cout << std::endl;
    std::cout << "===== Final Report =====" << std::endl;
    std::cout << "Commander: " << commanderName << std::endl;
    std::cout << "Missions: " << missionCount << std::endl;
    std::cout << "Success missions: " << successCount << std::endl;
    std::cout << "Failed missions: " << failCount << std::endl;
    std::cout << "Total score: " << totalScore << std::endl;
    std::cout << "Average score: " << averageScore << std::endl;
    std::cout << "Best score: " << bestScore << std::endl;
    std::cout << "Worst score: " << worstScore << std::endl;

    printMissionHistory(
        missionNames,
        oxygenHistory,
        batteryHistory,
        distanceHistory,
        dangerHistory,
        shieldHistory,
        scoreHistory,
        successHistory
    );

    return 0;
}