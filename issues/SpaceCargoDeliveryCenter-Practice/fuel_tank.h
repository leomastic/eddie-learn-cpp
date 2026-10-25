#pragma once
#include <string>

enum class FuelStatus {
    Empty,
    Low,
    Normal,
    Full
};

class FuelTank {
public:
    explicit FuelTank(int level);

    int level() const;

    bool isEmpty() const;
    bool isLow() const;
    bool isFull() const;

    FuelStatus status() const;

    void consume(int amount);
    void refuel(int amount);
    void reset();

    static std::string statusToString(FuelStatus status);

private:
    int level_;
};

