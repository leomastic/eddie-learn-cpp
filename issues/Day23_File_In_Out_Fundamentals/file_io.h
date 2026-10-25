#pragma once

#include "mission.h"
#include <string>
#include <vector>

bool saveMissions(const std::string& filename, const std::vector<Mission>& missions);

std::vector<Mission> loadMissions(const std::string& filename);
