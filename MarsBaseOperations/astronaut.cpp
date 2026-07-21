#include "astronaut.h"
#include "utils.h"

#include <iostream>

Astronaut createAstronaut() {
    Astronaut astronaut;

    astronaut.name = readNonEmptyWord("Astronaut name: ");
    astronaut.skillLevel = readIntInRange("Skill level (1-10): ", 1, 10);
    astronaut.status = ASTRONAUT_STATUS_AVAILABLE;
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

void printAllAstronauts(const Astronaut astronauts[], int astronautCount) {
    if (astronautCount == 0) {
        std::cout << "No astronauts registered." << std::endl;
        return;
    }

    for (int i = 0; i < astronautCount; ++i) {
        std::cout << "Astronaut " << (i + 1) << ":" << std::endl;
        printAstronaut(astronauts[i]);
        std::cout << std::endl;
    }
}

int findAstronautIndexByName(const Astronaut astronauts[], int astronautCount, const std::string& name) {
    for (int i = 0; i < astronautCount; ++i) {
        if (name == astronauts[i].name) {
            return i;
        }
    }

    return -1;
}

int countAvailableAstronauts(const Astronaut astronauts[], int astronautCount) {
    int count = 0;

    for (int i = 0; i < astronautCount; ++i) {
        if (astronauts[i].status == ASTRONAUT_STATUS_AVAILABLE) {
            ++count;
        }
    }

    return count;
}

std::string astronautStatusToString(int status) {
    switch (status) {
        case ASTRONAUT_STATUS_ASSIGNED:
            return "Assigned";

        case ASTRONAUT_STATUS_AVAILABLE:
            return "Available";

        case ASTRONAUT_STATUS_INJURED:
            return "Injured";

        case ASTRONAUT_STATUS_RESTING:
            return "Resting";

        default:
            return "Unknown";
    }
}

void resetAstronautStatus(Astronaut& astronaut) {
    astronaut.status = ASTRONAUT_STATUS_AVAILABLE;
    astronaut.assignedMissionId = -1;
}