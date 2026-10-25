#include "delivery_center.h"
#include "cargo.h"
#include "vehicle.h"
#include "utils.h"
#include <iostream>

enum class MenuChoice {
    AddVehicle = 1,
    AddCargo,
    LoadCargo,
    StartDelivery,
    Travel,
    CompleteDelivery,
    CancelDelivery,
    StartRefueling,
    RefuelVehicle,
    StopRefueling,
    ShowVehicle,
    ShowCargo,
    ShowAllVehicles,
    ShowAllCargo,
    ShowSummary,
    Exit
};

MenuChoice readMenuChoice() {
    int choice = readIntInRange(
        "\nMenu choice (1-16):\n"
        "1 = Add Vehicle\n"
        "2 = Add Cargo\n"
        "3 = Load Cargo\n"
        "4 = Start Delivery\n"
        "5 = Travel\n"
        "6 = Complete Delivery\n"
        "7 = Cancel Delivery\n"
        "8 = Start Refueling\n"
        "9 = Refuel Vehicle\n"
        "10 = Stop Refueling\n"
        "11 = Show Vehicle\n"
        "12 = Show Cargo\n"
        "13 = Show All Vehicles\n"
        "14 = Show All Cargo\n"
        "15 = Show Summary\n"
        "16 = Exit\n"
        "Choose: ",
        1,
        16
    );

    switch (choice) {
        case 1:
            return MenuChoice::AddVehicle;

        case 2:
            return MenuChoice::AddCargo;

        case 3:
            return MenuChoice::LoadCargo;

        case 4:
            return MenuChoice::StartDelivery;

        case 5:
            return MenuChoice::Travel;

        case 6:
            return MenuChoice::CompleteDelivery;

        case 7:
            return MenuChoice::CancelDelivery;

        case 8:
            return MenuChoice::StartRefueling;

        case 9:
            return MenuChoice::RefuelVehicle;

        case 10:
            return MenuChoice::StopRefueling;

        case 11:
            return MenuChoice::ShowVehicle;

        case 12:
            return MenuChoice::ShowCargo;

        case 13:
            return MenuChoice::ShowAllVehicles;

        case 14:
            return MenuChoice::ShowAllCargo;

        case 15:
            return MenuChoice::ShowSummary;

        default:
            return MenuChoice::Exit;
    }
}

void printMenu() {
    std::cout << "\n===== Space Cargo Delivery Center =====" << std::endl;
    std::cout << "1. Add vehicle" << std::endl;
    std::cout << "2. Add cargo" << std::endl;
    std::cout << "3. Load cargo" << std::endl;
    std::cout << "4. Start delivery" << std::endl;
    std::cout << "5. Travel" << std::endl;
    std::cout << "6. Complete delivery" << std::endl;
    std::cout << "7. Cancel delivery" << std::endl;
    std::cout << "8. Start refueling" << std::endl;
    std::cout << "9. Refuel vehicle" << std::endl;
    std::cout << "10. Stop refueling" << std::endl;
    std::cout << "11. Show one vehicle" << std::endl;
    std::cout << "12. Show one cargo" << std::endl;
    std::cout << "13. Show all vehicles" << std::endl;
    std::cout << "14. Show all cargo" << std::endl;
    std::cout << "15. Show center summary" << std::endl;
    std::cout << "16. Exit" << std::endl;
}

