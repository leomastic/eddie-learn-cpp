#include "maintenance_center.h"
#include <initializer_list>
#include <iostream>
#include <iomanip>

MaintenanceCenter::MaintenanceCenter() = default;

MaintenanceCenter::MaintenanceCenter(std::initializer_list<Robot> robots, std::initializer_list<Technician> technicians)
    : robots_(robots), technicians_(technicians) {}

int MaintenanceCenter::findRobotIndexById(
    const std::string& robotId
) const {
    for (std::size_t i = 0; i < robots_.size(); ++i) {
        if (robots_[i].id() == robotId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int MaintenanceCenter::findTechnicianIndexById(
    const std::string& technicianId
) const {
    for (std::size_t i = 0; i < technicians_.size(); ++i) {
        if (technicians_[i].id() == technicianId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool MaintenanceCenter::addRobot(
    const std::string& id,
    const std::string& name,
    int batteryLevel,
    int operatingHours
) {
    if (id.empty() || name.empty() || batteryLevel < 0 || batteryLevel > 100 || operatingHours < 0 || findRobotIndexById(id) >= 0) {
        return false;
    }

    robots_.emplace_back(id, name, batteryLevel, operatingHours);
    return true;
}

bool MaintenanceCenter::addTechnician(const std::string& id, const std::string& name) {
    if (id.empty() || name.empty() || findTechnicianIndexById(id) >= 0) {
        return false;
    }

    technicians_.emplace_back(id, name);
    return true;
}

bool MaintenanceCenter::reportRobotError(const std::string& robotId, int errorCode) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    return robots_[robotIndex].reportError(errorCode);
}

bool MaintenanceCenter::addRobotOperatingHours(
    const std::string& robotId,
    int hours
) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    return robots_[robotIndex].addOperatingHours(hours);
}

bool MaintenanceCenter::assignMaintenance(
    const std::string& robotId,
    const std::string& technicianId
) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    int technicianIndex = findTechnicianIndexById(technicianId);
    if (technicianIndex < 0) {
        return false;
    }

    Robot& robot = robots_[robotIndex];
    Technician& technician = technicians_[technicianIndex];

    if (!robot.canBeAssigned() || !technician.isAvailable()) {
        return false;
    }

    if (!technician.assignRobot(robotId)) {
        return false;
    }

    if (!robot.startMaintenance()) {
        technician.cancelAssignment();
        return false;
    }

    return true;
}

bool MaintenanceCenter::completeMaintenance(
    const std::string& robotId
) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    Robot& robot = robots_[robotIndex];
    if (!robot.isUnderMaintenance()) {
        return false;
    }

    int technicianIndex = -1;
    for (std::size_t i = 0; i < technicians_.size(); ++i) {
        if (technicians_[i].assignedRobotId() == robotId) {
            technicianIndex = static_cast<int>(i);
            break;
        }
    }

    if (technicianIndex < 0) {
        return false;
    }

    if (!robot.completeMaintenance()) {
        return false;
    }

    Technician& technician = technicians_[technicianIndex];
    return technician.completeAssignment();
}

bool MaintenanceCenter::cancelMaintenance(const std::string& robotId) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    Robot& robot = robots_[robotIndex];
    if (!robot.isUnderMaintenance()) {
        return false;
    }

    for (std::size_t i = 0; i < technicians_.size(); ++i) {
        if (technicians_[i].assignedRobotId() == robotId) {
            if (!robot.cancelMaintenance()) {
                return false;
            }
            if (!technicians_[i].cancelAssignment()) {
                return false;
            }
            return true;
        }
    }

    return false;
}

bool MaintenanceCenter::startRobotCharging(const std::string& robotId) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    return robots_[robotIndex].startCharging();
}

bool MaintenanceCenter::chargeRobot(const std::string& robotId, int amount) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    return robots_[robotIndex].chargeBattery(amount);
}

bool MaintenanceCenter::stopRobotCharging(const std::string& robotId) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    return robots_[robotIndex].stopCharging();
}

bool MaintenanceCenter::consumeRobotBattery(const std::string& robotId, int amount) {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex < 0) {
        return false;
    }

    return robots_[robotIndex].consumeBattery(amount);
}

bool MaintenanceCenter::printRobot(const std::string& robotId) const {
    int robotIndex = findRobotIndexById(robotId);
    if (robotIndex >= 0) {
        robots_[robotIndex].print();
        return true;
    }

    return false;
}

bool MaintenanceCenter::printTechnician(const std::string& technicianId) const {
    int technicianIndex = findTechnicianIndexById(technicianId);
    if (technicianIndex >= 0) {
        technicians_[technicianIndex].print();
        return true;
    }

    return false;
}

