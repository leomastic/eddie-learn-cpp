#include "technician.h"
#include "utils.h"
#include <iostream>
#include <utility>

Technician::Technician(
    std::string id,
    std::string name
)
    : id_(std::move(id)),
      name_(std::move(name)),
      assignedRobotId_(),
      completedMaintenanceCount_(0) {
}

const std::string& Technician::id() const {
    return this->id_;
}

const std::string& Technician::name() const {
    return this->name_;
}

const std::string& Technician::assignedRobotId() const {
    return this->assignedRobotId_;
}

int Technician::completedMaintenanceCount() const {
    return this->completedMaintenanceCount_;
}

bool Technician::isAvailable() const {
    return this->assignedRobotId_.empty();
}

bool Technician::hasAssignment() const {
    return !this->assignedRobotId_.empty();
}

bool Technician::assignRobot(const std::string& robotId) {
    if (robotId.empty() || !isAvailable()) {
        return false;
    }

    this->assignedRobotId_ = robotId;
    return true;
}

bool Technician::completeAssignment() {
    if (this->assignedRobotId_.empty()) {
        return false;
    }

    this->assignedRobotId_.clear();
    ++this->completedMaintenanceCount_;
    return true;
}

bool Technician::cancelAssignment() {
    if (this->assignedRobotId_.empty()) {
        return false;
    }

    this->assignedRobotId_.clear();
    return true;
}

Technician createTechnician() {
    std::cout << std::endl;
    std::string id = readNonEmptyWord("Please enter the technician id: ");
    std::string name = readNonEmptyLine("Please enter the technician name: ");

    return Technician(id, name);
}

void Technician::print() const {
    std::cout << "Technician information:" << std::endl;
    std::cout << "Technician ID: " << this->id_ << std::endl;
    std::cout << "Name: " << this->name_ << std::endl;

    std::cout << "Status: ";
    if (isAvailable()) {
        std::cout << "Available";
    } else {
        std::cout << "Busy";
    }
    std::cout << std::endl;

    std::cout << "Assigned robot: ";
    if (!isAvailable()) {
        std::cout << this->assignedRobotId_ << std::endl;
    } else {
        std::cout << "NONE";
    }
    std::cout << std::endl;

    std::cout << "Completed maintenance jobs: " << this->completedMaintenanceCount_ << std::endl;
}