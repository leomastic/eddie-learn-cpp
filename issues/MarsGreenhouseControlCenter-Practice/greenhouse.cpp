#include "greenhouse.h"
#include "utils.h"
#include <iostream>
#include <utility>
#include <algorithm>

Greenhouse::Greenhouse(
    std::string id,
    std::string name,
    int waterLevel,
    int temperature,
    int humidity
)
    : id_(std::move(id)),
      name_(std::move(name)),
      waterTank_(waterLevel),
      temperature_(std::clamp(temperature, -100, 100)),
      humidity_(std::clamp(humidity, 0, 100)),
      status_(GreenhouseStatus::Operational),
      plantBatches_() {
    updateStatus();
}

const std::string& Greenhouse::id() const {
    return id_;
}

const std::string& Greenhouse::name() const {
    return name_;
}

int Greenhouse::waterLevel() const {
    return waterTank_.level();
}

WaterStatus Greenhouse::waterStatus() const {
    return waterTank_.status();
}

int Greenhouse::temperature() const {
    return temperature_;
}

int Greenhouse::humidity() const {
    return humidity_;
}

GreenhouseStatus Greenhouse::status() const {
    return status_;
}

std::size_t Greenhouse::plantBatchCount() const {
    return plantBatches_.size();
}

bool Greenhouse::isOperational() const {
    return status_ == GreenhouseStatus::Operational;
}

bool Greenhouse::isOffline() const {
    return status_ == GreenhouseStatus::Offline;
}

bool Greenhouse::hasSafeTemperature() const {
    return temperature_ >= 18 && temperature_ <= 30;
}

bool Greenhouse::hasSafeHumidity() const {
    return humidity_ >= 40 && humidity_ <= 75;
}

bool Greenhouse::hasDangerousTemperature() const {
    return temperature_ < 5 || temperature_ > 45;
}

bool Greenhouse::hasDangerousHumidity() const {
    return humidity_ < 15 || humidity_ > 95;
}

void Greenhouse::updateStatus() {
    if(status_ == GreenhouseStatus::Offline) {
        return;
    } else if(waterTank_.isEmpty()) {
        status_ = GreenhouseStatus::Critical;
    } else if(hasDangerousTemperature()) {
        status_ = GreenhouseStatus::Critical;
    } else if(hasDangerousHumidity()) {
        status_ = GreenhouseStatus::Critical;
    } else if(!hasSafeTemperature()) {
        status_ = GreenhouseStatus::EnvironmentWarning;
    } else if(!hasSafeHumidity()) {
        status_ = GreenhouseStatus::EnvironmentWarning;
    } else if(waterTank_.isLow()) {
        status_ = GreenhouseStatus::NeedsWater;
    } else {
        status_ = GreenhouseStatus::Operational;
    }
}

bool Greenhouse::updateEnvironment(int temperature, int humidity) {
    if (status_ == GreenhouseStatus::Offline) {
        return false;
    }

    if (temperature < -100 || temperature > 100) {
        return false;
    }

    if (humidity < 0 || humidity > 100) {
        return false;
    }

    temperature_ = temperature;
    humidity_ = humidity;
    updateStatus();
    return true;
}

bool Greenhouse::refillWater(int amount) {
    if (status_ == GreenhouseStatus::Offline) {
        return false;
    }

    if (amount <= 0) {
        return false;
    }

    waterTank_.refill(amount);
    updateStatus();
    return true;
}

int Greenhouse::findPlantBatchIndexById(const std::string& plantBatchId) const {
    for (int index = 0; index < static_cast<int>(plantBatches_.size()); ++index) {
        if (plantBatches_[index].id() == plantBatchId) {
            return index;
        }
    }

    return -1;
}

int Greenhouse::plantBatchCurrentGrowthDays(const std::string& plantBatchId) const {
    int index = findPlantBatchIndexById(plantBatchId);
    if (index == -1) {
        return -1;
    }

    return plantBatches_[index].currentGrowthDays();
}

