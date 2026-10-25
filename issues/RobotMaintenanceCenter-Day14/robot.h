#pragma once
#include <string>
#include "battery.h"

enum class RobotStatus {
    Ready,
    NeedsMaintenance,
    UnderMaintenance,
    Charging,
    OutOfService
};

class Robot {
public:
    Robot(
        std::string id,
        std::string name,
        int batteryLevel,
        int operatingHours
    );

    const std::string& id() const;
    const std::string& name() const;

    int batteryLevel() const;
    BatteryStatus batteryStatus() const;

    int operatingHours() const;
    int errorCode() const;

    RobotStatus status() const;

    bool hasError() const;
    bool needsMaintenance() const;
    bool canBeAssigned() const;
    bool isUnderMaintenance() const;

    bool reportError(int errorCode);
    bool clearError();
    bool addOperatingHours(int hours);

    bool startMaintenance();
    bool completeMaintenance();

    bool startCharging();
    bool chargeBattery(int amount);
    bool stopCharging();
    bool consumeBattery(int amount);

    static std::string statusToString(RobotStatus status);

    void print() const;

private:
    void updateStatus();

    std::string id_;
    std::string name_;
    Battery battery_;
    int operatingHours_;
    int errorCode_;
    RobotStatus status_;
};

Robot createRobot();