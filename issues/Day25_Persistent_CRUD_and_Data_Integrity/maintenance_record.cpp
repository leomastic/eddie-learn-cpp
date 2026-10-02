#include "maintenance_record.h"

MaintenanceRecord::MaintenanceRecord(
    int id,
    const std::string& component,
    const std::string& date,
    int severity,
    const std::string& notes
) : id_(id), component_(component), date_(date), severity_(severity), notes_(notes) {}

int MaintenanceRecord::getId() const {
    return id_;
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

void MaintenanceRecord::setComponent(const std::string& component) {
    component_ = component;
}

void MaintenanceRecord::setDate(const std::string& date) {
    date_ = date;
}

void MaintenanceRecord::setSeverity(int severity) {
    severity_ = severity;
}

void MaintenanceRecord::setNotes(const std::string& notes) {
    notes_ = notes;
}
