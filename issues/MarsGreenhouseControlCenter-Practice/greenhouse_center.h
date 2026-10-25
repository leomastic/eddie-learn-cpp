#pragma once

#include <string>
#include <vector>
#include "greenhouse.h"

class GreenhouseCenter {
public:
    GreenhouseCenter();

    bool addGreenhouse(
        const std::string& id,
        const std::string& name,
        int waterLevel,
        int temperature,
        int humidity
    );

    bool updateGreenhouseEnvironment(
        const std::string& greenhouseId,
        int temperature,
        int humidity
    );

    bool refillGreenhouseWater(
        const std::string& greenhouseId,
        int amount
    );

    bool addPlantBatch(
        const std::string& greenhouseId,
        const std::string& plantBatchId,
        const std::string& plantName,
        int requiredGrowthDays
    );

    bool advanceGreenhouseOneDay(
        const std::string& greenhouseId
    );

    bool harvestPlantBatch(
        const std::string& greenhouseId,
        const std::string& plantBatchId
    );

    bool failPlantBatch(
        const std::string& greenhouseId,
        const std::string& plantBatchId
    );

    bool shutDownGreenhouse(
        const std::string& greenhouseId
    );

    bool restartGreenhouse(
        const std::string& greenhouseId
    );

    bool printGreenhouse(
        const std::string& greenhouseId
    ) const;

    bool printGreenhousePlantBatches(
        const std::string& greenhouseId
    ) const;

    void printAllGreenhouses() const;

    int operationalGreenhouseCount() const;
    int needsWaterGreenhouseCount() const;
    int environmentWarningGreenhouseCount() const;
    int criticalGreenhouseCount() const;
    int offlineGreenhouseCount() const;

    double averageWaterLevel() const;
    double averageTemperature() const;
    double averageHumidity() const;

    int totalPlantBatchCount() const;
    int greenhouseWithMostPlantsIndex() const;

    void printSummary() const;

private:
    int findGreenhouseIndexById(
        const std::string& greenhouseId
    ) const;

    std::vector<Greenhouse> greenhouses_;
};
