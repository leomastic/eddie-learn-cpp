#include "vehicle.h"
#include "utils.h"
#include <utility>
#include <iostream>

Vehicle::Vehicle(
    std::string id,
    std::string name,
    int fuelLevel,
    int maximumCargoWeight
)
    : id_(std::move(id)),
      name_(std::move(name)),
      fuelTank_(fuelLevel),
      maximumCargoWeight_(
          maximumCargoWeight > 0
              ? maximumCargoWeight
              : 1
      ),
      assignedCargoId_(),
      assignedCargoWeight_(0),
      status_(VehicleStatus::Available) {
    updateStatus();
}

const std::string& Vehicle::id() const {
    return id_;
}

const std::string& Vehicle::name() const {
    return name_;
}

int Vehicle::fuelLevel() const {
    return fuelTank_.level();
}

FuelStatus Vehicle::fuelStatus() const {
    return fuelTank_.status();
}

int Vehicle::maximumCargoWeight() const {
    return maximumCargoWeight_;
}

const std::string& Vehicle::assignedCargoId() const {
    return assignedCargoId_;
}

int Vehicle::assignedCargoWeight() const {
    return assignedCargoWeight_;
}

VehicleStatus Vehicle::status() const {
    return status_;
}

bool Vehicle::isAvailable() const {
    return status_ == VehicleStatus::Available;
}

bool Vehicle::hasCargo() const {
    return !assignedCargoId_.empty();
}

bool Vehicle::canAcceptCargo(int cargoWeight) const {
    if(isAvailable() && !hasCargo() && cargoWeight > 0 && cargoWeight <= maximumCargoWeight_ && !fuelTank_.isEmpty()) {
        return true;
    }

    return false;
}

bool Vehicle::isInTransit() const {
    return status_ == VehicleStatus::InTransit;
}

bool Vehicle::isRefueling() const {
    return status_ == VehicleStatus::Refueling;
}

void Vehicle::updateStatus() {
    if(isInTransit() || isRefueling()) {
        return;
    } else if(fuelTank_.isEmpty()) {
        status_ = VehicleStatus::OutOfService;
    } else if(hasCargo()) {
        status_ = VehicleStatus::Loaded;
    } else {
        status_ = VehicleStatus::Available;
    }
}

bool Vehicle::loadCargo(const std::string& cargoId, int cargoWeight) {
    if(!cargoId.empty() && canAcceptCargo(cargoWeight)) {
        assignedCargoId_ = cargoId;
        assignedCargoWeight_ = cargoWeight;
        updateStatus();
        return true;
    }

    return false;
}

bool Vehicle::unloadCargo() {
    if(status_ == VehicleStatus::Loaded && hasCargo()) {
        assignedCargoId_.clear();
        assignedCargoWeight_ = 0;
        updateStatus();
        return true;
    }

    return false;
}

bool Vehicle::startDelivery() {
    if(status_ == VehicleStatus::Loaded && hasCargo() && !fuelTank_.isLow() && !fuelTank_.isEmpty()) {
        status_ = VehicleStatus::InTransit;
        return true;
    }

    return false;
}

bool Vehicle::travel(int fuelAmount) {
    if(isInTransit() && fuelAmount > 0) {
        fuelTank_.consume(fuelAmount);
        if(fuelTank_.isEmpty()) {
            status_ = VehicleStatus::OutOfService;
        }
        return true;
    }

    return false;
}

bool Vehicle::completeDelivery() {
    if(isInTransit() && hasCargo() && !fuelTank_.isEmpty()) {
        assignedCargoId_.clear();
        assignedCargoWeight_ = 0;
        status_ = VehicleStatus::Available;
        updateStatus();
        return true;
    }

    return false;
}

bool Vehicle::startRefueling() {
    if(!isInTransit() && !isRefueling() && !fuelTank_.isFull()
        && status_ == VehicleStatus::OutOfService) {
        status_ = VehicleStatus::Refueling;
        return true;
    }

    return false;
}

bool Vehicle::refuel(int amount) {
    if(status_ == VehicleStatus::Refueling && amount > 0) {
        fuelTank_.refuel(amount);
        if(fuelLevel() == 100) {
            status_ = VehicleStatus::Available;
            updateStatus();
            return true;
        }
        return true;
    }
    return false;
}

bool Vehicle::stopRefueling() {
    if(status_ == VehicleStatus::Refueling) {
        status_ = VehicleStatus::Available;
        updateStatus();
        return true;
    }

    return false;
}

std::string Vehicle::statusToString(VehicleStatus status) {
    switch(status) {
        case VehicleStatus::Available:
            return "Availible";

        case VehicleStatus::InTransit:
            return "In Transit";

        case VehicleStatus::Loaded:
            return "Loaded";

        case VehicleStatus::OutOfService:
            return "Out Of Service";

        case VehicleStatus::Refueling:
            return "Refueling";

        default:
            return "Unknown";
    }
}

Vehicle createVehicle() {
    std::cout << std::endl;

    std::string id = readNonEmptyWord("Please enter the vehicle ID: ");
    std::string name = readNonEmptyWord("Please enter the vehicle name: ");
    int fuelLvl = readIntInRange("Please enter the fuel level (1 --> 100): ", 1, 100);
    int maximumCargoWeight = readIntInRange("Please enter the maximum cargo weight (1 --> 10000): ", 1, 10000);

    std::cout << std::endl;

    return Vehicle(id, name, fuelLvl, maximumCargoWeight);
}

void Vehicle::print() const {
    std::cout << "Vehicle status:" << std::endl;

    std::cout << "Vehicle ID: " << id_ << std::endl;
    std::cout << "Vehicle name: " << name_ << std::endl;
    std::cout << "Fuel level: " << fuelLevel() << std::endl;
    std::cout << "Fuel status: " << fuelTank_.statusToString(fuelStatus()) << std::endl;
    std::cout << "Maximum Cargo Weight: " << maximumCargoWeight_ << std::endl;
    if(!assignedCargoId_.empty()) {
        std::cout << "Assigned Cargo ID: " << assignedCargoId_ << std::endl;
        std::cout << "Assign Cargo Weight: " << assignedCargoWeight_ << std::endl;
    } else {
        std::cout << "Assign Cargo ID: None" << std::endl;
        std::cout << "Assign Cargo Weight: 0" << std::endl;
    }
    std::cout << "Status: " << statusToString(status_) << std::endl;
}