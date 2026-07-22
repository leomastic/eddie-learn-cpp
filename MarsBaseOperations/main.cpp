#include <algorithm>
#include <iostream>
#include <vector>

#include "astronaut.h"
#include "inventory.h"
#include "mission.h"
#include "report.h"
#include "utils.h"

enum class MenuChoice {
    AddAstronaut = 1, ShowAstronauts, AddMission, ShowMissions,
    AssignAstronaut, CheckReadiness, LaunchMission, CompleteMission,
    RestockInventory, ShowInventory, ShowBaseReport, ResetAstronaut, Exit
};

void printMenu() {
    std::cout << "===== Mars Base Operations Center =====\n"
              << "1. Add astronaut\n2. Show all astronauts\n3. Add mission\n"
              << "4. Show all missions\n5. Assign astronaut to mission\n"
              << "6. Check mission readiness\n7. Launch mission\n8. Complete mission\n"
              << "9. Restock inventory\n10. Show inventory\n11. Show full base report\n"
              << "12. Reset astronaut status\n13. Exit\n";
}

void addAstronaut(std::vector<Astronaut>& astronauts) {
    Astronaut astronaut = createAstronaut();
    if (findAstronautIndexByName(astronauts, astronaut.name) != -1) {
        std::cout << "An astronaut with this name already exists.\n";
        return;
    }
    astronauts.push_back(astronaut);
    std::cout << "Astronaut added.\n";
}

void addMission(std::vector<Mission>& missions) {
    Mission mission = createMission();
    if (findMissionIndexById(missions, mission.id) != -1) {
        std::cout << "A mission with this ID already exists.\n";
        return;
    }
    missions.push_back(mission);
    std::cout << "Mission added.\n";
}

void assignAstronaut(std::vector<Astronaut>& astronauts, std::vector<Mission>& missions,
                     const Inventory& inventory) {
    const std::string name = readNonEmptyWord("Astronaut name: ");
    const int astronautIndex = findAstronautIndexByName(astronauts, name);
    if (astronautIndex == -1) { std::cout << "Astronaut not found.\n"; return; }
    const int missionId = readIntInRange("Mission ID: ", 1, 100000);
    const int missionIndex = findMissionIndexById(missions, missionId);
    if (missionIndex == -1) { std::cout << "Mission not found.\n"; return; }

    Mission& mission = missions[missionIndex];
    const bool alreadyAssigned = std::find(
        mission.assignedAstronautIndexes.begin(),
        mission.assignedAstronautIndexes.end(), astronautIndex
    ) != mission.assignedAstronautIndexes.end();
    if (alreadyAssigned) {
        std::cout << "Astronaut is already assigned to this mission.\n";
    } else if (astronauts[astronautIndex].status != AstronautStatus::Available) {
        std::cout << "Astronaut is not available.\n";
    } else if (mission.status != MissionStatus::Planning && mission.status != MissionStatus::Ready) {
        std::cout << "Mission is not accepting assignments.\n";
    } else if (assignAstronautToMission(mission, astronauts, astronautIndex)) {
        updateMissionStatus(mission, astronauts, inventory);
        std::cout << "Astronaut " << astronauts[astronautIndex].name
                  << " assigned to mission " << mission.id << ".\n";
    }
}

int readMissionIndex(const std::vector<Mission>& missions) {
    const int id = readIntInRange("Mission ID: ", 1, 100000);
    const int index = findMissionIndexById(missions, id);
    if (index == -1) std::cout << "Mission not found.\n";
    return index;
}

void resetAstronaut(std::vector<Astronaut>& astronauts) {
    const std::string name = readNonEmptyWord("Astronaut name: ");
    const int index = findAstronautIndexByName(astronauts, name);
    if (index == -1) { std::cout << "Astronaut not found.\n"; return; }
    if (astronauts[index].status == AstronautStatus::Assigned) {
        std::cout << "Cannot reset an astronaut who is assigned to a mission.\n";
        return;
    }
    resetAstronautStatus(astronauts[index]);
    std::cout << "Astronaut " << astronauts[index].name << " is now available.\n";
}

int main() {
    std::vector<Astronaut> astronauts;
    std::vector<Mission> missions;
    Inventory inventory = createInitialInventory();

    while (true) {
        printMenu();
        const MenuChoice choice = static_cast<MenuChoice>(readIntInRange("Choose: ", 1, 13));
        if (choice == MenuChoice::Exit) break;
        switch (choice) {
            case MenuChoice::AddAstronaut: addAstronaut(astronauts); break;
            case MenuChoice::ShowAstronauts: printAllAstronauts(astronauts); break;
            case MenuChoice::AddMission: addMission(missions); break;
            case MenuChoice::ShowMissions: printAllMissions(missions, astronauts); break;
            case MenuChoice::AssignAstronaut: assignAstronaut(astronauts, missions, inventory); break;
            case MenuChoice::CheckReadiness: {
                const int index = readMissionIndex(missions);
                if (index != -1) printMissionReadinessReport(missions[index], astronauts, inventory);
                break;
            }
            case MenuChoice::LaunchMission: {
                const int index = readMissionIndex(missions);
                if (index != -1 && !launchMission(missions[index], astronauts, inventory))
                    std::cout << "Mission launch failed.\n";
                break;
            }
            case MenuChoice::CompleteMission: {
                const int index = readMissionIndex(missions);
                if (index != -1 && !completeMission(missions[index], astronauts))
                    std::cout << "Mission completion failed.\n";
                break;
            }
            case MenuChoice::RestockInventory:
                restockInventory(inventory);
                for (Mission& mission : missions) updateMissionStatus(mission, astronauts, inventory);
                break;
            case MenuChoice::ShowInventory: printInventory(inventory); break;
            case MenuChoice::ShowBaseReport: printBaseReport(astronauts, missions, inventory); break;
            case MenuChoice::ResetAstronaut: resetAstronaut(astronauts); break;
            case MenuChoice::Exit: break;
        }
        std::cout << '\n';
    }
    return 0;
}