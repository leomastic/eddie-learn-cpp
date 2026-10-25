Why is fleet.cpp separate from robot.cpp?
Fleet.cpp is responsible for operations on the whole collection of robots, such as printing the fleet, searching by name, and calculating summary values. Robot.cpp only manages a single robot's creation, reset, and single-robot display logic.

What responsibility belongs to simulation.cpp?
Simulation.cpp owns the logic for running robot rounds, updating sensor values, and moving the fleet through one or more simulation rounds. It is the module that coordinates robot actions and state transitions over time.

Why does fleet.h need to know about Robot?
Fleet.h uses Robot in function signatures and stores robots in a std::vector<Robot>. The fleet module must know the Robot type so it can accept and examine robot objects.

Why should a .cpp include its own .h first?
Including its own header first ensures the header is self-sufficient and catches missing includes early. It also prevents implementation files from accidentally relying on transitive includes.

What happens if simulation.cpp is missing from add_executable()?
If simulation.cpp is missing, the build will succeed only if no simulation symbols are used. If they are used, the linker will fail with undefined reference errors for runRobotRound, runFleetRound, or other simulation functions.

What is the difference between a declaration and a definition?
A declaration introduces a function or type name and its interface, while a definition provides the actual implementation or body. For example, a function prototype is a declaration; the function body is its definition.

Why does printAllRobots() use const std::vector<Robot>&?
Using const std::vector<Robot>& avoids copying the whole vector and guarantees that the function will not modify the fleet while printing it.

Why does runFleetRound() use std::vector<Robot>& without const?
runFleetRound() updates each robot's sensors and state, so it must accept a non-const reference to modify the original fleet.

Why should main.cpp not contain all state-machine rules?
Keeping state-machine rules out of main.cpp keeps the program modular and easier to understand. Main.cpp should coordinate modules, while state_machine.cpp should contain the decision and transition logic.

Which module was hardest to design, and why?
State_machine.cpp was the hardest to design because it needed to follow the priority rules correctly and handle both action decision and state transitions with the emergency battery check first.

Bugs I found while testing
- I first allowed duplicate robot names when adding a new robot, so I added a duplicate-name check in main.cpp.
- I also had a risk of empty name input, so I added readNonEmptyWord() and used it both for robot names and menu prompts.
