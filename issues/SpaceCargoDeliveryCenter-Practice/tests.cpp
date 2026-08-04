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

void testCargo() {
    Cargo cargo("C001", "Medical supplies", 120);
    expect(cargo.isWaiting(), "New cargo starts waiting");
    expect(cargo.assignToVehicle("V001"), "Cargo can be assigned to a vehicle");
    expect(cargo.isLoaded(), "Cargo becomes loaded after assignment");
    expect(cargo.startDelivery(), "Cargo can start delivery when loaded");
    expect(cargo.isInTransit(), "Cargo becomes in transit");
    expect(cargo.completeDelivery(), "Cargo can complete delivery");
    expect(cargo.isDelivered(), "Cargo becomes delivered");
}

void testVehicle() {
    Vehicle vehicle("V001", "Lunar Hauler", 80, 500);
    expect(vehicle.isAvailable(), "Vehicle starts available");
    expect(vehicle.loadCargo("C001", 120), "Vehicle loads cargo");
    expect(vehicle.hasCargo(), "Vehicle has cargo after loading");
    expect(vehicle.startDelivery(), "Vehicle starts delivery");
    expect(vehicle.isInTransit(), "Vehicle becomes in transit");
    expect(vehicle.completeDelivery(), "Vehicle completes delivery");
    expect(vehicle.isAvailable(), "Vehicle becomes available after completion");
    expect(!vehicle.hasCargo(), "Vehicle cargo assignment clears");
}

void testDeliveryCenter() {
    DeliveryCenter center;

    expect(center.addVehicle("V001", "Lunar Hauler", 80, 500), "Add valid vehicle");
    expect(!center.addVehicle("V001", "Duplicate", 40, 300), "Reject duplicate vehicle ID");

    expect(center.addCargo("C001", "Medical supplies", 120), "Add valid cargo");
    expect(!center.addCargo("C001", "Duplicate", 100), "Reject duplicate cargo ID");

    expect(center.loadCargo("C001", "V001"), "Load cargo onto vehicle");
    expect(center.startDelivery("C001"), "Start delivery successfully");
    expect(center.travel("C001", 25), "Travel successfully");
    expect(center.completeDelivery("C001"), "Complete delivery successfully");

    expect(!center.cancelDelivery("C001"), "Cancellation should fail after delivery completes");
}

int main() {
    testFuelTank();
    testCargo();
    testVehicle();
    testDeliveryCenter();

    std::cout << "All tests passed." << std::endl;
    return 0;
}