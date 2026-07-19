#include <iostream>
#include "robot.h"
#include "state_machine.h"
#include "utils.h"
#include "simulation.h"

int main() {
    std::cout << "Robot State Machine Simulator" << std::endl;

    Robot robot = createRobot();

    int rounds = readIntInRange("Number of simulation rounds (1-10): ", 1, 10);

    runSimulation(robot, rounds);

    std::cout << "\nFinal state: "
              << robotStateToString(robot.state)
              << std::endl;

    return 0;
}