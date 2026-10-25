#include <iostream>
#include <string>

enum class RobotState {
    Idle,
    Searching,
    MovingToVictim,
    RescuingVictim,
    ReturningToBase,
    EmergencyStopped
};

std::string robotStateToString(RobotState state) {
    switch (state) {
        case RobotState::Idle:
            return "Idle";

        case RobotState::Searching:
            return "Searching";

        case RobotState::MovingToVictim:
            return "Moving To Victim";

        case RobotState::RescuingVictim:
            return "Rescuing Victim";

        case RobotState::ReturningToBase:
            return "Returning To Base";

        case RobotState::EmergencyStopped:
            return "Emergency Stopped";
    }

    return "Unknown";
}

int main() {
    RobotState state = RobotState::Idle;

    std::cout << "Current state: "
              << robotStateToString(state)
              << std::endl;

    state = RobotState::Searching;

    std::cout << "Current state: "
              << robotStateToString(state)
              << std::endl;

    state = RobotState::MovingToVictim;

    std::cout << "Current state: "
              << robotStateToString(state)
              << std::endl;

    return 0;
}