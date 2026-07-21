#pragma once
#include <string>

#include "astronaut.h"
#include "inventory.h"

const int MISSION_STATUS_PLANNING = 0;
const int MISSION_STATUS_READY = 1;
const int MISSION_STATUS_IN_PROGRESS = 2;
const int MISSION_STATUS_COMPLETED = 3;
const int MISSION_STATUS_CANCELLED = 4;
const int MAX_ASSIGNED_ASTRONAUTS = 100;

struct Mission {
    int id;
    std::string name;

    int requiredAstronauts;
    int minimumTotalSkill;

    int requiredOxygen;
    int requiredWater;
    int requiredFood;

    int assignedAstronautIndexes[MAX_ASSIGNED_ASTRONAUTS];
    int assignedCount;

    int status;
};

Mission createMission();

void printMission(const Mission& mission, const Astronaut astronauts[], int astronautCount);

void printAllMissions(const Mission missions[], int missionCount, const Astronaut astronauts[], int astronautCount);

int findMissionIndexById(const Mission missions[], int missionCount, int missionId);

bool assignAstronautToMission(Mission& mission, Astronaut& astronaut, int astronautIndex);

int calculateAssignedSkill(const Mission& mission, const Astronaut astronauts[], int astronautCount);

bool hasEnoughAstronauts(const Mission& mission);

bool hasEnoughSkill(const Mission& mission, const Astronaut astronauts[], int astronautCount);

bool isMissionReady(const Mission& mission, const Astronaut astronauts[], int astronautCount, const Inventory& inventory);

void updateMissionStatus(Mission& mission, const Astronaut astronauts[], int astronautCount, const Inventory& inventory);

bool launchMission(Mission& mission, Astronaut astronauts[], int astronautCount, Inventory& inventory);

bool completeMission(Mission& mission, Astronaut astronauts[], int astronautCount);

std::string missionStatusToString(int status);