#include <iostream>
#include <string>

struct Robot {
    std::string name;
    int batteryLevel;
    int damageLevel;
    double repairCostPerPoint;
    bool isCritical;
};

double calculateRepairCost(Robot robot) {
    return robot.damageLevel * robot.repairCostPerPoint;
}

bool needsRepair(Robot robot) {
    return robot.damageLevel > 0;
}

bool isRobotDangerous(Robot robot) {
    return robot.batteryLevel < 30 || robot.damageLevel > 70;
}

bool isUrgentRepair(Robot robot) {
    if (robot.isCritical && robot.damageLevel >= 50) {
        return true;
    }

    if (robot.batteryLevel < 20 && robot.damageLevel >= 40) {
        return true;
    }

    return false;
}

int calculatePriorityScore(Robot robot) {
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

void printRobot(Robot robot) {
    std::cout << "Robot name: " << robot.name << std::endl;
    std::cout << "Battery: " << robot.batteryLevel << std::endl;
    std::cout << "Damage: " << robot.damageLevel << std::endl;
    std::cout << "Repair cost: " << calculateRepairCost(robot) << std::endl;
    std::cout << "Priority: " << calculatePriorityScore(robot) << std::endl;
    std::cout << "Critical: " << (robot.isCritical ? "Yes" : "No") << std::endl;

    if (!needsRepair(robot)) {
        std::cout << "Status: OK" << std::endl;
    } else if (isUrgentRepair(robot)) {
        std::cout << "Status: URGENT REPAIR" << std::endl;
    } else if (isRobotDangerous(robot)) {
        std::cout << "Status: DANGER" << std::endl;
    } else {
        std::cout << "Status: NEEDS REPAIR" << std::endl;
    }
}

int main() {
    Robot robot;

    robot.name = "RoboA";
    robot.batteryLevel = 80;
    robot.damageLevel = 20;
    robot.repairCostPerPoint = 5.5;
    robot.isCritical = true;

    printRobot(robot);

    return 0;
}