#pragma once
#include "robot.h"
#include <vector>

void runFleetRound(std::vector<Robot>& robots);

void runFleetSimulation(
    std::vector<Robot>& robots,
    int rounds
);