void MaintenanceCenter::printAllRobots() const {
    if (robots_.empty()) {
        std::cout << "No robots in the maintenance center." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < robots_.size(); ++i) {
        std::cout << "Robot " << (i + 1) << ":" << std::endl;
        robots_[i].print();
        std::cout << std::endl;
    }
}

void MaintenanceCenter::printAllTechnicians() const {
    if (technicians_.empty()) {
        std::cout << "No technicians in the maintenance center." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < technicians_.size(); ++i) {
        std::cout << "Technician " << (i + 1) << ":" << std::endl;
        technicians_[i].print();
        std::cout << std::endl;
    }
}

int MaintenanceCenter::readyRobotCount() const {
    int count = 0;

    for (const Robot& robot : robots_) {
        if (robot.status() == RobotStatus::Ready) {
            ++count;
        }
    }

    return count;
}

int MaintenanceCenter::maintenanceRequiredRobotCount() const {
    int count = 0;

    for (const Robot& robot : robots_) {
        if (robot.status() == RobotStatus::NeedsMaintenance) {
            ++count;
        }
    }

    return count;
}

int MaintenanceCenter::underMaintenanceRobotCount() const {
    int count = 0;

    for (const Robot& robot : robots_) {
        if (robot.status() == RobotStatus::UnderMaintenance) {
            ++count;
        }
    }

    return count;
}

int MaintenanceCenter::chargingRobotCount() const {
    int count = 0;

    for (const Robot& robot : robots_) {
        if (robot.status() == RobotStatus::Charging) {
            ++count;
        }
    }

    return count;
}

int MaintenanceCenter::outOfServiceRobotCount() const {
    int count = 0;

    for (const Robot& robot : robots_) {
        if (robot.status() == RobotStatus::OutOfService) {
            ++count;
        }
    }

    return count;
}

int MaintenanceCenter::availableTechnicianCount() const {
    int count = 0;

    for (const Technician& technician : technicians_) {
        if (technician.isAvailable()) {
            ++count;
        }
    }

    return count;
}

int MaintenanceCenter::busyTechnicianCount() const {
    int count = 0;

    for (const Technician& technician : technicians_) {
        if (!technician.isAvailable()) {
            ++count;
        }
    }

    return count;
}

double MaintenanceCenter::averageBatteryLevel() const {
    if (robots_.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const Robot& robot : robots_) {
        sum += robot.batteryLevel();
    }

    return sum / static_cast<double>(robots_.size());
}

int MaintenanceCenter::mostExperiencedTechnicianIndex() const {
    if (technicians_.empty()) {
        return -1;
    }

    int bestIndex = 0;
    for (std::size_t i = 1; i < technicians_.size(); ++i) {
        if (technicians_[i].completedMaintenanceCount() > technicians_[bestIndex].completedMaintenanceCount()) {
            bestIndex = static_cast<int>(i);
        }
    }

    return bestIndex;
}

void MaintenanceCenter::printSummary() const {
    int total = static_cast<int>(robots_.size());
    int ready = readyRobotCount();
    int needsMaintenance = maintenanceRequiredRobotCount();
    int underMaintenance = underMaintenanceRobotCount();
    int charging = chargingRobotCount();
    int outOfService = outOfServiceRobotCount();

    int totalTechnicians = static_cast<int>(technicians_.size());
    int availableTechnicians = availableTechnicianCount();
    int busyTechnicians = busyTechnicianCount();
    double averageRobotBattery = averageBatteryLevel();

    int expIndex = mostExperiencedTechnicianIndex();
    std::string mostExperiencedTechnician = "None";
    int completedMaintenanceJobs = 0;

    if (expIndex >= 0) {
        mostExperiencedTechnician = technicians_[expIndex].name();
        completedMaintenanceJobs = technicians_[expIndex].completedMaintenanceCount();
    }

    std::cout << "===== Maintenance Center Summary =====" << std::endl;
    std::cout << std::endl;
    std::cout << "Total robots: " << total << std::endl;
    std::cout << "Ready robots: " << ready << std::endl;
    std::cout << "Robots needing maintenance: " << needsMaintenance << std::endl;
    std::cout << "Robots under maintenance: " << underMaintenance << std::endl;
    std::cout << "Charging robots: " << charging << std::endl;
    std::cout << "Out-of-service robots: " << outOfService << std::endl;
    std::cout << std::endl;
    std::cout << "Total technicians: " << totalTechnicians << std::endl;
    std::cout << "Available technicians: " << availableTechnicians << std::endl;
    std::cout << "Busy technicians: " << busyTechnicians << std::endl;
    std::cout << std::endl;
    std::cout << "Average robot battery: " << std::fixed << std::setprecision(1)
              << averageRobotBattery << std::endl;
    std::cout << std::endl;
    std::cout << "Most experienced technician: " << mostExperiencedTechnician << std::endl;
    std::cout << "Completed maintenance jobs: " << completedMaintenanceJobs << std::endl;
}