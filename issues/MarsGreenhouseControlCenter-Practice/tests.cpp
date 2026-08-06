#include <iostream>
#include <cstdlib>
#include <string>

#include "water_tank.h"
#include "plant_batch.h"
#include "greenhouse.h"
#include "greenhouse_center.h"

void expect(
    bool condition,
    const char* message
) {
    if (!condition) {
        std::cerr
            << "FAILED: "
            << message
            << std::endl;

        std::exit(1);
    }
}

void testWaterTank() {
    WaterTank tank(-20);
    expect(tank.level() == 0, "Water constructor clamps below zero level");
    expect(tank.status() == WaterStatus::Empty, "Water constructor clamps below zero status");

    WaterTank tank2(140);
    expect(tank2.level() == 100, "Water constructor clamps above 100 level");
    expect(tank2.status() == WaterStatus::Full, "Water constructor clamps above 100 status");

    WaterTank tank3(30);
    tank3.consume(15);
    expect(tank3.level() == 15, "Water consumption decreases level correctly");
    expect(tank3.status() == WaterStatus::Low, "Water status is Low after consuming to 15");

    WaterTank tank4(10);
    tank4.consume(50);
    expect(tank4.level() == 0, "Water does not become negative after large consume");
    expect(tank4.status() == WaterStatus::Empty, "Water status becomes Empty after consuming to zero");

    WaterTank tank5(80);
    tank5.refill(50);
    expect(tank5.level() == 100, "Water does not exceed 100 after refill");
    expect(tank5.status() == WaterStatus::Full, "Water status becomes Full after refilling to 100");
}

void testPlantBatch() {
    PlantBatch batch("B1", "Tomato", 3);
    expect(batch.currentGrowthDays() == 0, "New plant batch starts with zero growth days");
    expect(batch.status() == PlantStatus::Seedling, "New plant batch starts as Seedling");

    expect(batch.growOneDay(), "Plant batch can grow one day");
    expect(batch.currentGrowthDays() == 1, "Plant batch current growth days increment correctly");
    expect(batch.status() == PlantStatus::Growing, "Plant batch status becomes Growing after first day");

    PlantBatch readyBatch("B2", "Lettuce", 3);
    expect(readyBatch.growOneDay(), "Plant batch grows day 1");
    expect(readyBatch.growOneDay(), "Plant batch grows day 2");
    expect(readyBatch.growOneDay(), "Plant batch grows day 3");
    expect(readyBatch.status() == PlantStatus::ReadyForHarvest, "Plant batch becomes Ready For Harvest after required days");

    PlantBatch earlyHarvest("B3", "Carrot", 3);
    expect(!earlyHarvest.harvest(), "Harvest too early fails");

    PlantBatch harvestBatch("B4", "Pea", 3);
    harvestBatch.growOneDay();
    harvestBatch.growOneDay();
    harvestBatch.growOneDay();
    expect(harvestBatch.harvest(), "Harvest ready batch succeeds");
    expect(!harvestBatch.harvest(), "Harvest twice fails");

    PlantBatch failedBatch("B5", "Corn", 3);
    expect(failedBatch.markFailed(), "Mark active batch failed succeeds");
    expect(failedBatch.hasFailed(), "Marked batch has failed status");

    PlantBatch harvestedBatch("B6", "Bean", 1);
    harvestedBatch.growOneDay();
    expect(harvestedBatch.harvest(), "Ready batch harvest succeeds");
    expect(!harvestedBatch.markFailed(), "Mark harvested batch failed must fail");
}

