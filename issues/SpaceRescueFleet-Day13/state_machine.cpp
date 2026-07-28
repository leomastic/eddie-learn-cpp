#include "state_machine.h"

RobotAction Robot::decideAction() const{
    if (hasLowBattery()) {
        return RobotAction::EmergencyStop;
    }

    RobotState state = this->state();
    switch(state) {
        case RobotState::Idle:
            return RobotAction::Stop;

        case RobotState::Searching:
            if(this->victimDetected()) {
                return RobotAction::MoveForward;
            }

            return RobotAction::ScanArea;
        
        case RobotState::MovingToVictim:
            if(this->distanceToObstacle() < 20.0) {
                return RobotAction::TurnRight;
            }

            if(this->victimReached()) {
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

RobotState Robot::calculateNextState() const{
    if(this->batteryLevel().level() < 15) {
        return RobotState::EmergencyStopped;
    }

    RobotState state = this->state();
    switch(state) {
        case RobotState::Idle:
            return RobotState::Searching;
        
        case RobotState::Searching:
            if(this->victimDetected()) {
                return RobotState::MovingToVictim;
            }

            return RobotState::Searching;

        case RobotState::MovingToVictim:
            if(this->distanceToObstacle() < 20.0) {
                return RobotState::AvoidingObstacle;
            }

            if(this->victimReached()) {
                return RobotState::RescuingVictim;
            }

            return RobotState::MovingToVictim;

        case RobotState::AvoidingObstacle:
            if(this->distanceToObstacle() >= 20.0) {
                return RobotState::MovingToVictim;
            }

            return RobotState::AvoidingObstacle;

        case RobotState::RescuingVictim:
            if(this->rescueCompleted()) {
                return RobotState::ReturningToBase;
            }

            return RobotState::RescuingVictim;

        case RobotState::ReturningToBase:
            if(this->arrivedAtBase()) {
                return RobotState::Idle;
            }

            return RobotState::ReturningToBase;

        case RobotState::EmergencyStopped:
            return RobotState::EmergencyStopped;
    }

    return RobotState::EmergencyStopped;
}