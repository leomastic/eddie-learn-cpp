# Self Check

## Why is astronaut.cpp separate from mission.cpp?
Astronaut-related logic belongs in astronaut.cpp because it manages astronaut data, status updates, and astronaut-specific helpers. Keeping it separate makes the code easier to understand and reuse.

## Why does report.cpp need information from several modules?
Report.cpp combines astronaut, mission, and inventory data into a single summary, so it depends on all three modules to produce the full base report.

## Which module should own hasEnoughResources() and why?
Inventory should own hasEnoughResources() because it is directly about checking whether the base has enough stored resources.

## Which module should own isMissionReady() and why?
Mission should own isMissionReady() because readiness is a mission rule that depends on the mission requirements, assigned astronauts, and the inventory.

## Why should main.cpp not calculate mission readiness directly?
Main.cpp should stay focused on flow and user interaction, while mission readiness rules belong in mission-related code to keep the logic centralized.

## What is the difference between compile-time and link-time errors?
A compile-time error happens when the code cannot be translated by the compiler, while a link-time error happens when the compiled objects cannot be linked into an executable.

## What happened when report.cpp was removed from CMake?
The build failed at link time because the executable no longer had the report implementation object to satisfy the referenced functions.

## What happened when a required header dependency was removed?
The compiler failed because a type or declaration used in the header was no longer known, which caused a compile-time error.

## Why does printBaseReport() use const references?
Const references allow the function to read data without making copies and prevent accidental modification.

## Why does launchMission() need non-const references?
LaunchMission must update mission status and inventory contents, so it needs writable references to those objects.

## Why should hasEnoughResources() not print messages?
It should act as a pure check so it can be reused by multiple functions without forcing output side effects.

## Why should consumeResources() be separate from hasEnoughResources()? 
They have different responsibilities: one checks whether resources are sufficient, and the other performs the state change.

## Which header has the most dependencies? Why?
mission.h has the most dependencies because it needs astronaut, inventory, and vector types to define the mission rules and related functions. The vector types remove separate collection-count parameters from the public APIs.

## Why are enum classes used for status and menu choices?
Astronaut status, mission status, and menu choices are scoped enum classes. This prevents unrelated integer values from being assigned accidentally and makes state transitions explicit at each call site.

## Why are vectors used instead of fixed arrays?
Astronauts, missions, and each mission's assigned crew indexes use `std::vector`. Vectors grow safely with `push_back()` and provide their size to every function, avoiding manual count synchronization and fixed-array overflow risks. Crew indexes are validated against the astronaut vector before use.

## Which module was hardest to design?
The mission module was hardest because it coordinates assignment, readiness, launch, and completion rules across multiple data types.

## What responsibility did you initially place in the wrong module?
I initially placed readiness output in the main flow, but it belongs in the report/mission side so the logic remains modular.

## Bugs I found while testing

### Bug: Mission resources were consumed even when readiness failed.
Cause: Launch validation was incomplete and the mission could consume resources before the readiness checks were fully enforced.
Fix: LaunchMission now checks readiness and resource availability before consuming anything.
What I learned: Validation must happen before changing program state.

### Bug: Duplicate astronaut names could still be added.
Cause: The add-astronaut flow did not reject duplicates consistently.
Fix: The menu flow now checks for an existing astronaut name before adding a new one.
What I learned: Duplicate protections should be enforced at the boundary where new data is accepted.

### Bug: Line input discarded the next value.
Cause: The line-reading helpers ignored a complete input line even though numeric helpers had already consumed the newline.
Fix: Numeric and yes/no helpers now consume their own trailing input, while line helpers read directly with `getline()`.
What I learned: Input-buffer ownership should be centralized and consistent across helper functions.

### Design correction: Fixed arrays and integer states did not meet the exercise requirements.
The implementation now uses `std::vector`, `AstronautStatus`, `MissionStatus`, and `MenuChoice`. The menu handlers keep `main()` focused on orchestration and keep it below the requested line limit.

## Module Responsibility Table

| Module | Main responsibility |
| --- | --- |
| astronaut | Stores astronaut data and provides astronaut-specific operations such as creation, printing, status reset, and lookup. |
| mission | Owns mission data, assignment rules, readiness evaluation, launch handling, and completion logic. |
| inventory | Manages base resource storage and resource-related operations such as restocking and consumption checks. |
| report | Produces read-only summaries and readiness reports by combining data from the other modules. |
| utils | Provides reusable input validation and safe reading helpers for console input. |
| main | Coordinates application flow and menu interaction without owning the detailed business rules. |
