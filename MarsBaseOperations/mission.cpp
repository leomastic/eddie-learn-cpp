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
    mission.status = MissionStatus::Planning;
    return mission;
}

void printMission(const Mission& mission, const std::vector<Astronaut>& astronauts) {
    std::cout << "Mission ID: " << mission.id << std::endl;
    std::cout << "Name: " << mission.name << std::endl;
    std::cout << "Status: " << missionStatusToString(mission.status) << std::endl;
    std::cout << "Required astronauts: " << mission.requiredAstronauts << std::endl;
    std::cout << "Assigned astronauts: " << mission.assignedAstronautIndexes.size() << std::endl;
    std::cout << "Minimum total skill: " << mission.minimumTotalSkill << std::endl;
    std::cout << "Assigned total skill: " << calculateAssignedSkill(mission, astronauts) << std::endl;
    std::cout << "Required oxygen: " << mission.requiredOxygen << std::endl;
    std::cout << "Required water: " << mission.requiredWater << std::endl;
    std::cout << "Required food: " << mission.requiredFood << std::endl;

    std::cout << "Assigned crew:" << std::endl;
    if (mission.assignedAstronautIndexes.empty()) {
        std::cout << "- None" << std::endl;
    } else {
        for (int index : mission.assignedAstronautIndexes) {
            if (index >= 0 && static_cast<std::size_t>(index) < astronauts.size()) {
                std::cout << "- " << astronauts[index].name << std::endl;
            }
        }
    }
}

void printAllMissions(const std::vector<Mission>& missions, const std::vector<Astronaut>& astronauts) {
    if (missions.empty()) {
        std::cout << "No missions registered." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < missions.size(); ++i) {
        std::cout << "Mission " << (i + 1) << ":" << std::endl;
        printMission(missions[i], astronauts);
        std::cout << std::endl;
    }
}

int findMissionIndexById(const std::vector<Mission>& missions, int missionId) {
    for (std::size_t i = 0; i < missions.size(); ++i) {
        if (missions[i].id == missionId) {
            return i;
        }
    }
    return -1;
}

bool assignAstronautToMission(Mission& mission, std::vector<Astronaut>& astronauts, int astronautIndex) {
    if (astronautIndex < 0 || static_cast<std::size_t>(astronautIndex) >= astronauts.size()) {
        return false;
    }

    Astronaut& astronaut = astronauts[astronautIndex];
    if (astronaut.status != AstronautStatus::Available) {
        return false;
    }

    if (mission.status != MissionStatus::Planning && mission.status != MissionStatus::Ready) {
        return false;
    }

    for (int assignedIndex : mission.assignedAstronautIndexes) {
        if (assignedIndex == astronautIndex) {
            return false;
        }
    }

    mission.assignedAstronautIndexes.push_back(astronautIndex);
    astronaut.status = AstronautStatus::Assigned;
    astronaut.assignedMissionId = mission.id;
    return true;
}

int calculateAssignedSkill(const Mission& mission, const std::vector<Astronaut>& astronauts) {
    int totalSkill = 0;
    for (int index : mission.assignedAstronautIndexes) {
        if (index >= 0 && static_cast<std::size_t>(index) < astronauts.size()) {
            totalSkill += astronauts[index].skillLevel;
        }
    }
    return totalSkill;
}

bool hasEnoughAstronauts(const Mission& mission) {
    return static_cast<int>(mission.assignedAstronautIndexes.size()) >= mission.requiredAstronauts;
}

bool hasEnoughSkill(const Mission& mission, const std::vector<Astronaut>& astronauts) {
    return calculateAssignedSkill(mission, astronauts) >= mission.minimumTotalSkill;
}

bool isMissionReady(const Mission& mission, const std::vector<Astronaut>& astronauts, const Inventory& inventory) {
    return hasEnoughAstronauts(mission)
        && hasEnoughSkill(mission, astronauts)
        && hasEnoughResources(inventory, mission.requiredOxygen, mission.requiredWater, mission.requiredFood)
        && (mission.status == MissionStatus::Planning || mission.status == MissionStatus::Ready);
}

void updateMissionStatus(Mission& mission, const std::vector<Astronaut>& astronauts, const Inventory& inventory) {
    if (mission.status != MissionStatus::Planning && mission.status != MissionStatus::Ready) {
        return;
    }

    mission.status = isMissionReady(mission, astronauts, inventory) ? MissionStatus::Ready : MissionStatus::Planning;
}

bool launchMission(Mission& mission, std::vector<Astronaut>& astronauts, Inventory& inventory) {
    if (mission.status != MissionStatus::Ready || !isMissionReady(mission, astronauts, inventory)) {
        std::cout << "Mission is not ready." << std::endl;
        return false;
    }

    consumeResources(inventory, mission.requiredOxygen, mission.requiredWater, mission.requiredFood);
    mission.status = MissionStatus::InProgress;
    std::cout << "Mission " << mission.id << " launched successfully." << std::endl;
    return true;
}

bool completeMission(Mission& mission, std::vector<Astronaut>& astronauts) {
    if (mission.status != MissionStatus::InProgress) {
        std::cout << "Mission is not in progress." << std::endl;
        return false;
    }

    mission.status = MissionStatus::Completed;
    for (int index : mission.assignedAstronautIndexes) {
        if (index >= 0 && static_cast<std::size_t>(index) < astronauts.size()) {
            astronauts[index].status = AstronautStatus::Resting;
            astronauts[index].assignedMissionId = -1;
        }
    }
    std::cout << "Mission " << mission.id << " completed." << std::endl;
    std::cout << "Assigned astronauts are now resting." << std::endl;
    return true;
}

std::string missionStatusToString(MissionStatus status) {
    switch (status) {
        case MissionStatus::Planning:
            return "Planning";
        case MissionStatus::Ready:
            return "Ready";
        case MissionStatus::InProgress:
            return "In progress";
        case MissionStatus::Completed:
            return "Completed";
        case MissionStatus::Cancelled:
            return "Cancelled";
        default:
            return "Unknown";
    }
}
