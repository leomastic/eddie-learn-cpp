#include "astronaut.h"
#include "utils.h"

#include <iostream>

Astronaut createAstronaut() {
    Astronaut astronaut;

    astronaut.name = readNonEmptyWord("Astronaut name: ");
    astronaut.skillLevel = readIntInRange("Skill level (1-10): ", 1, 10);
    astronaut.status = AstronautStatus::Available;
    astronaut.assignedMissionId = -1;

    return astronaut;
}

void printAstronaut(const Astronaut& astronaut) {
    std::cout << "Name: " << astronaut.name << std::endl;
    std::cout << "Skill level: " << astronaut.skillLevel << std::endl;
    std::cout << "Status: " << astronautStatusToString(astronaut.status) << std::endl;
    std::cout << "Assigned mission ID: ";
    if (astronaut.assignedMissionId == -1) {
        std::cout << "None" << std::endl;
    } else {
        std::cout << astronaut.assignedMissionId << std::endl;
    }
}

void printAllAstronauts(const std::vector<Astronaut>& astronauts) {
    if (astronauts.empty()) {
        std::cout << "No astronauts registered." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < astronauts.size(); ++i) {
        std::cout << "Astronaut " << (i + 1) << ":" << std::endl;
        printAstronaut(astronauts[i]);
        std::cout << std::endl;
    }
}

int findAstronautIndexByName(const std::vector<Astronaut>& astronauts, const std::string& name) {
    for (std::size_t i = 0; i < astronauts.size(); ++i) {
        if (name == astronauts[i].name) {
            return i;
        }
    }

    return -1;
}

int countAvailableAstronauts(const std::vector<Astronaut>& astronauts) {
    int count = 0;

    for (const Astronaut& astronaut : astronauts) {
        if (astronaut.status == AstronautStatus::Available) {
            ++count;
        }
    }

    return count;
}

std::string astronautStatusToString(AstronautStatus status) {
    switch (status) {
        case AstronautStatus::Assigned:
            return "Assigned";

        case AstronautStatus::Available:
            return "Available";

        case AstronautStatus::Injured:
            return "Injured";

        case AstronautStatus::Resting:
            return "Resting";

        default:
            return "Unknown";
    }
}

void resetAstronautStatus(Astronaut& astronaut) {
    astronaut.status = AstronautStatus::Available;
    astronaut.assignedMissionId = -1;
}