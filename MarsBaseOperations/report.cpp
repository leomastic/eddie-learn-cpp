#include "report.h"

#include <iostream>

#include "inventory.h"
#include "mission.h"
#include "astronaut.h"

void printMissionReadinessReport(const Mission& mission, const std::vector<Astronaut>& astronauts, const Inventory& inventory) {
    std::cout << "===== Mission Readiness =====" << std::endl;
    std::cout << "Mission: " << mission.name << std::endl;
    std::cout << "Assigned astronauts: " << mission.assignedAstronautIndexes.size() << " / " << mission.requiredAstronauts << std::endl;
    std::cout << "Assigned total skill: " << calculateAssignedSkill(mission, astronauts) << " / " << mission.minimumTotalSkill << std::endl;
    std::cout << "Oxygen: " << (inventory.oxygen >= mission.requiredOxygen ? "Enough" : "Not enough") << std::endl;
    std::cout << "Water: " << (inventory.water >= mission.requiredWater ? "Enough" : "Not enough") << std::endl;
    std::cout << "Food: " << (inventory.food >= mission.requiredFood ? "Enough" : "Not enough") << std::endl;
    std::cout << "Mission ready: " << (isMissionReady(mission, astronauts, inventory) ? "Yes" : "No") << std::endl;
}

void printBaseReport(const std::vector<Astronaut>& astronauts, const std::vector<Mission>& missions, const Inventory& inventory) {
    int available = 0;
    int assigned = 0;
    int resting = 0;
    int injured = 0;

    for (const Astronaut& astronaut : astronauts) {
        switch (astronaut.status) {
            case AstronautStatus::Available:
                ++available;
                break;
            case AstronautStatus::Assigned:
                ++assigned;
                break;
            case AstronautStatus::Resting:
                ++resting;
                break;
            case AstronautStatus::Injured:
                ++injured;
                break;
        }
    }

    int planning = 0;
    int ready = 0;
    int inProgress = 0;
    int completed = 0;
    int cancelled = 0;

    for (const Mission& mission : missions) {
        switch (mission.status) {
            case MissionStatus::Planning:
                ++planning;
                break;
            case MissionStatus::Ready:
                ++ready;
                break;
            case MissionStatus::InProgress:
                ++inProgress;
                break;
            case MissionStatus::Completed:
                ++completed;
                break;
            case MissionStatus::Cancelled:
                ++cancelled;
                break;
        }
    }

    std::cout << "===== Mars Base Report =====" << std::endl;
    std::cout << "Astronauts:" << std::endl;
    std::cout << "Total: " << astronauts.size() << std::endl;
    std::cout << "Available: " << available << std::endl;
    std::cout << "Assigned: " << assigned << std::endl;
    std::cout << "Resting: " << resting << std::endl;
    std::cout << "Injured: " << injured << std::endl;

    std::cout << std::endl;
    std::cout << "Missions:" << std::endl;
    std::cout << "Total: " << missions.size() << std::endl;
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
