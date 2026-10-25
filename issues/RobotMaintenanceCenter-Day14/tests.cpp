#include "maintenance_center.h"
#include <cassert>
#include <cmath>
#include <iostream>

void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAILED: " << message << std::endl;
        std::exit(1);
    }
}

int main() {
    {
        MaintenanceCenter center({}, {});
        expect(center.addRobot("R001", "Atlas", 80, 0), "Add valid robot");
        expect(!center.addRobot("R001", "Atlas", 80, 0), "Duplicate robot ID");
    }

    {
        MaintenanceCenter center({}, {});
        expect(center.addTechnician("T001", "Eddie"), "Add valid technician");
        expect(!center.addTechnician("T001", "Eddie"), "Duplicate technician ID");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 0)}, {});
        expect(center.reportRobotError("R001", 301), "Report error");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 0)}, {});
        expect(!center.reportRobotError("R001", 0), "Reject invalid error code");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 950)}, {});
        expect(center.addRobotOperatingHours("R001", 100), "Add operating hours");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 950)}, {Technician("T001", "Eddie")});
        expect(center.reportRobotError("R001", 301), "Set robot to need maintenance");
        expect(center.assignMaintenance("R001", "T001"), "Assign maintenance successfully");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 0)}, {Technician("T001", "Eddie")});
        expect(!center.assignMaintenance("R001", "T001"), "Reject assignment of a ready robot");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 950), Robot("R002", "Beta", 80, 950)}, {Technician("T001", "Eddie")});
        expect(center.reportRobotError("R001", 301), "Set first robot to need maintenance");
        expect(center.assignMaintenance("R001", "T001"), "Assign first robot");
        expect(!center.assignMaintenance("R002", "T001"), "Reject assignment to a busy technician");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 1200)}, {Technician("T001", "Eddie")});
        expect(center.reportRobotError("R001", 301), "Set error before completion");
        expect(center.assignMaintenance("R001", "T001"), "Assign maintenance before completion");
        expect(center.completeMaintenance("R001"), "Complete maintenance");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 80, 0)}, {Technician("T001", "Eddie")});
        expect(!center.completeMaintenance("R001"), "Reject completion without maintenance");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 40, 0)}, {});
        expect(center.startRobotCharging("R001"), "Start charging");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 40, 0)}, {});
        expect(center.startRobotCharging("R001"), "Start charging for battery charge");
        expect(center.chargeRobot("R001", 35), "Charge battery");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 90, 0)}, {});
        expect(center.startRobotCharging("R001"), "Start charging for cap at 100");
        expect(center.chargeRobot("R001", 30), "Charge battery to 100");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 75, 300)}, {});
        expect(center.startRobotCharging("R001"), "Start charging for stop test");
        expect(center.stopRobotCharging("R001"), "Stop charging");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 50, 0)}, {});
        expect(center.consumeRobotBattery("R001", 20), "Consume battery");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 10, 0)}, {});
        expect(center.consumeRobotBattery("R001", 20), "Consume battery to empty");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 50, 0)}, {});
        expect(center.startRobotCharging("R001"), "Start charging before reject consumption");
        expect(!center.consumeRobotBattery("R001", 20), "Reject battery use while charging");
    }

    {
        MaintenanceCenter center({Robot("R001", "Atlas", 50, 0)}, {Technician("T001", "Eddie")});
        expect(center.reportRobotError("R001", 301), "Mark robot for maintenance");
        expect(center.assignMaintenance("R001", "T001"), "Assign maintenance before charging rejection");
        expect(!center.startRobotCharging("R001"), "Reject charging while under maintenance");
    }

    {
        MaintenanceCenter center({Robot("R1", "A", 80, 0), Robot("R2", "B", 70, 0), Robot("R3", "C", 60, 1000), Robot("R4", "D", 50, 0), Robot("R5", "E", 40, 0), Robot("R6", "F", 10, 0)}, {Technician("T1", "Eddie"), Technician("T2", "Alice"), Technician("T3", "Bob")});
        expect(center.startRobotCharging("R4"), "Set charging robot");
        expect(center.reportRobotError("R3", 301), "Set maintenance robot");
        expect(center.assignMaintenance("R3", "T1"), "Set under maintenance robot");
        expect(center.reportRobotError("R5", 301), "Set needs-maintenance robot");
        expect(center.consumeRobotBattery("R6", 20), "Set out of service robot");
        expect(center.chargeRobot("R4", 10), "Charge the charging robot");
        expect(center.readyRobotCount() == 2, "Ready robots count");
        expect(center.maintenanceRequiredRobotCount() == 1, "Maintenance required count");
        expect(center.underMaintenanceRobotCount() == 1, "Under maintenance count");
        expect(center.chargingRobotCount() == 1, "Charging count");
        expect(center.outOfServiceRobotCount() == 1, "Out-of-service count");
        expect(center.availableTechnicianCount() == 2, "Available technician count");
        expect(center.busyTechnicianCount() == 1, "Busy technician count");
    }

    {
        MaintenanceCenter center({Robot("R1", "A", 80, 0), Robot("R2", "B", 40, 0), Robot("R3", "C", 30, 0)}, {});
        expect(std::fabs(center.averageBatteryLevel() - 50.0) < 1e-9, "Average battery");
    }

    {
        MaintenanceCenter center({}, {});
        expect(center.averageBatteryLevel() == 0.0, "Empty center average battery");
        expect(center.mostExperiencedTechnicianIndex() == -1, "Empty center most experienced technician");
    }

    std::cout << "All RobotMaintenanceCenter-Day14 regression tests passed." << std::endl;
    return 0;
}
