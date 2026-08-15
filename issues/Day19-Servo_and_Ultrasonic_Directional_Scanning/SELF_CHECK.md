# Day 19 Self-Check & Quality Verification Report

## 1. Hardware Setup & Pin Mapping Check
- [x] **Trig Pin:** Connected to Arduino Digital Pin `8` (Output).
- [x] **Echo Pin:** Connected to Arduino Digital Pin `7` (Input).
- [x] **Servo Pin:** Connected to PWM Digital Pin `9`.
- [x] **Power & Ground:** Common ground established across Arduino, Servo, and HC-SR04 sensor.
- [x] **Mechanical Mount:** Bracket secured to servo shaft with no loose play.

## 2. Servo Range & Calibration Check
- [x] **Right Target Angle:** Calibrated to `33°` (Range: `0°–89°`).
- [x] **Center Target Angle:** Calibrated to `93°` (Range: `90°`).
- [x] **Left Target Angle:** Calibrated to `153°` (Range: `91°–180°`).
- [x] **Mechanical Safeguard:** Motion constrained within safe range (`21°` to `160°`) to prevent frame collision and gear binding.
- [x] **Settling Delay:** Verified at `750 ms` (`servoSettleTimeMs = 750`) to ensure vibration subsides before ping execution.

## 3. Sensor & Measurement Logic Check
- [x] **Trigger Waveform:** 10 µs `HIGH` pulse generated correctly on `trigPin`.
- [x] **Pulse Duration Measurement:** Captured using `pulseIn(echoPin, HIGH)`.
- [x] **Distance Conversion Formula:** Correctly implemented as `duration * 0.0343 / 2`.
- [x] **Timeout & Error Output:** Returns `-1.0` cm on timeout/failure.

## 4. Directional Selection & Safety Check
- [x] **Filter Function (`isValidDistance`):** Properly flags distances $\ge 0.0$ cm as valid and ignores `-1.0` error flags.
- [x] **Maximum Clearance Finder (`findMostOpenDirection`):** Correctly evaluates all 3 directions and picks the path with maximum valid distance.
- [x] **Fallback Protection:** Defaults to `ScanDirection::Unknown` if all 3 directional readings fail (`-1.0`).
- [x] **Reset State:** Servo returns to `CENTER` (`93°`) after each full sweep sequence.

## 5. Experimental Data & Reliability Verification
- [x] **Sample Count:** 38 full consecutive scan cycles recorded and logged.
- [x] **Decision Accuracy:** 100% decision consistency across all 38 test runs (`LEFT` consistently chosen as the most open path).
- [x] **Noise Tolerance:** Logic successfully ignored intermittent acoustic dropouts (e.g., Center dropping from ~118 cm to ~62 cm).

---

## Technical Summary Matrix

| Verification Item | Target Standard | Observed Status | Pass/Fail |
| :--- | :--- | :--- | :---: |
| **Servo Settling Delay** | Motor vibration stopped | Stable at 750 ms delay | **PASS** |
| **Frame Clearance** | No mechanical binding | Operating between 33°–153° | **PASS** |
| **Error Flagging** | Return `-1.0` on pulse timeout | Converted from `pulseIn()` 0 | **PASS** |
| **Decision Stability** | Consistent path choice | 38/38 runs selected `LEFT` | **PASS** |
| **Acoustic Noise Mitigation** | System unaffected by noise | Relative comparison logic holds | **PASS** |

---

## Detailed Question Responses

**1. Which pins are used by the ultrasonic sensor?**  
Digital Pin 8 (`TRIG`) and Digital Pin 7 (`ECHO`).

**2. Which pin controls the servo?**  
Digital Pin 9 (PWM Control).

**3. On the KE3066, does a smaller servo angle point more toward the robot's left or right?**  
A smaller angle (0° to 89°) points toward the robot's **RIGHT**.

**4. Approximately which direction does 90° represent?**  
It represents the **CENTER** (straight ahead).

**5. Why should Day19 reuse Day18 calibration instead of blindly using 0, 90, and 180?**  
Using theoretical angles (0°, 90°, 180°) can cause physical collision between the bracket and the robot frame, binding the gears and causing power spikes. Reusing calibrated angles (33°, 93°, 153°) ensures safe motion.

