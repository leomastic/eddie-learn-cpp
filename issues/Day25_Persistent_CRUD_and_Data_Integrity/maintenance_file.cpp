#include "maintenance_file.h"

#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <string>

namespace {

bool parseLongLong(const std::string& text, long long& value) {
    if (text.empty()) {
        return false;
    }

    for (char ch : text) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }

    errno = 0;
    char* end = nullptr;
    const long long parsed = std::strtoll(text.c_str(), &end, 10);
    if (errno == ERANGE || end == nullptr || *end != '\0') {
        return false;
    }

    if (parsed < 1 || parsed > std::numeric_limits<int>::max()) {
        return false;
    }

    value = parsed;
    return true;
}

bool isValidSeverityText(const std::string& text) {
    if (text.empty()) {
        return false;
    }

    for (char ch : text) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }

    long long parsed = 0;
    if (!parseLongLong(text, parsed)) {
        return false;
    }

    return parsed >= 1 && parsed <= 5;
}

bool parseLine(const std::string& line, MaintenanceRecord& record) {
    const std::size_t firstSep = line.find('|');
    if (firstSep == std::string::npos) {
        return false;
    }

    const std::size_t secondSep = line.find('|', firstSep + 1);
    if (secondSep == std::string::npos) {
        return false;
    }

    const std::size_t thirdSep = line.find('|', secondSep + 1);
    if (thirdSep == std::string::npos) {
        return false;
    }

    const std::size_t fourthSep = line.find('|', thirdSep + 1);
    if (fourthSep == std::string::npos) {
        return false;
    }

    const std::string idText = line.substr(0, firstSep);
    const std::string component = line.substr(firstSep + 1, secondSep - firstSep - 1);
    const std::string date = line.substr(secondSep + 1, thirdSep - secondSep - 1);
    const std::string severityText = line.substr(thirdSep + 1, fourthSep - thirdSep - 1);
    const std::string notes = line.substr(fourthSep + 1);

    if (idText.empty() || component.empty() || date.empty() || severityText.empty() || notes.empty()) {
        return false;
    }

    if (component.find('|') != std::string::npos || date.find('|') != std::string::npos || severityText.find('|') != std::string::npos) {
        return false;
    }

    long long idValue = 0;
    if (!parseLongLong(idText, idValue)) {
        return false;
    }

    if (!isValidSeverityText(severityText)) {
        return false;
    }

    const int severity = static_cast<int>(std::strtol(severityText.c_str(), nullptr, 10));
    record = MaintenanceRecord(static_cast<int>(idValue), component, date, severity, notes);
    return true;
}

}  // namespace

bool saveMaintenanceLog(const std::string& filename, const MaintenanceLog& log) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < log.getRecordCount(); ++i) {
        const MaintenanceRecord& record = log.getRecord(i);
        file << record.getId() << '|'
             << record.getComponent() << '|'
             << record.getDate() << '|'
             << record.getSeverity() << '|'
             << record.getNotes() << '\n';
    }

    file.close();
    return true;
}

bool loadMaintenanceLog(const std::string& filename, MaintenanceLog& log) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    MaintenanceLog loadedLog;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        MaintenanceRecord parsedRecord(0, "", "", 0, "");
        if (!parseLine(line, parsedRecord)) {
            continue;
        }

        loadedLog.addLoadedRecord(parsedRecord);
    }

    file.close();

    log = loadedLog;
    return true;
}
