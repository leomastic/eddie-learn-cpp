#include "battery.h"
#include <algorithm>

Battery::Battery(int level)
    : level_(std::clamp(level, 0, 100)) {
}

int Battery::level() const {
    return this->level_;
}

bool Battery::isEmpty() const {
    if(this->level_ == 0) {
        return true;
    } else {
        return false;
    }
}

bool Battery::isLow() const {
    return level_ > 0 && level_ < 15;
}

bool Battery::isFull() const {
    if(this->level_ == 100) {
        return true;
    } else {
        return false;
    }
}

BatteryStatus Battery::status() const {
    if (isEmpty()) {
        return BatteryStatus::Empty;
    }

    if (isLow()) {
        return BatteryStatus::Low;
    }

    if (isFull()) {
        return BatteryStatus::Full;
    }

    return BatteryStatus::Normal;
}

void Battery::consume(int amount) {
    if (amount <= 0) {
        return;
    }

    level_ = std::max(0, level_ - amount);
}

void Battery::charge(int amount) {
    if (amount <= 0) {
        return;
    }

    level_ = std::min(100, level_ + amount);
}

void Battery::reset() {
    this->level_ = 100;
}

std::string Battery::statusToString(BatteryStatus status) {
    switch(status) {
        case BatteryStatus::Empty:
            return "Empty";

        case BatteryStatus::Full:
            return "Full";

        case BatteryStatus::Low:
            return "Low";

        default:
            return "Normal";
    }
}