#include "maintenance_log.h"

namespace {

bool isValidRecordValue(
    const std::string& component,
    const std::string& date,
    int severity,
    const std::string& notes
) {
    return !component.empty() && !date.empty() && !notes.empty() && severity >= 1 && severity <= 5;
}

}  // namespace

MaintenanceLog::MaintenanceLog() : nextId_(1) {}

int MaintenanceLog::addRecord(
    const std::string& component,
    const std::string& date,
    int severity,
    const std::string& notes
) {
    if (!isValidRecordValue(component, date, severity, notes)) {
        return -1;
    }

    const int id = nextId_;
    records_.push_back(MaintenanceRecord(id, component, date, severity, notes));
    ++nextId_;
    return id;
}

void MaintenanceLog::addLoadedRecord(const MaintenanceRecord& record) {
    records_.push_back(record);

    if (record.getId() >= nextId_) {
        nextId_ = record.getId() + 1;
    }
}

int MaintenanceLog::getRecordCount() const {
    return static_cast<int>(records_.size());
}

const MaintenanceRecord& MaintenanceLog::getRecord(int index) const {
    return records_.at(static_cast<std::size_t>(index));
}

int MaintenanceLog::findRecordIndexById(int id) const {
    for (int i = 0; i < getRecordCount(); ++i) {
        if (records_[i].getId() == id) {
            return i;
        }
    }

    return -1;
}

bool MaintenanceLog::updateRecord(
    int id,
    const std::string& component,
    const std::string& date,
    int severity,
    const std::string& notes
) {
    if (!isValidRecordValue(component, date, severity, notes)) {
        return false;
    }

    const int index = findRecordIndexById(id);
    if (index == -1) {
        return false;
    }

    records_[index].setComponent(component);
    records_[index].setDate(date);
    records_[index].setSeverity(severity);
    records_[index].setNotes(notes);
    return true;
}

bool MaintenanceLog::deleteRecord(int id) {
    const int index = findRecordIndexById(id);
    if (index == -1) {
        return false;
    }

    for (int i = index; i < getRecordCount() - 1; ++i) {
        records_[i] = records_[i + 1];
    }

    records_.pop_back();
    return true;
}

void MaintenanceLog::clear() {
    records_.clear();
    nextId_ = 1;
}

int MaintenanceLog::countCriticalRecords() const {
    int count = 0;

    for (int i = 0; i < getRecordCount(); ++i) {
        if (records_[i].getSeverity() >= 4) {
            ++count;
        }
    }

    return count;
}

int MaintenanceLog::findHighestSeverityIndex() const {
    if (records_.empty()) {
        return -1;
    }

    int highestIndex = 0;
    int highestSeverity = records_[0].getSeverity();

    for (std::size_t i = 1; i < records_.size(); ++i) {
        if (records_[i].getSeverity() > highestSeverity) {
            highestSeverity = records_[i].getSeverity();
            highestIndex = static_cast<int>(i);
        }
    }

    return highestIndex;
}

