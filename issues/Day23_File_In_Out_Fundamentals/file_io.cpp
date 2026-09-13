#include "file_io.h"

#include <fstream>
#include <string>

bool saveMissions(const std::string& filename, const std::vector<Mission>& missions) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const Mission& m : missions) {
        file << m.getName() << "|" << m.getPriority() << "\n";
    }

    file.close();
    return true;
}

std::vector<Mission> loadMissions(const std::string& filename) {
    std::vector<Mission> missions;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return missions;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::size_t sep = line.find('|');
        if (sep == std::string::npos) continue;

        std::string name = line.substr(0, sep);
        std::string priText = line.substr(sep + 1);
        int pri = std::stoi(priText);

        if (name.empty() || pri < 1 || pri > 5) continue;

        missions.push_back(Mission(name, pri));
    }

    file.close();
    return missions;
}
