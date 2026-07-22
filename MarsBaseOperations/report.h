#pragma once
#include <vector>

#include "astronaut.h"
#include "mission.h"

void printMissionReadinessReport(const Mission& mission, const std::vector<Astronaut>& astronauts, const Inventory& inventory);

void printBaseReport(const std::vector<Astronaut>& astronauts, const std::vector<Mission>& missions, const Inventory& inventory);