#include "report.h"

#include <iostream>

#include "inventory.h"
#include "mission.h"
#include "astronaut.h"

void printMissionReadinessReport(const Mission& mission, const Astronaut astronauts[], int astronautCount, const Inventory& inventory) {
    std::cout << "===== Mission Readiness =====" << std::endl;
    std::cout << "Mission: " << mission.name << std::endl;
    std::cout << "Assigned astronauts: " << mission.assignedCount << " / " << mission.requiredAstronauts << std::endl;
    std::cout << "Assigned total skill: " << calculateAssignedSkill(mission, astronauts, astronautCount) << " / " << mission.minimumTotalSkill << std::endl;
    std::cout << "Oxygen: " << (inventory.oxygen >= mission.requiredOxygen ? "Enough" : "Not enough") << std::endl;
    std::cout << "Water: " << (inventory.water >= mission.requiredWater ? "Enough" : "Not enough") << std::endl;
    std::cout << "Food: " << (inventory.food >= mission.requiredFood ? "Enough" : "Not enough") << std::endl;
    std::cout << "Mission ready: " << (isMissionReady(mission, astronauts, astronautCount, inventory) ? "Yes" : "No") << std::endl;
}

void printBaseReport(const Astronaut astronauts[], int astronautCount, const Mission missions[], int missionCount, const Inventory& inventory) {
    int available = 0;
    int assigned = 0;
    int resting = 0;
    int injured = 0;

    for (int i = 0; i < astronautCount; ++i) {
        switch (astronauts[i].status) {
            case ASTRONAUT_STATUS_AVAILABLE:
                ++available;
                break;
            case ASTRONAUT_STATUS_ASSIGNED:
                ++assigned;
                break;
            case ASTRONAUT_STATUS_RESTING:
                ++resting;
                break;
            case ASTRONAUT_STATUS_INJURED:
                ++injured;
                break;
        }
    }

    int planning = 0;
    int ready = 0;
    int inProgress = 0;
    int completed = 0;
    int cancelled = 0;

    for (int i = 0; i < missionCount; ++i) {
        switch (missions[i].status) {
            case MISSION_STATUS_PLANNING:
                ++planning;
                break;
            case MISSION_STATUS_READY:
                ++ready;
                break;
            case MISSION_STATUS_IN_PROGRESS:
                ++inProgress;
                break;
            case MISSION_STATUS_COMPLETED:
                ++completed;
                break;
            case MISSION_STATUS_CANCELLED:
                ++cancelled;
                break;
        }
    }

    std::cout << "===== Mars Base Report =====" << std::endl;
    std::cout << "Astronauts:" << std::endl;
    std::cout << "Total: " << astronautCount << std::endl;
    std::cout << "Available: " << available << std::endl;
    std::cout << "Assigned: " << assigned << std::endl;
    std::cout << "Resting: " << resting << std::endl;
    std::cout << "Injured: " << injured << std::endl;

    std::cout << std::endl;
    std::cout << "Missions:" << std::endl;
    std::cout << "Total: " << missionCount << std::endl;
    std::cout << "Planning: " << planning << std::endl;
    std::cout << "Ready: " << ready << std::endl;
    std::cout << "In progress: " << inProgress << std::endl;
    std::cout << "Completed: " << completed << std::endl;
    std::cout << "Cancelled: " << cancelled << std::endl;

    std::cout << std::endl;
    std::cout << "Inventory:" << std::endl;
    std::cout << "Oxygen: " << inventory.oxygen << std::endl;
    std::cout << "Water: " << inventory.water << std::endl;
    std::cout << "Food: " << inventory.food << std::endl;

    std::cout << std::endl;
    std::cout << "Operational status:" << std::endl;
    std::cout << "Available astronauts: " << available << std::endl;
    std::cout << "Ready missions: " << ready << std::endl;
    std::cout << "Active missions: " << inProgress << std::endl;
}
