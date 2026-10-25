#include <iostream>
#include <string>
#include "greenhouse_center.h"
#include "utils.h"

enum class MenuChoice {
    AddGreenhouse = 1,
    UpdateEnvironment,
    RefillWater,
    AddPlantBatch,
    AdvanceOneDay,
    HarvestPlantBatch,
    FailPlantBatch,
    ShutDown,
    Restart,
    ShowGreenhouse,
    ShowPlantBatches,
    ShowAllGreenhouses,
    ShowSummary,
    Exit
};

void printMenu() {
    std::cout << "===== Mars Greenhouse Control Center =====" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Add greenhouse" << std::endl;
    std::cout << "2. Update environment" << std::endl;
    std::cout << "3. Refill water" << std::endl;
    std::cout << "4. Add plant batch" << std::endl;
    std::cout << "5. Advance greenhouse one day" << std::endl;
    std::cout << "6. Harvest plant batch" << std::endl;
    std::cout << "7. Mark plant batch failed" << std::endl;
    std::cout << "8. Shut down greenhouse" << std::endl;
    std::cout << "9. Restart greenhouse" << std::endl;
    std::cout << "10. Show one greenhouse" << std::endl;
    std::cout << "11. Show greenhouse plant batches" << std::endl;
    std::cout << "12. Show all greenhouses" << std::endl;
    std::cout << "13. Show center summary" << std::endl;
    std::cout << "14. Exit" << std::endl;
}

int main() {
    GreenhouseCenter center;
    bool running = true;

    while (running) {
        printMenu();
        int choice = readIntInRange("Please select an option: ", 1, 14);
        std::cout << std::endl;

        switch (static_cast<MenuChoice>(choice)) {
            case MenuChoice::AddGreenhouse: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                std::string name = readNonEmptyLine("Please enter the greenhouse name: ");
                int waterLevel = readIntInRange("Please enter the initial water level (0 --> 100): ", 0, 100);
                int temperature = readIntInRange("Please enter the initial temperature (-100 --> 100): ", -100, 100);
                int humidity = readIntInRange("Please enter the initial humidity (0 --> 100): ", 0, 100);

                if (center.addGreenhouse(id, name, waterLevel, temperature, humidity)) {
                    std::cout << "Greenhouse added successfully." << std::endl;
                } else {
                    std::cout << "Failed to add greenhouse." << std::endl;
                }
                break;
            }
            case MenuChoice::UpdateEnvironment: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                int temperature = readIntInRange("Please enter the new temperature (-100 --> 100): ", -100, 100);
                int humidity = readIntInRange("Please enter the new humidity (0 --> 100): ", 0, 100);

                if (center.updateGreenhouseEnvironment(id, temperature, humidity)) {
                    std::cout << "Environment updated successfully." << std::endl;
                } else {
                    std::cout << "Failed to update environment." << std::endl;
                }
                break;
            }
            case MenuChoice::RefillWater: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                int amount = readIntInRange("Please enter the refill amount (> 0): ", 1, 100);

                if (center.refillGreenhouseWater(id, amount)) {
                    std::cout << "Water refilled successfully." << std::endl;
                } else {
                    std::cout << "Failed to refill water." << std::endl;
                }
                break;
            }
            case MenuChoice::AddPlantBatch: {
                std::string greenhouseId = readNonEmptyWord("Please enter the greenhouse id: ");
                std::string batchId = readNonEmptyWord("Please enter the plant batch id: ");
                std::string plantName = readNonEmptyLine("Please enter the plant name: ");
                int requiredGrowthDays = readIntInRange("Please enter the required growth days (1 --> 100000): ", 1, 100000);

                if (center.addPlantBatch(greenhouseId, batchId, plantName, requiredGrowthDays)) {
                    std::cout << "Plant batch added successfully." << std::endl;
                } else {
                    std::cout << "Failed to add plant batch." << std::endl;
                }
                break;
            }
            case MenuChoice::AdvanceOneDay: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                if (center.advanceGreenhouseOneDay(id)) {
                    std::cout << "Greenhouse advanced one day." << std::endl;
                } else {
                    std::cout << "Failed to advance greenhouse one day." << std::endl;
                }
                break;
            }
            case MenuChoice::HarvestPlantBatch: {
                std::string greenhouseId = readNonEmptyWord("Please enter the greenhouse id: ");
                std::string batchId = readNonEmptyWord("Please enter the plant batch id: ");
                if (center.harvestPlantBatch(greenhouseId, batchId)) {
                    std::cout << "Plant batch harvested successfully." << std::endl;
                } else {
                    std::cout << "Failed to harvest plant batch." << std::endl;
                }
                break;
            }
            case MenuChoice::FailPlantBatch: {
                std::string greenhouseId = readNonEmptyWord("Please enter the greenhouse id: ");
                std::string batchId = readNonEmptyWord("Please enter the plant batch id: ");
                if (center.failPlantBatch(greenhouseId, batchId)) {
                    std::cout << "Plant batch marked failed." << std::endl;
                } else {
                    std::cout << "Failed to mark plant batch failed." << std::endl;
                }
                break;
            }
            case MenuChoice::ShutDown: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                if (center.shutDownGreenhouse(id)) {
                    std::cout << "Greenhouse shut down." << std::endl;
                } else {
                    std::cout << "Failed to shut down greenhouse." << std::endl;
                }
                break;
            }
            case MenuChoice::Restart: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                if (center.restartGreenhouse(id)) {
                    std::cout << "Greenhouse restarted." << std::endl;
                } else {
                    std::cout << "Failed to restart greenhouse." << std::endl;
                }
                break;
            }
            case MenuChoice::ShowGreenhouse: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                if (!center.printGreenhouse(id)) {
                    std::cout << "Greenhouse not found." << std::endl;
                }
                break;
            }
            case MenuChoice::ShowPlantBatches: {
                std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
                if (!center.printGreenhousePlantBatches(id)) {
                    std::cout << "Greenhouse not found." << std::endl;
                }
                break;
            }
            case MenuChoice::ShowAllGreenhouses: {
                center.printAllGreenhouses();
                break;
            }
            case MenuChoice::ShowSummary: {
                center.printSummary();
                break;
            }
            case MenuChoice::Exit: {
                running = false;
                std::cout << "Exiting..." << std::endl;
                break;
            }
            default: {
                std::cout << "Unknown option." << std::endl;
                break;
            }
        }

        std::cout << std::endl;
    }

    return 0;
}