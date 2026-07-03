#include <iostream>
#include <string>
#include <vector>

struct Robot {
    std::string name;
    int batteryLevel;
    int damageLevel;
    bool isCritical;
};

void printRobotInfo(Robot r) {
    std::cout << "The robot name is: " << r.name << std::endl;
    std::cout << "The robot battery level is: " << r.batteryLevel << std::endl;
    std::cout << "The robot damage level is: " << r.damageLevel << std::endl;
    std::cout << "Is critical?: " << (r.isCritical? "True" : "False") << std::endl;
}

int main() {
    //Old way to define a robot
    //int batteryLevel;
    //std::string name;
    //bool isCritical;
    //int damageLevel;


    //New way using struct
    
    
    Robot theRobot;

    std::vector<Robot> robots;

    std::cout << "Input robot name: \n";
    std::cin >> theRobot.name;
    std::cout << "Input robot battery level: \n";
    std::cin >> theRobot.batteryLevel;
    std::cout << "Input robot damage level: \n";
    std::cin >> theRobot.damageLevel;
    std::cout << "Input robot is critical? (1 for yes, 0 for no): \n";
    std::cin >> theRobot.isCritical;
    printRobotInfo(theRobot);


    return 0;
}