#include "maintenance_file.h"
#include "maintenance_log.h"
#include "maintenance_record.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

enum class MenuChoice {
    ListRecords = 1,
    AddRecord,
    Save,
    Reload,
    ShowCriticalRecords,
    Exit
};

int readIntInRange(const std::string& prompt, int minValue, int maxValue) {
    int value = 0;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue << "." << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

std::string readRequiredText(const std::string& prompt) {
    std::string text;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, text);

        if (!text.empty()) {
            return text;
        }

        std::cout << "This field cannot be empty." << std::endl;
    }
}

MenuChoice readMenuChoice() {
    int choice = readIntInRange("Choose: ", 1, 6);

    switch (choice) {
        case 1: return MenuChoice::ListRecords;
        case 2: return MenuChoice::AddRecord;
        case 3: return MenuChoice::Save;
        case 4: return MenuChoice::Reload;
        case 5: return MenuChoice::ShowCriticalRecords;
        default: return MenuChoice::Exit;
    }
}

void printMenu() {
    std::cout << "===== Robot Maintenance Log =====" << std::endl;
    std::cout << std::endl;
    std::cout << "1. List records" << std::endl;
    std::cout << "2. Add record" << std::endl;
    std::cout << "3. Save" << std::endl;
    std::cout << "4. Reload" << std::endl;
    std::cout << "5. Show critical records" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << std::endl;
}

void printRecord(const MaintenanceRecord& record) {
    std::cout << "Component: " << record.getComponent() << std::endl;
    std::cout << "Date: " << record.getDate() << std::endl;
    std::cout << "Severity: " << record.getSeverity() << std::endl;
    std::cout << "Notes: " << record.getNotes() << std::endl;
}

void printCriticalRecords(const MaintenanceLog& log) {
    std::cout << "=== Important Maintenance ===" << std::endl;

    bool found = false;
    for (int i = 0; i < log.getRecordCount(); ++i) {
        const MaintenanceRecord& record = log.getRecord(i);
        if (record.getSeverity() >= 4) {
            std::cout << record.getComponent() << std::endl;
            std::cout << "Severity: " << record.getSeverity() << std::endl;
            std::cout << record.getNotes() << std::endl;
            std::cout << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No critical records found." << std::endl;
    }
}

}  // namespace

int main() {
    const std::string filename = "maintenance.txt";
    MaintenanceLog log;

    std::cout << "Attempting to load maintenance log..." << std::endl;
    if (loadMaintenanceLog(filename, log)) {
        std::cout << "Loaded " << log.getRecordCount() << " records from " << filename << std::endl;
    } else {
        std::cout << "No existing maintenance log found. Starting fresh." << std::endl;
    }

    bool running = true;
    while (running) {
        printMenu();
        const MenuChoice choice = readMenuChoice();

        switch (choice) {
            case MenuChoice::ListRecords: {
                std::cout << "=== Maintenance Records ===" << std::endl;
                if (log.getRecordCount() == 0) {
                    std::cout << "No records in the log." << std::endl;
                } else {
                    for (int i = 0; i < log.getRecordCount(); ++i) {
                        const MaintenanceRecord& record = log.getRecord(i);
                        std::cout << "Record " << (i + 1) << std::endl;
                        printRecord(record);
                        std::cout << std::endl;
                    }
                }
                break;
            }

            case MenuChoice::AddRecord: {
                const std::string component = readRequiredText("Component: ");
                const std::string date = readRequiredText("Date (YYYY-MM-DD): ");
                const int severity = readIntInRange("Severity (1-5): ", 1, 5);
                const std::string notes = readRequiredText("Notes: ");

                MaintenanceRecord record(component, date, severity, notes);
                if (record.getComponent().empty()) {
                    std::cout << "The record data was invalid and could not be added." << std::endl;
                    break;
                }

                log.addRecord(record);
                std::cout << "Record added successfully." << std::endl;
                break;
            }

            case MenuChoice::Save: {
                if (saveMaintenanceLog(filename, log)) {
                    std::cout << "Maintenance log saved successfully to " << filename << std::endl;
                } else {
                    std::cout << "Failed to save maintenance log." << std::endl;
                }
                break;
            }

            case MenuChoice::Reload: {
                MaintenanceLog backup = log;
                if (loadMaintenanceLog(filename, log)) {
                    std::cout << "Maintenance log reloaded from " << filename << std::endl;
                } else {
                    std::cout << "Failed to reload maintenance log. Existing records remain unchanged." << std::endl;
                    log = backup;
                }
                break;
            }

            case MenuChoice::ShowCriticalRecords: {
                printCriticalRecords(log);
                break;
            }

            case MenuChoice::Exit:
                std::cout << "Exiting Robot Maintenance Log." << std::endl;
                running = false;
                break;
        }
    }

    return 0;
}
