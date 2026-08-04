#pragma once
#include <vector>
#include "vehicle.h"
#include "cargo.h"

class DeliveryCenter {
public: 
    DeliveryCenter();
    int findVehicleIndexById(const std::string& vehicleId) const;
    int findCargoIndexById(const std::string& cargoId) const;

    bool addVehicle(const std::string& id, const std::string& name, int fuelLevel, int maximumCargoWeight);
    bool addCargo(const std::string& id, const std::string& description, int weight);

    bool loadCargo(const std::string& cargoId, const std::string& vehicleId);

    bool startDelivery(const std::string& cargoId);
    bool travel(const std::string& cargoId, int fuelAmount);
    bool completeDelivery(const std::string& cargoId);
    bool cancelDelivery(const std::string& cargoId);

    bool startVehicleRefueling(const std::string& vehicleId);
    bool refuelVehicle(const std::string& vehicleId, int amount);
    bool stopVehicleRefueling(const std::string& vehicleId);

    bool printVehicle(const std::string& vehicleID) const;
    bool printCargo(const std::string& cargoId) const;

    void printAllVehicles() const;
    void printAllCargo() const;

    void printSummary() const;

private:

    int availableVehicleCount() const;
    int loadedVehicleCount() const;
    int inTransitVehicleCount() const;
    int refuelingVehicleCount() const;
    int outOfServiceVehicleCount() const;

    int waitingCargoCount() const;
    int loadedCargoCount() const;
    int inTransitCargoCount() const;
    int deliveredCargoCount() const;
    int cancelledCargoCount() const;

    double averageFuelLevel() const;
    int totalWaitingCargoWeight() const;    
    int highestCapacityVehicleIndex() const;

    std::vector<Vehicle> vehicles_;
    std::vector<Cargo> cargoPackages_;
};