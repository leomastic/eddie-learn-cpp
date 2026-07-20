#include "robot.h"
#include "state_machine.h"

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

    return RobotAction::Stop;
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

    return RobotState::EmergencyStopped;
}