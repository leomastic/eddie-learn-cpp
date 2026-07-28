#pragma once
#include <string>

enum class BatteryStatus {
    Empty,
    Low,
    Normal,
    Full
};

class Battery {
public:
    explicit Battery(int level);

    int level() const;

    bool isEmpty() const;
    bool isLow() const;
    bool isFull() const;

    BatteryStatus status() const;

    void consume(int amount);
    void charge(int amount);
    void reset();

    static std::string statusToString(BatteryStatus status);

private:
    int level_;

    BatteryStatus status_;
};