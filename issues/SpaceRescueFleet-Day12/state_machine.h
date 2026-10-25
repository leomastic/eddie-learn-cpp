#pragma once
#include "robot.h"

RobotAction decideAction(const Robot& robot);

RobotState calculateNextState(const Robot& robot);