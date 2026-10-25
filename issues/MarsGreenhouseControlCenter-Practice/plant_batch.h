#pragma once
#include <string>

enum class PlantStatus {
    Seedling,
    Growing,
    ReadyForHarvest,
    Harvested,
    Failed
};

class PlantBatch {
public:
    PlantBatch(
        std::string id,
        std::string plantName,
        int requiredGrowthDays
    );

    const std::string& id() const;
    const std::string& plantName() const;

    int requiredGrowthDays() const;
    int currentGrowthDays() const;

    PlantStatus status() const;

    bool canGrow() const;
    bool isReadyForHarvest() const;
    bool isHarvested() const;
    bool hasFailed() const;

    bool growOneDay();
    bool harvest();
    bool markFailed();

    static std::string statusToString(PlantStatus status);

    void print() const;

private:
    std::string id_;
    std::string plantName_;

    int requiredGrowthDays_;
    int currentGrowthDays_;

    PlantStatus status_;
};

PlantBatch createPlantBatch();