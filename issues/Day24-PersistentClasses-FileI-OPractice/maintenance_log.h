#pragma once

#include "maintenance_record.h"

#include <vector>

class MaintenanceLog {
private:
    std::vector<MaintenanceRecord> records_;

public:
    void addRecord(const MaintenanceRecord& record);

    int getRecordCount() const;

    const MaintenanceRecord& getRecord(int index) const;

    void clear();

    int countCriticalRecords() const;

    int findHighestSeverityIndex() const;
};
