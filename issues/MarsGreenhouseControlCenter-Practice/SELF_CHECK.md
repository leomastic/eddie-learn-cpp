## SELF_CHECK Answers

1. I created `greenhouse_center.h` and `greenhouse_center.cpp` first because the center class is the new core abstraction for managing multiple greenhouses. That gave me a place to add index lookup, routing methods, and statistics before wiring it into `main.cpp`. I also created `tests.cpp` early to verify behavior as I added features.

2. `CMakeLists.txt` defines how the project is built. It lists source files, executable targets, compiler settings, and dependencies so CMake can generate a proper build system.

3. I built the project before implementing all classes to catch integration and compile issues early. That way I could verify that files were included correctly and that the existing code still compiled after each change.

4. If a `.cpp` file is not added to the CMake target, it won’t be compiled or linked into the executable. That means any code defined only in that file won’t be available and you may get linker errors.

5. A declaration in a header announces a function or class interface. A definition in a source file provides the actual implementation or body. Headers tell users what exists; source files show how it works.

6. `#pragma once` prevents a header from being included multiple times in the same compilation unit. It avoids duplicate declarations and reduces the risk of redefinition errors.

7. Composition means one object contains another object as a member. It models “has-a” relationships by embedding one class inside another.

8. Composition is used in `Greenhouse` with `WaterTank waterTank_` and `std::vector<PlantBatch> plantBatches_`, and in `GreenhouseCenter` with `std::vector<Greenhouse> greenhouses_`.

9. `Greenhouse` contains a `WaterTank` instead of a raw integer because water has behavior and rules: status, refill, consume, and clamping. That logic belongs in a dedicated class.

10. `WaterTank` owns the water invariant. It ensures level stays within `0..100` and exposes status rules for empty/low/full.

11. `PlantBatch` owns plant-growth transitions. It knows when a batch can grow, when it becomes ready, and how harvest/failure works.

12. `Greenhouse` owns environmental status rules. It decides operational, needs water, warnings, critical, and offline based on temperature, humidity, and tank state.

13. `Greenhouse::updateStatus()` is private because it is an internal consistency helper. The class controls when status changes, so callers should use high-level operations instead.

14. `GreenhouseCenter` uses indexes because it stores greenhouses in a vector and needs a simple way to find and access the correct element without exposing internals.

15. A lookup function returns `-1` to indicate “not found.” It’s a standard sentinel when the valid indexes are `0` or higher.

16. An index must be checked before vector access to avoid out-of-range access, undefined behavior, and potential crashes.

17. Plant-batch IDs can repeat in different greenhouses because each greenhouse is a separate container. IDs must be unique only within the same greenhouse to prevent collisions there.

18. `advanceOneDay()` must avoid partial plant growth to keep the operation atomic. Either the whole daily cycle succeeds, or nothing changes.

19. If some plants grew before discovering there was not enough water, the greenhouse state would be inconsistent: partial growth, drained water, and incorrect status.

20. The program counts required water before growing plants so it can decide whether the whole operation can complete safely without partial progress.

21. A critical greenhouse rejects daily growth because it is already in a failure state and should not continue normal operations until conditions are corrected.

22. An offline greenhouse rejects updates because offline means it is not operating, so environment changes or refills should not be accepted until it is restarted.

23. Restarting calls `updateStatus()` because the greenhouse may need a new status based on current water, temperature, and humidity after coming back online.

24. Status-rule priority is important because multiple conditions can be true at once. The system must choose the most severe applicable status.

25. Dangerous temperature overrides low-water status because danger to the environment is more urgent than needing water. Critical conditions should take precedence.

26. Average functions check for an empty vector to avoid division by zero and to return a sensible default value when there are no items.

27. The maximum search keeps the earlier greenhouse in a tie to preserve stable selection and deterministic behavior when counts are equal.

28. The hardest compiler/linker error was the missing `findPlantBatchIndexById` declaration in `greenhouse.h`, which caused “no member” and “type qualifier is not allowed on a nonmember function” errors.

29. Error: `Greenhouse::findPlantBatchIndexById` was implemented in `.cpp` but not declared in `greenhouse.h`.
    Cause: header and source were out of sync.
    Fix: add the method declaration to `greenhouse.h`.
    What I learned: declarations and definitions must match exactly for the class interface to compile correctly.

30. Mistake: I initially had `water_tank.cpp` use `0 < level_ < 20`.
    Symptom: `WaterStatus::Full` tests failed because the chained comparison was wrong in C++.
    Fix: change it to `level_ > 0 && level_ < 20`.
    What I learned: C++ does not support Python-style chained comparisons; use explicit boolean operators.

31. One state-transition bug I found was `advanceOneDay()` allowing progress in a critical greenhouse if the status wasn’t checked early enough. That violated the rule that critical greenhouses cannot grow plants.

32. The hardest part of initializing the project from scratch was designing the center class and menu flow together so the operations, lookup logic, and statistics all fit cleanly.

33. The easiest files to create without looking at earlier projects were `water_tank.cpp` and `plant_batch.cpp`, because their behavior is straightforward and self-contained.

34. The files I needed to think about most carefully were `greenhouse.cpp` and `greenhouse_center.cpp` because they encode the business rules, status priorities, atomic growth behavior, and center-level routing.

35. Next time I’d start with a clearer separation of interface and implementation: define the class APIs first, then add tests immediately, and build incrementally after each feature.