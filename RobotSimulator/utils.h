#pragma once
#include <string>

int readIntInRange(std::string prompt, int minValue, int maxValue);

double readDoubleInRange(std::string prompt, double minValue, double maxValue);

bool readYesNo(std::string prompt);