#include "mission.h"
#include "file_io.h"
#include <string>
#include <vector>

enum class MenuChoice {
    ListMissions = 1,
    AddMission,
    SaveMissions,
    ReloadMissionsFromFile,
    Exit
};

MenuChoice readMenuChoice();
    
void printMenu();

int readIntInRange(const std::string& prompt, int minValue, int maxValue);
#include <fstream>
#include <iostream>
#include <limits>

int readIntInRange(const std::string& prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue << " and " << maxValue << "." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Remove the trailing newline so subsequent getline() works correctly.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

// Mission implementation moved to mission.cpp
// File I/O functions implemented in file_io.cpp

MenuChoice readMenuChoice() {
    int choice = readIntInRange("Choose: ", 1, 5);

    switch (choice) {
        case 1:
            return MenuChoice::ListMissions;

        case 2:
            return MenuChoice::AddMission;

        case 3:
            return MenuChoice::SaveMissions;

        case 4:
            return MenuChoice::ReloadMissionsFromFile;

        default:
            return MenuChoice::Exit;
    }
}

void printMenu() {
    std::cout << "===== Mission Logbook =====" << std::endl;
    std::cout << std::endl;
    std::cout << "1. List missions" << std::endl;
    std::cout << "2. Add mission" << std::endl;
    std::cout << "3. Save missions" << std::endl;
    std::cout << "4. Reload missions from file" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << std::endl;
}

// Append a short activity message to activity.log (append mode)
void appendActivity(const std::string& message) {
    std::ofstream a("activity.log", std::ios::app);
    if (!a.is_open()) {
        return;
    }

    a << message << "\n";
    a.close();
}

int main() {
    bool running = true;
    std::vector<Mission> missions = {};

    // Load missions from file at startup
    const std::string filename = "missions.txt";
    missions = loadMissions(filename);
    std::cout << "Loaded " << missions.size() << " missions from " << filename << std::endl;
    appendActivity("Program started");

    while (running) {
        printMenu();
        MenuChoice choice = readMenuChoice();

        switch(choice) {
            case MenuChoice::ListMissions: {
                std::cout << "=== Mission List ===" << std::endl;

                if (missions.empty()) {
                    std::cout << "No missions available." << std::endl;
                } else {
                    for (std::size_t i = 0; i < missions.size(); ++i) {
                        std::cout << "Mission " << i + 1
                                << ": "
                                << missions[i].getName()
                                << " (priority "
                                << missions[i].getPriority()
                                << ")"
                                << std::endl;
                    }
                }
                break;
            }
            case MenuChoice::AddMission: {
                std::cout << "Mission name: ";
                std::string name;
                std::getline(std::cin, name);

                if (name.empty()) {
                    std::cout << "Mission name cannot be empty." << std::endl;
                    break;
                }

                int priority = readIntInRange("Priority (1-5): ", 1, 5);

                missions.push_back(Mission(name, priority));
                std::cout << "Mission added successfully." << std::endl;
                appendActivity(std::string("Added mission: ") + name);
                break;
            }

            case MenuChoice::SaveMissions: {
                bool saved = saveMissions(filename, missions);

                if (saved) {
                    std::cout << "Missions saved successfully." << std::endl;
                    appendActivity("Saved missions");
                } else {
                    std::cout << "Failed to save missions." << std::endl;
                }
                break;
            }

            case MenuChoice::ReloadMissionsFromFile: {
                missions = loadMissions(filename);
                std::cout << "Missions reloaded from file." << std::endl;
                appendActivity("Reloaded missions");
                break;
            }

            case MenuChoice::Exit:
                std::cout << "Exiting the Program..." << std::endl;
                // Auto-save on exit (Challenge 2): attempt to save; warn if it fails.
                if (saveMissions(filename, missions)) {
                    appendActivity("Saved missions on exit");
                } else {
                    std::cout << "Warning: Failed to save missions on exit." << std::endl;
                    appendActivity("Failed to save missions on exit");
                }
                appendActivity("Program exited");
                running = false;
                break;

            default:
                std::cout << "Unknown menu choice." << std::endl;
                break;
        }
    }

    return 0;
}