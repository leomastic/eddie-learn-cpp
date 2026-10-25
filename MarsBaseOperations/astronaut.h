#pragma once
#include <string>
#include <vector>

enum class AstronautStatus {
    Available,
    Assigned,
    Resting,
    Injured
};

struct Astronaut {
    std::string name;
    int skillLevel;
    AstronautStatus status;
    int assignedMissionId;
};

Astronaut createAstronaut();

void printAstronaut(const Astronaut& astronaut);

void printAllAstronauts(const std::vector<Astronaut>& astronauts);

int findAstronautIndexByName(const std::vector<Astronaut>& astronauts, const std::string& name);

int countAvailableAstronauts(const std::vector<Astronaut>& astronauts);

std::string astronautStatusToString(AstronautStatus status);

void resetAstronautStatus(Astronaut& astronaut);