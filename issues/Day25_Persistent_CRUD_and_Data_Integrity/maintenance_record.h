#pragma once

#include <string>

class MaintenanceRecord {
private:
    int id_;
    std::string component_;
    std::string date_;
    int severity_;
    std::string notes_;

public:
    MaintenanceRecord(
        int id = 0,
        const std::string& component = "",
        const std::string& date = "",
        int severity = 0,
        const std::string& notes = ""
    );

    int getId() const;
    const std::string& getComponent() const;
    const std::string& getDate() const;
    int getSeverity() const;
    const std::string& getNotes() const;

    void setComponent(const std::string& component);
    void setDate(const std::string& date);
    void setSeverity(int severity);
    void setNotes(const std::string& notes);
};