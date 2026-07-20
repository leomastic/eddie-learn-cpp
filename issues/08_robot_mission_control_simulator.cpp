#include <iostream>
#include <string>
#include <vector>

struct Robot {
    std::string name;

    int batteryLevel;
    int motorHealth;
    int sensorHealth;

    double distanceToObstacle;

    bool leftLineDetected;
    bool rightLineDetected;
};

enum class RobotStatus {
    Ready,
    NeedsCheck,
    Critical
};

enum class RobotAction {
    MoveForward,
    TurnLeft,
    TurnRight,
    Stop,
    EmergencyStop
};

enum class RobotMode {
    Manual,
    LineFollowing,
    ObstacleAvoidance
};

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid integer." << std::endl;
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
            std::cout << "Invalid value. Please enter a valid number." << std::endl;
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
        std::cout << prompt << "(1 for yes, 0 for no): ";

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter 1 or 0." << std::endl;
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

RobotMode readRobotMode() {
    int choice = readIntInRange(
        "Robot mode:\n1 = Manual\n2 = LineFollowing\n3 = ObstacleAvoidance\nChoose mode (1-3): ",
        1,
        3
    );

    if (choice == 1) {
        return RobotMode::Manual;
    }

    if (choice == 2) {
        return RobotMode::LineFollowing;
    }

    return RobotMode::ObstacleAvoidance;
}

Robot readRobot(int index) {
    Robot robot;

    std::cout << std::endl;
    std::cout << "Robot " << index << std::endl;
    std::cout << "Robot name (no space): ";
    std::cin >> robot.name;

    robot.batteryLevel = readIntInRange("Robot battery level (0-100): ", 0, 100);
    robot.motorHealth = readIntInRange("Robot motor health (0-100): ", 0, 100);
    robot.sensorHealth = readIntInRange("Robot sensor health (0-100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0-1000.0): ", 0.0, 1000.0);

    robot.leftLineDetected = readYesNo("Left line detected? ");
    robot.rightLineDetected = readYesNo("Right line detected? ");
    std::cout << std::endl;

    return robot;
}

RobotStatus calculateRobotStatus(const Robot& robot) {
    if (robot.batteryLevel < 15 || robot.motorHealth < 30 || robot.sensorHealth < 30) {
        return RobotStatus::Critical;
    }

    if (robot.batteryLevel < 40 || robot.motorHealth < 60 || robot.sensorHealth < 60) {
        return RobotStatus::NeedsCheck;
    }

    return RobotStatus::Ready;
}

RobotAction decideRobotAction(const Robot& robot, RobotMode mode) {
    RobotStatus status = calculateRobotStatus(robot);

    if (status == RobotStatus::Critical) {
        return RobotAction::EmergencyStop;
    }

    if (mode == RobotMode::Manual) {
        return RobotAction::Stop;
    }

    if (mode == RobotMode::ObstacleAvoidance) {
        if (robot.distanceToObstacle < 20.0) {
            return RobotAction::TurnRight;
        }

        return RobotAction::MoveForward;
    }

    if (mode == RobotMode::LineFollowing) {
        if (robot.leftLineDetected && robot.rightLineDetected) {
            return RobotAction::MoveForward;
        }

        if (robot.leftLineDetected && !robot.rightLineDetected) {
            return RobotAction::TurnLeft;
        }

        if (!robot.leftLineDetected && robot.rightLineDetected) {
            return RobotAction::TurnRight;
        }

        return RobotAction::Stop;
    }

    return RobotAction::Stop;
}

int calculateRobotScore(const Robot& robot) {
    int score = robot.batteryLevel + robot.motorHealth + robot.sensorHealth;

    if (robot.distanceToObstacle >= 100.0) {
        score += 20;
    }

    if (robot.motorHealth >= 90) {
        score += 10;
    }

    if (robot.sensorHealth >= 90) {
        score += 10;
    }

    if (robot.batteryLevel >= 80) {
        score += 10;
    }

    if (robot.distanceToObstacle < 20.0) {
        score -= 30;
    }

    if (robot.batteryLevel < 20) {
        score -= 20;
    }

    return score;
}

std::string robotStatusToString(RobotStatus status) {
    if (status == RobotStatus::Critical) {
        return "Critical";
    }

    if (status == RobotStatus::NeedsCheck) {
        return "Needs Check";
    }

    return "Ready";
}

std::string robotActionToString(RobotAction action) {
    if (action == RobotAction::EmergencyStop) {
        return "Emergency Stop";
    }

    if (action == RobotAction::MoveForward) {
        return "Move Forward";
    }

    if (action == RobotAction::TurnLeft) {
        return "Turn Left";
    }

    if (action == RobotAction::TurnRight) {
        return "Turn Right";
    }

    return "Stop";
}

