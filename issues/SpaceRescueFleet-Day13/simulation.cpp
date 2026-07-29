#include "simulation.h"
#include "state_machine.h"
#include "utils.h"
#include <iostream>

void Robot::updateSensorData() {
    std::cout << std::endl;
    std::cout << "Updating sensor information for " << this->name_ << "." << std::endl;

    int newBatteryLevel = readIntInRange("Battery level (0--100): ", 0, 100);
    battery_ = Battery(newBatteryLevel);


    this->distanceToObstacle_ = readDoubleInRange("Distance to obstacle (0.0--1000.0): ", 0.0, 1000.0);
    this->victimDetected_ = readYesNo("Victim detected? ");
    this->victimReached_ = readYesNo("Victim reached? ");
    this->rescueCompleted_ = readYesNo("Rescue completed? ");
    this->arrivedAtBase_ = readYesNo("Arrived at base? ");
    std::cout << std::endl;
}

void Robot::runRound() {
    std::cout << "Robot: " << this->name_ << std::endl;
    std::cout << "Current state: " << this->stateToString(this->state_) << std::endl; 

    RobotAction action = this->decideAction();
    consumeEnergyForAction(action);

    std::cout
        << "Action: "
        << actionToString(action)
        << std::endl;

    std::cout
        << "Battery after action: "
        << batteryLevel()
        << std::endl;

    std::cout << std::endl;
    std::cout << "Update sensor data..." << std::endl;

    this->updateSensorData();

    RobotState nextState = this->calculateNextState();
    if (nextState == this->state_) {
        std::cout << "State remains " << this->stateToString(this->state_) << std::endl;
    } else {
        std::cout
        << "State changed from "
        << Robot::stateToString(this->state())
        << " to "
        << Robot::stateToString(nextState)
        << '\n';
    }

    this->state_ = nextState;
}

void runFleetRound(std::vector<Robot>& robots) {
    if (robots.empty()) {
        std::cout << "Fleet is empty. No robots to simulate." << std::endl;
        return;
    }

    for (size_t i = 0; i < robots.size(); ++i) {
        std::cout << "Robot " << (i + 1) << " of " << robots.size() << std::endl;
        robots[i].runRound();
        if (i + 1 < robots.size()) {
            std::cout << std::endl;
        }
    }
}

void runFleetSimulation(
    std::vector<Robot>& robots,
    int rounds
) {
    for (int round = 1; round <= rounds; ++round) {
        std::cout << "===== Simulation Round " << round << " =====" << std::endl;
        std::cout << std::endl;
        runFleetRound(robots);
        if (round < rounds) {
            std::cout << std::endl;
        }
    }
}
