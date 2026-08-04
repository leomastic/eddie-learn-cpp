#include "delivery_center.h"
#include <iostream>
#include <iomanip>

DeliveryCenter::DeliveryCenter() {
}

int DeliveryCenter::findVehicleIndexById(const std::string& vehicleId) const {
    for (std::size_t i = 0; i < vehicles_.size(); ++i) {
        if (vehicles_[i].id() == vehicleId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int DeliveryCenter::findCargoIndexById(const std::string& cargoId) const {
    for (std::size_t i = 0; i < cargoPackages_.size(); ++i) {
        if (cargoPackages_[i].id() == cargoId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool DeliveryCenter::addVehicle(const std::string& id, const std::string& name, int fuelLevel, int maximumCargoWeight) {
    if(!id.empty() && !name.empty() && fuelLevel >= 0 && fuelLevel <= 100 && maximumCargoWeight > 0 && findVehicleIndexById(id) < 0) {
        vehicles_.emplace_back(
            id,
            name,
            fuelLevel,
            maximumCargoWeight
        );
        return true;
    }

    return false;
}

bool DeliveryCenter::addCargo(const std::string& id, const std::string& description, int weight) {
    if(!id.empty() && !description.empty() && weight > 0 && findCargoIndexById(id) < 0) {
        cargoPackages_.emplace_back(
            id,
            description,
            weight
        );

        return true;
    }

    return false;
}

bool DeliveryCenter::loadCargo(const std::string& cargoId, const std::string& vehicleId) {
    int cargoIndex = findCargoIndexById(cargoId);
    int vehicleIndex = findVehicleIndexById(vehicleId);

    if(cargoIndex < 0 || vehicleIndex < 0) {
        return false;
    }

    Cargo& cargo = cargoPackages_[cargoIndex];
    Vehicle& vehicle = vehicles_[vehicleIndex];

    if (!cargo.assignToVehicle(vehicleId)) {
        return false;
    }

    if (!vehicle.loadCargo(cargoId, cargo.weight())) {
        cargo.removeVehicleAssignment();
        return false;
    }

    return true;
}

bool DeliveryCenter::startDelivery(const std::string& cargoId) {
    int cargoIndex = findCargoIndexById(cargoId);
    if(cargoIndex < 0) {
        return false;
    }

    Cargo& cargo = cargoPackages_[cargoIndex];

    if (!cargo.isLoaded()) {
        return false;
    }

    std::string vehicleId = cargo.assignedVehicleId();
    if (vehicleId.empty()) {
        return false;
    }

    int vehicleIndex = findVehicleIndexById(vehicleId);
    if (vehicleIndex < 0) {
        return false;
    }

    Vehicle& vehicle = vehicles_[vehicleIndex];

    if (!vehicle.startDelivery()) {
        return false;
    }

    if (!cargo.startDelivery()) {
        return false;
    }

    return true;
}

bool DeliveryCenter::travel(const std::string& cargoId, int fuelAmount) {
    int cargoIndex = findCargoIndexById(cargoId);
    if(cargoIndex < 0) {
        return false;
    }

    Cargo& cargo = cargoPackages_[cargoIndex];

    if(!cargo.isInTransit()) {
        return false;
    }

    std::string vehicleId = cargo.assignedVehicleId();
    if (vehicleId.empty()) {
        return false;
    }

    int vehicleIndex = findVehicleIndexById(vehicleId);
    if (vehicleIndex < 0) {
        return false;
    }

    Vehicle& vehicle = vehicles_[vehicleIndex];

    return vehicle.travel(fuelAmount);
}

bool DeliveryCenter::completeDelivery(const std::string& cargoId) {
    int cargoIndex = findCargoIndexById(cargoId);
    if(cargoIndex < 0) {
        return false;
    }

    Cargo& cargo = cargoPackages_[cargoIndex];

    if(!cargo.isInTransit()) {
        return false;
    }

    std::string vehicleId = cargo.assignedVehicleId();
    if (vehicleId.empty()) {
        return false;
    }

    int vehicleIndex = findVehicleIndexById(vehicleId);
    if (vehicleIndex < 0) {
        return false;
    }

    Vehicle& vehicle = vehicles_[vehicleIndex];

    if (!vehicle.completeDelivery()) {
        return false;
    }

    if (!cargo.completeDelivery()) {
        return false;
    }

    return true;

}

bool DeliveryCenter::cancelDelivery(const std::string& cargoId) {
    int cargoIndex = findCargoIndexById(cargoId);
    if (cargoIndex < 0) {
        return false;
    }

    Cargo& cargo = cargoPackages_[cargoIndex];

    if (cargo.isWaiting()) {
        return cargo.cancelDelivery();
    } 
    else if (cargo.isLoaded()) {
        std::string vehicleId = cargo.assignedVehicleId();
        int vehicleIndex = findVehicleIndexById(vehicleId);

        if (vehicleIndex < 0) {
            return false;
        }

        Vehicle& vehicle = vehicles_[vehicleIndex];

        if (!vehicle.unloadCargo()) {
            return false;
        }

        if (!cargo.cancelDelivery()) {
            return false;
        }

        return true;
    }

    return false;
}

bool DeliveryCenter::startVehicleRefueling(const std::string& vehicleId) {
    int vehicleIndex = findVehicleIndexById(vehicleId);
    if (vehicleIndex < 0) {
        return false;
    }

    return vehicles_[vehicleIndex].startRefueling();
}

bool DeliveryCenter::refuelVehicle(const std::string& vehicleId, int amount) {
    int vehicleIndex = findVehicleIndexById(vehicleId);
    if (vehicleIndex < 0) {
        return false;
    }

    return vehicles_[vehicleIndex].refuel(amount);
}

bool DeliveryCenter::stopVehicleRefueling(const std::string& vehicleId) {
    int vehicleIndex = findVehicleIndexById(vehicleId);
    if (vehicleIndex < 0) {
        return false;
    }

    return vehicles_[vehicleIndex].stopRefueling();
}

bool DeliveryCenter::printVehicle(const std::string& vehicleId) const {
    int vehicleIndex = findVehicleIndexById(vehicleId);
    if (vehicleIndex < 0) {
        return false;
    }

    const Vehicle& vehicle = vehicles_[vehicleIndex];
    vehicle.print();
    return true;
}

bool DeliveryCenter::printCargo(const std::string& cargoId) const {
    int cargoIndex = findCargoIndexById(cargoId);
    if (cargoIndex < 0) {
        return false;
    }

    const Cargo& cargo = cargoPackages_[cargoIndex];
    cargo.print();
    return true;
}

void DeliveryCenter::printAllVehicles() const {
    if(vehicles_.empty()) {
        std::cout << "No vehicles in the delivery center." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < vehicles_.size(); ++i) {
        std::cout << "Vehicle " << (i + 1) << ":" << std::endl;
        vehicles_[i].print();
        std::cout << std::endl;
    }
}

void DeliveryCenter::printAllCargo() const {
    if(cargoPackages_.empty()) {
        std::cout << "No cargo packages in the delivery center." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < cargoPackages_.size(); ++i) {
        std::cout << "Cargo Packages " << (i + 1) << ":" << std::endl;
        cargoPackages_[i].print();
        std::cout << std::endl;
    }
}

int DeliveryCenter::availableVehicleCount() const {
    int count = 0;

    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.status() == VehicleStatus::Available) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::loadedVehicleCount() const {
    int count = 0;

    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.status() == VehicleStatus::Loaded) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::inTransitVehicleCount() const {
    int count = 0;

    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.status() == VehicleStatus::InTransit) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::refuelingVehicleCount() const {
    int count = 0;

    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.status() == VehicleStatus::Refueling) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::outOfServiceVehicleCount() const {
    int count = 0;

    for (const Vehicle& vehicle : vehicles_) {
        if (vehicle.status() == VehicleStatus::OutOfService) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::waitingCargoCount() const {
    int count = 0;

    for (const Cargo& cargo : cargoPackages_) {
        if (cargo.status() == CargoStatus::Waiting) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::loadedCargoCount() const {
    int count = 0;

    for (const Cargo& cargo : cargoPackages_) {
        if (cargo.status() == CargoStatus::Loaded) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::inTransitCargoCount() const {
    int count = 0;

    for (const Cargo& cargo : cargoPackages_) {
        if (cargo.status() == CargoStatus::InTransit) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::deliveredCargoCount() const {
    int count = 0;

    for (const Cargo& cargo : cargoPackages_) {
        if (cargo.status() == CargoStatus::Delivered) {
            ++count;
        }
    }

    return count;
}

int DeliveryCenter::cancelledCargoCount() const {
    int count = 0;

    for (const Cargo& cargo : cargoPackages_) {
        if (cargo.status() == CargoStatus::Cancelled) {
            ++count;
        }
    }

    return count;
}

double DeliveryCenter::averageFuelLevel() const {
    if (vehicles_.empty()) {
        return 0.0;
    }

    double totalFuel = 0.0;
    for (const Vehicle& vehicle : vehicles_) {
        totalFuel += vehicle.fuelLevel();
    }

    return totalFuel / static_cast<double>(vehicles_.size());
}

int DeliveryCenter::totalWaitingCargoWeight() const {
    int totalWeight = 0;

    for (const Cargo& cargo : cargoPackages_) {
        if (cargo.isWaiting()) { 
            totalWeight += cargo.weight();
        }
    }

    return totalWeight;
}

int DeliveryCenter::highestCapacityVehicleIndex() const {
    if (vehicles_.empty()) {
        return -1;
    }

    int highestIndex = 0;
    int maxCapacity = vehicles_[0].maximumCargoWeight();

    for (size_t i = 1; i < vehicles_.size(); ++i) {
        if (vehicles_[i].maximumCargoWeight() > maxCapacity) {
            maxCapacity = vehicles_[i].maximumCargoWeight();
            highestIndex = static_cast<int>(i);
        }
    }

    return highestIndex;
}

void DeliveryCenter::printSummary() const {
    int total = static_cast<int>(vehicles_.size());
    int availableVehicle = availableVehicleCount();
    int loadedVehicle = loadedVehicleCount();
    int inTransitVehicle = inTransitVehicleCount();
    int refuelingVehicle = refuelingVehicleCount();
    int outOfServiceVehicle = outOfServiceVehicleCount();

    int totalCargo = static_cast<int>(cargoPackages_.size());
    int waitingCargo = waitingCargoCount();
    int loadedCargo = loadedCargoCount();
    int inTransitCargo = inTransitCargoCount();
    int deliveredCargo = deliveredCargoCount();
    int cancelledCargo = cancelledCargoCount();

    double averageFuel = averageFuelLevel();
    int TotalWaitingCargoWeight = totalWaitingCargoWeight();

    int highestCapaVehicleIndex = highestCapacityVehicleIndex();
    std::string highestCapaVehicleName = "None";
    int maximumCargoWeight = 0;

    if (highestCapaVehicleIndex >= 0) {
        highestCapaVehicleName = vehicles_[highestCapaVehicleIndex].name();
        maximumCargoWeight = vehicles_[highestCapaVehicleIndex].maximumCargoWeight();
    }

    std::cout << "===== Space Cargo Delivery Center Summary =====" << std::endl;
    std::cout << std::endl;

    std::cout << "Vehicle:" << std::endl;
    std::cout << "Total vehicles: " << total << std::endl;
    std::cout << "Available vehicles: " << availableVehicle << std::endl;
    std::cout << "Loaded vehicles: " << loadedVehicle << std::endl;
    std::cout << "Vehicles in transit: " << inTransitVehicle << std::endl;
    std::cout << "Refueling vehicles: " << refuelingVehicle << std::endl;
    std::cout << "Out-of-service vehicles: " << outOfServiceVehicle << std::endl;

    std::cout << std::endl;

    std::cout << "Cargo:" << std::endl;
    std::cout << "Total cargo packages: " << totalCargo << std::endl;
    std::cout << "Waiting cargo: " << waitingCargo << std::endl;
    std::cout << "Loaded cargo: " << loadedCargo << std::endl;
    std::cout << "In transit cargo: " << inTransitCargo << std::endl;
    std::cout << "Delivered cargo: " << deliveredCargo << std::endl;
    std::cout << "Cancelled cargo: " << cancelledCargo << std::endl;

    std::cout << std::endl;

    std::cout << "Average vehicle fuel: " 
              << std::fixed << std::setprecision(1)
              << averageFuel << std::endl;

    std::cout << "Total waiting cargo weight: " 
              << std::fixed << std::setprecision(1)
              << TotalWaitingCargoWeight << std::endl;

    std::cout << std::endl;

    std::cout << "Highest-capacity vehicle: " << highestCapaVehicleName << std::endl;
    std::cout << "Maximum cargo weight: " << maximumCargoWeight << std::endl;
}