#include <iostream>
#include <string>
#include <vector>

enum class RobotMode {
    Manual,
    Search,
    Rescue,
    ObstacleAvoidance,
    LineFollowing,
    EmergencyStop
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
    ScanArea,
    RescueVictim,
    EmergencyStop
};

enum class MissionPriority {
    Low,
    Medium,
    High,
    Critical
};

enum class MenuChoice {
    ShowAllRobots,
    ShowSummary,
    ChangeRobotMode,
    UpdateRobotSensors,
    DecideRobotAction,
    ChargeRobot,
    DamageRobot,
    RepairRobot,
    EmergencyStopRobot,
    FindBestRobot,
    Exit
};

struct Robot {
    std::string name;

    int batteryLevel;
    int motorHealth;
    int sensorHealth;

    double distanceToObstacle;

    bool victimDetected;
    bool leftLineDetected;
    bool rightLineDetected;

    RobotMode mode;
};

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue << " and " << maxValue << "." << std::endl;
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
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue << " and " << maxValue << "." << std::endl;
            continue;
        }

        return value;
    }
}

bool readYesNo(std::string prompt) {
    int value;

    while (true) {
        std::cout << prompt << " (1 for yes, 0 for no): ";

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (value) {
            case 1:
                return true;

            case 0:
                return false;

            default:
                std::cout << "Please enter 1 or 0." << std::endl;
                break;
        }
    }
}

RobotMode readRobotMode() {
    int choice = readIntInRange(
        "Robot mode:\n1 = Manual\n2 = Search\n3 = Rescue\n4 = ObstacleAvoidance\n5 = LineFollowing\n6 = EmergencyStop\nChoose mode (1-6): ",
        1,
        6
    );

    switch (choice) {
        case 1:
            return RobotMode::Manual;

        case 2:
            return RobotMode::Search;

        case 3:
            return RobotMode::Rescue;

        case 4:
            return RobotMode::ObstacleAvoidance;

        case 5:
            return RobotMode::LineFollowing;

        case 6:
            return RobotMode::EmergencyStop;

        default:
            return RobotMode::Manual;
    }
}

MenuChoice readMenuChoice() {
    int choice = readIntInRange(
        "\nMenu choice (1-11):\n"
        "1 = Show all robots\n"
        "2 = Show summary\n"
        "3 = Change robot mode\n"
        "4 = Update robot sensors\n"
        "5 = Decide robot action\n"
        "6 = Charge robot\n"
        "7 = Damage robot\n"
        "8 = Repair robot\n"
        "9 = Emergency stop robot\n"
        "10 = Find best robot\n"
        "11 = Exit\n"
        "Choose: ",
        1,
        11
    );

    switch (choice) {
        case 1:
            return MenuChoice::ShowAllRobots;

        case 2:
            return MenuChoice::ShowSummary;

        case 3:
            return MenuChoice::ChangeRobotMode;

        case 4:
            return MenuChoice::UpdateRobotSensors;

        case 5:
            return MenuChoice::DecideRobotAction;

        case 6:
            return MenuChoice::ChargeRobot;

        case 7:
            return MenuChoice::DamageRobot;

        case 8:
            return MenuChoice::RepairRobot;

        case 9:
            return MenuChoice::EmergencyStopRobot;

        case 10:
            return MenuChoice::FindBestRobot;

        default:
            return MenuChoice::Exit;
    }
}

