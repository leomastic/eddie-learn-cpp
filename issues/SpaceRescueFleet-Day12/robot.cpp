#include "robot.h"
#include "utils.h"
#include <iostream>

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
    this->name_ = robotName;
    this->batteryLevel_ = batteryLevel;
    this->distanceToObstacle_ = distanceToObstacle;
    this->victimDetected_ = victimDetected;
    this->victimReached_ = victimReached;
    this->rescueCompleted_ = rescueCompleted;
    this->arrivedAtBase_ = arrivedAtBase;
    this->state_ = state;
}

const std::string& Robot::name() const {
    return this->name_;
}

int Robot::batteryLevel() const {
    return this->batteryLevel_;
}

double Robot::distanceToObstacle() const {
    return this->distanceToObstacle_;
}

RobotState Robot::state() const {
    return this->state_;
}

bool Robot::victimDetected() const {
    return this->victimDetected_;
}

bool Robot::victimReached() const {
    return this->victimReached_;
}

bool Robot::rescueCompleted() const {
    return this->rescueCompleted_;
}

bool Robot::arrivedAtBase() const {
    return this->arrivedAtBase_;
}

Robot createRobot() {
    std::cout << std::endl;
    std::string name = readNonEmptyWord("Please enter the robot name (no space): ");

    int batteryLevel = readIntInRange("Please enter the robot battery level (0 --> 100): ", 0, 100);
    double distanceToObstacle = readDoubleInRange("Please enter the distance to obstacle (0.0 --> 1000.0): ", 0, 1000);

    bool victimDetected = readYesNo("Victim detected? ");
    bool victimReached = readYesNo("Victim reached? ");
    bool rescueCompleted = readYesNo("Rescue completed? ");
    bool arrivedAtBase = readYesNo("Arrived at base? ");

    RobotState state = RobotState::Idle;
    std::cout << std::endl;

    return Robot(name, batteryLevel, distanceToObstacle, victimDetected,
                 victimReached, rescueCompleted, arrivedAtBase, state);
}

void Robot::print() const {
    std::cout << "Robot status:" << std::endl;
    std::cout << "Name: " << this->name_ << std::endl;
    std::cout << "Battery level: " << this->batteryLevel_ << std::endl;
    std::cout << "Distance to obstacle: " << this->distanceToObstacle_ << std::endl;
    std::cout << "Victim detected: " << (this->victimDetected_ ? "Yes" : "No") << std::endl;
    std::cout << "Victim reached: " << (this->victimReached_ ? "Yes" : "No") << std::endl;
    std::cout << "Rescue completed: " << (this->rescueCompleted_ ? "Yes" : "No") << std::endl;
    std::cout << "Arrived at base: " << (this->arrivedAtBase_ ? "Yes" : "No") << std::endl;
    std::cout << "Current state: " << this->stateToString(this->state_) << std::endl;
}

void Robot::reset() {
    this->batteryLevel_ = 100;
    this->distanceToObstacle_ = 1000.0;

    this->victimDetected_ = false;
    this->victimReached_ = false;
    this->rescueCompleted_ = false;
    this->arrivedAtBase_ = true;

    this->state_ = RobotState::Idle;
}

std::string Robot::stateToString(RobotState state) {
    switch (state) {
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

std::string actionToString(RobotAction action) {
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