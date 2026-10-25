#include "robot.h"
#include "utils.h"
#include <utility>
#include <iostream>

Robot::Robot(
    std::string id,
    std::string name,
    int batteryLevel,
    int operatingHours
)
    : id_(std::move(id)),
      name_(std::move(name)),
      battery_(batteryLevel),
      operatingHours_(operatingHours < 0 ? 0 : operatingHours),
      errorCode_(0),
      status_(RobotStatus::Ready) {
    this->updateStatus();
}

const std::string& Robot::id() const {
    return this->id_;
}

const std::string& Robot::name() const {
    return this->name_;
}

int Robot::batteryLevel() const {
    return this->battery_.level();
}

BatteryStatus Robot::batteryStatus() const {
    return this->battery_.status();
}

int Robot::operatingHours() const {
    return this->operatingHours_;
}

int Robot::errorCode() const {
    return this->errorCode_;
}

RobotStatus Robot::status() const {
    return this->status_;
}

bool Robot::hasError() const {
    return this->errorCode_ != 0;
}

bool Robot::needsMaintenance() const {
    return this->hasError() || this->operatingHours_ >= 1000 || this->batteryLevel() == 0;
}

bool Robot::canBeAssigned() const {
    return this->status_ == RobotStatus::NeedsMaintenance;
}

bool Robot::isUnderMaintenance() const {
    return this->status_ == RobotStatus::UnderMaintenance;
}

void Robot::updateStatus() {
    if (this->status_ == RobotStatus::UnderMaintenance) {
        return;
    }

    if (this->status_ == RobotStatus::Charging) {
        return;
    }

    if (this->batteryLevel() == 0) {
        this->status_ = RobotStatus::OutOfService;
    } else if (this->hasError() || this->operatingHours_ >= 1000) {
        this->status_ = RobotStatus::NeedsMaintenance;
    } else {
        this->status_ = RobotStatus::Ready;
    }
}

bool Robot::reportError(int errorCode) {
    if (errorCode <= 0) {
        return false;
    }

    this->errorCode_ = errorCode;
    this->updateStatus();
    return true;
}

bool Robot::clearError() {
    if (!hasError()) {
        return false;
    }

    this->errorCode_ = 0;
    this->updateStatus();
    return true;
}

bool Robot::addOperatingHours(int hours) {
    if (hours <= 0) {
        return false;
    }

    this->operatingHours_ += hours;
    this->updateStatus();
    return true;
}

bool Robot::startMaintenance() {
    if (this->status_ == RobotStatus::NeedsMaintenance) {
        this->status_ = RobotStatus::UnderMaintenance;
        return true;
    }

    return false;
}

bool Robot::completeMaintenance() {
    if (this->status_ != RobotStatus::UnderMaintenance) {
        return false;
    }

    this->errorCode_ = 0;
    this->operatingHours_ = 0;

    if (this->batteryLevel() == 0) {
        this->status_ = RobotStatus::OutOfService;
    } else if (this->hasError() || this->operatingHours_ >= 1000) {
        this->status_ = RobotStatus::NeedsMaintenance;
    } else {
        this->status_ = RobotStatus::Ready;
    }

    return true;
}

bool Robot::cancelMaintenance() {
    if (this->status_ != RobotStatus::UnderMaintenance) {
        return false;
    }

    this->status_ = RobotStatus::NeedsMaintenance;
    return true;
}

bool Robot::startCharging() {
    if (this->status_ == RobotStatus::UnderMaintenance || this->status_ == RobotStatus::Charging || this->battery_.isFull()) {
        return false;
    }

    this->status_ = RobotStatus::Charging;
    return true;
}

bool Robot::chargeBattery(int amount) {
    if (this->status_ != RobotStatus::Charging || amount <= 0) {
        return false;
    }

    this->battery_.charge(amount);

    if (this->battery_.isFull()) {
        this->status_ = RobotStatus::Ready;
        this->updateStatus();
    }

    return true;
}

bool Robot::stopCharging() {
    if (this->status_ != RobotStatus::Charging) {
        return false;
    }

    this->status_ = RobotStatus::Ready;
    this->updateStatus();
    return true;
}

bool Robot::consumeBattery(int amount) {
    if (this->status_ != RobotStatus::Ready || amount <= 0) {
        return false;
    }

    this->battery_.consume(amount);
    this->updateStatus();
    return true;
}

std::string Robot::statusToString(RobotStatus status) {
    switch (status) {
        case RobotStatus::Ready:
            return "Ready";

        case RobotStatus::NeedsMaintenance:
            return "Needs Maintenance";

        case RobotStatus::UnderMaintenance:
            return "Under Maintenance";

        case RobotStatus::Charging:
            return "Charging";

        case RobotStatus::OutOfService:
            return "Out Of Service";
    }

    return "Unknown";
}

Robot createRobot() {
    std::cout << std::endl;
    std::string id = readNonEmptyWord("Please enter the robot id: ");
    std::string name = readNonEmptyLine("Please enter the robot name: ");

    int batteryLevel = readIntInRange("Please enter the robot battery level (0 --> 100): ", 0, 100);
    int operatingHours = readIntInRange("Please enter the operating hours (0 --> 2000): ", 0, 2000);

    std::cout << std::endl;

    return Robot(id, name, batteryLevel, operatingHours);
}

void Robot::print() const {
    std::cout << "Robot status:" << std::endl;
    std::cout << "Robot ID: " << this->id_ << std::endl;
    std::cout << "Name: " << this->name_ << std::endl;
    std::cout
        << "Battery level: "
        << batteryLevel()
        << std::endl;

    std::cout
        << "Battery status: "
        << Battery::statusToString(battery_.status())
        << std::endl;
    std::cout << "Operating hours: " << this->operatingHours_ << std::endl;
    std::cout << "Error code: " << this->errorCode_ << std::endl;
    std::cout << "Status: " << statusToString(this->status_) << std::endl;
}