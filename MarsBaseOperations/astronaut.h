#pragma once
#include <string>

const int ASTRONAUT_STATUS_AVAILABLE = 0;
const int ASTRONAUT_STATUS_ASSIGNED = 1;
const int ASTRONAUT_STATUS_RESTING = 2;
const int ASTRONAUT_STATUS_INJURED = 3;

struct Astronaut {
    std::string name;
    int skillLevel;
    int status;
    int assignedMissionId;
};

Astronaut createAstronaut();

void printAstronaut(const Astronaut& astronaut);

void printAllAstronauts(const Astronaut astronauts[], int astronautCount);

int findAstronautIndexByName(const Astronaut astronauts[], int astronautCount, const std::string& name);

int countAvailableAstronauts(const Astronaut astronauts[], int astronautCount);

std::string astronautStatusToString(int status);

void resetAstronautStatus(Astronaut& astronaut);