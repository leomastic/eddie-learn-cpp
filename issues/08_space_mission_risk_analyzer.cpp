#include <iostream>
#include <string>
#include <vector>

struct Mission {
    std::string name;
    double distance;
    int fuelLevel;
    int crewCount;
    int dangerLevel;
    bool hasShield;
};

enum class MissionStatus {
    Ready,
    Warning,
    Blocked
};

enum class RiskLevel {
    Low,
    Medium,
    High,
    Critical
};

enum class LaunchDecision {
    Launch,
    Delay,
    Cancel
};

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt << std::endl;

        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value from "
                      << minValue << " to " << maxValue << std::endl;
            continue;
        }

        return value;
    }
}

double readDoubleInRange(std::string prompt, double minValue, double maxValue) {
    double value;

    while (true) {
        std::cout << prompt << std::endl;

        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value from "
                      << minValue << " to " << maxValue << std::endl;
            continue;
        }

        return value;
    }
}

bool readYesNo(std::string prompt) {
    int value;

    while (true) {
        std::cout << prompt << " (1 = yes, 0 = no): ";

        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Enter 1 for yes or 0 for no." << std::endl;
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

Mission readMission(int missionNumber) {
    Mission mission;

    std::cout << std::endl;
    std::cout << "Mission " << missionNumber << std::endl;

    std::cout << "Mission name (no space): ";
    std::cin >> mission.name;

    mission.distance = readDoubleInRange("Distance to target (1-10000): ", 1.0, 10000.0);
    mission.fuelLevel = readIntInRange("Fuel level (0-100): ", 0, 100);
    mission.crewCount = readIntInRange("Crew count (1-10): ", 1, 10);
    mission.dangerLevel = readIntInRange("Danger level (0-10): ", 0, 10);
    mission.hasShield = readYesNo("Has shield? ");

    return mission;
}

MissionStatus calculateMissionStatus(const Mission& mission) {
    if (mission.fuelLevel < 30) {
        return MissionStatus::Blocked;
    }

    if (mission.crewCount < 2) {
        return MissionStatus::Blocked;
    }

    if (mission.dangerLevel >= 9 && !mission.hasShield) {
        return MissionStatus::Blocked;
    }

    if (mission.fuelLevel < 50) {
        return MissionStatus::Warning;
    }

    if (mission.dangerLevel >= 6) {
        return MissionStatus::Warning;
    }

    if (mission.distance > 5000.0) {
        return MissionStatus::Warning;
    }

    return MissionStatus::Ready;
}

RiskLevel calculateRiskLevel(const Mission& mission) {
    if (mission.dangerLevel >= 9 || mission.fuelLevel < 20) {
        return RiskLevel::Critical;
    }

    if (mission.dangerLevel >= 7 ||
        mission.fuelLevel < 40 ||
        mission.distance > 7000.0) {
        return RiskLevel::High;
    }

    if (mission.dangerLevel >= 4 ||
        mission.fuelLevel < 70 ||
        mission.distance > 3000.0) {
        return RiskLevel::Medium;
    }

    return RiskLevel::Low;
}

LaunchDecision calculateLaunchDecision(const Mission& mission) {
    MissionStatus status = calculateMissionStatus(mission);
    RiskLevel risk = calculateRiskLevel(mission);

    if (status == MissionStatus::Blocked || risk == RiskLevel::Critical) {
        return LaunchDecision::Cancel;
    }

    if (status == MissionStatus::Warning || risk == RiskLevel::High) {
        return LaunchDecision::Delay;
    }

    return LaunchDecision::Launch;
}

std::string missionStatusToString(MissionStatus status) {
    if (status == MissionStatus::Ready) {
        return "READY";
    }

    if (status == MissionStatus::Warning) {
        return "WARNING";
    }

    return "BLOCKED";
}

std::string riskLevelToString(RiskLevel risk) {
    if (risk == RiskLevel::Low) {
        return "LOW";
    }

    if (risk == RiskLevel::Medium) {
        return "MEDIUM";
    }

    if (risk == RiskLevel::High) {
        return "HIGH";
    }

    return "CRITICAL";
}

std::string launchDecisionToString(LaunchDecision decision) {
    if (decision == LaunchDecision::Launch) {
        return "LAUNCH";
    }

    if (decision == LaunchDecision::Delay) {
        return "DELAY";
    }

    return "CANCEL";
}

int calculateRiskScore(const Mission& mission) {
    int score = mission.dangerLevel * 10;

    if (mission.fuelLevel < 30) {
        score += 30;
    } else if (mission.fuelLevel < 50) {
        score += 15;
    }

    if (mission.distance > 7000.0) {
        score += 20;
    } else if (mission.distance > 5000.0) {
        score += 10;
    }

    if (!mission.hasShield) {
        score += 10;
    }

    if (mission.crewCount < 2) {
        score += 20;
    }

    return score;
}

int countLaunchMissions(const std::vector<Mission>& missions) {
    int count = 0;

    for (const Mission& mission : missions) {
        if (calculateLaunchDecision(mission) == LaunchDecision::Launch) {
            count++;
        }
    }

    return count;
}

int countDelayMissions(const std::vector<Mission>& missions) {
    int count = 0;

    for (const Mission& mission : missions) {
        if (calculateLaunchDecision(mission) == LaunchDecision::Delay) {
            count++;
        }
    }

    return count;
}

int countCancelMissions(const std::vector<Mission>& missions) {
    int count = 0;

    for (const Mission& mission : missions) {
        if (calculateLaunchDecision(mission) == LaunchDecision::Cancel) {
            count++;
        }
    }

    return count;
}

int findHighestRiskMissionIndex(const std::vector<Mission>& missions) {
    if (missions.size() == 0) {
        return -1;
    }

    int bestIndex = 0;
    int bestScore = calculateRiskScore(missions[0]);

    for (int i = 1; i < missions.size(); i++) {
        int score = calculateRiskScore(missions[i]);

        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }

    return bestIndex;
}

void printMissionReport(const std::vector<Mission>& missions) {
    std::cout << std::endl;
    std::cout << "===== Mission Report =====" << std::endl;

    for (int i = 0; i < missions.size(); i++) {
        const Mission& mission = missions[i];

        MissionStatus status = calculateMissionStatus(mission);
        RiskLevel risk = calculateRiskLevel(mission);
        LaunchDecision decision = calculateLaunchDecision(mission);

        std::cout << "Mission " << i + 1
                  << " | Name: " << mission.name
                  << " | Distance: " << mission.distance
                  << " | Fuel: " << mission.fuelLevel
                  << " | Crew: " << mission.crewCount
                  << " | Danger: " << mission.dangerLevel
                  << " | Shield: " << (mission.hasShield ? "Yes" : "No")
                  << " | Status: " << missionStatusToString(status)
                  << " | Risk: " << riskLevelToString(risk)
                  << " | Decision: " << launchDecisionToString(decision)
                  << " | Risk score: " << calculateRiskScore(mission)
                  << std::endl;
    }
}

int main() {
    std::cout << "===== Space Mission Risk Analyzer =====" << std::endl;

    std::cout << "Commander name: ";
    std::string commanderName;
    std::cin >> commanderName;

    int missionCount = readIntInRange("Number of missions (1-10): ", 1, 10);

    std::vector<Mission> missions;

    for (int i = 1; i <= missionCount; i++) {
        Mission mission = readMission(i);
        missions.push_back(mission);

        MissionStatus status = calculateMissionStatus(mission);
        RiskLevel risk = calculateRiskLevel(mission);
        LaunchDecision decision = calculateLaunchDecision(mission);

        std::cout << "Status: " << missionStatusToString(status) << std::endl;
        std::cout << "Risk: " << riskLevelToString(risk) << std::endl;
        std::cout << "Decision: " << launchDecisionToString(decision) << std::endl;
        std::cout << "Risk score: " << calculateRiskScore(mission) << std::endl;
    }

    int launchCount = countLaunchMissions(missions);
    int delayCount = countDelayMissions(missions);
    int cancelCount = countCancelMissions(missions);
    int highestRiskIndex = findHighestRiskMissionIndex(missions);

    std::cout << std::endl;
    std::cout << "===== Mission Summary =====" << std::endl;
    std::cout << "Commander: " << commanderName << std::endl;
    std::cout << "Total missions: " << missionCount << std::endl;
    std::cout << "Launch missions: " << launchCount << std::endl;
    std::cout << "Delay missions: " << delayCount << std::endl;
    std::cout << "Cancel missions: " << cancelCount << std::endl;

    if (highestRiskIndex >= 0) {
        Mission mission = missions[highestRiskIndex];

        std::cout << "Highest risk mission: "
                  << mission.name
                  << " with risk score "
                  << calculateRiskScore(mission)
                  << std::endl;
    }

    printMissionReport(missions);

    return 0;
}