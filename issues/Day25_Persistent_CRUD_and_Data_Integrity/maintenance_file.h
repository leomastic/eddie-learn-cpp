#pragma once

#include "maintenance_log.h"

#include <string>

bool saveMaintenanceLog(const std::string& filename, const MaintenanceLog& log);
bool loadMaintenanceLog(const std::string& filename, MaintenanceLog& log);
