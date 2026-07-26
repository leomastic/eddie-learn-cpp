#pragma once
#include "robot.h"
#include <vector>

void updateSensorData(Robot& robot);

void runRobotRound(Robot& robot);

void runFleetRound(std::vector<Robot>& robots);

void runFleetSimulation(
    std::vector<Robot>& robots,
    int rounds
);
