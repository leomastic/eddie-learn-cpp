#pragma once

#include <string>

class MaintenanceRecord {
private:
    std::string component_;
    std::string date_;
    int severity_;
    std::string notes_;

public:
    MaintenanceRecord(
        const std::string& component,
        const std::string& date,
        int severity,
        const std::string& notes
    );

    const std::string& getComponent() const;
    const std::string& getDate() const;
    int getSeverity() const;
    const std::string& getNotes() const;
};