#include <iostream>
#include <string>
#include <vector>

enum class RobotState {
    Idle,
    Searching,
    MovingToVictim,
    RescuingVictim,
    AvoidingObstacle,
    ReturningToBase,
    EmergencyStopped
};

enum class RobotAction {
    Stop,
    ScanArea,
    MoveForward,
    TurnRight,
    RescueVictim,
    ReturnToBase,
    EmergencyStop
};

struct Robot {
    std::string name;

    int batteryLevel;

    double distanceToObstacle;

    bool victimDetected;
    bool victimReached;
    bool rescueCompleted;
    bool arrivedAtBase;

    RobotState state;
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

Robot createRobot() {
    Robot robot;

    std::cout << std::endl;
    std::cout << "Robot name (no space): ";
    std::cin >> robot.name;

    robot.batteryLevel = readIntInRange("Robot battery level (0-100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0-1000.0): ", 0.0, 1000.0);

    robot.arrivedAtBase = readYesNo("Arrived At Base? ");
    robot.rescueCompleted = readYesNo("Rescue Completed? ");
    robot.victimDetected = readYesNo("Victim Detected? ");
    robot.victimReached = readYesNo("Victim reached? ");

    robot.state = RobotState::Idle;
    std::cout << std::endl;

    return robot;
}

RobotAction decideAction(const Robot& robot) {
    if(robot.batteryLevel < 15) {
        return RobotAction::EmergencyStop;
    }

    RobotState state = robot.state;
    switch(state) {
        case RobotState::Idle:
            return RobotAction::Stop;

        case RobotState::Searching:
            if(robot.victimDetected) {
                return RobotAction::MoveForward;
            }

            return RobotAction::ScanArea;
        
        case RobotState::MovingToVictim:
            if(robot.distanceToObstacle < 20.0) {
                return RobotAction::TurnRight;
            }

            if(robot.victimReached) {
                return RobotAction::RescueVictim;
            }

            return RobotAction::MoveForward;

        case RobotState::RescuingVictim:
            return RobotAction::RescueVictim;
        
        case RobotState::AvoidingObstacle:
            return RobotAction::TurnRight;
    
        case RobotState::ReturningToBase:
            return RobotAction::ReturnToBase;

        case RobotState::EmergencyStopped:
            return RobotAction::EmergencyStop;
    }
}

RobotState calculateNextState(const Robot& robot) {
    if(robot.batteryLevel < 15) {
        return RobotState::EmergencyStopped;
    }

    RobotState state = robot.state;
    switch(state) {
        case RobotState::Idle:
            return RobotState::Searching;
        
        case RobotState::Searching:
            if(robot.victimDetected) {
                return RobotState::MovingToVictim;
            }

            return RobotState::Searching;

        case RobotState::MovingToVictim:
            if(robot.distanceToObstacle < 20.0) {
                return RobotState::AvoidingObstacle;
            }

            if(robot.victimReached) {
                return RobotState::RescuingVictim;
            }

            return RobotState::MovingToVictim;

        case RobotState::AvoidingObstacle:
            if(robot.distanceToObstacle >= 20.0) {
                return RobotState::MovingToVictim;
            }

            return RobotState::AvoidingObstacle;

        case RobotState::RescuingVictim:
            if(robot.rescueCompleted) {
                return RobotState::ReturningToBase;
            }

            return RobotState::RescuingVictim;

        case RobotState::ReturningToBase:
            if(robot.arrivedAtBase) {
                return RobotState::Idle;
            }

            return RobotState::ReturningToBase;

        case RobotState::EmergencyStopped:
            return RobotState::EmergencyStopped;
    }
}

std::string robotStateToString(RobotState state) {
    switch(state) {
        case RobotState::AvoidingObstacle:
            return "Avoiding Obstacle";
        
        case RobotState::EmergencyStopped:
            return "Emergency Stopped";

        case RobotState::Idle:
            return "Idle";

        case RobotState::MovingToVictim:
            return "Moving To Victim";

        case RobotState::RescuingVictim:
            return "Rescuing Victim";

        case RobotState::ReturningToBase:
            return "Returning To Base";

        case RobotState::Searching:
            return "Searching";

        default:
            return "Unknown";
    }
}

std::string robotActionToString(RobotAction action) {
    switch(action) {
        case RobotAction::EmergencyStop:
            return "Emergency Stop";

        case RobotAction::MoveForward:
            return "Move Forward";

        case RobotAction::RescueVictim:
            return "Rescue Victim";

        case RobotAction::ReturnToBase:
            return "Return To Base";

        case RobotAction::ScanArea:
            return "Scan Area";

        case RobotAction::Stop:
            return "Stop";

        case RobotAction::TurnRight:
            return "Turn Right";

        default:
            return "Unknown";
    }
}

void printRobot(const Robot& robot) {
    std::cout << "Robot status:" << std::endl;
    std::cout << "Name: " << robot.name << std::endl;
    std::cout << "Battery level: " << robot.batteryLevel << std::endl;
    std::cout << "Distance to obstacle: " << robot.distanceToObstacle << std::endl;
    std::cout << "Victim detected: " << (robot.victimDetected ? "Yes" : "No") << std::endl;
    std::cout << "Victim reached: " << (robot.victimReached ? "Yes" : "No") << std::endl;
    std::cout << "Rescue completed: " << (robot.rescueCompleted ? "Yes" : "No") << std::endl;
    std::cout << "Arrived at base: " << (robot.arrivedAtBase ? "Yes" : "No") << std::endl;
    std::cout << "Current state: " << robotStateToString(robot.state) << std::endl;
}

void updateSensorData(Robot& robot) {
    std::cout << std::endl;
    robot.batteryLevel = readIntInRange("Battery level (0-100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0-1000.0): ", 0.0, 1000.0);
    robot.victimDetected = readYesNo("Victim detected?");
    robot.victimReached = readYesNo("Victim reached?");
    robot.rescueCompleted = readYesNo("Rescue completed?");
    robot.arrivedAtBase = readYesNo("Arrived at base?");
    std::cout << std::endl;
}

void runSimulation(Robot& robot, int rounds) {
    for (int round = 1; round <= rounds; ++round) {
        std::cout << "\n===== Round " << round << " =====" << std::endl;

        printRobot(robot);

        RobotAction action = decideAction(robot);
        std::cout << "Action: " << robotActionToString(action) << std::endl;

        updateSensorData(robot);

        RobotState nextState = calculateNextState(robot);

        std::cout << "State changed from "
                  << robotStateToString(robot.state)
                  << " to "
                  << robotStateToString(nextState)
                  << std::endl;

        robot.state = nextState;
    }
}

int main() {
    std::cout << "Robot State Machine Simulator" << std::endl;

    Robot robot = createRobot();

    int rounds = readIntInRange("Number of simulation rounds (1-10): ", 1, 10);

    runSimulation(robot, rounds);

    std::cout << "\nFinal state: "
              << robotStateToString(robot.state)
              << std::endl;

    return 0;
}