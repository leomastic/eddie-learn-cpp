#include "robot.h"
#include "technician.h"
#include "maintenance_center.h"
#include "utils.h"
#include <iostream>

MenuChoice readMenuChoice() {
    int choice = readIntInRange(
        "\nMenu choice (1-16):\n"
        "1 = Add Robot\n"
        "2 = Add Technician\n"
        "3 = Report Robot Error\n"
        "4 = Add Operating Hours\n"
        "5 = Assign Maintenance\n"
        "6 = Complete Maintenance\n"
        "7 = Start Charging\n"
        "8 = Charge Robot\n"
        "9 = Stop Charging\n"
        "10 = Consume Battery\n"
        "11 = Show Robot\n"
        "12 = Show Technician\n"
        "13 = Show All Robots\n"
        "14 = Show All Technicians\n"
        "15 = Show Summary\n"
        "16 = Exit\n"
        "Choose: ",
        1,
        16
    );

    switch (choice) {
        case 1:
            return MenuChoice::AddRobot;

        case 2:
            return MenuChoice::AddTechnician;

        case 3:
            return MenuChoice::ReportRobotError;

        case 4:
            return MenuChoice::AddOperatingHours;

        case 5:
            return MenuChoice::AssignMaintenance;

        case 6:
            return MenuChoice::CompleteMaintenance;

        case 7:
            return MenuChoice::StartCharging;

        case 8:
            return MenuChoice::ChargeRobot;

        case 9:
            return MenuChoice::StopCharging;

        case 10:
            return MenuChoice::ConsumeBattery;

        case 11:
            return MenuChoice::ShowRobot;

        case 12:
            return MenuChoice::ShowTechnician;

        case 13:
            return MenuChoice::ShowAllRobots;

        case 14:
            return MenuChoice::ShowAllTechnicians;

        case 15:
            return MenuChoice::ShowSummary;

        default:
            return MenuChoice::Exit;
    }
}

void printMenu() {
    std::cout << "\n===== Robot Maintenance Center =====" << std::endl;
    std::cout << "1. Add robot" << std::endl;
    std::cout << "2. Add technician" << std::endl;
    std::cout << "3. Report robot error" << std::endl;
    std::cout << "4. Add robot operating hours" << std::endl;
    std::cout << "5. Assign maintenance" << std::endl;
    std::cout << "6. Complete maintenance" << std::endl;
    std::cout << "7. Start robot charging" << std::endl;
    std::cout << "8. Charge robot" << std::endl;
    std::cout << "9. Stop robot charging" << std::endl;
    std::cout << "10. Consume robot battery" << std::endl;
    std::cout << "11. Show one robot" << std::endl;
    std::cout << "12. Show one technician" << std::endl;
    std::cout << "13. Show all robots" << std::endl;
    std::cout << "14. Show all technicians" << std::endl;
    std::cout << "15. Show center summary" << std::endl;
    std::cout << "16. Exit" << std::endl;
}

int main() {
    MaintenanceCenter maintenanceCenter({}, {});
    bool running = true;
    
    while (running)
    {
        printMenu();
        int choiceValue = readIntInRange("Choose: ", 1, 16);
        MenuChoice choice = static_cast<MenuChoice>(choiceValue);

        switch (choice) {
            case MenuChoice::AddRobot: {
                Robot robot = createRobot();

                if (maintenanceCenter.findRobotIndexById(robot.id()) != -1) {
                    std::cout << "Robot could not be added." << std::endl;
                } else if (maintenanceCenter.addRobot(robot.id(), robot.name(), robot.batteryLevel(), robot.operatingHours())) {
                    std::cout << "Robot added successfully." << std::endl;
                } else {
                    std::cout << "Robot could not be added." << std::endl;
                }
                break;
            }
            
            case MenuChoice::AddTechnician: {
                Technician technician = createTechnician();

                if (maintenanceCenter.findTechnicianIndexById(technician.id()) != -1) {
                    std::cout << "Technician could not be added." << std::endl;
                } else if (maintenanceCenter.addTechnician(technician.id(), technician.name())) {
                    std::cout << "Technician added successfully." << std::endl;
                } else {
                    std::cout << "Technician could not be added." << std::endl;
                }
                break;
            }

            case MenuChoice::ReportRobotError: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");
                int errorCode = readIntInRange("Enter Error Code: ", 1, 9999);

                if (maintenanceCenter.reportRobotError(robotId, errorCode)) {
                    std::cout << "Reported error successfully." << std::endl;
                } else {
                    std::cout << "Failed to report error (robot not found or invalid code)." << std::endl;
                }
                break;
            }

            case MenuChoice::AddOperatingHours: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");
                int hours = readIntInRange("Enter The Operating Hour (1 --> 2000): ", 1, 2000);

                maintenanceCenter.addRobotOperatingHours(robotId, hours);
                std::cout << "Added robot operating hours." << std::endl;
                break;
            }

            case MenuChoice::AssignMaintenance: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");
                std::string technicianId = readNonEmptyWord("Enter Technician ID: ");

                maintenanceCenter.assignMaintenance(robotId, technicianId);
                std::cout << "Assigned maintenance." << std::endl;
                break;
            }

            case MenuChoice::CompleteMaintenance: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");

                maintenanceCenter.completeMaintenance(robotId);
                std::cout << "Complete Maintenance" << std::endl;
                break;
            }

            case MenuChoice::StartCharging: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");

                maintenanceCenter.startRobotCharging(robotId);
                std::cout << "Start charging." << std::endl;
                break;
            }

            case MenuChoice::ChargeRobot: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");
                int chargeAmount = readIntInRange(
                    "Please enter charge amount (0 - 100%): ", 0, 100);

                if (maintenanceCenter.chargeRobot(robotId, chargeAmount)) {
                    std::cout << "Charged robot successfully." << std::endl;
                } else {
                    std::cout << "Failed to charge robot." << std::endl;
                }
                break;
            }

            case MenuChoice::StopCharging: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");

                maintenanceCenter.stopRobotCharging(robotId);
                std::cout << "Robot charge stopped." << std::endl;
                break;
            }

            case MenuChoice::ConsumeBattery: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");
                int consumeAmount = readIntInRange(
                    "Please enter consume amount (0 - 100%): ", 0, 100);

                if (maintenanceCenter.consumeRobotBattery(robotId, consumeAmount)) {
                    std::cout << "Battery consumed successfully." << std::endl;
                } else {
                    std::cout << "Failed to consume battery." << std::endl;
                }
                break;
            }           

            case MenuChoice::ShowRobot: {
                std::string robotId = readNonEmptyWord("Enter Robot ID: ");

                maintenanceCenter.printRobot(robotId);
                break;
            }

            case MenuChoice::ShowTechnician: {
                std::string technicainId = readNonEmptyWord("Enter Technician ID: ");

                maintenanceCenter.printTechnician(technicainId);
                break;
            }

            case MenuChoice::ShowAllRobots: {
                maintenanceCenter.printAllRobots();
                break;
            }

            case MenuChoice::ShowAllTechnicians: {
                maintenanceCenter.printAllTechnicians();
                break;
            }

            case MenuChoice::ShowSummary: {
                maintenanceCenter.printSummary();
                break;
            }

            case MenuChoice::Exit:
                std::cout << "Exiting the Program..." << std::endl;
                running = false;
                break;

            default:
                std::cout << "Unknown menu choice." << std::endl;
                break;

            return 0;
        }
    }
}