int main() {
    DeliveryCenter deliveryCenter;
    bool running = true;

    while(running) {
        printMenu();
        int choiceValue = readIntInRange("Choose: ", 1, 16);
        MenuChoice choice = static_cast<MenuChoice>(choiceValue);

        switch(choice) {
            case MenuChoice::AddVehicle: {
                Vehicle vehicle = createVehicle();

                if (deliveryCenter.findVehicleIndexById(vehicle.id()) != -1) {
                    std::cout << "Vehicle could not be added." << std::endl;
                } else if (deliveryCenter.addVehicle(vehicle.id(), vehicle.name(), vehicle.fuelLevel(), vehicle.maximumCargoWeight())) {
                    std::cout << "Vehicle added successfully." << std::endl;
                } else {
                    std::cout << "Vehicle could not be added." << std::endl;
                }
                break;
            }    

            case MenuChoice::AddCargo: {
                Cargo cargo = createCargo();

                if (deliveryCenter.findCargoIndexById(cargo.id()) != -1) {
                    std::cout << "Cargo could not be added." << std::endl;
                } else if (deliveryCenter.addCargo(cargo.id(), cargo.description(), cargo.weight())) {
                    std::cout << "Cargo added successfully." << std::endl;
                } else {
                    std::cout << "Cargo could not be added." << std::endl;
                }
                break;
            }

            case MenuChoice::LoadCargo: {
                std::string cargoID = readNonEmptyWord("Enter Cargo ID ");
                std::string vehicleID = readNonEmptyWord("Enter Vehicle ID ");

                if(deliveryCenter.loadCargo(cargoID, vehicleID)) {
                    std::cout << "Cargo loaded successfully." << std::endl;
                } else {
                    std::cout << "Failed to load cargo." << std::endl;
                }
                break;
            }

            case MenuChoice::StartDelivery: {
                std::string cargoID = readNonEmptyWord("Enter Cargo ID ");

                if(deliveryCenter.startDelivery(cargoID)) {
                    std::cout << "Start Delivery Successfully." << std::endl;
                } else {
                    std::cout << "Failed to start delivery" << std::endl;
                }
                break;
            }

            case MenuChoice::Travel: {
                std::string cargoID = readNonEmptyWord("Enter Cargo ID ");
                int fuelAmount = readIntInRange("Please enter the fuel amount: ", 0, 100);

                if(deliveryCenter.travel(cargoID, fuelAmount)) {
                    std::cout << "Travel successfully." << std::endl;
                } else {
                    std::cout << "Failed to travel." << std::endl;
                }
                break;
            }

            case MenuChoice::CompleteDelivery: {
                std::string cargoID = readNonEmptyWord("Enter Cargo ID ");

                if(deliveryCenter.completeDelivery(cargoID)) {
                    std::cout << "Complete delivery successfully." << std::endl;
                } else {
                    std::cout << "Failed to complete delivery." << std::endl;
                }
                break;
            }

            case MenuChoice::CancelDelivery: {
                std::string cargoID = readNonEmptyWord("Enter Cargo ID ");

                if(deliveryCenter.cancelDelivery(cargoID)) {
                    std::cout << "Cancel delivery successfully." << std::endl;
                } else {
                    std::cout << "Failed to cancel delivery." << std::endl;
                }
                break;
            }

            case MenuChoice::StartRefueling: {
                std::string vehicleID = readNonEmptyWord("Enter Vehicle ID ");

                if(deliveryCenter.startVehicleRefueling(vehicleID)) {
                    std::cout << "Start refueling successfully." << std::endl;
                } else {
                    std::cout << "Failed to start refueling." << std::endl;
                }
                break;
            }

            case MenuChoice::RefuelVehicle: {
                std::string vehicleID = readNonEmptyWord("Enter Vehicle ID ");
                int amount = readIntInRange("Please enter the amount you want to refuel.", 0, 100);

                if(deliveryCenter.refuelVehicle(vehicleID, amount)) {
                    std::cout << "Refuel vehicle successfully." << std::endl;
                } else {
                    std::cout << "Failed to refuel vehicle." << std::endl;
                }
                break;
            }

            case MenuChoice::StopRefueling: {
                std::string vehicleID = readNonEmptyWord("Enter Vehicle ID ");

                if(deliveryCenter.stopVehicleRefueling(vehicleID)) {
                    std::cout << "Stop refueling successfully." << std::endl;
                } else {
                    std::cout << "Failed to stop refueling." << std::endl;
                }
                break;
            }

            case MenuChoice::ShowVehicle: {
                std::string vehicleID = readNonEmptyWord("Enter Vehicle ID ");

                if(deliveryCenter.printVehicle(vehicleID)) {
                    std::cout << "Print vehicle successfully." << std::endl;
                } else {
                    std::cout << "Failed to print vehicle (No vehicle exist)." << std::endl;
                }
                break;
            }

            case MenuChoice::ShowCargo: {
                std::string cargoID = readNonEmptyWord("Enter Cargo ID ");

                if(deliveryCenter.printCargo(cargoID)) {
                    std::cout << "Print cargo successfully." << std::endl;
                } else {
                    std::cout << "Failed to print cargo (No cargo exist)." << std::endl;
                }
                break;
            }

            case MenuChoice::ShowAllVehicles: {
                deliveryCenter.printAllVehicles();
                break;
            }

            case MenuChoice::ShowAllCargo: {
                deliveryCenter.printAllCargo();
                break;
            }

            case MenuChoice::ShowSummary: {
                deliveryCenter.printSummary();
                break;
            }

            case MenuChoice::Exit:
                std::cout << "Exiting the Program..." << std::endl;
                running = false;
                break;

            default:
                std::cout << "Unknown menu choice." << std::endl;
                break;
        }
    }
    
    return 0;
}