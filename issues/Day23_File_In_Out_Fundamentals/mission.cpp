#include "mission.h"

Mission::Mission(const std::string& name, int priority)
    : name_(name), priority_(priority) {
}

const std::string& Mission::getName() const {
    return name_;
}

int Mission::getPriority() const {
    return priority_;
}