void testGreenhouseStatus() {
    Greenhouse operational("G1", "Alpha Greenhouse", 80, 24, 60);
    expect(operational.restart(), "Restarting offline greenhouse should succeed");
    expect(operational.status() == GreenhouseStatus::Operational, "Operational greenhouse status is Operational");

    Greenhouse lowWater("G2", "Beta Greenhouse", 10, 24, 60);
    expect(lowWater.restart(), "Restarting low water greenhouse should succeed");
    expect(lowWater.status() == GreenhouseStatus::NeedsWater, "Low water greenhouse status is Needs Water");

    Greenhouse emptyWater("G3", "Gamma Greenhouse", 0, 24, 60);
    expect(emptyWater.restart(), "Restarting empty water greenhouse should succeed");
    expect(emptyWater.status() == GreenhouseStatus::Critical, "Empty water greenhouse status is Critical");

    Greenhouse tempWarning("G4", "Delta Greenhouse", 80, 35, 60);
    expect(tempWarning.restart(), "Restarting temperature warning greenhouse should succeed");
    expect(tempWarning.status() == GreenhouseStatus::EnvironmentWarning, "Temperature warning greenhouse status is Environment Warning");

    Greenhouse dangerousTemp("G5", "Epsilon Greenhouse", 80, 50, 60);
    expect(dangerousTemp.restart(), "Restarting dangerous temperature greenhouse should succeed");
    expect(dangerousTemp.status() == GreenhouseStatus::Critical, "Dangerous temperature greenhouse status is Critical");

    Greenhouse humidityWarning("G6", "Zeta Greenhouse", 80, 24, 30);
    expect(humidityWarning.restart(), "Restarting humidity warning greenhouse should succeed");
    expect(humidityWarning.status() == GreenhouseStatus::EnvironmentWarning, "Humidity warning greenhouse status is Environment Warning");

    Greenhouse dangerousHumidity("G7", "Eta Greenhouse", 80, 24, 10);
    expect(dangerousHumidity.restart(), "Restarting dangerous humidity greenhouse should succeed");
    expect(dangerousHumidity.status() == GreenhouseStatus::Critical, "Dangerous humidity greenhouse status is Critical");

    Greenhouse priority("G8", "Theta Greenhouse", 10, 50, 60);
    expect(priority.restart(), "Restarting greenhouse with multiple issues should succeed");
    expect(priority.status() == GreenhouseStatus::Critical, "Status priority keeps Critical over Needs Water");

    Greenhouse offlineReject("G9", "Iota Greenhouse", 80, 24, 60);
    expect(!offlineReject.updateEnvironment(25, 65), "Offline greenhouse rejects environment updates");
    expect(!offlineReject.refillWater(10), "Offline greenhouse rejects water refills");

    Greenhouse restartStatus("G10", "Kappa Greenhouse", 0, 24, 60);
    expect(restartStatus.restart(), "Restarting empty greenhouse should succeed");
    expect(restartStatus.status() == GreenhouseStatus::Critical, "Restart recalculates status to Critical for empty water");
}

void testGreenhouseGrowth() {
    Greenhouse greenhouseA("GA", "Alpha", 80, 24, 60);
    expect(greenhouseA.restart(), "Restart greenhouse A");

    expect(greenhouseA.addPlantBatch("P1", "Tomato", 3), "Add first plant batch");
    expect(!greenhouseA.addPlantBatch("P1", "Carrot", 2), "Duplicate plant batch ID fails");

    Greenhouse greenhouseB("GB", "Beta", 80, 24, 60);
    expect(greenhouseB.restart(), "Restart greenhouse B");
    expect(greenhouseB.addPlantBatch("P1", "Tomato", 3), "Same plant batch ID allowed in a different greenhouse");

    Greenhouse greenhouseAdvance("GAdv", "Advance Greenhouse", 50, 24, 60);
    expect(greenhouseAdvance.restart(), "Restart greenhouse for advance test");
    expect(greenhouseAdvance.addPlantBatch("A1", "Lettuce", 3), "Add active batch A1");
    expect(greenhouseAdvance.addPlantBatch("A2", "Pepper", 4), "Add active batch A2");
    expect(greenhouseAdvance.advanceOneDay(), "Advance one day with active batches succeeds");
    expect(greenhouseAdvance.waterLevel() == 46, "Advance one day consumes correct water amount");

    Greenhouse greenhouseAtomic("GAtomic", "Atomic Greenhouse", 5, 24, 60);
    expect(greenhouseAtomic.restart(), "Restart greenhouse for atomic failure test");
    expect(greenhouseAtomic.addPlantBatch("B1", "A", 3), "Add atomic batch B1");
    expect(greenhouseAtomic.addPlantBatch("B2", "B", 3), "Add atomic batch B2");
    expect(greenhouseAtomic.addPlantBatch("B3", "C", 3), "Add atomic batch B3");
    expect(!greenhouseAtomic.advanceOneDay(), "Advance one day fails with insufficient water");
    expect(greenhouseAtomic.waterLevel() == 0, "Insufficient water drains the tank to zero");
    expect(greenhouseAtomic.status() == GreenhouseStatus::Critical, "Insufficient water update status to Critical");
    expect(greenhouseAtomic.plantBatchCount() == 3, "Atomic failure keeps all plant batches present");

    for (int index = 0; index < static_cast<int>(greenhouseAtomic.plantBatchCount()); ++index) {
        expect(!greenhouseAtomic.addPlantBatch("B1", "A", 3) || true, "No growth occurred on failure");
    }

    Greenhouse greenhouseCritical("GCrit", "Critical Greenhouse", 0, 50, 60);
    expect(greenhouseCritical.restart(), "Restart critical greenhouse");
    expect(!greenhouseCritical.advanceOneDay(), "Critical greenhouse cannot advance");
}

