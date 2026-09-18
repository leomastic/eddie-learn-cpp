#include "maintenance_file.h"

#include <fstream>
#include <string>

namespace {

bool isPositiveIntegerText(const std::string& text) {
    if (text.empty()) {
        return false;
    }

    for (char ch : text) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }

    return true;
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

    const std::string component = line.substr(0, firstSep);
    const std::string date = line.substr(firstSep + 1, secondSep - firstSep - 1);
    const std::string severityText = line.substr(secondSep + 1, thirdSep - secondSep - 1);
    const std::string notes = line.substr(thirdSep + 1);

    if (component.empty() || date.empty() || notes.empty()) {
        return false;
    }

    if (!isPositiveIntegerText(severityText)) {
        return false;
    }

    const int severity = std::stoi(severityText);
    if (severity < 1 || severity > 5) {
        return false;
    }

    record = MaintenanceRecord(component, date, severity, notes);
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
        file << record.getComponent() << '|'
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

        MaintenanceRecord parsedRecord("", "", 0, "");
        if (!parseLine(line, parsedRecord)) {
            continue;
        }

        loadedLog.addRecord(parsedRecord);
    }

    file.close();

    log.clear();
    for (int i = 0; i < loadedLog.getRecordCount(); ++i) {
        log.addRecord(loadedLog.getRecord(i));
    }

    return true;
}
