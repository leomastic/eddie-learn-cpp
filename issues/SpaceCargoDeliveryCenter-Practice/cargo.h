#pragma once
#include <string>

enum class CargoStatus {
    Waiting,
    Loaded,
    InTransit,
    Delivered,
    Cancelled
};

class Cargo {
public:
    Cargo(
        std::string id,
        std::string description,
        int weight
    );

    const std::string& id() const;
    const std::string& description() const;
    int weight() const;

    CargoStatus status() const;

    const std::string& assignedVehicleId() const;

    bool isWaiting() const;
    bool isLoaded() const;
    bool isInTransit() const;
    bool isDelivered() const;
    bool isCancelled() const;
    bool hasVehicleAssignment() const;
    bool assignToVehicle(const std::string& vehicleId);

    bool startDelivery();
    bool completeDelivery();
    bool cancelDelivery();
    bool removeVehicleAssignment();

    static std::string statusToString(CargoStatus status);

    void print() const;

private:
    std::string id_;
    std::string description_;
    int weight_;
    CargoStatus status_;
    std::string assignedVehicleId_;
};

Cargo createCargo();