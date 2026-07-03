#include <iostream>
#include <string>
#include <vector>

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue
                      << " and " << maxValue << std::endl;
            continue;
        }
        return value;
    }
}

double readDoubleInRange(std::string prompt, double minValue, double maxValue) {
    double value;

    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue
                      << " and " << maxValue << std::endl;
            continue;
        }
        return value;
    }
}

bool readYesNo(std::string prompt) {
    int v;
    while (true) {
        std::cout << prompt << " (1 = yes, 0 = no): ";
        if (!(std::cin >> v)) {
            std::cout << "Invalid input. Enter 1 for yes or 0 for no." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (v == 1) return true;
        if (v == 0) return false;
        std::cout << "Please enter 1 or 0." << std::endl;
    }
}

double calculateItemValue(int quantity, double unitPrice) {
    double total;

    total = quantity * unitPrice;

    return total;
}

double calculateTotalInventoryValue(
    std::vector<int> quantities,
    std::vector<double> unitPrices
) {
    double totalValue = 0;

    for(int i = 0; i < quantities.size(); ++i) {
        totalValue += quantities[i] * unitPrices[i];
    }

    return totalValue;
}

int findMostExpensiveItemIndex(
    std::vector<int> quantities,
    std::vector<double> unitPrices
) {
    if (quantities.empty() || unitPrices.empty()) return -1;
    int index = 0;
    double maxValue = quantities[0] * unitPrices[0];
    for (int i = 1; i < (int)quantities.size(); ++i) {
        double totalValue = quantities[i] * unitPrices[i];
        if (totalValue > maxValue) {
            maxValue = totalValue;
            index = i;
        }
    }
    return index;
}

int countLowStockItems(std::vector<int> quantities) {
    int count = 0;
    for (int quantity : quantities) {
        if (quantity < 5) ++count;
    }
    return count;
}

int countCriticalLowStockItems(
    std::vector<int> quantities,
    std::vector<bool> criticalFlags
) {
    int count = 0;
    for (int i = 0; i < (int)quantities.size() && i < (int)criticalFlags.size(); ++i) {
        if (quantities[i] < 5 && criticalFlags[i]) ++count;
    }
    return count;
}

void printInventoryReport(
    std::vector<std::string> itemNames,
    std::vector<int> quantities,
    std::vector<double> unitPrices,
    std::vector<bool> criticalFlags
) {
    std::cout << "======Inventory Report======" << std::endl;

    for(int i = 0; i < quantities.size(); ++i) {
        std::cout << "Item " << i << " | "
                  << "Name: " << itemNames[i] << " | "
                  << "Quantity: " << quantities[i] << " | "
                  << "Unit price: " << unitPrices[i] << " | "
                  << "Value: " << quantities[i] * unitPrices[i] << " | "
                  << "Critical?: " << (criticalFlags[i] ? "Yes" : "No") << " | "
                  << "Status: " << (quantities[i] < 5 ? "LOW STOCK" : "OK")
                  << std::endl;
    }
}

int main() {
    std::cout << "===== Space Cargo Inventory Manager =====" << std::endl;

    std::cout << "Manager name: ";
    std::string managerName;
    std::cin >> managerName;

    int itemCount = readIntInRange("Number of cargo items (1-10): ", 1, 10);

    std::vector<std::string> itemNames;
    std::vector<int> quantities;
    std::vector<double> unitPrices;
    std::vector<bool> criticalFlags;

    for (int item = 1; item <= itemCount; item++) {
        std::cout << std::endl;
        std::cout << "Item " << item << std::endl;

        std::cout << "Item name (no space): ";
        std::string itemName;
        std::cin >> itemName;

        int quantity = readIntInRange("Quantity (0-1000): ", 0, 1000);
        double unitPrice = readDoubleInRange("Unit price (0-10000): ", 0.0, 10000.0);
        bool isCritical = readYesNo("Is this item critical? ");

        itemNames.push_back(itemName);
        quantities.push_back(quantity);
        unitPrices.push_back(unitPrice);
        criticalFlags.push_back(isCritical);

        double itemValue = calculateItemValue(quantity, unitPrice);

        std::cout << "Item value: " << itemValue << std::endl;

        if (quantity < 5) {
            std::cout << "Status: LOW STOCK" << std::endl;
        } else {
            std::cout << "Status: OK" << std::endl;
        }

        if (isCritical && quantity < 5) {
            std::cout << "Warning: CRITICAL LOW STOCK" << std::endl;
        }
    }

    double totalValue = calculateTotalInventoryValue(quantities, unitPrices);
    int mostExpensiveIndex = findMostExpensiveItemIndex(quantities, unitPrices);
    int lowStockCount = countLowStockItems(quantities);
    int criticalLowStockCount = countCriticalLowStockItems(quantities, criticalFlags);

    std::cout << std::endl;
    std::cout << "===== Final Inventory Summary =====" << std::endl;
    std::cout << "Manager: " << managerName << std::endl;
    std::cout << "Total items: " << itemCount << std::endl;
    std::cout << "Total inventory value: " << totalValue << std::endl;
    std::cout << "Low stock items: " << lowStockCount << std::endl;
    std::cout << "Critical low stock items: " << criticalLowStockCount << std::endl;

    if (mostExpensiveIndex >= 0) {
        std::cout << "Most valuable item: "
                  << itemNames[mostExpensiveIndex]
                  << " with value "
                  << calculateItemValue(
                         quantities[mostExpensiveIndex],
                         unitPrices[mostExpensiveIndex]
                     )
                  << std::endl;
    }

    printInventoryReport(itemNames, quantities, unitPrices, criticalFlags);

    return 0;
}