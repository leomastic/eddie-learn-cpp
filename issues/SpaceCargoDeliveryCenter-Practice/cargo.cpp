#include "cargo.h"
#include "utils.h"
#include <utility>
#include <iostream>

Cargo::Cargo(
    std::string id,
    std::string description,
    int weight
)
    : id_(std::move(id)),
      description_(std::move(description)),
      weight_(weight > 0 ? weight : 1),
      status_(CargoStatus::Waiting),
      assignedVehicleId_() {
}

const std::string& Cargo::id() const {
    return this->id_;
}

const std::string& Cargo::description() const {
    return this->description_;
}

int Cargo::weight() const {
    return this->weight_;
}

CargoStatus Cargo::status() const {
    return this->status_;
}

const std::string& Cargo::assignedVehicleId() const {
    return this->assignedVehicleId_;
}

bool Cargo::isWaiting() const {
    return status_ == CargoStatus::Waiting;
}

bool Cargo::isLoaded() const {
    return status_ == CargoStatus::Loaded;
}

bool Cargo::isInTransit() const {
    return status_ == CargoStatus::InTransit;
}

bool Cargo::isDelivered() const {
    return status_ == CargoStatus::Delivered;
}

bool Cargo::isCancelled() const {
    return status_ == CargoStatus::Cancelled;
}

bool Cargo::hasVehicleAssignment() const {
    return !assignedVehicleId_.empty();
}

bool Cargo::assignToVehicle(const std::string& vehicleId) {
    if(!vehicleId.empty() && isWaiting() && !hasVehicleAssignment()) {
        assignedVehicleId_ = vehicleId;
        status_ = CargoStatus::Loaded;
        return true;
    }

    return false;
}

bool Cargo::startDelivery() {
    if(isLoaded() && hasVehicleAssignment()) {
        status_ = CargoStatus::InTransit;
        return true;
    }

    return false;
}

bool Cargo::completeDelivery() {
    if(isInTransit()) {
        status_ = CargoStatus::Delivered;
        assignedVehicleId_.clear();
        return true;
    }

    return false;
}

bool Cargo::cancelDelivery() {
    if(isWaiting() || isLoaded()) {
        status_ = CargoStatus::Cancelled;
        assignedVehicleId_.clear();
        return true;
    }

    return false;
}

bool Cargo::removeVehicleAssignment() {
    if(isLoaded() && hasVehicleAssignment()) {
        assignedVehicleId_.clear();
        status_ = CargoStatus::Waiting;
        return true;
    }

    return false;
}

std::string Cargo::statusToString(CargoStatus status) {
    switch(status) {
        case CargoStatus::Waiting:
            return "Waiting";

        case CargoStatus::Loaded:
            return "Loaded";

        case CargoStatus::InTransit:
            return "In Transit";

        case CargoStatus::Delivered:
            return "Delivered";

        case CargoStatus::Cancelled:
            return "Cancelled";

        default:
            return "Unknown";
    }
}

Cargo createCargo() {
    std::cout << std::endl;

    std::string id = readNonEmptyWord("Please enter the cargo id: ");
    std::string description = readNonEmptyLine("Please enter the cargo description: ");
    int weight = readIntInRange("Please enter the cargo weight (1 --> 1000): ", 1, 1000);

    std::cout << std::endl;

    return Cargo(id, description, weight);
}

void Cargo::print() const {
    std::cout << "Cargo status:" << std::endl;

    std::cout << "Cargo ID: " << this->id_ << std::endl;
    std::cout << "Description: " << this->description_ << std::endl;
    std::cout << "Weight: " << this->weight_ << std::endl;
    std::cout << "Status: " << statusToString(this->status_) << std::endl;
    if(!assignedVehicleId_.empty()) {
        std::cout << "Assigned vehicle ID: " << this->assignedVehicleId_ << std::endl;
    } else {
        std::cout << "Assigned vehicle ID: None" << std::endl;
    }
}