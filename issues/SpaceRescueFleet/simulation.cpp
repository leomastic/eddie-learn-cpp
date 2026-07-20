#include "simulation.h"
#include "state_machine.h"
#include "utils.h"
#include <iostream>

void updateSensorData(Robot& robot) {
    std::cout << std::endl;
    std::cout << "Updating sensor information for " << robot.name << "." << std::endl;
    robot.batteryLevel = readIntInRange("Battery level (0--100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0--1000.0): ", 0.0, 1000.0);
    robot.victimDetected = readYesNo("Victim detected? ");
    robot.victimReached = readYesNo("Victim reached? ");
    robot.rescueCompleted = readYesNo("Rescue completed? ");
    robot.arrivedAtBase = readYesNo("Arrived at base? ");
    std::cout << std::endl;
}

void runRobotRound(Robot& robot) {
    std::cout << "Robot: " << robot.name << std::endl;
    std::cout << "Current state: " << robotStateToString(robot.state) << std::endl;

    RobotAction action = decideAction(robot);
    std::cout << "Action: " << robotActionToString(action) << std::endl;
    std::cout << std::endl;
    std::cout << "Update sensor data..." << std::endl;

    updateSensorData(robot);

    RobotState nextState = calculateNextState(robot);
    if (nextState == robot.state) {
        std::cout << "State remains " << robotStateToString(robot.state) << std::endl;
    } else {
        std::cout << "State changed from " << robotStateToString(robot.state)
                  << " to " << robotStateToString(nextState) << std::endl;
    }

    robot.state = nextState;
}

void runFleetRound(std::vector<Robot>& robots) {
    if (robots.empty()) {
        std::cout << "Fleet is empty. No robots to simulate." << std::endl;
        return;
    }

    for (size_t i = 0; i < robots.size(); ++i) {
        std::cout << "Robot " << (i + 1) << " of " << robots.size() << std::endl;
        runRobotRound(robots[i]);
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
