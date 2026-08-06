#include "greenhouse_center.h"
#include <iostream>
#include <iomanip>

GreenhouseCenter::GreenhouseCenter()
    : greenhouses_{} {
}

int GreenhouseCenter::findGreenhouseIndexById(const std::string& greenhouseId) const {
    for (int index = 0; index < static_cast<int>(greenhouses_.size()); ++index) {
        if (greenhouses_[index].id() == greenhouseId) {
            return index;
        }
    }

    return -1;
}

bool GreenhouseCenter::addGreenhouse(
    const std::string& id,
    const std::string& name,
    int waterLevel,
    int temperature,
    int humidity
) {
    if (id.empty() || name.empty()) {
        return false;
    }

    if (waterLevel < 0 || waterLevel > 100) {
        return false;
    }

    if (temperature < -100 || temperature > 100) {
        return false;
    }

    if (humidity < 0 || humidity > 100) {
        return false;
    }

    if (findGreenhouseIndexById(id) != -1) {
        return false;
    }

    greenhouses_.emplace_back(
        id,
        name,
        waterLevel,
        temperature,
        humidity
    );

    return true;
}

bool GreenhouseCenter::updateGreenhouseEnvironment(
    const std::string& greenhouseId,
    int temperature,
    int humidity
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].updateEnvironment(temperature, humidity);
}

bool GreenhouseCenter::refillGreenhouseWater(
    const std::string& greenhouseId,
    int amount
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].refillWater(amount);
}

bool GreenhouseCenter::addPlantBatch(
    const std::string& greenhouseId,
    const std::string& plantBatchId,
    const std::string& plantName,
    int requiredGrowthDays
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].addPlantBatch(
        plantBatchId,
        plantName,
        requiredGrowthDays
    );
}

bool GreenhouseCenter::advanceGreenhouseOneDay(
    const std::string& greenhouseId
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].advanceOneDay();
}

bool GreenhouseCenter::harvestPlantBatch(
    const std::string& greenhouseId,
    const std::string& plantBatchId
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].harvestPlantBatch(plantBatchId);
}

bool GreenhouseCenter::failPlantBatch(
    const std::string& greenhouseId,
    const std::string& plantBatchId
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].failPlantBatch(plantBatchId);
}

bool GreenhouseCenter::shutDownGreenhouse(
    const std::string& greenhouseId
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].shutDown();
}

bool GreenhouseCenter::restartGreenhouse(
    const std::string& greenhouseId
) {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    return greenhouses_[index].restart();
}

bool GreenhouseCenter::printGreenhouse(
    const std::string& greenhouseId
) const {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    greenhouses_[index].print();
    return true;
}

bool GreenhouseCenter::printGreenhousePlantBatches(
    const std::string& greenhouseId
) const {
    int index = findGreenhouseIndexById(greenhouseId);
    if (index == -1) {
        return false;
    }

    greenhouses_[index].printPlantBatches();
    return true;
}

void GreenhouseCenter::printAllGreenhouses() const {
    if (greenhouses_.empty()) {
        std::cout << "No greenhouses available." << std::endl;
        return;
    }

    for (const auto& greenhouse : greenhouses_) {
        greenhouse.print();
        std::cout << std::endl;
    }
}

int GreenhouseCenter::operationalGreenhouseCount() const {
    int count = 0;
    for (const auto& greenhouse : greenhouses_) {
        if (greenhouse.status() == GreenhouseStatus::Operational) {
            count += 1;
        }
    }
    return count;
}

int GreenhouseCenter::needsWaterGreenhouseCount() const {
    int count = 0;
    for (const auto& greenhouse : greenhouses_) {
        if (greenhouse.status() == GreenhouseStatus::NeedsWater) {
            count += 1;
        }
    }
    return count;
}

int GreenhouseCenter::environmentWarningGreenhouseCount() const {
    int count = 0;
    for (const auto& greenhouse : greenhouses_) {
        if (greenhouse.status() == GreenhouseStatus::EnvironmentWarning) {
            count += 1;
        }
    }
    return count;
}

int GreenhouseCenter::criticalGreenhouseCount() const {
    int count = 0;
    for (const auto& greenhouse : greenhouses_) {
        if (greenhouse.status() == GreenhouseStatus::Critical) {
            count += 1;
        }
    }
    return count;
}

int GreenhouseCenter::offlineGreenhouseCount() const {
    int count = 0;
    for (const auto& greenhouse : greenhouses_) {
        if (greenhouse.status() == GreenhouseStatus::Offline) {
            count += 1;
        }
    }
    return count;
}

double GreenhouseCenter::averageWaterLevel() const {
    if (greenhouses_.empty()) {
        return 0.0;
    }

    double total = 0.0;
    for (const auto& greenhouse : greenhouses_) {
        total += greenhouse.waterLevel();
    }

    return total / greenhouses_.size();
}

double GreenhouseCenter::averageTemperature() const {
    if (greenhouses_.empty()) {
        return 0.0;
    }

    double total = 0.0;
    for (const auto& greenhouse : greenhouses_) {
        total += greenhouse.temperature();
    }

    return total / greenhouses_.size();
}

double GreenhouseCenter::averageHumidity() const {
    if (greenhouses_.empty()) {
        return 0.0;
    }

    double total = 0.0;
    for (const auto& greenhouse : greenhouses_) {
        total += greenhouse.humidity();
    }

    return total / greenhouses_.size();
}

int GreenhouseCenter::totalPlantBatchCount() const {
    int total = 0;
    for (const auto& greenhouse : greenhouses_) {
        total += static_cast<int>(greenhouse.plantBatchCount());
    }
    return total;
}

int GreenhouseCenter::greenhouseWithMostPlantsIndex() const {
    if (greenhouses_.empty()) {
        return -1;
    }

    int bestIndex = 0;
    int bestCount = static_cast<int>(greenhouses_[0].plantBatchCount());

    for (int index = 1; index < static_cast<int>(greenhouses_.size()); ++index) {
        int count = static_cast<int>(greenhouses_[index].plantBatchCount());
        if (count > bestCount) {
            bestCount = count;
            bestIndex = index;
        }
    }

    return bestIndex;
}

void GreenhouseCenter::printSummary() const {
    std::cout << "===== Mars Greenhouse Center Summary =====" << std::endl;
    std::cout << std::endl;

    std::cout << "Total greenhouses: " << static_cast<int>(greenhouses_.size()) << std::endl;
    std::cout << "Operational: " << operationalGreenhouseCount() << std::endl;
    std::cout << "Needs water: " << needsWaterGreenhouseCount() << std::endl;
    std::cout << "Environment warnings: " << environmentWarningGreenhouseCount() << std::endl;
    std::cout << "Critical: " << criticalGreenhouseCount() << std::endl;
    std::cout << "Offline: " << offlineGreenhouseCount() << std::endl;
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Average water level: " << averageWaterLevel() << std::endl;
    std::cout << "Average temperature: " << averageTemperature() << std::endl;
    std::cout << "Average humidity: " << averageHumidity() << std::endl;
    std::cout << std::endl;

    std::cout << "Total plant batches: " << totalPlantBatchCount() << std::endl;
    std::cout << std::endl;

    int bestIndex = greenhouseWithMostPlantsIndex();
    if (bestIndex == -1) {
        std::cout << "Greenhouse with most plant batches: None" << std::endl;
        return;
    }

    std::cout << "Greenhouse with most plant batches:" << std::endl;
    std::cout << greenhouses_[bestIndex].name() << std::endl;
    std::cout << "Plant batchs: " << greenhouses_[bestIndex].plantBatchCount() << std::endl;
}
