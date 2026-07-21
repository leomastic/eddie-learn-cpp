#include <iostream>

#include "astronaut.h"
#include "inventory.h"
#include "mission.h"
#include "report.h"
#include "utils.h"

const int MENU_CHOICE_ADD_ASTRONAUT = 1;
const int MENU_CHOICE_SHOW_ASTRONAUTS = 2;
const int MENU_CHOICE_ADD_MISSION = 3;
const int MENU_CHOICE_SHOW_MISSIONS = 4;
const int MENU_CHOICE_ASSIGN_ASTRONAUT = 5;
const int MENU_CHOICE_CHECK_MISSION_READINESS = 6;
const int MENU_CHOICE_LAUNCH_MISSION = 7;
const int MENU_CHOICE_COMPLETE_MISSION = 8;
const int MENU_CHOICE_RESTOCK_INVENTORY = 9;
const int MENU_CHOICE_SHOW_INVENTORY = 10;
const int MENU_CHOICE_SHOW_BASE_REPORT = 11;
const int MENU_CHOICE_RESET_ASTRONAUT_STATUS = 12;
const int MENU_CHOICE_EXIT = 13;

int main() {
    Astronaut astronauts[100];
    int astronautCount = 0;
    Mission missions[100];
    int missionCount = 0;
    Inventory inventory = createInitialInventory();

    while (true) {
        std::cout << "===== Mars Base Operations Center =====" << std::endl;
        std::cout << "1. Add astronaut" << std::endl;
        std::cout << "2. Show all astronauts" << std::endl;
        std::cout << "3. Add mission" << std::endl;
        std::cout << "4. Show all missions" << std::endl;
        std::cout << "5. Assign astronaut to mission" << std::endl;
        std::cout << "6. Check mission readiness" << std::endl;
        std::cout << "7. Launch mission" << std::endl;
        std::cout << "8. Complete mission" << std::endl;
        std::cout << "9. Restock inventory" << std::endl;
        std::cout << "10. Show inventory" << std::endl;
        std::cout << "11. Show full base report" << std::endl;
        std::cout << "12. Reset astronaut status" << std::endl;
        std::cout << "13. Exit" << std::endl;

        int choice = readIntInRange("Choose: ", 1, 13);

        if (choice == MENU_CHOICE_EXIT) {
            break;
        }

        switch (choice) {
            case MENU_CHOICE_ADD_ASTRONAUT: {
                Astronaut astronaut = createAstronaut();
                if (findAstronautIndexByName(astronauts, astronautCount, astronaut.name) != -1) {
                    std::cout << "An astronaut with this name already exists." << std::endl;
                } else {
                    astronauts[astronautCount] = astronaut;
                    ++astronautCount;
                    std::cout << "Astronaut added." << std::endl;
                }
                break;
            }
            case MENU_CHOICE_SHOW_ASTRONAUTS:
                printAllAstronauts(astronauts, astronautCount);
                break;
            case MENU_CHOICE_ADD_MISSION: {
                Mission mission = createMission();
                if (findMissionIndexById(missions, missionCount, mission.id) != -1) {
                    std::cout << "A mission with this ID already exists." << std::endl;
                } else {
                    missions[missionCount] = mission;
                    ++missionCount;
                    std::cout << "Mission added." << std::endl;
                }
                break;
            }
            case MENU_CHOICE_SHOW_MISSIONS:
                printAllMissions(missions, missionCount, astronauts, astronautCount);
                break;
            case MENU_CHOICE_ASSIGN_ASTRONAUT: {
                std::string astronautName = readNonEmptyWord("Astronaut name: ");
                int astronautIndex = findAstronautIndexByName(astronauts, astronautCount, astronautName);
                if (astronautIndex == -1) {
                    std::cout << "Astronaut not found." << std::endl;
                } else {
                    int missionId = readIntInRange("Mission ID: ", 1, 100000);
                    int missionIndex = findMissionIndexById(missions, missionCount, missionId);
                    if (missionIndex == -1) {
                        std::cout << "Mission not found." << std::endl;
                    } else if (!assignAstronautToMission(missions[missionIndex], astronauts[astronautIndex], astronautIndex)) {
                        std::cout << "Astronaut is not available or mission is not accepting assignments." << std::endl;
                    } else {
                        updateMissionStatus(missions[missionIndex], astronauts, astronautCount, inventory);
                        std::cout << "Astronaut " << astronauts[astronautIndex].name << " assigned to mission " << missions[missionIndex].id << "." << std::endl;
                    }
                }
                break;
            }
            case MENU_CHOICE_CHECK_MISSION_READINESS: {
                int missionId = readIntInRange("Mission ID: ", 1, 100000);
                int missionIndex = findMissionIndexById(missions, missionCount, missionId);
                if (missionIndex == -1) {
                    std::cout << "Mission not found." << std::endl;
                } else {
                    printMissionReadinessReport(missions[missionIndex], astronauts, astronautCount, inventory);
                }
                break;
            }
            case MENU_CHOICE_LAUNCH_MISSION: {
                int missionId = readIntInRange("Mission ID: ", 1, 100000);
                int missionIndex = findMissionIndexById(missions, missionCount, missionId);
                if (missionIndex == -1) {
                    std::cout << "Mission not found." << std::endl;
                } else if (!launchMission(missions[missionIndex], astronauts, astronautCount, inventory)) {
                    std::cout << "Mission launch failed." << std::endl;
                }
                break;
            }
            case MENU_CHOICE_COMPLETE_MISSION: {
                int missionId = readIntInRange("Mission ID: ", 1, 100000);
                int missionIndex = findMissionIndexById(missions, missionCount, missionId);
                if (missionIndex == -1) {
                    std::cout << "Mission not found." << std::endl;
                } else if (!completeMission(missions[missionIndex], astronauts, astronautCount)) {
                    std::cout << "Mission completion failed." << std::endl;
                }
                break;
            }
            case MENU_CHOICE_RESTOCK_INVENTORY:
                restockInventory(inventory);
                for (int i = 0; i < missionCount; ++i) {
                    updateMissionStatus(missions[i], astronauts, astronautCount, inventory);
                }
                break;
            case MENU_CHOICE_SHOW_INVENTORY:
                printInventory(inventory);
                break;
            case MENU_CHOICE_SHOW_BASE_REPORT:
                printBaseReport(astronauts, astronautCount, missions, missionCount, inventory);
                break;
            case MENU_CHOICE_RESET_ASTRONAUT_STATUS: {
                std::string astronautName = readNonEmptyWord("Astronaut name: ");
                int astronautIndex = findAstronautIndexByName(astronauts, astronautCount, astronautName);
                if (astronautIndex == -1) {
                    std::cout << "Astronaut not found." << std::endl;
                } else if (astronauts[astronautIndex].status == ASTRONAUT_STATUS_ASSIGNED) {
                    std::cout << "Cannot reset an astronaut who is assigned to a mission." << std::endl;
                } else {
                    resetAstronautStatus(astronauts[astronautIndex]);
                    std::cout << "Astronaut " << astronauts[astronautIndex].name << " is now available." << std::endl;
                }
                break;
            }
            default:
                break;
        }

        std::cout << std::endl;
    }

    return 0;
}
