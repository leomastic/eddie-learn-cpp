#include <iostream>
#include <vector>

#include "fleet.h"
#include "robot.h"
#include "simulation.h"
#include "utils.h"

enum class MenuChoice {
    AddRobot = 1,
    ShowRobots,
    UpdateSensors,
    RunOneRound,
    RunMultipleRounds,
    FindBestRobot,
    ShowSummary,
    ResetRobot,
    Exit
};

static void printMenu() {
    std::cout << "===== Space Rescue Fleet =====" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Add robot" << std::endl;
    std::cout << "2. Show all robots" << std::endl;
    std::cout << "3. Update robot sensors" << std::endl;
    std::cout << "4. Run one simulation round" << std::endl;
    std::cout << "5. Run multiple simulation rounds" << std::endl;
    std::cout << "6. Find best rescue robot" << std::endl;
    std::cout << "7. Show fleet summary" << std::endl;
    std::cout << "8. Reset a robot" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::vector<Robot> robots;
    bool running = true;

    while (running) {
        printMenu();
        int choiceValue = readIntInRange("Choose: ", 1, 9);
        MenuChoice choice = static_cast<MenuChoice>(choiceValue);

        switch (choice) {
            case MenuChoice::AddRobot: {
                Robot robot = createRobot();
                if (findRobotIndexByName(robots, robot.name()) != -1) {
                    std::cout << "A robot with this name already exists." << std::endl;
                } else {
                    robots.push_back(robot);
                }
                break;
            }

            case MenuChoice::ShowRobots:
                printAllRobots(robots);
                break;

            case MenuChoice::UpdateSensors: {
                std::string name = readNonEmptyWord("Enter the robot name: ");
                int index = findRobotIndexByName(robots, name);
                if (index >= 0) {
                    robots[index].updateSensorData();
                } else {
                    std::cout << "Robot not found." << std::endl;
                }
                break;
            }

            case MenuChoice::RunOneRound:
                runFleetRound(robots);
                break;

            case MenuChoice::RunMultipleRounds: {
                int rounds = readIntInRange("Number of rounds (1--10): ", 1, 10);
                runFleetSimulation(robots, rounds);
                break;
            }

            case MenuChoice::FindBestRobot: {
                int bestIndex = findBestRescueRobotIndex(robots);
                if (bestIndex >= 0) {
                    std::cout << "Best rescue robot: " << robots[bestIndex].name() << std::endl;
                } else {
                    std::cout << "Best rescue robot: None" << std::endl;
                }
                break;
            }

            case MenuChoice::ShowSummary:
                printFleetSummary(robots);
                break;

            case MenuChoice::ResetRobot: {
                std::string name = readNonEmptyWord("Enter the robot name: ");
                int index = findRobotIndexByName(robots, name);
                if (index >= 0) {
                    robots[index].reset();
                    std::cout << "Robot " << robots[index].name() << " has been reset." << std::endl;
                } else {
                    std::cout << "Robot not found." << std::endl;
                }
                break;
            }

            case MenuChoice::Exit:
                running = false;
                break;
        }

        std::cout << std::endl;
    }

    return 0;
}
