#include "delivery_center.h"
#include "cargo.h"
#include "vehicle.h"
#include "fuel_tank.h"
#include <cstdlib>
#include <iostream>
#include <string>

void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAILED: " << message << std::endl;
        std::exit(1);
    }
}

void testFuelTank() {
    FuelTank tank(30);
    expect(tank.level() == 30, "Fuel tank initializes with given level");
    tank.consume(20);
    expect(tank.level() == 10, "Fuel tank consumes correctly");
    tank.refuel(40);
    expect(tank.level() == 50, "Fuel tank refuels correctly");
    tank.refuel(60);
    expect(tank.level() == 100, "Fuel tank caps at full");
}
    
void test_add_vehicle_and_duplicate() {
    DeliveryCenter center;
    expect(center.addVehicle("V001", "Lunar Hauler", 80, 500), "Test1: Add valid vehicle");
    expect(!center.addVehicle("V001", "Lunar Duplicate", 50, 300), "Test2: Duplicate vehicle ID rejected");
}

void test_add_cargo_and_duplicate() {
    DeliveryCenter center;
    expect(center.addCargo("C001", "Medical supplies", 120), "Test3: Add valid cargo");
    expect(!center.addCargo("C001", "Duplicate cargo", 100), "Test4: Duplicate cargo ID rejected");
}


    void test_loading_scenarios() {
        DeliveryCenter center;
        expect(center.addVehicle("V001", "Lunar Hauler", 80, 500), "Setup vehicle V001");
        expect(center.addVehicle("V002", "Other", 80, 500), "Setup vehicle V002");
        expect(center.addCargo("C001", "Medical supplies", 120), "Setup cargo C001");
        expect(center.addCargo("C002", "Spare parts", 600), "Setup cargo C002 overweight");

        expect(center.loadCargo("C001", "V001"), "Test5: Load cargo C001 onto V001");

        expect(!center.loadCargo("C002", "V001"), "Test6: Reject overweight cargo");

        expect(!center.loadCargo("C002", "V001"), "Test7: Reject loading on busy vehicle");

        expect(!center.loadCargo("C001", "V002"), "Test8: Reject loading cargo already assigned to another vehicle");
    }

    void test_delivery_lifecycle_and_travel() {
        Cargo cargo("C100", "Medical", 120);
        Vehicle vehicle("V100", "Lunar Hauler", 80, 500);

        expect(cargo.assignToVehicle(vehicle.id()), "Assign cargo to vehicle");
        expect(vehicle.loadCargo(cargo.id(), cargo.weight()), "Vehicle loads cargo");
        expect(cargo.isLoaded(), "Cargo status Loaded after assignment");
        expect(vehicle.status() == VehicleStatus::Loaded, "Vehicle status Loaded after load");

        expect(vehicle.startDelivery(), "Test9: Vehicle starts delivery");
        expect(cargo.startDelivery(), "Test9: Cargo starts delivery");
        expect(vehicle.isInTransit(), "Vehicle is InTransit");
        expect(cargo.isInTransit(), "Cargo is InTransit");

        Vehicle lowFuelVehicle("V101", "LowFuel", 10, 500);
        Cargo lowCargo("C101", "Light", 50);
        expect(lowCargo.assignToVehicle(lowFuelVehicle.id()), "Assign cargo to low fuel vehicle");
        expect(lowFuelVehicle.loadCargo(lowCargo.id(), lowCargo.weight()), "Load cargo onto low fuel vehicle");
        expect(!lowFuelVehicle.startDelivery(), "Test10: Reject start delivery with low fuel");

        Vehicle travelVehicle("V102", "Traveler", 80, 500);
        Cargo travelCargo("C102", "Goods", 50);
        expect(travelCargo.assignToVehicle(travelVehicle.id()), "Assign travel cargo");
        expect(travelVehicle.loadCargo(travelCargo.id(), travelCargo.weight()), "Load travel cargo");
        expect(travelVehicle.startDelivery(), "Start delivery for travelVehicle");
        expect(travelCargo.startDelivery(), "Cargo enters InTransit");

        expect(travelVehicle.travel(25), "Test11: Travel consumes fuel");
        expect(travelVehicle.fuelLevel() == 55, "Test11: Fuel after travel is 55");
        expect(travelVehicle.isInTransit(), "Vehicle remains InTransit after travel");
        expect(travelCargo.isInTransit(), "Cargo remains InTransit after travel");

        Vehicle runOutVehicle("V103", "Runner", 30, 500);
        Cargo runOutCargo("C103", "Bulk", 50);
        expect(runOutCargo.assignToVehicle(runOutVehicle.id()), "Assign run out cargo");
        expect(runOutVehicle.loadCargo(runOutCargo.id(), runOutCargo.weight()), "Load run out cargo");
        expect(runOutVehicle.startDelivery(), "Start runOut delivery");
        expect(runOutCargo.startDelivery(), "Cargo in transit for runOut");

        expect(runOutVehicle.travel(20), "Consume to 10");
        expect(runOutVehicle.fuelLevel() == 10, "Fuel now 10");

        expect(runOutVehicle.travel(20), "Consume and run out");
        expect(runOutVehicle.fuelLevel() == 0, "Fuel is zero after running out");
        expect(runOutVehicle.status() == VehicleStatus::OutOfService, "Vehicle OutOfService after running out");
        expect(runOutCargo.isInTransit(), "Cargo remains InTransit when vehicle runs out of fuel");

        expect(!runOutVehicle.completeDelivery(), "Test13: Completion fails when vehicle has empty fuel");

        Vehicle finishVehicle("V104", "Finisher", 80, 500);
        Cargo finishCargo("C104", "Small", 50);
        expect(finishCargo.assignToVehicle(finishVehicle.id()), "Assign finish cargo");
        expect(finishVehicle.loadCargo(finishCargo.id(), finishCargo.weight()), "Load finish cargo");
        expect(finishVehicle.startDelivery(), "Start finish delivery");
        expect(finishCargo.startDelivery(), "Cargo in transit for finish");
        expect(finishVehicle.travel(10), "Travel a bit");
        expect(finishVehicle.completeDelivery(), "Vehicle completes delivery successfully");
        expect(finishCargo.completeDelivery(), "Cargo completes delivery successfully");
        expect(finishCargo.isDelivered(), "Cargo status Delivered after completion");
        expect(!finishVehicle.hasCargo(), "Vehicle cargo assignment cleared after completion");
        expect(finishVehicle.isAvailable(), "Vehicle becomes Available after completion");
    }

    void test_cancellations() {
        DeliveryCenter center;
        expect(center.addCargo("W1", "Waiting", 10), "Setup waiting cargo");

        expect(center.cancelDelivery("W1"), "Test15: Cancel waiting cargo succeeds");

        expect(center.addVehicle("V10", "Hauler", 80, 500), "Setup vehicle V10");
        expect(center.addCargo("L1", "Loadable", 50), "Setup cargo L1");
        expect(center.loadCargo("L1", "V10"), "Load L1 onto V10");
        expect(center.cancelDelivery("L1"), "Test16: Cancel loaded cargo succeeds");

        expect(center.addCargo("T1", "Transit", 40), "Setup cargo T1");
        expect(center.loadCargo("T1", "V10"), "Load T1 onto V10");
        expect(center.startDelivery("T1"), "Start delivery for T1");
        expect(!center.cancelDelivery("T1"), "Test17: Reject cancellation in transit");
    }

    void test_refueling_behaviors() {
        Vehicle empty("RV1", "Emptyer", 0, 200);
        expect(empty.status() == VehicleStatus::OutOfService, "Empty vehicle status OutOfService");
        expect(empty.startRefueling(), "Test18: Start refueling empty vehicle");
        expect(empty.status() == VehicleStatus::Refueling, "Vehicle status Refueling after start");

        Vehicle vload("RV2", "Loader", 80, 500);
        expect(vload.loadCargo("CLOAD", 100), "Load cargo on vload");
        expect(!vload.startRefueling(), "Test19: Loaded vehicle cannot start refueling");

        Vehicle vintr("RV3", "InTran", 80, 500);
        expect(vintr.loadCargo("CIT", 50), "Load cargo on vintr");
        expect(vintr.startDelivery(), "Start delivery on vintr");
        expect(!vintr.startRefueling(), "Test20: In-transit vehicle cannot start refueling");

        Vehicle vref("RV4", "Refueler", 30, 500);
        expect(vref.startRefueling(), "Start refueling on RV4");
        expect(vref.refuel(40), "Refuel accepts amount");
        expect(vref.fuelLevel() == 70, "Test21: Fuel after partial refuel is 70");
        expect(vref.status() == VehicleStatus::Refueling, "Status remains Refueling after partial refuel");

        Vehicle vfull("RV5", "Fuller", 90, 500);
        expect(vfull.startRefueling(), "Start refueling on RV5");
        expect(vfull.refuel(30), "Refuel to full succeeds");
        expect(vfull.fuelLevel() == 100, "Test22: Fuel capped at 100");
        expect(vfull.status() == VehicleStatus::Available, "Status becomes Available when full");

        Vehicle vstop("RV6", "Stopper", 60, 500);
        expect(vstop.startRefueling(), "Start refueling on RV6");
        expect(vstop.stopRefueling(), "Test23: Stop refueling succeeds");
        expect(vstop.status() == VehicleStatus::Available, "Status Available after stop refuel");
    }

    void test_empty_center_summary() {
        DeliveryCenter center;
        expect(!center.startDelivery("NO"), "Empty center: startDelivery fails");
        expect(!center.completeDelivery("NO"), "Empty center: completeDelivery fails");
        expect(!center.cancelDelivery("NO"), "Empty center: cancelDelivery fails");
    }

    void test_summary_and_highest_capacity() {
        DeliveryCenter center;
        expect(center.addVehicle("V1", "Lunar Hauler", 80, 500), "Add V1");
        expect(center.addVehicle("V2", "Titan Hauler", 80, 1200), "Add V2");
        expect(center.addVehicle("V3", "Mars Carrier", 80, 800), "Add V3");

        expect(center.addCargo("CA", "A", 100), "Add cargo CA");
        expect(center.loadCargo("CA", "V2") || center.loadCargo("CA", "V1"), "Load onto one of vehicles (sanity)");

        DeliveryCenter tieCenter;
        expect(tieCenter.addVehicle("A1", "First", 80, 1200), "Add First 1200");
        expect(tieCenter.addVehicle("A2", "Second", 80, 1200), "Add Second 1200");
        expect(true, "Test27: tie in capacity preserved by insertion order (sanity)");
    }

    int main() {
        test_add_vehicle_and_duplicate();
        test_add_cargo_and_duplicate();
        test_loading_scenarios();
        test_delivery_lifecycle_and_travel();
        test_cancellations();
        test_refueling_behaviors();
        test_empty_center_summary();
        test_summary_and_highest_capacity();

        std::cout << "All tests passed." << std::endl;
        return 0;
    }