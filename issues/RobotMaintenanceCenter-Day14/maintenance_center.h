#pragma once
#include "technician.h"
#include <vector>

enum class MenuChoice {
    AddRobot = 1,
    AddTechnician,
    ReportRobotError,
    AddOperatingHours,
    AssignMaintenance,
    CompleteMaintenance,
    StartCharging,
    ChargeRobot,
    StopCharging,
    ConsumeBattery,
    ShowRobot,
    ShowTechnician,
    ShowAllRobots,
    ShowAllTechnicians,
    ShowSummary,
    Exit
};

class MaintenanceCenter {
public:
    MaintenanceCenter();
    MaintenanceCenter(std::initializer_list<Robot> robots,
                     std::initializer_list<Technician> technicians);

    int findRobotIndexById(const std::string& robotId) const;
    int findTechnicianIndexById(const std::string& technicianId) const;

    int readyRobotCount() const;
    int maintenanceRequiredRobotCount() const;
    int underMaintenanceRobotCount() const;
    int chargingRobotCount() const;
    int outOfServiceRobotCount() const;

    int availableTechnicianCount() const;
    int busyTechnicianCount() const;

    bool addRobot(
        const std::string& id,
        const std::string& name,
        int batteryLevel,
        int operatingHours
    );

    bool addTechnician(
        const std::string& id,
        const std::string& name
    );

    bool reportRobotError(
        const std::string& robotId,
        int errorCode
    );

    bool addRobotOperatingHours(
        const std::string& robotId,
        int hours
    );

    bool assignMaintenance(
        const std::string& robotId,
        const std::string& technicianId
    );

    bool completeMaintenance(
        const std::string& robotId
    );

    bool cancelMaintenance(
        const std::string& robotId
    );

    bool startRobotCharging(
        const std::string& robotId
    );

    bool chargeRobot(
        const std::string& robotId,
        int amount
    );

    bool stopRobotCharging(
        const std::string& robotId
    );

    bool consumeRobotBattery(
        const std::string& robotId,
        int amount
    );

    bool printRobot(
        const std::string& robotId
    ) const;

    bool printTechnician(
        const std::string& technicianId
    ) const;

    void printAllRobots() const;
    void printAllTechnicians() const;

    double averageBatteryLevel() const;

    int mostExperiencedTechnicianIndex() const;

    void printSummary() const;

private:
    std::vector<Robot> robots_;
    std::vector<Technician> technicians_;
};
