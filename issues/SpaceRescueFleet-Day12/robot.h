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

class Robot {
public:
    std::string name;

    int batteryLevel;
    double distanceToObstacle;

    bool victimDetected;
    bool victimReached;
    bool rescueCompleted;
    bool arrivedAtBase;

    RobotState state;

    Robot();

    Robot(
        std::string robotName,
        int batteryLevel,
        double distanceToObstacle,
        bool victimDetected,
        bool victimReached,
        bool rescueCompleted,
        bool arrivedAtBase,
        RobotState state
    );

    Robot create();

    void print();

    void reset();

    std::string stateToString();

    std::string actionToString(RobotAction);
};

Robot createRobot();

void resetRobot(Robot& robot);