std::string robotModeToString(RobotMode mode) {
    if (mode == RobotMode::Manual) {
        return "Manual";
    }

    if (mode == RobotMode::LineFollowing) {
        return "Line Following";
    }

    return "Obstacle Avoidance";
}

int countReadyRobots(const std::vector<Robot>& robots) {
    int count = 0;
    for (const Robot& robot : robots) {
        if (calculateRobotStatus(robot) == RobotStatus::Ready) {
            ++count;
        }
    }

    return count;
}

int countNeedsCheckRobots(const std::vector<Robot>& robots) {
    int count = 0;
    for (const Robot& robot : robots) {
        if (calculateRobotStatus(robot) == RobotStatus::NeedsCheck) {
            ++count;
        }
    }

    return count;
}

int countCriticalRobots(const std::vector<Robot>& robots) {
    int count = 0;
    for (const Robot& robot : robots) {
        if (calculateRobotStatus(robot) == RobotStatus::Critical) {
            ++count;
        }
    }

    return count;
}

int countEmergencyStopRobots(const std::vector<Robot>& robots, RobotMode mode) {
    int count = 0;
    for (const Robot& robot : robots) {
        if (decideRobotAction(robot, mode) == RobotAction::EmergencyStop) {
            ++count;
        }
    }

    return count;
}

int findBestRobotIndex(const std::vector<Robot>& robots) {
    if (robots.empty()) {
        return -1;
    }

    int bestIndex = -1;
    int bestScore = 0;

    for (int i = 0; i < static_cast<int>(robots.size()); ++i) {
        int score = calculateRobotScore(robots[i]);

        if (bestIndex < 0 || score > bestScore) {
            bestIndex = i;
            bestScore = score;
        }
    }

    return bestIndex;
}

void printRobotReport(const std::vector<Robot>& robots, RobotMode mode) {
    std::cout << "\n===== Robot Report =====" << std::endl;
    std::cout << "Total robot: " << robots.size() << std::endl;

    for (size_t i = 0; i < robots.size(); ++i) {
        const Robot& robot = robots[i];
        RobotStatus status = calculateRobotStatus(robot);
        RobotAction action = decideRobotAction(robot, mode);

        std::cout << "\nRobot " << (i + 1) << ": " << robot.name << std::endl;
        std::cout << "Battery: " << robot.batteryLevel << std::endl;
        std::cout << "Motor health: " << robot.motorHealth << std::endl;
        std::cout << "Sensor health: " << robot.sensorHealth << std::endl;
        std::cout << "Distance to obstacle: " << robot.distanceToObstacle << std::endl;
        std::cout << "Left line detected: " << (robot.leftLineDetected ? "Yes" : "No") << std::endl;
        std::cout << "Right line detected: " << (robot.rightLineDetected ? "Yes" : "No") << std::endl;
        std::cout << "Status: " << robotStatusToString(status) << std::endl;
        std::cout << "Mode: " << robotModeToString(mode) << std::endl;
        std::cout << "Action: " << robotActionToString(action) << std::endl;
        std::cout << "Score: " << calculateRobotScore(robot) << std::endl;
    }

    std::cout << "\n===== Summary =====" << std::endl;
    std::cout << "Ready robots: " << countReadyRobots(robots) << std::endl;
    std::cout << "Needs check robots: " << countNeedsCheckRobots(robots) << std::endl;
    std::cout << "Critical robots: " << countCriticalRobots(robots) << std::endl;
    std::cout << "Emergency stop robots: " << countEmergencyStopRobots(robots, mode) << std::endl;

    int bestIndex = findBestRobotIndex(robots);
    if (bestIndex >= 0) {
        std::cout << "Best robot: "
                  << robots[bestIndex].name
                  << " with score "
                  << calculateRobotScore(robots[bestIndex])
                  << std::endl;
    } else {
        std::cout << "Best robot: None" << std::endl;
    }
}

int main() {
    std::cout << "===== Robot Mission Control Simulator =====" << std::endl;

    std::cout << "Operator name: ";
    std::string operatorName;
    std::getline(std::cin, operatorName);

    RobotMode mode = readRobotMode();
    int robotCount = readIntInRange("Number of robots (1-10): ", 1, 10);

    std::vector<Robot> robots;
    robots.reserve(robotCount);
    for (int i = 0; i < robotCount; ++i) {
        robots.push_back(readRobot(i + 1));
    }

    printRobotReport(robots, mode);
    return 0;
}



// siuuuuuuuu


// Dong nay la 400 dong =)