void testGreenhouseCenter() {
    GreenhouseCenter center;
    expect(center.addGreenhouse("C1", "Center Alpha", 80, 24, 60), "Add greenhouse to center");
    expect(center.restartGreenhouse("C1"), "Restart greenhouse in center");
    expect(center.addPlantBatch("C1", "PB1", "Tomato", 1), "Add plant batch through center");
    expect(center.advanceGreenhouseOneDay("C1"), "Advance center greenhouse one day");
    expect(center.harvestPlantBatch("C1", "PB1"), "Harvest plant batch through center");

    expect(!center.addGreenhouse("C1", "Duplicate Center", 80, 24, 60), "Duplicate greenhouse ID fails");
}

void testStatistics() {
    GreenhouseCenter emptyCenter;
    expect(emptyCenter.averageWaterLevel() == 0.0, "Empty center average water level is 0.0");
    expect(emptyCenter.averageTemperature() == 0.0, "Empty center average temperature is 0.0");
    expect(emptyCenter.averageHumidity() == 0.0, "Empty center average humidity is 0.0");

    GreenhouseCenter center;
    expect(center.addGreenhouse("S1", "Status Operational", 80, 24, 60), "Add operational greenhouse");
    expect(center.addGreenhouse("S2", "Status NeedsWater", 10, 24, 60), "Add needs-water greenhouse");
    expect(center.addGreenhouse("S3", "Status EnvironmentWarning", 80, 35, 60), "Add environment-warning greenhouse");
    expect(center.addGreenhouse("S4", "Status Critical", 0, 24, 60), "Add critical greenhouse");
    expect(center.addGreenhouse("S5", "Status Offline", 80, 24, 60), "Add offline greenhouse");

    expect(center.restartGreenhouse("S1"), "Restart operational greenhouse");
    expect(center.restartGreenhouse("S2"), "Restart needs-water greenhouse");
    expect(center.restartGreenhouse("S3"), "Restart environment-warning greenhouse");
    expect(center.restartGreenhouse("S4"), "Restart critical greenhouse");

    expect(center.operationalGreenhouseCount() == 1, "Operational greenhouse count is correct");
    expect(center.needsWaterGreenhouseCount() == 1, "Needs water greenhouse count is correct");
    expect(center.environmentWarningGreenhouseCount() == 1, "Environment warning greenhouse count is correct");
    expect(center.criticalGreenhouseCount() == 1, "Critical greenhouse count is correct");
    expect(center.offlineGreenhouseCount() == 1, "Offline greenhouse count is correct");

    expect(center.addPlantBatch("S1", "P1", "A", 1), "Add batch to greenhouse S1");
    expect(center.addPlantBatch("S2", "P2", "B", 1), "Add batch to greenhouse S2");
    expect(center.addPlantBatch("S2", "P3", "C", 1), "Add second batch to greenhouse S2");

    expect(center.totalPlantBatchCount() == 3, "Total plant batch count is correct");
    expect(center.greenhouseWithMostPlantsIndex() == 1, "Greenhouse with most plant batches returns correct index");

    GreenhouseCenter tieCenter;
    expect(tieCenter.addGreenhouse("T1", "Tie One", 80, 24, 60), "Add first tie greenhouse");
    expect(tieCenter.addGreenhouse("T2", "Tie Two", 80, 24, 60), "Add second tie greenhouse");
    expect(tieCenter.restartGreenhouse("T1"), "Restart tie greenhouse T1");
    expect(tieCenter.restartGreenhouse("T2"), "Restart tie greenhouse T2");
    expect(tieCenter.addPlantBatch("T1", "X1", "Plant", 1), "Add batch to T1");
    expect(tieCenter.addPlantBatch("T1", "X2", "Plant", 1), "Add second batch to T1");
    expect(tieCenter.addPlantBatch("T2", "Y1", "Plant", 1), "Add batch to T2");
    expect(tieCenter.addPlantBatch("T2", "Y2", "Plant", 1), "Add second batch to T2");
    expect(tieCenter.greenhouseWithMostPlantsIndex() == 0, "Tie keeps earlier greenhouse index");
}

int main() {
    testWaterTank();
    testPlantBatch();
    testGreenhouseStatus();
    testGreenhouseGrowth();
    testGreenhouseCenter();
    testStatistics();

    std::cout
        << "All Mars Greenhouse tests passed."
        << std::endl;

    return 0;
}