#pragma once
#include <string>
#include <vector>
#include "water_tank.h"
#include "plant_batch.h"

enum class GreenhouseStatus {
    Operational,
    NeedsWater,
    EnvironmentWarning,
    Critical,
    Offline
};

class Greenhouse {
public:
    Greenhouse(
        std::string id,
        std::string name,
        int waterLevel,
        int temperature,
        int humidity
    );

    const std::string& id() const;
    const std::string& name() const;

    int waterLevel() const;
    WaterStatus waterStatus() const;

    int temperature() const;
    int humidity() const;

    GreenhouseStatus status() const;

    std::size_t plantBatchCount() const;
    int plantBatchCurrentGrowthDays(const std::string& plantBatchId) const;

    bool isOperational() const;
    bool isOffline() const;

    bool hasSafeTemperature() const;
    bool hasSafeHumidity() const;

    bool hasDangerousTemperature() const;
    bool hasDangerousHumidity() const;

    void updateStatus();
    bool updateEnvironment(int temperature, int humidity);
    bool refillWater(int amount);
    bool addPlantBatch(
        const std::string& id,
        const std::string& plantName,
        int requiredGrowthDays
    );
    bool advanceOneDay();
    bool harvestPlantBatch(
        const std::string& plantBatchId
    );
    bool failPlantBatch(
        const std::string& plantBatchId
    );
    bool shutDown();
    bool restart();
    void print() const;
    void printPlantBatches() const;
    static std::string statusToString(
        GreenhouseStatus status
    );

private:
    int findPlantBatchIndexById(const std::string& plantBatchId) const;
    std::string id_;
    std::string name_;

    WaterTank waterTank_;

    int temperature_;
    int humidity_;

    GreenhouseStatus status_;

    std::vector<PlantBatch> plantBatches_;
};

Greenhouse createGreenHouse();