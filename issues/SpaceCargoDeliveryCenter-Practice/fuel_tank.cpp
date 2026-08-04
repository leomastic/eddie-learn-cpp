#include "fuel_tank.h"
#include <algorithm>

FuelTank::FuelTank(int level)
    : level_(std::clamp(level, 0, 100)) {
}

int FuelTank::level() const {
    return level_;
}

bool FuelTank::isEmpty() const {
    return level_ == 0;
}

bool FuelTank::isLow() const {
    return level_ > 0 && level_ < 20;
}

bool FuelTank::isFull() const {
    return level_ == 100;
}

FuelStatus FuelTank::status() const {
    if(isEmpty()) {
        return FuelStatus::Empty;
    }

    if(isLow()) {
        return FuelStatus::Low;
    }

    if(isFull()) {
        return FuelStatus::Full;
    }

    return FuelStatus::Normal;
}

void FuelTank::consume(int amount) {
    if(amount < 0) {
        return;
    }

    if(level_ - amount < 0) {
        level_ = 0;
    } 

    level_ = std::max(0, level_ - amount);
}

void FuelTank::refuel(int amount) {
    if(amount < 0) {
        return;
    }

    if(level_ + amount > 100) {
        level_ = 100;
    }

    level_ = std::min(100, level_ + amount);
}

void FuelTank::reset() {
    level_ = 100;
}

std::string FuelTank::statusToString(FuelStatus status) {
    switch(status) {
        case FuelStatus::Empty:
            return "Empty";

        case FuelStatus::Low:
            return "Low";

        case FuelStatus::Full:
            return "Full";

        case FuelStatus::Normal:
            return "Normal";

        default:
            return "Unknown";
    }
}