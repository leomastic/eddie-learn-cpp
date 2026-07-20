#include <iostream>
#include <string>
#include <vector>

enum class RobotMode {
    Manual,
    LineFollowing,
    ObstacleAvoidance,
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
    EmergencyStop
};

enum class MenuChoice {
    ShowStatus,
    ChangeMode,
    UpdateSensors,
    DecideAction,
    ChargeBattery,
    DamageRobot,
    RepairRobot,
    EmergencyStop,
    Exit
};

struct Robot {
    std::string name;

    int batteryLevel;
    int motorHealth;
    int sensorHealth;

    double distanceToObstacle;

    bool leftLineDetected;
    bool rightLineDetected;

    RobotMode mode;
};

RobotMode readRobotMode();
MenuChoice readMenuChoice();

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while(true) {
        std::cout << prompt;

        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value.";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if(value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue << "."
                      << std::endl;
            continue;
        }

        return value;
    }
}

double readDoubleInRange(std::string prompt, double minValue, double maxValue) {
    double value;

    while(true) {
        std::cout << prompt;

        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value.";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if(value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue << "."
                      << std::endl;
            continue;
        }

        return value;
    }
}

bool readYesNo(std::string prompt) {
    int value;

    while(true) {
        std::cout << prompt;
        
        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch(value) {
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

Robot createRobot() {
    Robot robot;

    std::cout << std::endl;
    std::cout << "Robot name (no space): ";
    std::cin >> robot.name;

    robot.batteryLevel = readIntInRange("Robot battery level (0-100): ", 0, 100);
    robot.motorHealth = readIntInRange("Robot motor health (0-100): ", 0, 100);
    robot.sensorHealth = readIntInRange("Robot sensor health (0-100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0-1000.0): ", 0.0, 1000.0);

    robot.leftLineDetected = readYesNo("Left line detected? ");
    robot.rightLineDetected = readYesNo("Right line detected? ");

    robot.mode = readRobotMode();
    std::cout << std::endl;

    return robot;
}

RobotMode readRobotMode() {
    int choice = readIntInRange(
        "Robot mode:\n1 = Manual\n2 = LineFollowing\n3 = ObstacleAvoidance\n4 = EmergencyStop\nChoose mode (1-4): ",
        1,
        4
    );

    switch(choice) {
        case 1:
            return RobotMode::Manual;
        case 2:
            return RobotMode::LineFollowing;
        case 3:
            return RobotMode::ObstacleAvoidance;
        default:
            return RobotMode::EmergencyStop;
    }
}

MenuChoice readMenuChoice() {
    int choice = readIntInRange(
        "\nMenu choice (1-9):\n"
        "1 = Show Status\n"
        "2 = Change Mode\n"
        "3 = Update Sensors\n"
        "4 = Decide Action\n"
        "5 = Charge Battery\n"
        "6 = Damage Robot\n"
        "7 = Repair Robot\n"
        "8 = Emergency Stop\n"
        "9 = Exit\n"
        "Choose: ",
        1,
        9
    );

    switch (choice) {
        case 1:
            return MenuChoice::ShowStatus;

        case 2:
            return MenuChoice::ChangeMode;

        case 3:
            return MenuChoice::UpdateSensors;

        case 4:
            return MenuChoice::DecideAction;

        case 5:
            return MenuChoice::ChargeBattery;

        case 6:
            return MenuChoice::DamageRobot;

        case 7:
            return MenuChoice::RepairRobot;

        case 8:
            return MenuChoice::EmergencyStop;

        default:
            return MenuChoice::Exit;
    }
}

RobotStatus calculateRobotStatus(const Robot& robot) {
    if(robot.batteryLevel < 15 || robot.motorHealth < 30 || robot.sensorHealth < 30) {
        return RobotStatus::Critical;
    }

    if(robot.batteryLevel < 40 || robot.motorHealth < 60 || robot.sensorHealth < 60) {
        return RobotStatus::NeedsCheck;
    }

    return RobotStatus::Ready;
}

RobotAction decideRobotAction(const Robot& robot) {
    RobotAction action = RobotAction::EmergencyStop;
    if(calculateRobotStatus(robot) == RobotStatus::Critical) {
        return action;
    }

    RobotMode mode = robot.mode;
    switch(mode) {
        case RobotMode::EmergencyStop:
            action = RobotAction::EmergencyStop;
            break;
        case RobotMode::Manual:
            action = RobotAction::Stop;
            break;
        case RobotMode::ObstacleAvoidance:
            if(robot.distanceToObstacle < 20.0) {
                action = RobotAction::TurnRight;
            } else {
                action = RobotAction::MoveForward;
            }
            break;
        case RobotMode::LineFollowing:
            if(robot.leftLineDetected && robot.rightLineDetected) {
                action = RobotAction::MoveForward;
            } else if(robot.leftLineDetected && !robot.rightLineDetected) {
                action = RobotAction::TurnLeft;
            } else if(!robot.leftLineDetected && robot.rightLineDetected) {
                action = RobotAction::TurnRight;
            } else {
                action = RobotAction::Stop;
            }
            break;
        default:
            break;
    }
    return action;
}

std::string robotModeToString(RobotMode mode) {
    switch(mode) {
        case RobotMode::EmergencyStop:
            return "Emergency Stop";
        case RobotMode::Manual:
            return "Manual";
        case RobotMode::LineFollowing:
            return "Line Following";
        case RobotMode::ObstacleAvoidance:
            return "Obstacle Avoidance";
        default:
            return "Unknown";
    }
}

std::string robotStatusToString(RobotStatus status) {
    switch(status) {
        case RobotStatus::Critical:
            return "Critical";
        case RobotStatus::NeedsCheck:
            return "Needs Check";
        default:
            return "Ready";
    }
}

std::string robotActionToString(RobotAction action) {
    switch(action) {
        case RobotAction::EmergencyStop:
            return "Emergency Stop";
        case RobotAction::MoveForward:
            return "Move forward";
        case RobotAction::TurnLeft:
            return "Turn Left";
        case RobotAction::TurnRight:
            return "Turn Right";
        default:
            return "Stop";
    }
}

std::string menuChoiceToString(MenuChoice choice) {
    switch(choice) {
        case MenuChoice::ChangeMode:
            return "Change Mode";
        case MenuChoice::ChargeBattery:
            return "Charge Battery";
        case MenuChoice::DamageRobot:
            return "Damage Robot";
        case MenuChoice::DecideAction:
            return "Decide Action";
        case MenuChoice::EmergencyStop:
            return "Emergency Stop";
        case MenuChoice::RepairRobot:
            return "Repair Robot";
        case MenuChoice::ShowStatus:
            return "Show Status";
        case MenuChoice::UpdateSensors:
            return "Update Sensors";
        default:
            return "Exit";
    }
}

void printMenu() {
    std::cout << "\n=== Robot Control Center ===" << std::endl;
    std::cout << "1. Show Status" << std::endl;
    std::cout << "2. Change Mode" << std::endl;
    std::cout << "3. Update Sensors" << std::endl;
    std::cout << "4. Decide Action" << std::endl;
    std::cout << "5. Charge Battery" << std::endl;
    std::cout << "6. Damage Robot" << std::endl;
    std::cout << "7. Repair Robot" << std::endl;
    std::cout << "8. Emergency Stop" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

void printRobotStatus(const Robot& robot) {
    RobotStatus status = calculateRobotStatus(robot);
    RobotAction action = decideRobotAction(robot);

    std::cout << "\n=== Robot Status ===" << std::endl;
    std::cout << "Name: " << robot.name << std::endl;
    std::cout << "Battery: " << robot.batteryLevel << "/100" << std::endl;
    std::cout << "Motor health: " << robot.motorHealth << "/100" << std::endl;
    std::cout << "Sensor health: " << robot.sensorHealth << "/100" << std::endl;
    std::cout << "Distance to obstacle: " << robot.distanceToObstacle << std::endl;
    std::cout << "Left line detected: " << (robot.leftLineDetected ? "yes" : "no") << std::endl;
    std::cout << "Right line detected: " << (robot.rightLineDetected ? "yes" : "no") << std::endl;
    std::cout << "Mode: " << robotModeToString(robot.mode) << std::endl;
    std::cout << "Status: " << robotStatusToString(status) << std::endl;
    std::cout << "Suggested action: " << robotActionToString(action) << std::endl;
}

void changeRobotMode(Robot& robot) {
    robot.mode = readRobotMode();
    std::cout << "Mode changed to: " << robotModeToString(robot.mode) << std::endl;
}

void updateSensorData(Robot& robot) {
    robot.distanceToObstacle = readDoubleInRange(
        "Distance to obstacle (0.0-1000.0): ",
        0.0,
        1000.0
    );

    robot.leftLineDetected = readYesNo("Left line detected? (1=yes, 0=no): ");
    robot.rightLineDetected = readYesNo("Right line detected? (1=yes, 0=no): ");

    std::cout << "Sensor data updated." << std::endl;
}

void chargeBattery(Robot& robot) {
    robot.batteryLevel += 20;

    if (robot.batteryLevel > 100) {
        robot.batteryLevel = 100;
    }

    std::cout << "Battery charged to " << robot.batteryLevel << std::endl;
}

void damageRobot(Robot& robot) {
    int amount = readIntInRange("Damage amount (1-50): ", 1, 50);

    robot.motorHealth -= amount;
    robot.sensorHealth -= amount;

    if (robot.motorHealth < 0) {
        robot.motorHealth = 0;
    }

    if (robot.sensorHealth < 0) {
        robot.sensorHealth = 0;
    }

    std::cout << "Robot damaged. Motor and sensor health reduced." << std::endl;
}

void repairRobot(Robot& robot) {
    robot.motorHealth += 20;
    robot.sensorHealth += 20;

    if (robot.motorHealth > 100) {
        robot.motorHealth = 100;
    }

    if (robot.sensorHealth > 100) {
        robot.sensorHealth = 100;
    }

    std::cout << "Robot repaired. Motor and sensor health improved." << std::endl;
}

void emergencyStop(Robot& robot) {
    robot.mode = RobotMode::EmergencyStop;
    std::cout << "Emergency stop activated." << std::endl;
}

bool handleMenuChoice(Robot& robot, MenuChoice choice) {
    switch (choice) {
        case MenuChoice::ShowStatus:
            printRobotStatus(robot);
            return true;

        case MenuChoice::ChangeMode:
            changeRobotMode(robot);
            return true;

        case MenuChoice::UpdateSensors:
            updateSensorData(robot);
            return true;

        case MenuChoice::DecideAction: {
            RobotAction action = decideRobotAction(robot);
            std::cout << "Robot action: "
                      << robotActionToString(action)
                      << std::endl;
            return true;
        }

        case MenuChoice::ChargeBattery:
            chargeBattery(robot);
            return true;

        case MenuChoice::DamageRobot:
            damageRobot(robot);
            return true;

        case MenuChoice::RepairRobot:
            repairRobot(robot);
            return true;

        case MenuChoice::EmergencyStop:
            emergencyStop(robot);
            return true;

        case MenuChoice::Exit:
            std::cout << "Exiting Robot Control Center." << std::endl;
            return false;

        default:
            std::cout << "Unknown menu choice." << std::endl;
            return true;
    }
}

int main() {
    std::cout << "Welcome to the Robot Control Center!" << std::endl;

    Robot robot = createRobot();
    bool running = true;

    while (running) {
        printMenu();
        MenuChoice choice = readMenuChoice();
        running = handleMenuChoice(robot, choice);
    }

    std::cout << "Goodbye!" << std::endl;
    return 0;
}