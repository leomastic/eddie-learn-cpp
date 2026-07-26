#include "robot.h"
#include "utils.h"
#include <iostream>

Robot::Robot() {
    // Create an empty robot object
}

Robot createRobot() {
    return Robot().create();
}

void resetRobot(Robot& robot) {
    robot.reset();
}

Robot::Robot(
    std::string robotName,
    int batteryLevel,
    double distanceToObstacle,
    bool victimDetected,
    bool victimReached,
    bool rescueCompleted,
    bool arrivedAtBase,
    RobotState state
) {
    this->name = robotName;
    this->batteryLevel = batteryLevel;
    this->distanceToObstacle = distanceToObstacle;
    this->victimDetected = victimDetected;
    this->victimReached = victimReached;
    this->rescueCompleted = rescueCompleted;
    this->arrivedAtBase = arrivedAtBase;
    this->state = state;
}

Robot Robot::create() {
    std::cout << std::endl;
    std::cout << "Please enter the robot name (no space): ";
    std::cin >> name;

    batteryLevel = readIntInRange("Please enter the robot battery level (0 --> 100): ", 0, 100);
    distanceToObstacle = readDoubleInRange("Please enter the distance to obstacle (0.0 --> 1000.0): ", 0, 1000);

    victimDetected = readYesNo("Victim detected? ");
    victimReached = readYesNo("Victim reached? ");
    rescueCompleted = readYesNo("Rescue completed? ");
    arrivedAtBase = readYesNo("Arrived at base? ");

    state = RobotState::Idle;
    std::cout << std::endl;

    return Robot(name, batteryLevel, distanceToObstacle, victimDetected,
                 victimReached, rescueCompleted, arrivedAtBase, state);
}

void Robot::print() {
    std::cout << "Robot status:" << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Battery level: " << this->batteryLevel << std::endl;
    std::cout << "Distance to obstacle: " << this->distanceToObstacle << std::endl;
    std::cout << "Victim detected: " << (this->victimDetected ? "Yes" : "No") << std::endl;
    std::cout << "Victim reached: " << (this->victimReached ? "Yes" : "No") << std::endl;
    std::cout << "Rescue completed: " << (this->rescueCompleted ? "Yes" : "No") << std::endl;
    std::cout << "Arrived at base: " << (this->arrivedAtBase ? "Yes" : "No") << std::endl;
    std::cout << "Current state: " << this->stateToString() << std::endl;
}

void Robot::reset() {
    this->batteryLevel = 100;
    this->distanceToObstacle = 1000.0;

    this->victimDetected = false;
    this->victimReached = false;
    this->rescueCompleted = false;
    this->arrivedAtBase = true;

    this->state = RobotState::Idle;
}

std::string Robot::stateToString() {
    switch (this->state) {
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

std::string Robot::actionToString(RobotAction action) {
    switch (action) {
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