**6. What does `measureDistanceCm()` do?**  
It triggers the ultrasonic sensor, measures the high pulse duration on the echo pin, and converts time into distance in centimeters.

**7. Why can the Day17 measurement function be reused today?**  
Because it is a standalone hardware abstraction function; its job is purely to return the distance straight ahead of wherever the sensor is physically pointing.

**8. Why must the servo settle before taking an ultrasonic measurement?**  
Moving the motor creates mechanical vibration and inertia. Waiting allows the sensor to come to a complete physical stop so the ping measures a true static heading.

**9. What could happen if you measure immediately after `servo.write()`?**  
The sensor will emit sound waves while still rotating or shaking, yielding inaccurate readings or off-target distances.

**10. What does `servoSettleTimeMs` represent?**  
The delay time in milliseconds required for the motor to complete its turn and stop vibrating completely.

**11. How did you experimentally choose your settling time?**  
By testing values from 100 ms to 1000 ms and observing physical wobble. At 750 ms, motor motion and frame vibration completely subsided.

**12. What does `enum class ScanDirection` represent?**  
It represents the physical looking directions of the robot (`Right`, `Center`, `Left`, `Unknown`).

**13. Why is `ScanDirection::Right` clearer than a number such as 0?**  
It self-documents the intent of the code, making it readable and preventing accidental assignment errors compared to magic numbers.

**14. What does `angleForDirection()` do?**  
It maps a semantic `ScanDirection` enum value to its corresponding calibrated servo angle integer.

**15. What does `directionToString()` do?**  
It converts `ScanDirection` enum states into human-readable strings for clear `Serial` printing.

**16. What responsibilities does `measureDirection()` combine?**  
It combines moving the servo to a target direction, pausing for motor settling, taking the ultrasonic ping, and formatting/printing the result.

**17. Why should the servo return to center after scanning?**  
To leave the perception system in a predictable baseline state so future motion or scanning logic doesn't assume an incorrect head position.

**18. What three values describe one complete Day19 scan?**  
`rightDistance`, `centerDistance`, and `leftDistance`.

**19. What does `-1` mean when returned by the ultrasonic measurement function?**  
It indicates an invalid echo, timeout, or out-of-range state.

**20. Why must `-1` not be treated like a normal distance?**  
Because mathematically `-1` is a small number. If treated as real distance, an error flag would appear closer than obstacles; if treated as infinite space without filtering, logic comparisons could misinterpret it.

**21. What does `isValidDistance()` do?**  
It checks whether a distance value is non-negative (`distance >= 0`), filtering out error flags (`-1.0`).

**22. How do you determine the most open direction?**  
By filtering out invalid readings first, then comparing valid distances across Right, Center, and Left, selecting the direction with the highest value.

**23. What should happen if all three distance measurements are invalid?**  
The decision logic should report `ScanDirection::Unknown` rather than selecting a false path.

**24. Why is `Unknown` useful?**  
It explicitly communicates perception failure or complete sensor blockage to higher-level decision nodes.

**25. Why should sensing and decision-making be separate functions?**  
To keep code modular. Sensing acquires raw data, while decision logic evaluates it; separating them allows changing decision rules without rewriting hardware control code.

**26. If RIGHT is 70 cm, CENTER is 25 cm, and LEFT is 45 cm, which direction is most open?**  
**RIGHT** (70 cm).

**27. If RIGHT is -1, CENTER is 30 cm, and LEFT is 50 cm, which valid direction is most open?**  
**LEFT** (50 cm).

**28. If RIGHT is -1, CENTER is -1, and LEFT is -1, what should the result be?**  
**UNKNOWN** (`ScanDirection::Unknown`).

**29. Why might two complete scans of an unchanged environment produce slightly different distances?**  
Due to environmental noise, beam dispersion (~15° cone), minor servo gear play, and surface reflections.

**30. What was the most interesting behavior you observed when combining the servo and ultrasonic sensor?**  
Seeing how software delay logic (`servoSettleTimeMs`) directly compensates for physical mass inertia to turn noisy hardware signals into reliable navigation choices.