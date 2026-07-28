#include "battery.h"
#include <algorithm>

Battery::Battery(int level)
    : level_(std::clamp(level, 0, 100)),
      status_(BatteryStatus::Full) {
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
    if(0 < this->level_ < 15) {
        return true;
    } else {
        return false;
    }
}

bool Battery::isFull() const {
    if(this->level_ == 100) {
        return true;
    } else {
        return false;
    }
}

BatteryStatus Battery::status() const {
    return this->status_;
}

void Battery::consume(int amount) {
    if(amount <= 0) {
        this->level_ = this->level_;
    } else if(amount > this->level_) {
        this->level_ = 0;
    } else {
        this->level_ -= amount;
    }
}

void Battery::charge(int amount) {
    if(amount <= 0) {
        this->level_ = this->level_;
    } else if(amount > (100 - this->level_)) {
        this->level_ = 100;
    } else {
        this->level_ += amount;
    }
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