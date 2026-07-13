#include <iostream>
#include <string>

enum class RobotMode {
    Manual,
    LineFollowing,
    ObstacleAvoidance,
    EmergencyStop
};

std::string robotModeToString(RobotMode mode) {
    switch (mode) {
        case RobotMode::Manual:
            return "Manual";

        case RobotMode::LineFollowing:
            return "Line Following";

        case RobotMode::ObstacleAvoidance:
            return "Obstacle Avoidance";

        case RobotMode::EmergencyStop:
            return "Emergency Stop";

        default:
            return "Unknown";
    }
}

void printModeDescription(RobotMode mode) {
    switch (mode) {
        case RobotMode::Manual:
            std::cout << "The robot waits for user commands." << std::endl;
            break;

        case RobotMode::LineFollowing:
            std::cout << "The robot uses line sensors to move." << std::endl;
            break;

        case RobotMode::ObstacleAvoidance:
            std::cout << "The robot uses distance sensor to avoid obstacles." << std::endl;
            break;

        case RobotMode::EmergencyStop:
            std::cout << "The robot stops all motors immediately." << std::endl;
            break;

        default:
            std::cout << "Unknown mode." << std::endl;
            break;
    }
}

int main() {
    RobotMode mode = RobotMode::LineFollowing;

    std::cout << "Current mode: " << robotModeToString(mode) << std::endl;
    printModeDescription(mode);

    mode = RobotMode::EmergencyStop;

    std::cout << "Current mode: " << robotModeToString(mode) << std::endl;
    printModeDescription(mode);

    return 0;
}