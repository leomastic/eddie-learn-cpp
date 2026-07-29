#include "robot.h"
#include "fleet.h"
#include "state_machine.h"
#include <iostream>
#include <iomanip>

void printAllRobots(const std::vector<Robot>& robots) {
    if (robots.empty()) {
        std::cout << "No robots in the fleet." << std::endl;
        return;
    }

    for (size_t i = 0; i < robots.size(); ++i) {
        std::cout << "Robot " << (i + 1) << ":" << std::endl;
        robots[i].print();
        std::cout << std::endl;
    }
}

int findRobotIndexByName(
    const std::vector<Robot>& robots,
    const std::string& name
) {
    for (size_t i = 0; i < robots.size(); ++i) {
        Robot robot = robots[i];
        if (robots[i].name() == name) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int findBestRescueRobotIndex(
    const std::vector<Robot>& robots
) {
    int bestIndex = -1;

    for (size_t i = 0; i < robots.size(); ++i) {
        const Robot& robot = robots[i];
        bool eligible = robot.batteryLevel() >= 15
            && robot.state() != RobotState::EmergencyStopped;

        if (!eligible) {
            continue;
        }

        if (bestIndex == -1) {
            bestIndex = static_cast<int>(i);
            continue;
        }

        const Robot& bestRobot = robots[bestIndex];
        if (robot.batteryLevel() > bestRobot.batteryLevel()
            || (robot.batteryLevel() == bestRobot.batteryLevel()
                && robot.distanceToObstacle() > bestRobot.distanceToObstacle())) {
            bestIndex = static_cast<int>(i);
        }
    }

    return bestIndex;
}

int countReadyRobots(const std::vector<Robot>& robots) {
    int count = 0;
    for (const Robot& robot : robots) {
        if (robot.batteryLevel() >= 30
            && robot.state() != RobotState::EmergencyStopped) {
            ++count;
        }
    }

    return count;
}

int countEmergencyRobots(const std::vector<Robot>& robots) {
    int count = 0;
    for (const Robot& robot : robots) {
        if (robot.decideAction() == RobotAction::EmergencyStop) {
            ++count;
        }
    }

    return count;
}

double calculateAverageBattery(
    const std::vector<Robot>& robots
) {
    if (robots.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const Robot& robot : robots) {
        sum += robot.batteryLevel();
    }

    return sum / robots.size();
}

void printFleetSummary(
    const std::vector<Robot>& robots
) {
    if (robots.empty()) {
        std::cout << "Fleet is empty." << std::endl;
        return;
    }

    int total = static_cast<int>(robots.size());
    int ready = countReadyRobots(robots);
    int emergency = countEmergencyRobots(robots);
    double averageBattery = calculateAverageBattery(robots);
    int bestIndex = findBestRescueRobotIndex(robots);

    std::cout << "===== Fleet Summary =====" << std::endl;
    std::cout << std::endl;
    std::cout << "Total robots: " << total << std::endl;
    std::cout << "Ready robots: " << ready << std::endl;
    std::cout << "Emergency robots: " << emergency << std::endl;
    std::cout << "Average battery: " << std::fixed << std::setprecision(1)
              << averageBattery << std::endl;

    if (bestIndex >= 0) {
        std::cout << "Best rescue robot: " << robots[bestIndex].name() << std::endl;
    } else {
        std::cout << "Best rescue robot: None" << std::endl;
    }
}