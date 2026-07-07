#include <iostream>
#include <string>
#include <vector>

enum class MissionType {
    Exploration,
    Rescue,
    Supply,
    Defense
};

struct Spaceship {
    std::string name;
    int fuelLevel;
    int engineHealth;
    int shieldPower;
    int crewCapacity;
    int cargoCapacity;
    bool hasMedicalBay;
};

struct Mission {
    std::string name;
    MissionType type;
    int requiredCrew;
    int requiredCargo;
    double distance;
    int dangerLevel;
    bool needsMedicalSupport;
};

enum class ShipStatus {
    Ready,
    NeedsMaintenance,
    OutOfService
};

enum class MissionRisk {
    Low,
    Medium,
    High,
    Critical
};

enum class AssignmentDecision {
    Assign,
    Delay,
    Reject
};

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if(value < minValue || value > maxValue){
            std::cout << "Invalid value. Please enter a value from " << minValue 
                                                                     << " to " << maxValue
                                                                     << std::endl;
            continue;
        }

        return value;
    }
}

double readDoubleInRange(std::string prompt, double minValue, double maxValue) {
    double value;

    while (true) {
        std::cout << prompt;

        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if(value < minValue || value > maxValue){
            std::cout << "Invalid value. Please enter a value from " << minValue 
                                                                     << " to " << maxValue
                                                                     << std::endl;
            continue;
        }

        return value;
    }
}

bool readYesNo(std::string prompt) {
    int value;

    while (true) {
        std::cout << prompt << " (1 for yes, 0 for no): ";

        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Enter 1 or 0." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value == 1) {
            return true;
        }

        if (value == 0) {
            return false;
        }

        std::cout << "Please enter 1 or 0." << std::endl;
    }
}

Spaceship readSpaceship(int shipNumber) {
    Spaceship ship;

    std::cout << std::endl;
    std::cout << "Spaceship " << shipNumber << std::endl;

    std::cout << "Ship name (no space): ";
    std::cin >> ship.name;

    ship.fuelLevel = readIntInRange("Fuel level (0-100): ", 0, 100);
    ship.engineHealth = readIntInRange("Engine health (0-100): ", 0, 100);
    ship.shieldPower = readIntInRange("Shield power (0-100): ", 0, 100);
    ship.crewCapacity = readIntInRange("Crew capacity (1-20): ", 1, 20);
    ship.cargoCapacity = readIntInRange("Cargo capacity (0-1000): ", 0, 1000);
    ship.hasMedicalBay = readYesNo("Has medical bay? ");

    return ship;
}

MissionType missionTypeFromCode(int typeCode) {
    if (typeCode == 1) {
        return MissionType::Exploration;
    }

    if (typeCode == 2) {
        return MissionType::Rescue;
    }

    if (typeCode == 3) {
        return MissionType::Supply;
    }

    return MissionType::Defense;
}

Mission readMission(int missionNumber) {
    Mission mission;

    std::cout << std::endl;
    std::cout << "Mission " << missionNumber << std::endl;

    std::cout << "Mission name (no space): ";
    std::cin >> mission.name;

    int typeCode = readIntInRange(
        "Mission type (1=Exploration, 2=Rescue, 3=Supply, 4=Defense): ",
        1,
        4
    );

    mission.type = missionTypeFromCode(typeCode);
    mission.requiredCrew = readIntInRange("Required crew (1-20): ", 1, 20);
    mission.requiredCargo = readIntInRange("Required cargo (0-1000): ", 0, 1000);
    mission.distance = readDoubleInRange("Distance (1-10000): ", 1.0, 10000.0);
    mission.dangerLevel = readIntInRange("Danger level (0-10): ", 0, 10);
    mission.needsMedicalSupport = readYesNo("Needs medical support? ");

    return mission;
}

ShipStatus calculateShipStatus(const Spaceship& ship) {
    if(ship.engineHealth < 30 || ship.fuelLevel < 20) {
        return ShipStatus::OutOfService;
    }

    if(ship.engineHealth < 60 || ship.fuelLevel < 40 || ship.shieldPower < 30) {
        return ShipStatus::NeedsMaintenance;
    }

    return ShipStatus::Ready;
}

MissionRisk calculateMissionRisk(const Mission& mission) {
    if(mission.dangerLevel >= 9 || mission.distance > 8000) {
        return MissionRisk::Critical;
    }

    if(mission.dangerLevel >= 7 || mission.distance > 6000) {
        return MissionRisk::High;
    }

    if(mission.dangerLevel >= 4 || mission.distance > 3000) {
        return MissionRisk::Medium;
    }

    return MissionRisk::Low;
}

std::string shipStatusToString(ShipStatus status) {
    if(status == ShipStatus::NeedsMaintenance) {
        return "Needs maintenance";
    }

    if(status == ShipStatus::OutOfService) {
        return "Out of service";
    }

    return "Ready";
}

