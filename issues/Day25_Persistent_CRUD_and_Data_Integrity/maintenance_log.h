#pragma once

#include "maintenance_record.h"

#include <vector>

class MaintenanceLog {
private:
    std::vector<MaintenanceRecord> records_;
    int nextId_;

public:
    MaintenanceLog();

    int addRecord(
        const std::string& component,
        const std::string& date,
        int severity,
        const std::string& notes
    );

    bool addLoadedRecord(const MaintenanceRecord& record);

    int getRecordCount() const;
    const MaintenanceRecord& getRecord(int index) const;

    int findRecordIndexById(int id) const;

    bool updateRecord(
        int id,
        const std::string& component,
        const std::string& date,
        int severity,
        const std::string& notes
    );

    bool deleteRecord(int id);

    void clear();

    int countCriticalRecords() const;
    int findHighestSeverityIndex() const;
};