bool Greenhouse::addPlantBatch(
    const std::string& id,
    const std::string& plantName,
    int requiredGrowthDays
) {
    if (status_ == GreenhouseStatus::Offline) {
        return false;
    }

    if (id.empty() || plantName.empty() || requiredGrowthDays <= 0) {
        return false;
    }

    if (findPlantBatchIndexById(id) != -1) {
        return false;
    }

    plantBatches_.emplace_back(
        id,
        plantName,
        requiredGrowthDays
    );

    return true;
}

bool Greenhouse::advanceOneDay() {
    if (status_ == GreenhouseStatus::Offline) {
        return false;
    }

    if (status_ == GreenhouseStatus::Critical) {
        return false;
    }

    if (plantBatches_.empty()) {
        return false;
    }

    int activeBatchCount = 0;
    for (const PlantBatch& batch : plantBatches_) {
        if (batch.canGrow()) {
            activeBatchCount += 1;
        }
    }

    if (activeBatchCount == 0) {
        return true;
    }

    int requiredWater = activeBatchCount * 2;
    int currentWater = waterTank_.level();

    if (currentWater < requiredWater) {
        waterTank_.consume(currentWater);
        updateStatus();
        return false;
    }

    for (PlantBatch& batch : plantBatches_) {
        if (batch.canGrow()) {
            batch.growOneDay();
        }
    }

    waterTank_.consume(requiredWater);
    updateStatus();
    return true;
}

bool Greenhouse::harvestPlantBatch(const std::string& plantBatchId) {
    int index = findPlantBatchIndexById(plantBatchId);
    if (index == -1) {
        return false;
    }

    return plantBatches_[index].harvest();
}

bool Greenhouse::failPlantBatch(const std::string& plantBatchId) {
    int index = findPlantBatchIndexById(plantBatchId);
    if (index == -1) {
        return false;
    }

    return plantBatches_[index].markFailed();
}

bool Greenhouse::shutDown() {
    if (status_ == GreenhouseStatus::Offline) {
        return false;
    }

    status_ = GreenhouseStatus::Offline;
    return true;
}

bool Greenhouse::restart() {
    if (status_ != GreenhouseStatus::Offline) {
        return false;
    }

    status_ = GreenhouseStatus::Operational;
    updateStatus();
    return true;
}

std::string Greenhouse::statusToString(GreenhouseStatus status) {
    switch (status) {
        case GreenhouseStatus::Operational:
            return "Operational";

        case GreenhouseStatus::NeedsWater:
            return "Needs Water";

        case GreenhouseStatus::EnvironmentWarning:
            return "Environment Warning";

        case GreenhouseStatus::Critical:
            return "Critical";

        case GreenhouseStatus::Offline:
            return "Offline";

        default:
            return "Unknown";
    }
}

Greenhouse createGreenHouse() {
    std::cout << std::endl;

    std::string id = readNonEmptyWord("Please enter the greenhouse id: ");
    std::string name = readNonEmptyLine("Please enter the greenhouse name: ");
    int waterLevel = readIntInRange("Please enter the initial water level (0 --> 100): ", 0, 100);
    int temperature = readIntInRange("Please enter the initial temperature (-100 --> 100): ", -100, 100);
    int humidity = readIntInRange("Please enter the initial humidity (0 --> 100): ", 0, 100);

    std::cout << std::endl;

    return Greenhouse(id, name, waterLevel, temperature, humidity);
}

void Greenhouse::print() const {
    std::cout << "Greenhouse ID: " << id_ << std::endl;
    std::cout << "Name: " << name_ << std::endl;
    std::cout << "Water level: " << waterTank_.level() << std::endl;
    std::cout << "Water status: " << WaterTank::statusToString(waterTank_.status()) << std::endl;
    std::cout << "Temperature: " << temperature_ << std::endl;
    std::cout << "Humidity: " << humidity_ << std::endl;
    std::cout << "Plant batches: " << plantBatches_.size() << std::endl;
    std::cout << "Status: " << statusToString(status_) << std::endl;
}

void Greenhouse::printPlantBatches() const {
    if (plantBatches_.empty()) {
        std::cout << "No plant batches in this greenhouse." << std::endl;
        return;
    }

    for (const PlantBatch& batch : plantBatches_) {
        batch.print();
    }
}