std::string missionTypeToString(MissionType type) {
    if(type == MissionType::Defense) {
        return "Defence";
    }

    if(type == MissionType::Exploration) {
        return "Exploration";
    }

    if(type == MissionType::Rescue) {
        return "Rescue";
    }

    return "Supply";
}

std::string missionRiskToString(MissionRisk risk) {
    if(risk == MissionRisk::Critical) {
        return "Critical";
    }

    if(risk == MissionRisk::High) {
        return "High";
    }

    if(risk == MissionRisk::Medium) {
        return "Medium";
    }

    return "Low";
}

std::string assignmentDecisionToString(AssignmentDecision decision) {
    if(decision == AssignmentDecision::Assign) {
        return "Assign";
    }

    if(decision == AssignmentDecision::Delay) {
        return "Delay";
    }

    return "Reject";
}

bool canHandleMission(const Spaceship& ship, const Mission& mission) {
    ShipStatus status = calculateShipStatus(ship);
    MissionRisk risk = calculateMissionRisk(mission);
    MissionType type = mission.type;

    if (status == ShipStatus::OutOfService) {
        return false;
    }

    if (ship.crewCapacity < mission.requiredCrew) {
        return false;
    }

    if (ship.cargoCapacity < mission.requiredCargo) {
        return false;
    }

    if (mission.needsMedicalSupport && !ship.hasMedicalBay) {
        return false;
    }

    if ((risk == MissionRisk::High || risk == MissionRisk::Critical) &&
        ship.shieldPower < 50) {
        return false;
    }

    if (risk == MissionRisk::Critical && ship.engineHealth < 70) {
        return false;
    }

    if (type == MissionType::Rescue && !ship.hasMedicalBay) {
        return false;
    }

    if (type == MissionType::Defense && ship.shieldPower < 70) {
        return false;
    }

    if (mission.distance > 5000.0 && ship.fuelLevel < 60) {
        return false;
    }

    return true;
}

bool isAlmostSuitable(const Spaceship& ship, const Mission& mission) {
    ShipStatus status = calculateShipStatus(ship);

    return status == ShipStatus::NeedsMaintenance &&
           ship.crewCapacity >= mission.requiredCrew &&
           ship.cargoCapacity >= mission.requiredCargo;
}

AssignmentDecision calculateAssignmentDecision(
    const std::vector<Spaceship>& ships,
    const Mission& mission
) {
    for (const Spaceship& ship : ships) {
        if (canHandleMission(ship, mission)) {
            return AssignmentDecision::Assign;
        }
    }

    for (const Spaceship& ship : ships) {
        if (isAlmostSuitable(ship, mission)) {
            return AssignmentDecision::Delay;
        }
    }

    return AssignmentDecision::Reject;
}

int calculateShipMissionScore(const Spaceship& ship, const Mission& mission) {
    int score = ship.fuelLevel + ship.engineHealth + ship.shieldPower;

    if (ship.hasMedicalBay) {
        score += 10;
    }

    if (ship.crewCapacity >= mission.requiredCrew + 5) {
        score += 10;
    }

    if (ship.cargoCapacity >= mission.requiredCargo + 100) {
        score += 10;
    }

    return score;
}

int findBestShipIndexForMission(
    const std::vector<Spaceship>& ships,
    const Mission& mission
) {
    int bestIndex = -1;
    int bestScore = 0;

    for (int i = 0; i < ships.size(); i++) {
        if (canHandleMission(ships[i], mission)) {
            int score = calculateShipMissionScore(ships[i], mission);

            if (bestIndex == -1 || score > bestScore) {
                bestIndex = i;
                bestScore = score;
            }
        }
    }

    return bestIndex;
}

int countReadyShips(const std::vector<Spaceship>& ships) {
    int count = 0;
    for (const Spaceship& ship : ships) {
        if (calculateShipStatus(ship) == ShipStatus::Ready) {
            ++count;
        }
    }

    return count;
}

int countMaintenanceShips(const std::vector<Spaceship>& ships) {
    int count = 0;
    for (const Spaceship& ship : ships) {
        if (calculateShipStatus(ship) == ShipStatus::NeedsMaintenance) {
            ++count;
        }
    }

    return count;
}

int countOutOfServiceShips(const std::vector<Spaceship>& ships) {
    int count = 0;
    for (const Spaceship& ship : ships) {
        if (calculateShipStatus(ship) == ShipStatus::OutOfService) {
            ++count;
        }
    }

    return count;
}

int countAssignableMissions(
    const std::vector<Spaceship>& ships,
    const std::vector<Mission>& missions
) {
    int count = 0;
    for (const Mission& mission : missions) {
        if (calculateAssignmentDecision(ships, mission) == AssignmentDecision::Assign) {
            ++count;
        }
    }

    return count;
}

int countDelayedMissions(
    const std::vector<Spaceship>& ships,
    const std::vector<Mission>& missions
) {
    int count = 0;
    for (const Mission& mission : missions) {
        if (calculateAssignmentDecision(ships, mission) == AssignmentDecision::Delay) {
            ++count;
        }
    }

    return count;
}

