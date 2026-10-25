# Day 20 Self-Check & Engineering Reflections

### 1. What are the three main stages of today's autonomous control loop?
* **Perception (SENSE):** Gathering raw measurements from the ultrasonic sensor and servo.
* **Decision (DECIDE):** Processing measurements against threshold logic to choose the next action (`RobotAction`).
* **Action (ACT):** Driving the motor drivers to physically move or turn the robot.

---

### 2. What does perception mean? What does decision mean? What does action mean?
* **Perception:** Converting physical signals into software data (e.g., echo duration in microseconds into `float distanceCm`).
* **Decision:** Evaluating pure data state without touching hardware pins to decide *what* the robot should do.
* **Action:** Translating decisions into low-level GPIO/PWM output on motor pins to change physical state.

---

### 3. Which previous day provides motor control?
**Day 16.**

### 4. Which previous day provides ultrasonic distance measurement?
**Day 17.**

### 5. Which previous day provides servo calibration?
**Day 18.**

### 6. Which previous day provides directional scanning?
**Day 19.**

---

### 7. Why should we reuse previous calibration instead of starting again with generic values?
Because physical hardware varies across units. Using uncalibrated values (like assuming 90° is center when real center is 93°, or equal PWM speeds when motors drift) causes physical errors like crooked movement and misaligned scanning. Reuse guarantees verified baselines.

---

### 8. What does `obstacleDistanceCm` represent?
The threshold distance (35.0 cm) at which an object ahead is deemed too close for safe forward motion, triggering an immediate stop and directional scan.

---

### 9. Why shouldn't we simply choose 10 cm as the obstacle threshold without testing?
At 10 cm, the physical momentum of the robot, wheel slip on tiles, and processing/servo delays mean the robot cannot stop before physically colliding with the barrier.

---

### 10. Why might the robot continue moving slightly after the motor command changes to stop?
Physical kinetic energy/momentum, motor armature inertia, wheel slip against the floor, and power supply capacitance keeping drivers active momentarily.

---

### 11. How did you experimentally determine your obstacle threshold?
By driving the robot toward a cardboard box at moderate speed (`forwardLeftPwm = 120`, `forwardRightPwm = 160`) and recording actual stopping distance vs. threshold. At 20–25 cm, collisions occurred due to stopping inertia; 35.0 cm provided a reliable safety buffer.

---

### 12. What should the robot do if the front ultrasonic measurement is invalid while driving?
It must execute a **safe failure behavior**: treat the path as blocked (`isObstacleAhead() = true`), bring the motors to a stop, and initiate a directional scan.

---

### 13. Why is stopping safer than assuming an invalid measurement means open space?
An echo timeout (`-1.0`) can happen because an obstacle is angled, soft/absorbent (fabric/box flap), or too close (< 2 cm). Assuming open space means driving blind into potential hazards.

---

### 14. Why must the motors stop before directional scanning?
If motors move while the servo rotates, the robot's coordinate frame changes during measurement. Comparing left vs. right distances becomes invalid because the robot measured them from two completely different physical locations.

---

### 15. Why should the ultrasonic sensor remain centered during normal forward movement?
To ensure the front distance reading consistently monitors the vehicle's actual direction of travel.

---

### 16. On this KE3066, does a smaller servo angle point toward LEFT or RIGHT?
A smaller angle (33°) points toward the **RIGHT**. A larger angle (153°) points toward the **LEFT**.

---

### 17. What calibrated angle represents approximately straight ahead?
**93°**.

---

### 18. What is the difference between `ScanDirection` and `RobotAction`?
* `ScanDirection` represents **sensor geometry** (Where is the servo looking?).
* `RobotAction` represents **physical behavior** (What are the wheels doing?).

---

### 19. Why should `chooseAvoidanceAction()` not directly control the motors?
To maintain separation of concerns. Keeping decision logic pure and stateless allows testing navigation rules independently in code without causing unpredictable physical motor actions.

---

### 20. If RIGHT = 80 cm and LEFT = 35 cm, what action should be chosen?
`RobotAction::TurnRight`.

### 21. If RIGHT = 30 cm and LEFT = 75 cm, what action should be chosen?
`RobotAction::TurnLeft`.

### 22. If RIGHT = -1 and LEFT = 60 cm, what action should be chosen?
`RobotAction::TurnLeft` (since -1 represents out-of-range/open space or invalid, the valid open path on Left is prioritized).

### 23. If RIGHT = 50 cm and LEFT = -1, what action should be chosen?
`RobotAction::TurnRight`.

### 24. If RIGHT = -1 and LEFT = -1, what should the robot do?
`RobotAction::Stop` (or default safely to a stationary recovery, as both sensors failed to receive an echo).

---

### 25. What happens when right and left are equal in your implementation?
The decision condition `(effectiveRight >= effectiveLeft)` breaks ties deterministically by selecting `RobotAction::TurnRight`.

---

### 26. What does `turnDurationMs` represent?
The duration in milliseconds (550 ms) that motor turn PWM speeds are applied to rotate the robot body by roughly 90°.

---

### 27. Why doesn't a fixed turn time guarantee an exact angle?
Because open-loop timing is vulnerable to physical variables like floor surface friction, tire wear, wheel slip, and dropping battery voltage.

---

### 28. Name three physical factors that can change the amount the robot rotates.
1. Floor friction / surface material (tile vs. wood vs. carpet).
2. Battery discharge state (lower voltage = slower motor speed at same PWM).
3. Weight distribution and wheel slip.

---

### 29. Why shouldn't `isValidDistance()` be described as a noise filter?
Because `isValidDistance()` only performs a range check (`distance >= 0.0`). It filters explicit code errors (`-1.0`), but cannot detect physically impossible or noisy measurements like a random 69 cm spike in a series of 118 cm reads.

---

### 30. What is the difference between an invalid reading and a noisy but valid reading?
* **Invalid reading:** Hard failure returned by the driver/sensor (timeout, 0 duration, `-1.0`).
* **Noisy valid reading:** A mathematically valid distance value (e.g., 42 cm) produced by specular reflection or acoustic multipath interference rather than the real physical barrier distance.

---

### 31. Why is Serial logging useful for an autonomous robot?
It gives visual access to internal state (perception values, decisions, timer triggers) to explain *why* the robot executed a physical maneuver.

---

### 32. Why are we prioritizing reliability instead of speed today?
In robotics, a fast robot that crashes or behaves unpredictably is useless. A slow, reliable robot whose state transitions can be predicted and proven is the foundation for advanced autonomous behavior.

---

### 33. Describe one complete obstacle-avoidance cycle from sensing the obstacle until the robot resumes forward movement.
1. Robot drives forward; `measureDistanceCm()` returns 28 cm.
2. `isObstacleAhead(28.0)` returns `true`.
3. `stopMotors()` executes; robot rests for 200 ms.
4. Servo scans Right (33°): returns 72 cm.
5. Servo scans Left (153°): returns 38 cm.
6. Servo re-centers (93°).
7. `chooseAvoidanceAction(72.0, 38.0)` outputs `RobotAction::TurnRight`.
8. `turnRight(TurnMode::FromStop)` runs for 550 ms, then `stopMotors()`.
9. Main loop restarts, measures front distance (> 35 cm), and resumes `moveForward()`.

---

### 34. What was the biggest difference between writing normal software and programming a physical autonomous robot?
In pure software, state and inputs are deterministic. In physical robotics, code interacts with hardware noise, mechanical momentum, friction, and sensor limitations. Software logic must account for real-world physical uncertainty.