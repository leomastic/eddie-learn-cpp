#pragma once
#include <string>

enum class RobotState {
    Idle,
    Searching,
    MovingToVictim,
    AvoidingObstacle,
    RescuingVictim,
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

Robot createRobot();

void printRobot(const Robot& robot);

void resetRobot(Robot& robot);

std::string robotStateToString(RobotState state);

std::string robotActionToString(RobotAction action);