int countRejectedMissions(
    const std::vector<Spaceship>& ships,
    const std::vector<Mission>& missions
) {
    int count = 0;
    for (const Mission& mission : missions) {
        if (calculateAssignmentDecision(ships, mission) == AssignmentDecision::Reject) {
            ++count;
        }
    }

    return count;
}

void printFleetReport(const std::vector<Spaceship>& ships) {
    std::cout << "\n===== Fleet Report =====" << std::endl;
    std::cout << "Total ships: " << ships.size() << std::endl;
    std::cout << "Ready: " << countReadyShips(ships) << std::endl;
    std::cout << "Needs maintenance: " << countMaintenanceShips(ships) << std::endl;
    std::cout << "Out of service: " << countOutOfServiceShips(ships) << std::endl;

    for (int i = 0; i < ships.size(); ++i) {
        const Spaceship& ship = ships[i];
        std::cout << "\nShip " << (i + 1) << ": " << ship.name << " | ";
        std::cout << "  Fuel level: " << ship.fuelLevel << " | ";
        std::cout << "  Engine health: " << ship.engineHealth << " | ";
        std::cout << "  Shield power: " << ship.shieldPower << " | ";
        std::cout << "  Crew capacity: " << ship.crewCapacity << " | ";
        std::cout << "  Cargo capacity: " << ship.cargoCapacity << " | ";
        std::cout << "  Medical bay: " << (ship.hasMedicalBay ? "Yes" : "No") << " | ";
        std::cout << "  Status: " << shipStatusToString(calculateShipStatus(ship)) << " | ";
    }
}

void printMissionReport(
    const std::vector<Spaceship>& ships,
    const std::vector<Mission>& missions
) {
    std::cout << "\n===== Mission Report =====" << std::endl;
    std::cout << "Total missions: " << missions.size() << std::endl;

    for (int i = 0; i < missions.size(); ++i) {
        const Mission& mission = missions[i];
        std::cout << "\nMission " << (i + 1) << ": " << mission.name << " | ";
        std::cout << "  Type: " << missionTypeToString(mission.type) << " | ";
        std::cout << "  Required crew: " << mission.requiredCrew << " | ";
        std::cout << "  Required cargo: " << mission.requiredCargo << " | ";
        std::cout << "  Distance: " << mission.distance << " | ";
        std::cout << "  Danger level: " << mission.dangerLevel << " | ";
        std::cout << "  Medical support required: " << (mission.needsMedicalSupport ? "Yes" : "No") << " | ";
        std::cout << "  Risk: " << missionRiskToString(calculateMissionRisk(mission)) << " | ";
        AssignmentDecision decision = calculateAssignmentDecision(ships, mission);
        std::cout << "  Assignment decision: " << assignmentDecisionToString(decision) << " | ";

        if (decision == AssignmentDecision::Assign) {
            int bestShipIndex = findBestShipIndexForMission(ships, mission);
            if (bestShipIndex >= 0) {
                std::cout << "  Best ship: " << ships[bestShipIndex].name << " | ";
            }
        }
    }
}

void printFinalSummary(
    const std::vector<Spaceship>& ships,
    const std::vector<Mission>& missions
) {
    std::cout << "\n===== Final Summary =====" << std::endl;
    std::cout << "Ships ready for deployment: " << countReadyShips(ships) << std::endl;
    std::cout << "Ships requiring maintenance: " << countMaintenanceShips(ships) << std::endl;
    std::cout << "Ships out of service: " << countOutOfServiceShips(ships) << std::endl;
    std::cout << "Missions assignable: " << countAssignableMissions(ships, missions) << std::endl;
    std::cout << "Missions delayed: " << countDelayedMissions(ships, missions) << std::endl;
    std::cout << "Missions rejected: " << countRejectedMissions(ships, missions) << std::endl;
}

int main() {
    std::cout << "===== Space Fleet Dispatch Center =====" << std::endl;

    std::cout << "Commander name: ";
    std::string commanderName;
    std::cin >> commanderName;

    int shipCount = readIntInRange("Number of ships (1-10): ", 1, 10);

    std::vector<Spaceship> ships;

    for (int i = 1; i <= shipCount; i++) {
        Spaceship ship = readSpaceship(i);
        ships.push_back(ship);
    }

    int missionCount = readIntInRange("Number of missions (1-10): ", 1, 10);

    std::vector<Mission> missions;

    for (int i = 1; i <= missionCount; i++) {
        Mission mission = readMission(i);
        missions.push_back(mission);
    }

    std::cout << std::endl;
    std::cout << "Commander: " << commanderName << std::endl;

    printFleetReport(ships);
    printMissionReport(ships, missions);
    printFinalSummary(ships, missions);

    return 0;
}





//Dòng này là 555 dòng =)