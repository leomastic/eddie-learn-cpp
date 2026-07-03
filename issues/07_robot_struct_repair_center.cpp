#include <iostream>
#include <string>
#include <vector>

struct Robot {
    std::string name;
    int batteryLevel;
    int damageLevel;
    double repairCostPerPoint;
    bool isCritical;
};

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue << std::endl;
            continue;
        }

        return value;
    }
}

double readDoubleInRange(std::string prompt, double minValue, double maxValue) {
    double value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue << std::endl;
            continue;
        }

        return value;
    }
}

bool readYesNo(std::string prompt) {
    int value;

    while (true) {
        std::cout << prompt << " (1 = yes, 0 = no): ";

        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Enter 1 for yes or 0 for no." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value == 1) {
            return true;
        }

        if (value == 0) {
            return false;
        }

        std::cout << "Please enter 1 or 0." << std::endl;
    }
}

Robot readRobot(int robotNumber) {
    Robot robot;

    std::cout << std::endl;
    std::cout << "Robot " << robotNumber << std::endl;

    std::cout << "Robot name (no space): ";
    std::cin >> robot.name;

    robot.batteryLevel = readIntInRange("Battery level (0-100): ", 0, 100);
    robot.damageLevel = readIntInRange("Damage level (0-100): ", 0, 100);
    robot.repairCostPerPoint = readDoubleInRange(
        "Repair cost per damage point (0-1000): ",
        0.0,
        1000.0
    );
    robot.isCritical = readYesNo("Is this robot mission critical? ");

    return robot;
}

double calculateRepairCost(const Robot& robot) {
    return robot.damageLevel * robot.repairCostPerPoint;
}

bool needsRepair(const Robot& robot) {
    return robot.damageLevel > 0;
}

bool isRobotDangerous(const Robot& robot) {
    return robot.batteryLevel < 30 || robot.damageLevel > 70;
}

bool isUrgentRepair(const Robot& robot) {
    if (robot.isCritical && robot.damageLevel >= 50) {
        return true;
    }

    if (robot.batteryLevel < 20 && robot.damageLevel >= 40) {
        return true;
    }

    return false;
}

int calculatePriorityScore(const Robot& robot) {
    int priority = robot.damageLevel;

    if (robot.batteryLevel < 30) {
        priority += 20;
    }

    if (robot.isCritical) {
        priority += 30;
    }

    if (robot.damageLevel >= 80) {
        priority += 20;
    }

    return priority;
}

double calculateTotalRepairCost(const std::vector<Robot>& robots) {
    double total = 0.0;

    for (const Robot& robot : robots) {
        total += calculateRepairCost(robot);
    }

    return total;
}

int countRobotsNeedingRepair(const std::vector<Robot>& robots) {
    int count = 0;

    for (const Robot& robot : robots) {
        if (needsRepair(robot)) {
            count++;
        }
    }

    return count;
}

int countDangerousRobots(const std::vector<Robot>& robots) {
    int count = 0;

    for (const Robot& robot : robots) {
        if (isRobotDangerous(robot)) {
            count++;
        }
    }

    return count;
}

int countUrgentRobots(const std::vector<Robot>& robots) {
    int count = 0;

    for (const Robot& robot : robots) {
        if (isUrgentRepair(robot)) {
            count++;
        }
    }

    return count;
}

int findHighestPriorityRobotIndex(const std::vector<Robot>& robots) {
    if (robots.size() == 0) {
        return -1;
    }

    int bestIndex = 0;
    int bestScore = calculatePriorityScore(robots[0]);

    for (int i = 1; i < robots.size(); i++) {
        const Robot& robot = robots[i];
        int score = calculatePriorityScore(robot);

        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }

    return bestIndex;
}

void printRobotReport(const std::vector<Robot>& robots) {
    std::cout << std::endl;
    std::cout << "===== Robot Report =====" << std::endl;

    for (int i = 0; i < robots.size(); i++) {
        const Robot& robot = robots[i];

        std::string status;

        if (!needsRepair(robot)) {
            status = "OK";
        } else if (isUrgentRepair(robot)) {
            status = "URGENT REPAIR";
        } else if (isRobotDangerous(robot)) {
            status = "DANGER";
        } else {
            status = "NEEDS REPAIR";
        }

        std::cout << "Robot " << i + 1
                  << " | Name: " << robot.name
                  << " | Battery: " << robot.batteryLevel
                  << " | Damage: " << robot.damageLevel
                  << " | Critical: " << (robot.isCritical ? "Yes" : "No")
                  << " | Repair cost: " << calculateRepairCost(robot)
                  << " | Priority: " << calculatePriorityScore(robot)
                  << " | Status: " << status
                  << std::endl;
    }
}

int main() {
    std::cout << "===== Robot Struct Repair Center =====" << std::endl;

    std::cout << "Engineer name: ";
    std::string engineerName;
    std::cin >> engineerName;

    int robotCount = readIntInRange("Number of robots (1-10): ", 1, 10);

    std::vector<Robot> robots;

    for (int i = 1; i <= robotCount; i++) {
        Robot robot = readRobot(i);
        robots.push_back(robot);

        std::cout << "Repair cost: " << calculateRepairCost(robot) << std::endl;
        std::cout << "Priority score: " << calculatePriorityScore(robot) << std::endl;

        if (!needsRepair(robot)) {
            std::cout << "Status: OK, no repair needed." << std::endl;
        } else if (isUrgentRepair(robot)) {
            std::cout << "Status: URGENT REPAIR" << std::endl;
        } else if (isRobotDangerous(robot)) {
            std::cout << "Status: DANGER" << std::endl;
        } else {
            std::cout << "Status: NEEDS REPAIR" << std::endl;
        }
    }

    double totalCost = calculateTotalRepairCost(robots);
    int repairCount = countRobotsNeedingRepair(robots);
    int dangerCount = countDangerousRobots(robots);
    int urgentCount = countUrgentRobots(robots);
    int highestPriorityIndex = findHighestPriorityRobotIndex(robots);

    std::cout << std::endl;
    std::cout << "===== Repair Center Summary =====" << std::endl;
    std::cout << "Engineer: " << engineerName << std::endl;
    std::cout << "Total robots: " << robotCount << std::endl;
    std::cout << "Robots needing repair: " << repairCount << std::endl;
    std::cout << "Dangerous robots: " << dangerCount << std::endl;
    std::cout << "Urgent repair robots: " << urgentCount << std::endl;
    std::cout << "Total repair cost: " << totalCost << std::endl;

    if (highestPriorityIndex >= 0) {
        Robot highestRobot = robots[highestPriorityIndex];

        std::cout << "Highest priority robot: "
                  << highestRobot.name
                  << " with priority score "
                  << calculatePriorityScore(highestRobot)
                  << std::endl;
    }

    printRobotReport(robots);

    return 0;
}