#include "inventory.h"

#include <iostream>

#include "utils.h"

Inventory createInitialInventory() {
    Inventory inventory;
    inventory.oxygen = readIntInRange("Initial oxygen: ", 0, 10000);
    inventory.water = readIntInRange("Initial water: ", 0, 10000);
    inventory.food = readIntInRange("Initial food: ", 0, 10000);
    return inventory;
}

void printInventory(const Inventory& inventory) {
    std::cout << "===== Base Inventory =====" << std::endl;
    std::cout << "Oxygen: " << inventory.oxygen << std::endl;
    std::cout << "Water: " << inventory.water << std::endl;
    std::cout << "Food: " << inventory.food << std::endl;
}

void restockInventory(Inventory& inventory) {
    std::cout << "Current oxygen: " << inventory.oxygen << std::endl;
    int oxygenAdded = readIntInRange("Add oxygen: ", 0, 10000);
    inventory.oxygen += oxygenAdded;

    std::cout << "Current water: " << inventory.water << std::endl;
    int waterAdded = readIntInRange("Add water: ", 0, 10000);
    inventory.water += waterAdded;

    std::cout << "Current food: " << inventory.food << std::endl;
    int foodAdded = readIntInRange("Add food: ", 0, 10000);
    inventory.food += foodAdded;
}

bool hasEnoughResources(
    const Inventory& inventory,
    int requiredOxygen,
    int requiredWater,
    int requiredFood
) {
    return inventory.oxygen >= requiredOxygen
        && inventory.water >= requiredWater
        && inventory.food >= requiredFood;
}

void consumeResources(Inventory& inventory, int oxygen, int water, int food) {
    inventory.oxygen = (inventory.oxygen >= oxygen) ? inventory.oxygen - oxygen : 0;
    inventory.water = (inventory.water >= water) ? inventory.water - water : 0;
    inventory.food = (inventory.food >= food) ? inventory.food - food : 0;
}
