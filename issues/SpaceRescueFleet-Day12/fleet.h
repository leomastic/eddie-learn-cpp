#pragma once
#include "robot.h"
#include <vector>

void printAllRobots(const std::vector<Robot>& robots);

int findRobotIndexByName(
    const std::vector<Robot>& robots,
    const std::string& name
);

int findBestRescueRobotIndex(
    const std::vector<Robot>& robots
);

int countReadyRobots(const std::vector<Robot>& robots);

int countEmergencyRobots(const std::vector<Robot>& robots);

double calculateAverageBattery(
    const std::vector<Robot>& robots
);

void printFleetSummary(
    const std::vector<Robot>& robots
);