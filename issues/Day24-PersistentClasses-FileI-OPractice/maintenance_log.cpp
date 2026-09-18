#include "maintenance_log.h"

void MaintenanceLog::addRecord(const MaintenanceRecord& record) {
    records_.push_back(record);
}

int MaintenanceLog::getRecordCount() const {
    return static_cast<int>(records_.size());
}

const MaintenanceRecord& MaintenanceLog::getRecord(int index) const {
    return records_.at(static_cast<std::size_t>(index));
}

void MaintenanceLog::clear() {
    records_.clear();
}

int MaintenanceLog::countCriticalRecords() const {
    int count = 0;

    for (const MaintenanceRecord& record : records_) {
        if (record.getSeverity() >= 4) {
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
