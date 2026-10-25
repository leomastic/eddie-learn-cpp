#include "maintenance_record.h"

MaintenanceRecord::MaintenanceRecord(
    const std::string& component,
    const std::string& date,
    int severity,
    const std::string& notes
) : component_(component), date_(date), severity_(severity), notes_(notes) {
    if (component_.empty() || date_.empty() || notes_.empty() || severity_ < 1 || severity_ > 5) {
        component_ = "";
        date_ = "";
        severity_ = 0;
        notes_ = "";
    }
}

const std::string& MaintenanceRecord::getComponent() const {
    return component_;
}

const std::string& MaintenanceRecord::getDate() const {
    return date_;
}

int MaintenanceRecord::getSeverity() const {
    return severity_;
}

const std::string& MaintenanceRecord::getNotes() const {
    return notes_;
}