Robot readRobot(int index) {
    Robot robot;

    std::cout << "\nRobot " << index << std::endl;
    std::cout << "Robot name: ";
    std::cin >> robot.name;

    robot.batteryLevel = readIntInRange("Battery level (0-100): ", 0, 100);
    robot.motorHealth = readIntInRange("Motor health (0-100): ", 0, 100);
    robot.sensorHealth = readIntInRange("Sensor health (0-100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0-1000.0): ", 0.0, 1000.0);

    robot.victimDetected = readYesNo("Victim detected?");
    robot.leftLineDetected = readYesNo("Left line detected?");
    robot.rightLineDetected = readYesNo("Right line detected?");

    robot.mode = readRobotMode();

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

MissionPriority calculateMissionPriority(const Robot& robot) {
    if (robot.victimDetected && robot.distanceToObstacle < 20.0) {
        return MissionPriority::Critical;
    }

    if (robot.victimDetected) {
        return MissionPriority::High;
    }

    if (robot.distanceToObstacle < 50.0 || robot.batteryLevel < 40) {
        return MissionPriority::Medium;
    }

    return MissionPriority::Low;
}

RobotAction decideRobotAction(const Robot& robot) {
    if (calculateRobotStatus(robot) == RobotStatus::Critical) {
        return RobotAction::EmergencyStop;
    }

    if (robot.mode == RobotMode::EmergencyStop) {
        return RobotAction::EmergencyStop;
    }

    switch (robot.mode) {
        case RobotMode::Manual:
            return RobotAction::Stop;

        case RobotMode::Search:
            if (robot.victimDetected) {
                return RobotAction::Stop;
            }

            return RobotAction::ScanArea;

        case RobotMode::Rescue:
            if (robot.victimDetected && robot.distanceToObstacle < 20.0) {
                return RobotAction::RescueVictim;
            }

            if (robot.victimDetected) {
                return RobotAction::MoveForward;
            }

            return RobotAction::ScanArea;

        case RobotMode::ObstacleAvoidance:
            if (robot.distanceToObstacle < 20.0) {
                return RobotAction::TurnRight;
            }

            return RobotAction::MoveForward;

        case RobotMode::LineFollowing:
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

        default:
            return RobotAction::Stop;
    }
}

int calculateRobotScore(const Robot& robot) {
    int score = robot.batteryLevel + robot.motorHealth + robot.sensorHealth;

    if (robot.victimDetected) {
        score += 50;
    }

    if (robot.distanceToObstacle >= 100.0) {
        score += 20;
    }

    if (robot.batteryLevel >= 80) {
        score += 10;
    }

    if (robot.motorHealth >= 90) {
        score += 10;
    }

    if (robot.sensorHealth >= 90) {
        score += 10;
    }

    if (robot.mode == RobotMode::Rescue) {
        score += 20;
    }

    if (robot.mode == RobotMode::Search) {
        score += 10;
    }

    if (robot.distanceToObstacle < 20.0) {
        score -= 30;
    }

    if (robot.batteryLevel < 20) {
        score -= 20;
    }

    if (calculateRobotStatus(robot) == RobotStatus::Critical) {
        score -= 50;
    }

    return score;
}

std::string robotModeToString(RobotMode mode) {
    switch (mode) {
        case RobotMode::Manual:
            return "Manual";

        case RobotMode::Search:
            return "Search";

        case RobotMode::Rescue:
            return "Rescue";

        case RobotMode::ObstacleAvoidance:
            return "Obstacle Avoidance";

        case RobotMode::LineFollowing:
            return "Line Following";

        case RobotMode::EmergencyStop:
            return "Emergency Stop";
    }
    return "Unknown";
}

std::string robotStatusToString(RobotStatus status) {
    switch (status) {
        case RobotStatus::Ready:
            return "Ready";

        case RobotStatus::NeedsCheck:
            return "Needs Check";

        case RobotStatus::Critical:
            return "Critical";

    }
    return "Unknown";
}

std::string missionPriorityToString(MissionPriority priority) {
    switch (priority) {
        case MissionPriority::Low:
            return "Low";

        case MissionPriority::Medium:
            return "Medium";

        case MissionPriority::High:
            return "High";

        case MissionPriority::Critical:
            return "Critical";

    }
    return "Unknown";
}

std::string robotActionToString(RobotAction action) {
    switch (action) {
        case RobotAction::MoveForward:
            return "Move Forward";

        case RobotAction::TurnLeft:
            return "Turn Left";

        case RobotAction::TurnRight:
            return "Turn Right";

        case RobotAction::Stop:
            return "Stop";

        case RobotAction::ScanArea:
            return "Scan Area";

        case RobotAction::RescueVictim:
            return "Rescue Victim";

        case RobotAction::EmergencyStop:
            return "Emergency Stop";

    }
    return "Unknown";
}

std::string menuChoiceToString(MenuChoice choice) {
    switch (choice) {
        case MenuChoice::ShowAllRobots:
            return "Show All Robots";

        case MenuChoice::ShowSummary:
            return "Show Summary";

        case MenuChoice::ChangeRobotMode:
            return "Change Robot Mode";

        case MenuChoice::UpdateRobotSensors:
            return "Update Robot Sensors";

        case MenuChoice::DecideRobotAction:
            return "Decide Robot Action";

        case MenuChoice::ChargeRobot:
            return "Charge Robot";

        case MenuChoice::DamageRobot:
            return "Damage Robot";

        case MenuChoice::RepairRobot:
            return "Repair Robot";

        case MenuChoice::EmergencyStopRobot:
            return "Emergency Stop Robot";

        case MenuChoice::FindBestRobot:
            return "Find Best Robot";

        case MenuChoice::Exit:
            return "Exit";

    }
    return "Unknown";
}

void printMenu() {
    std::cout << "\n===== Robot Rescue Mission Control =====" << std::endl;
    std::cout << "1. Show all robots" << std::endl;
    std::cout << "2. Show summary" << std::endl;
    std::cout << "3. Change robot mode" << std::endl;
    std::cout << "4. Update robot sensors" << std::endl;
    std::cout << "5. Decide robot action" << std::endl;
    std::cout << "6. Charge robot" << std::endl;
    std::cout << "7. Damage robot" << std::endl;
    std::cout << "8. Repair robot" << std::endl;
    std::cout << "9. Emergency stop robot" << std::endl;
    std::cout << "10. Find best robot" << std::endl;
    std::cout << "11. Exit" << std::endl;
}

void printRobotReport(const Robot& robot, int index) {
    RobotStatus status = calculateRobotStatus(robot);
    MissionPriority priority = calculateMissionPriority(robot);
    RobotAction action = decideRobotAction(robot);
    int score = calculateRobotScore(robot);

    std::cout << "\nRobot " << index << ": " << robot.name << std::endl;
    std::cout << "Battery: " << robot.batteryLevel << std::endl;
    std::cout << "Motor health: " << robot.motorHealth << std::endl;
    std::cout << "Sensor health: " << robot.sensorHealth << std::endl;
    std::cout << "Distance to obstacle: " << robot.distanceToObstacle << std::endl;
    std::cout << "Victim detected: " << (robot.victimDetected ? "Yes" : "No") << std::endl;
    std::cout << "Left line detected: " << (robot.leftLineDetected ? "Yes" : "No") << std::endl;
    std::cout << "Right line detected: " << (robot.rightLineDetected ? "Yes" : "No") << std::endl;
    std::cout << "Mode: " << robotModeToString(robot.mode) << std::endl;
    std::cout << "Status: " << robotStatusToString(status) << std::endl;
    std::cout << "Mission priority: " << missionPriorityToString(priority) << std::endl;
    std::cout << "Suggested action: " << robotActionToString(action) << std::endl;
    std::cout << "Score: " << score << std::endl;
}

void printAllRobots(const std::vector<Robot>& robots) {
    if (robots.empty()) {
        std::cout << "No robots available." << std::endl;
        return;
    }

    for (int i = 0; i < static_cast<int>(robots.size()); ++i) {
        printRobotReport(robots[i], i + 1);
    }
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

int countVictimDetectedRobots(const std::vector<Robot>& robots) {
    int count = 0;
    for (const Robot& robot : robots) {
        if (robot.victimDetected) {
            ++count;
        }
    }
    return count;
}

int countEmergencyStopRobots(const std::vector<Robot>& robots) {
    int count = 0;

    for (const Robot& robot : robots) {
        if (decideRobotAction(robot) == RobotAction::EmergencyStop) {
            ++count;
        }
    }

    return count;
}

int findBestRobotIndex(const std::vector<Robot>& robots) {
    if (robots.empty()) {
        return -1;
    }

    int bestIndex = 0;
    int bestScore = calculateRobotScore(robots[0]);

    for (int i = 1; i < static_cast<int>(robots.size()); ++i) {
        int score = calculateRobotScore(robots[i]);

        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }

    return bestIndex;
}

void printSummary(const std::vector<Robot>& robots) {
    std::cout << "\nTotal robots: " << static_cast<int>(robots.size()) << std::endl;
    std::cout << "Ready robots: " << countReadyRobots(robots) << std::endl;
    std::cout << "Needs check robots: " << countNeedsCheckRobots(robots) << std::endl;
    std::cout << "Critical robots: " << countCriticalRobots(robots) << std::endl;
    std::cout << "Victim detected robots: " << countVictimDetectedRobots(robots) << std::endl;
    std::cout << "Emergency stop robots: " << countEmergencyStopRobots(robots) << std::endl;
}

int readRobotIndex(const std::vector<Robot>& robots) {
    if (robots.empty()) {
        return -1;
    }

    return readIntInRange(
        "Enter robot number: ",
        1,
        static_cast<int>(robots.size())
    ) - 1;
}

void changeRobotMode(std::vector<Robot>& robots) {
    int index = readRobotIndex(robots);
    std::cout << "Changing mode for robot " << robots[index].name << "." << std::endl;

    robots[index].mode = readRobotMode();
    std::cout << "Mode updated to " << robotModeToString(robots[index].mode) << "." << std::endl;
}

void updateRobotSensors(std::vector<Robot>& robots) {
    int index = readRobotIndex(robots);
    std::cout << "Updating sensors for robot " << robots[index].name << "." << std::endl;
    robots[index].distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0-1000.0): ", 0.0, 1000.0);
    robots[index].victimDetected = readYesNo("Victim detected?");
    robots[index].leftLineDetected = readYesNo("Left line detected?");
    robots[index].rightLineDetected = readYesNo("Right line detected?");

    std::cout << "Sensor data updated." << std::endl;
}

void chargeRobot(std::vector<Robot>& robots) {
    int index = readRobotIndex(robots);
    std::cout << "Charging robot " << robots[index].name << "." << std::endl;
    robots[index].batteryLevel += 20;

    if (robots[index].batteryLevel > 100) {
        robots[index].batteryLevel = 100;
    }
    std::cout << "Battery level is now " << robots[index].batteryLevel << "." << std::endl;
}

void damageRobot(std::vector<Robot>& robots) {
    int index = readRobotIndex(robots);
    int damage = readIntInRange("Damage amount (1-50): ", 1, 50);
    std::cout << "Damaging robot " << robots[index].name << " by " << damage << "." << std::endl;
    robots[index].motorHealth -= damage;
    robots[index].sensorHealth -= damage;

    if (robots[index].motorHealth < 0) {
        robots[index].motorHealth = 0;
    }

    if (robots[index].sensorHealth < 0) {
        robots[index].sensorHealth = 0;
    }

    std::cout << "Motor health is now " << robots[index].motorHealth << "." << std::endl;
    std::cout << "Sensor health is now " << robots[index].sensorHealth << "." << std::endl;
}

void repairRobot(std::vector<Robot>& robots) {
    int index = readRobotIndex(robots);
    std::cout << "Repairing robot " << robots[index].name << "." << std::endl;
    robots[index].motorHealth += 20;
    robots[index].sensorHealth += 20;

    if (robots[index].motorHealth > 100) {
        robots[index].motorHealth = 100;
    }

    if (robots[index].sensorHealth > 100) {
        robots[index].sensorHealth = 100;
    }

    std::cout << "Motor health is now " << robots[index].motorHealth << "." << std::endl;
    std::cout << "Sensor health is now " << robots[index].sensorHealth << "." << std::endl;
}

void emergencyStopRobot(std::vector<Robot>& robots) {
    int index = readRobotIndex(robots);
    robots[index].mode = RobotMode::EmergencyStop;
    std::cout << "Robot " << robots[index].name << " is now in Emergency Stop mode." << std::endl;
}

void showRobotAction(const std::vector<Robot>& robots) {
    int index = readRobotIndex(robots);
    RobotAction action = decideRobotAction(robots[index]);
    std::cout << "Robot " << robots[index].name << " should: " << robotActionToString(action) << std::endl;
}

void showBestRobot(const std::vector<Robot>& robots) {
    int bestIndex = findBestRobotIndex(robots);

    if (bestIndex < 0) {
        std::cout << "No robots available to evaluate." << std::endl;
        return;
    }

    std::cout << "Best robot: " << robots[bestIndex].name << " with score " << calculateRobotScore(robots[bestIndex]) << std::endl;
}

bool handleMenuChoice(std::vector<Robot>& robots, MenuChoice choice) {
    switch (choice) {
        case MenuChoice::ShowAllRobots:
            printAllRobots(robots);
            break;

        case MenuChoice::ShowSummary:
            printSummary(robots);
            break;

        case MenuChoice::ChangeRobotMode:
            changeRobotMode(robots);
            break;

        case MenuChoice::UpdateRobotSensors:
            updateRobotSensors(robots);
            break;

        case MenuChoice::DecideRobotAction:
            showRobotAction(robots);
            break;

        case MenuChoice::ChargeRobot:
            chargeRobot(robots);
            break;

        case MenuChoice::DamageRobot:
            damageRobot(robots);
            break;

        case MenuChoice::RepairRobot:
            repairRobot(robots);
            break;

        case MenuChoice::EmergencyStopRobot:
            emergencyStopRobot(robots);
            break;

        case MenuChoice::FindBestRobot:
            showBestRobot(robots);
            break;
            
        case MenuChoice::Exit:
            std::cout << "Exiting mission control." << std::endl;
            return false;

        default:
            std::cout << "Unknown menu choice." << std::endl;
            return true;
    }
}

int main() {
    std::cout << "Robot Rescue Mission Simulator" << std::endl;

    int robotCount = readIntInRange("Number of robots (1-10): ", 1, 10);
    std::vector<Robot> robots;
    robots.reserve(robotCount);

    for (int i = 1; i <= robotCount; ++i) {
        robots.push_back(readRobot(i));
    }

    bool running = true;
    while (running) {
        printMenu();
        MenuChoice choice = readMenuChoice();
        running = handleMenuChoice(robots, choice);
    }

    return 0;
}