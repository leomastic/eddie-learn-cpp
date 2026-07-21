#include "mission.h"

#include <iostream>

#include "inventory.h"
#include "utils.h"

Mission createMission() {
    Mission mission;
    mission.id = readIntInRange("Mission ID: ", 1, 100000);
    mission.name = readNonEmptyLine("Mission name: ");
    mission.requiredAstronauts = readIntInRange("Required astronauts: ", 1, 20);
    mission.minimumTotalSkill = readIntInRange("Minimum total skill: ", 1, 200);
    mission.requiredOxygen = readIntInRange("Required oxygen: ", 0, 10000);
    mission.requiredWater = readIntInRange("Required water: ", 0, 10000);
    mission.requiredFood = readIntInRange("Required food: ", 0, 10000);
    mission.status = MISSION_STATUS_PLANNING;
    mission.assignedCount = 0;
    return mission;
}

void printMission(const Mission& mission, const Astronaut astronauts[], int astronautCount) {
    std::cout << "Mission ID: " << mission.id << std::endl;
    std::cout << "Name: " << mission.name << std::endl;
    std::cout << "Status: " << missionStatusToString(mission.status) << std::endl;
    std::cout << "Required astronauts: " << mission.requiredAstronauts << std::endl;
    std::cout << "Assigned astronauts: " << mission.assignedCount << std::endl;
    std::cout << "Minimum total skill: " << mission.minimumTotalSkill << std::endl;
    std::cout << "Assigned total skill: " << calculateAssignedSkill(mission, astronauts, astronautCount) << std::endl;
    std::cout << "Required oxygen: " << mission.requiredOxygen << std::endl;
    std::cout << "Required water: " << mission.requiredWater << std::endl;
    std::cout << "Required food: " << mission.requiredFood << std::endl;

    std::cout << "Assigned crew:" << std::endl;
    if (mission.assignedCount == 0) {
        std::cout << "- None" << std::endl;
    } else {
        for (int i = 0; i < mission.assignedCount; ++i) {
            int index = mission.assignedAstronautIndexes[i];
            if (index >= 0 && index < astronautCount) {
                std::cout << "- " << astronauts[index].name << std::endl;
            }
        }
    }
}

void printAllMissions(const Mission missions[], int missionCount, const Astronaut astronauts[], int astronautCount) {
    if (missionCount == 0) {
        std::cout << "No missions registered." << std::endl;
        return;
    }

    for (int i = 0; i < missionCount; ++i) {
        std::cout << "Mission " << (i + 1) << ":" << std::endl;
        printMission(missions[i], astronauts, astronautCount);
        std::cout << std::endl;
    }
}

int findMissionIndexById(const Mission missions[], int missionCount, int missionId) {
    for (int i = 0; i < missionCount; ++i) {
        if (missions[i].id == missionId) {
            return i;
        }
    }
    return -1;
}

bool assignAstronautToMission(Mission& mission, Astronaut& astronaut, int astronautIndex) {
    if (astronautIndex < 0) {
        return false;
    }

    if (astronaut.status != ASTRONAUT_STATUS_AVAILABLE) {
        return false;
    }

    if (mission.status != MISSION_STATUS_PLANNING && mission.status != MISSION_STATUS_READY) {
        return false;
    }

    for (int i = 0; i < mission.assignedCount; ++i) {
        if (mission.assignedAstronautIndexes[i] == astronautIndex) {
            return false;
        }
    }

    if (mission.assignedCount >= MAX_ASSIGNED_ASTRONAUTS) {
        return false;
    }

    mission.assignedAstronautIndexes[mission.assignedCount] = astronautIndex;
    ++mission.assignedCount;
    astronaut.status = ASTRONAUT_STATUS_ASSIGNED;
    astronaut.assignedMissionId = mission.id;
    return true;
}

int calculateAssignedSkill(const Mission& mission, const Astronaut astronauts[], int astronautCount) {
    int totalSkill = 0;
    for (int i = 0; i < mission.assignedCount; ++i) {
        int index = mission.assignedAstronautIndexes[i];
        if (index >= 0 && index < astronautCount) {
            totalSkill += astronauts[index].skillLevel;
        }
    }
    return totalSkill;
}

bool hasEnoughAstronauts(const Mission& mission) {
    return mission.assignedCount >= mission.requiredAstronauts;
}

bool hasEnoughSkill(const Mission& mission, const Astronaut astronauts[], int astronautCount) {
    return calculateAssignedSkill(mission, astronauts, astronautCount) >= mission.minimumTotalSkill;
}

bool isMissionReady(const Mission& mission, const Astronaut astronauts[], int astronautCount, const Inventory& inventory) {
    return hasEnoughAstronauts(mission)
        && hasEnoughSkill(mission, astronauts, astronautCount)
        && hasEnoughResources(inventory, mission.requiredOxygen, mission.requiredWater, mission.requiredFood)
        && (mission.status == MISSION_STATUS_PLANNING || mission.status == MISSION_STATUS_READY);
}

void updateMissionStatus(Mission& mission, const Astronaut astronauts[], int astronautCount, const Inventory& inventory) {
    if (mission.status != MISSION_STATUS_PLANNING && mission.status != MISSION_STATUS_READY) {
        return;
    }

    mission.status = isMissionReady(mission, astronauts, astronautCount, inventory) ? MISSION_STATUS_READY : MISSION_STATUS_PLANNING;
}

bool launchMission(Mission& mission, Astronaut astronauts[], int astronautCount, Inventory& inventory) {
    if (mission.status != MISSION_STATUS_READY) {
        std::cout << "Mission is not ready." << std::endl;
        return false;
    }

    if (!isMissionReady(mission, astronauts, astronautCount, inventory)) {
        std::cout << "Mission is not ready." << std::endl;
        return false;
    }

    if (!hasEnoughResources(inventory, mission.requiredOxygen, mission.requiredWater, mission.requiredFood)) {
        std::cout << "Mission is not ready." << std::endl;
        return false;
    }

    consumeResources(inventory, mission.requiredOxygen, mission.requiredWater, mission.requiredFood);
    mission.status = MISSION_STATUS_IN_PROGRESS;
    std::cout << "Mission " << mission.id << " launched successfully." << std::endl;
    return true;
}

bool completeMission(Mission& mission, Astronaut astronauts[], int astronautCount) {
    if (mission.status != MISSION_STATUS_IN_PROGRESS) {
        std::cout << "Mission is not in progress." << std::endl;
        return false;
    }

    mission.status = MISSION_STATUS_COMPLETED;
    for (int i = 0; i < mission.assignedCount; ++i) {
        int index = mission.assignedAstronautIndexes[i];
        if (index >= 0 && index < astronautCount) {
            astronauts[index].status = ASTRONAUT_STATUS_RESTING;
            astronauts[index].assignedMissionId = -1;
        }
    }
    std::cout << "Mission " << mission.id << " completed." << std::endl;
    std::cout << "Assigned astronauts are now resting." << std::endl;
    return true;
}

std::string missionStatusToString(int status) {
    switch (status) {
        case MISSION_STATUS_PLANNING:
            return "Planning";
        case MISSION_STATUS_READY:
            return "Ready";
        case MISSION_STATUS_IN_PROGRESS:
            return "In progress";
        case MISSION_STATUS_COMPLETED:
            return "Completed";
        case MISSION_STATUS_CANCELLED:
            return "Cancelled";
        default:
            return "Unknown";
    }
}
