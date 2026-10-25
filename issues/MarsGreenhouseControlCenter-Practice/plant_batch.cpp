#include "plant_batch.h"
#include "utils.h"
#include <utility>
#include <iostream>

PlantBatch::PlantBatch(
    std::string id,
    std::string plantName,
    int requiredGrowthDays
)
    : id_(std::move(id)),
      plantName_(std::move(plantName)),
      requiredGrowthDays_(
          requiredGrowthDays > 0
              ? requiredGrowthDays
              : 1
      ),
      currentGrowthDays_(0),
      status_(PlantStatus::Seedling) {
}

const std::string& PlantBatch::id() const {
    return id_;
}

const std::string& PlantBatch::plantName() const {
    return plantName_;
}

int PlantBatch::requiredGrowthDays() const {
    return requiredGrowthDays_;
}

int PlantBatch::currentGrowthDays() const {
    return currentGrowthDays_;
}

PlantStatus PlantBatch::status() const {
    return status_;
}

bool PlantBatch::canGrow() const {
    if(status_ == PlantStatus::Seedling || status_ == PlantStatus::Growing) {
        return true;
    }

    return false;
}

bool PlantBatch::isReadyForHarvest() const {
    if(status_ == PlantStatus::ReadyForHarvest) {
        return true;
    }

    return false;
}

bool PlantBatch::isHarvested() const {
    if(status_ == PlantStatus::Harvested) {
        return true;
    }

    return false;
}

bool PlantBatch::hasFailed() const {
    if(status_ == PlantStatus::Failed) {
        return true;
    }

    return false;
}

bool PlantBatch::growOneDay() {
    if(canGrow()) {
        currentGrowthDays_ += 1;

        if(currentGrowthDays_ == requiredGrowthDays_) {
            status_ = PlantStatus::ReadyForHarvest;
        } else {
            status_ = PlantStatus::Growing;
        }

        return true;
    }

    return false;
}

bool PlantBatch::harvest() {
    if(isReadyForHarvest()) {
        status_ = PlantStatus::Harvested;
        return true;
    }

    return false;
}

bool PlantBatch::markFailed() {
    if(status_ == PlantStatus::Harvested || status_ == PlantStatus::Failed) {
        return false;
    }

    status_ = PlantStatus::Failed;
    return true;
}

std::string PlantBatch::statusToString(PlantStatus status) {
    switch(status) {
        case PlantStatus::Failed:
            return "Failed";

        case PlantStatus::Growing:
            return "Growing";

        case PlantStatus::Harvested:
            return "Harvested";

        case PlantStatus::ReadyForHarvest:
            return "Ready For Harvest";

        case PlantStatus::Seedling:
            return "Seedling";

        default:
            return "Unknown";
    }
}

PlantBatch createPlantBatch() {
    std::cout << std::endl;

    std::string id = readNonEmptyWord("Please enter the plant batch id: ");
    std::string plantName = readNonEmptyLine("Please enter the plant name: ");
    int requiredGrowthDays = readIntInRange("Please enter the required growth days (1 --> 100000): ", 1, 100000);

    std::cout << std::endl;

    return PlantBatch(id, plantName, requiredGrowthDays);
}

void PlantBatch::print() const {
    std::cout << "Plant batch status:" << std::endl;

    std::cout << "Plant batch ID: " << this->id_ << std::endl;
    std::cout << "Plant name: " << this->plantName_ << std::endl;
    std::cout << "Growth days: " << this->currentGrowthDays_ << std::endl;
    std::cout << "Required growth days: " << this->requiredGrowthDays_ << std::endl;
    std::cout << "Status: " << statusToString(this->status_) << std::endl;
}