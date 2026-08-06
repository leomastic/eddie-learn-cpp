#pragma once
#include <string>

enum class WaterStatus {
    Empty,
    Low,
    Normal,
    Full
};

class WaterTank {
public:
    WaterTank(int level);

    int level() const;

    bool isEmpty() const;
    bool isLow() const;
    bool isFull() const;

    WaterStatus status() const;

    void consume(int amount);
    void refill(int amount);
    void reset();

    static std::string statusToString(WaterStatus status);

private:
    int level_;
};