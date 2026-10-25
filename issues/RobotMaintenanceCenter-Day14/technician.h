#pragma once
#include "robot.h"

class Technician {
public:
    Technician(
        std::string id,
        std::string name
    );

    const std::string& id() const;
    const std::string& name() const;
    const std::string& assignedRobotId() const;

    int completedMaintenanceCount() const;

    bool isAvailable() const;
    bool hasAssignment() const;

    bool assignRobot(const std::string& robotId);
    bool completeAssignment();
    bool cancelAssignment();

    void print() const;

private:
    std::string id_;
    std::string name_;
    std::string assignedRobotId_;
    int completedMaintenanceCount_;
};

Technician createTechnician();