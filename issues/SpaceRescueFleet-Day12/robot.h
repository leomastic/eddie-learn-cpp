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
    Robot(std::string robotName,
          int batteryLevel,
          double distanceToObstacle,
          bool victimDetected,
          bool victimReached,
          bool rescueCompleted,
          bool arrivedAtBase,
          RobotState state);

    const std::string& name() const;
    int batteryLevel() const;
    double distanceToObstacle() const;
    RobotState state() const;

    bool victimDetected() const;
    bool victimReached() const;
    bool rescueCompleted() const;
    bool arrivedAtBase() const;

    void print() const;
    void reset();

    RobotAction decideAction() const;
    void updateSensorData();
    void runRound();

    static std::string stateToString(RobotState state);
    static std::string actionToString(RobotAction action);

private:
    RobotState calculateNextState() const;

    std::string name_;
    int batteryLevel_;
    double distanceToObstacle_;

    bool victimDetected_;
    bool victimReached_;
    bool rescueCompleted_;
    bool arrivedAtBase_;

    RobotState state_;
};

Robot createRobot();