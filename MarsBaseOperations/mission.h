#pragma once
#include <string>
#include <vector>

#include "astronaut.h"
#include "inventory.h"

enum class MissionStatus {
    Planning,
    Ready,
    InProgress,
    Completed,
    Cancelled
};

struct Mission {
    int id;
    std::string name;

    int requiredAstronauts;
    int minimumTotalSkill;

    int requiredOxygen;
    int requiredWater;
    int requiredFood;

    std::vector<int> assignedAstronautIndexes;
    MissionStatus status;
};

Mission createMission();

void printMission(const Mission& mission, const std::vector<Astronaut>& astronauts);

void printAllMissions(const std::vector<Mission>& missions, const std::vector<Astronaut>& astronauts);

int findMissionIndexById(const std::vector<Mission>& missions, int missionId);

bool assignAstronautToMission(Mission& mission, std::vector<Astronaut>& astronauts, int astronautIndex);

int calculateAssignedSkill(const Mission& mission, const std::vector<Astronaut>& astronauts);

bool hasEnoughAstronauts(const Mission& mission);

bool hasEnoughSkill(const Mission& mission, const std::vector<Astronaut>& astronauts);

bool isMissionReady(const Mission& mission, const std::vector<Astronaut>& astronauts, const Inventory& inventory);

void updateMissionStatus(Mission& mission, const std::vector<Astronaut>& astronauts, const Inventory& inventory);

bool launchMission(Mission& mission, std::vector<Astronaut>& astronauts, Inventory& inventory);

bool completeMission(Mission& mission, std::vector<Astronaut>& astronauts);

std::string missionStatusToString(MissionStatus status);