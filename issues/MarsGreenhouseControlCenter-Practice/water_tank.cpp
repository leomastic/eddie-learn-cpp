#include "water_tank.h"
#include <algorithm>

WaterTank::WaterTank(int level)
    : level_(std::clamp(level, 0, 100)) {
}

int WaterTank::level() const{
    return level_;
}

bool WaterTank::isEmpty() const {
    return level_ == 0;
}

bool WaterTank::isLow() const {
    return level_ > 0 && level_ < 20;
}

bool WaterTank::isFull() const {
    return level_ == 100;
}

WaterStatus WaterTank::status() const {
    if(isEmpty()) {
        return WaterStatus::Empty;
    } else if(isLow()) {
        return WaterStatus::Low;
    } else if(isFull()) {
        return WaterStatus::Full;
    } else {
        return WaterStatus::Normal;
    }
}

void WaterTank::consume(int amount) {
    if(amount <= 0) {
        return;
    }

    level_ -= amount;

    if(level_ < 0) {
        level_ = 0;
    }
}

void WaterTank::refill(int amount) {
    if(amount <= 0) {
        return;
    }

    level_ += amount;

    if(level_ > 100) {
        level_ = 100;
    }
}

void WaterTank::reset() {
    level_ = 100;
}

std::string WaterTank::statusToString(WaterStatus status) {
    switch(status) {
        case WaterStatus::Empty:
            return "Empty";

        case WaterStatus::Low:
            return "Low";

        case WaterStatus::Normal:
            return "Normal";

        case WaterStatus::Full:
            return "Full";

        default:
            return "Unknown";
    }
}