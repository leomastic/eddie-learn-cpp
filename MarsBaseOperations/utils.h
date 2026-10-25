#pragma once
#include <string>

int readIntInRange(const std::string& prompt, int minValue, int maxValue);

bool readYesNo(const std::string& prompt);

std::string readNonEmptyWord(const std::string& prompt);

std::string readNonEmptyLine(const std::string& prompt);