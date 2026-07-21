#pragma once
#include "astronaut.h"
#include "mission.h"

void printMissionReadinessReport(const Mission& mission, const Astronaut astronauts[], int astronautCount, const Inventory& inventory);

void printBaseReport(const Astronaut astronauts[], int astronautCount, const Mission missions[], int missionCount, const Inventory& inventory);