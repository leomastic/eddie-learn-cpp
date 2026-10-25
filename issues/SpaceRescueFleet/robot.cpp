#include "robot.h"
#include "utils.h"
#include <iostream>

Robot createRobot() {
    Robot robot;

    std::cout << std::endl;
    std::cout << "Please enter the robot name (no space): ";
    std::cin >> robot.name;

    robot.batteryLevel = readIntInRange("Please enter the robot battery level (0 --> 100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Please enter the distance to obstacle (0.0 --> 1000.0): "
                                                                                        , 0, 1000);

    robot.victimDetected = readYesNo("Victim detected? ");
    robot.victimReached = readYesNo("Victim reached? ");
    robot.rescueCompleted = readYesNo("Rescue completed? ");
    robot.arrivedAtBase =readYesNo("Arrived at base? ");

    robot.state = RobotState::Idle;
    std::cout << std::endl;

    return robot;
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

void resetRobot(Robot& robot) {
    robot.batteryLevel = 100;
    robot.distanceToObstacle = 1000.0;

    robot.victimDetected = false;
    robot.victimReached = false;
    robot.rescueCompleted = false;
    robot.arrivedAtBase = true;

    robot.state = RobotState::Idle;
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