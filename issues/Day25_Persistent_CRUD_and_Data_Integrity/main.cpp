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
    UpdateRecord,
    DeleteRecord,
    Save,
    Reload,
    ShowCriticalRecords,
    Exit
};

int readPositiveInt(const std::string& prompt) {
    int value = 0;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (value <= 0) {
            std::cout << "Please enter a positive integer." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

int readSeverity(const std::string& prompt) {
    while (true) {
        const int value = readPositiveInt(prompt);

        if (value >= 1 && value <= 5) {
            return value;
        }

        std::cout << "Severity must be between 1 and 5." << std::endl;
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
    while (true) {
        std::cout << "Choose: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid menu selection." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: return MenuChoice::ListRecords;
            case 2: return MenuChoice::AddRecord;
            case 3: return MenuChoice::UpdateRecord;
            case 4: return MenuChoice::DeleteRecord;
            case 5: return MenuChoice::Save;
            case 6: return MenuChoice::Reload;
            case 7: return MenuChoice::ShowCriticalRecords;
            case 8: return MenuChoice::Exit;
            default:
                std::cout << "Please choose a valid menu option." << std::endl;
                break;
        }
    }
}

void printRecord(const MaintenanceRecord& record) {
    std::cout << "ID: " << record.getId() << std::endl;
    std::cout << "Component: " << record.getComponent() << std::endl;
    std::cout << "Date: " << record.getDate() << std::endl;
    std::cout << "Severity: " << record.getSeverity() << std::endl;
    std::cout << "Notes: " << record.getNotes() << std::endl;
}

void printMenu() {
    std::cout << "===== Robot Maintenance Log =====" << std::endl;
    std::cout << std::endl;
    std::cout << "1. List records" << std::endl;
    std::cout << "2. Add record" << std::endl;
    std::cout << "3. Update record" << std::endl;
    std::cout << "4. Delete record" << std::endl;
    std::cout << "5. Save" << std::endl;
    std::cout << "6. Reload" << std::endl;
    std::cout << "7. Show critical records" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << std::endl;
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
                        std::cout << "Record index: " << i << std::endl;
                        printRecord(record);
                        std::cout << std::endl;
                    }
                }
                break;
            }

            case MenuChoice::AddRecord: {
                const std::string component = readRequiredText("Component: ");
                const std::string date = readRequiredText("Date (YYYY-MM-DD): ");
                const int severity = readSeverity("Severity (1-5): ");

                const std::string notes = readRequiredText("Notes: ");
                const int newId = log.addRecord(component, date, severity, notes);
                if (newId == -1) {
                    std::cout << "The record data was invalid and could not be added." << std::endl;
                } else {
                    std::cout << "Record added successfully with ID: " << newId << std::endl;
                }
                break;
            }

            case MenuChoice::UpdateRecord: {
                const int id = readPositiveInt("Record ID to update: ");
                const int index = log.findRecordIndexById(id);
                if (index == -1) {
                    std::cout << "Record ID " << id << " was not found." << std::endl;
                    break;
                }

                const std::string component = readRequiredText("New component: ");
                const std::string date = readRequiredText("New date (YYYY-MM-DD): ");
                const int severity = readSeverity("New severity (1-5): ");
                const std::string notes = readRequiredText("New notes: ");

                if (log.updateRecord(id, component, date, severity, notes)) {
                    std::cout << "Record ID " << id << " updated successfully." << std::endl;
                } else {
                    std::cout << "Failed to update record ID " << id << "." << std::endl;
                }
                break;
            }

            case MenuChoice::DeleteRecord: {
                const int id = readPositiveInt("Record ID to delete: ");
                if (log.deleteRecord(id)) {
                    std::cout << "Record ID " << id << " deleted successfully." << std::endl;
                } else {
                    std::cout << "Record ID " << id << " was not found." << std::endl;
                }
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
                MaintenanceLog savedLog;
                if (loadMaintenanceLog(filename, savedLog)) {
                    log = savedLog;
                    std::cout << "Maintenance log reloaded from " << filename << std::endl;
                } else {
                    std::cout << "Failed to reload maintenance log. Existing records remain unchanged." << std::endl;
                }
                break;
            }

            case MenuChoice::ShowCriticalRecords: {
                std::cout << "=== Critical Maintenance Records ===" << std::endl;
                bool found = false;
                for (int i = 0; i < log.getRecordCount(); ++i) {
                    const MaintenanceRecord& record = log.getRecord(i);
                    if (record.getSeverity() >= 4) {
                        std::cout << "ID: " << record.getId() << std::endl;
                        std::cout << "Component: " << record.getComponent() << std::endl;
                        std::cout << "Severity: " << record.getSeverity() << std::endl;
                        std::cout << "Notes: " << record.getNotes() << std::endl;
                        std::cout << std::endl;
                        found = true;
                    }
                }

                if (!found) {
                    std::cout << "No critical records found." << std::endl;
                }
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