#include "simulation.h"
#include "utils.h"
#include "state_machine.h"
#include <iostream>

void updateSensorData(Robot& robot) {
    std::cout << std::endl;
    robot.batteryLevel = readIntInRange("Battery level (0-100): ", 0, 100);
    robot.distanceToObstacle = readDoubleInRange("Distance to obstacle (0.0-1000.0): ", 0.0, 1000.0);
    robot.victimDetected = readYesNo("Victim detected?");
    robot.victimReached = readYesNo("Victim reached?");
    robot.rescueCompleted = readYesNo("Rescue completed?");
    robot.arrivedAtBase = readYesNo("Arrived at base?");
    std::cout << std::endl;
}

void runSimulation(Robot& robot, int rounds) {
    for (int round = 1; round <= rounds; ++round) {
        std::cout << "\n===== Round " << round << " =====" << std::endl;

        printRobot(robot);

        RobotAction action = decideAction(robot);
        std::cout << "Action: " << robotActionToString(action) << std::endl;

        updateSensorData(robot);

        RobotState nextState = calculateNextState(robot);

        std::cout << "State changed from "
                  << robotStateToString(robot.state)
                  << " to "
                  << robotStateToString(nextState)
                  << std::endl;

        robot.state = nextState;
    }
}