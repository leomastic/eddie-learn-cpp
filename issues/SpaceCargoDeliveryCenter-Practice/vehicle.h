#pragma once
#include <string>
#include "fuel_tank.h"

enum class VehicleStatus {
    Available,
    Loaded,
    InTransit,
    Refueling,
    OutOfService
};

class Vehicle {
public:
    Vehicle(
        std::string id,
        std::string name,
        int fuelLevel,
        int maximumCargoWeight
    );

    const std::string& id() const;
    const std::string& name() const;

    int fuelLevel() const;
    FuelStatus fuelStatus() const;

    int maximumCargoWeight() const;

    const std::string& assignedCargoId() const;
    int assignedCargoWeight() const;

    VehicleStatus status() const;

    bool isAvailable() const;
    bool hasCargo() const;
    bool canAcceptCargo(int cargoWeight) const;
    bool isInTransit() const;
    bool isRefueling() const;

    void updateStatus();

    bool loadCargo(const std::string& cargoId, int cargoWeight);
    bool unloadCargo();

    bool startDelivery();
    bool travel(int fuelAmount);
    bool completeDelivery();

    bool startRefueling();
    bool refuel(int amount);
    bool stopRefueling();

    static std::string statusToString(VehicleStatus status);

    void print() const;
    
private:
    std::string id_;
    std::string name_;

    FuelTank fuelTank_;

    int maximumCargoWeight_;

    std::string assignedCargoId_;
    int assignedCargoWeight_;

    VehicleStatus status_;
};

Vehicle createVehicle();