#include <iostream>
#include <string>
#include <cmath>
#include <vector>

enum class PlanetClass {
    Habitable,
    Research,
    Dangerous
};

enum class MissionDecision {
    Visit,
    Study,
    Avoid
};

enum class Weather {

    Sunny,

    Cloudy,

    Storm,

    Frozen

};

Weather readWeather();

struct Planet {
    std::string name;

    double temperature;
    double gravity;

    int oxygenLevel;
    int waterLevel;

    bool hasLife;
    Weather weather;
};

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while(true) {
        std::cout << prompt << std::endl;

        if(!(std::cin >> value)) {
            std::cout << "Invaild value. Please enter a valid value.";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if(value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue
                                                                        << " and " << maxValue
                                                                        << std::endl;
            continue;
        }

        return value;
    }
}

double readDoubleInRange(std::string prompt, double minValue, double maxValue) {
    double value;

    while(true) {
        std::cout << prompt << std::endl;

        if(!(std::cin >> value)) {
            std::cout << "Invaild value. Please enter a valid value.";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if(value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue
                                                                        << " and " << maxValue
                                                                        << std::endl;
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

Planet readPlanet(int index) {
    Planet planet;

    std::cout << std::endl;
    std::cout << "Planet " << index << std::endl;

    std::cout << "Planet name (no space): ";
    std::cin >> planet.name;

    planet.gravity = readDoubleInRange("Planet gravity Level (0.0 --> 100.0): ", 0.0, 100.0);
    planet.oxygenLevel = (int)readDoubleInRange("Planet oxygen level (0.0 --> 100.0): ", 0.0, 100.0);
    planet.temperature = readDoubleInRange("Planet temperature (|-273.0| --> 100000000.0): ", -273.0, 100000000.0);
    planet.waterLevel = (int)readDoubleInRange("Planet water level (1 --> 100): ", 1, 100);
    planet.hasLife = readYesNo("Planet has life? ");
    planet.weather = readWeather();

    return planet;
}

PlanetClass calculatePlanetClass(const Planet& planet) {
    if (planet.oxygenLevel >= 70 ||
        planet.waterLevel >= 60 ||
        (planet.gravity >= 0.8 && planet.gravity <= 1.2) ||
        (planet.temperature >= -20 && planet.temperature <= 40)
    ) {
        return PlanetClass::Habitable;
    }

    if (planet.oxygenLevel >= 30 ||
        planet.waterLevel >= 20
    ) {
        return PlanetClass::Research;
    }

    return PlanetClass::Dangerous;
}

MissionDecision calculateMissionDecision(const Planet& planet) {
    if(calculatePlanetClass(planet) == PlanetClass::Habitable && planet.hasLife) {
        return MissionDecision::Visit;
    }

    if(calculatePlanetClass(planet) == PlanetClass::Habitable && (!(planet.hasLife))) {
        return MissionDecision::Study;
    }

    if(calculatePlanetClass(planet) == PlanetClass::Research) {
        return MissionDecision::Study;
    }

    return MissionDecision::Avoid;
}

Weather readWeather() {
    int choice;

    while (true) {
        std::cout << "Weather (1 = Sunny, 2 = Cloudy, 3 = Storm, 4 = Frozen): ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number from 1 to 4." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            return Weather::Sunny;
        }

        if (choice == 2) {
            return Weather::Cloudy;
        }

        if (choice == 3) {
            return Weather::Storm;
        }

        if (choice == 4) {
            return Weather::Frozen;
        }

        std::cout << "Please enter 1, 2, 3 or 4." << std::endl;
    }
}

std::string planetClassToString(PlanetClass planetClass) {
    if(planetClass == PlanetClass::Habitable) {
        return "Habitable";
    }

    if(planetClass == PlanetClass::Research) {
        return "Research";
    }

    return "Dangerous";
}

std::string missionDecisionToString(MissionDecision decision) {
    if(decision == MissionDecision::Visit) {
        return "Visit";
    }

    if(decision == MissionDecision::Study) {
        return "Study";
    }

    return "Avoid";
}

std::string weatherToString(Weather weather) {
    if (weather == Weather::Sunny) {
        return "Sunny";
    }

    if (weather == Weather::Cloudy) {
        return "Cloudy";
    }

    if (weather == Weather::Storm) {
        return "Storm";
    }

    return "Frozen";
}

int countHabitable(const std::vector<Planet>& planets) {
    int count = 0;

    for (const Planet& planet : planets) {
        if (calculatePlanetClass(planet) == PlanetClass::Habitable) {
            ++count;
        }
    }

    return count;
}

int countResearch(const std::vector<Planet>& planets) {
    int count = 0;

    for (const Planet& planet : planets) {
        if (calculatePlanetClass(planet) == PlanetClass::Research) {
            ++count;
        }
    }

    return count;
}

int countDangerous(const std::vector<Planet>& planets) {
    int count = 0;

    for (const Planet& planet : planets) {
        if (calculatePlanetClass(planet) == PlanetClass::Dangerous) {
            ++count;
        }
    }

    return count;
}

int countVisit(const std::vector<Planet>& planets) {
    int count = 0;

    for (const Planet& planet : planets) {
        if (calculateMissionDecision(planet) == MissionDecision::Visit) {
            ++count;
        }
    }

    return count;
}

int countStudy(const std::vector<Planet>& planets) {
    int count = 0;

    for (const Planet& planet : planets) {
        if (calculateMissionDecision(planet) == MissionDecision::Study) {
            ++count;
        }
    }

    return count;
}

int countAvoid(const std::vector<Planet>& planets) {
    int count = 0;

    for (const Planet& planet : planets) {
        if (calculateMissionDecision(planet) == MissionDecision::Avoid) {
            ++count;
        }
    }

    return count;
}

int calculatePlanetScore(const Planet& planet) {
    int score = planet.oxygenLevel + planet.waterLevel;
    score += std::max(0, 100 - (int)std::abs(planet.temperature));
    score += std::max(0, 100 - (int)(std::abs(planet.gravity - 1.0) * 50));
    return score;
}

int findBestPlanetIndex(const std::vector<Planet>& planets) {
    int bestIndex = -1;
    int bestScore = 0;

    for (int i = 0; i < planets.size(); i++) {
        if (calculateMissionDecision(planets[i]) == MissionDecision::Visit) {
            int score = calculatePlanetScore(planets[i]);

            if(bestIndex == -1 || score > bestScore) {
                bestIndex = i;
                bestScore = score;
            }
        }
    }

    return bestIndex;
}

void printReport(const std::vector<Planet>& planets) {
    std::cout << "\n===== Planet Report =====" << std::endl;
    std::cout << "Total planet: " << planets.size() << std::endl;

    for (int i = 0; i < planets.size(); ++i) {
        const Planet& planet = planets[i];
        std::cout << "\nPlanet " << (i + 1) << ": " << planet.name << " | ";
        std::cout << "Temperature: " << planet.temperature << " | ";
        std::cout << "Gravity: " << planet.gravity << " | ";
        std::cout << "Oxygen: " << planet.oxygenLevel << " | ";
        std::cout << "Water: " << planet.waterLevel << "% | ";
        std::cout << "Life: " << (planet.hasLife ? "Yes" : "No") << " | ";
        std::cout << "Weather: " << weatherToString(planet.weather) << " | ";
        std::cout << "Class: " << planetClassToString(calculatePlanetClass(planet)) << " | ";
        std::cout << "Decision: " << missionDecisionToString(calculateMissionDecision(planet)) << " | ";
        std::cout << "Score: " << calculatePlanetScore(planet) << " | ";
    }

    std::cout << "\n===== Review Planet Report =====" << std::endl;
    std::cout << "Habitable planets: " << countHabitable(planets) << std::endl;
    std::cout << "Research planets: " << countResearch(planets) << std::endl;
    std::cout << "Dangerous planets: " << countDangerous(planets) << std::endl;
    std::cout << "Visit: " << countVisit(planets) << std::endl;
    std::cout << "Study: " << countStudy(planets) << std::endl;
    std::cout << "Avoid: " << countAvoid(planets) << std::endl;
    std::cout << "Best planet: " << findBestPlanetIndex(planets) << std::endl;
}

int main() {
    int numPlanets = readIntInRange("Enter number of planets: ", 1, 100);
    std::vector<Planet> planets;

    for (int i = 1; i <= numPlanets; ++i) {
        Planet planet = readPlanet(i);
        planets.push_back(planet);
    }

    printReport(planets);

    return 0;
}