#pragma once

struct Inventory {
    int oxygen;
    int water;
    int food;
};

Inventory createInitialInventory();

void printInventory(
    const Inventory& inventory
);

void restockInventory(
    Inventory& inventory
);

bool hasEnoughResources(
    const Inventory& inventory,
    int requiredOxygen,
    int requiredWater,
    int requiredFood
);

void consumeResources(
    Inventory& inventory,
    int oxygen,
    int water,
    int food
);
