# Day19 Servo + Ultrasonic Directional Scanning

## Hardware
* Arduino Board
* HC-SR04 Ultrasonic Sensor
* KE3066 Servo Motor
* Sensor Bracket & Mount
* Breadboard & Jumper Wires

## Pin Mapping
* `trigPin = 8;` (Output)
* `echoPin = 7;` (Input)
* `servoPin = 9;` (PWM Control)

## KE3066 Direction Convention
* **Right side of robot:** 0° to 89°
* **Center of robot:** 90°
* **Left side of robot:** 91° to 180°

## Reused Day18 Servo Calibration

* **Right Angle:** 33°
* **Center Angle:** 93°
* **Left Angle:** 153°
* **Safe Mechanical Range:** 21° to 160°

**Reason for reuse:**
We use these previously calibrated angles instead of raw geometric limits (0°, 90°, 180°) to prevent the sensor bracket from colliding with the robot frame. Reusing these safe limits prevents mechanical binding, protects the servo gears from damage, and avoids dangerous power spikes.

## Servo Settling Time Experiment

| Commanded Delay | Observed Motion | Observation |
| :---------------------- | :----------------- | :------------------------------------------------- |
| **100 ms** | Still Rotating | Ping taken mid-rotation; off-target reading |
| **250 ms** | Slight Wobble | Sensor shaking during ping; slight distance noise |
| **500 ms** | Mostly Still | Slight residual vibration during full-range sweeps |
| **750 ms** | **Completely Still** | **Motor stopped completely and vibration fully subsided** |
| **1000 ms** | Fully Stable | Clear readings, but overall scan cycle is unnecessarily slow |

* **Chosen Settling Time:** `const int servoSettleTimeMs = 750;`

## How Directional Measurement Works

The `measureDirection()` function combines servo positioning, mechanical settling, ultrasonic ping execution, and distance conversion into a single reliable process:

| Step | Operation | Description |
| :--- | :--- | :--- |
| **1** | **Move Servo** | Commands `scanServo.write(targetAngle)` to rotate the sensor to the calibrated angle. |
| **2** | **Wait to Settle** | Pauses execution for `servoSettleTimeMs` (750 ms) so physical movement and bracket vibrations stop completely. |
| **3** | **Send Trigger** | Drives the `TRIG` pin `HIGH` for 10 µs to emit an ultrasonic sound wave burst. |
| **4** | **Measure Echo** | Calls `pulseIn(echoPin, HIGH)` to capture the microsecond travel duration of the returning sound wave. |
| **5** | **Calculate Distance** | Converts round-trip time into centimeters using $\text{duration} \times 0.0343 / 2$ (returns `-1` if no echo is received). |

## Scan Sequence

measure RIGHT
↓
measure CENTER
↓
measure LEFT
↓
return servo to CENTER
↓
compare measurements
↓
print result
↓
wait
↓
repeat


## Directional Measurement Experiments
*Note: Experiments pending teacher's WiFi module hardware setup.*

## Most Open Direction

The `findMostOpenDirection()` function evaluates the scanned environment and selects the path with the greatest physical clearance by comparing valid distance measurements across all three directions.

| Step | Action | Logic Description |
| :--- | :--- | :--- |
| **1** | **Initialize Tracking** | Sets `maxDistance = -1.0` and defaults `bestDirection` to `ScanDirection::Unknown`. |
| **2** | **Filter Invalid Readings** | Checks each value with `isValidDistance()`. Readings of `-1` (timeouts or errors) are ignored. |
| **3** | **Compare Clearances** | Compares each valid direction distance (`rightDistance`, `centerDistance`, `leftDistance`) against `maxDistance`. |
| **4** | **Update Winner** | Whenever a valid distance exceeds `maxDistance`, `maxDistance` is updated and `bestDirection` is set to that direction. |
| **5** | **Return Selection** | Returns the direction with the greatest clearance (`Right`, `Center`, or `Left`). If all three readings are invalid, returns `ScanDirection::Unknown`. |

## Invalid Echo Handling

| Aspect | Mechanism & Logic |
| :--- | :--- |
| **Timeout Occurrence** | When `pulseIn()` times out waiting for an echo (out-of-range or absorbed sound waves), it returns `0`. The software converts this `0` to `-1.0` cm to serve as an explicit error flag. |
| **Validation Filter** | The helper function `isValidDistance(distance)` evaluates whether `distance >= 0.0`. It returns `true` for valid physical readings and `false` for error flags (`-1.0`). |
| **Selection Protection** | In `findMostOpenDirection()`, direction measurements are checked with `isValidDistance()` before comparison. Invalid `-1.0` values are ignored, preventing an error flag from winning as the maximum clearance distance. |
| **Fallback Behavior** | If all three scanned directions return `-1.0`, the function safely returns `ScanDirection::Unknown`, signaling a perception failure to the robot controller. |

## Repeated Scan Experiment

Twenty consecutive scanning cycles were conducted in a static environment to measure long-term sensor stability and decision consistency.

| Scan Run | Right (cm) | Center (cm) | Left (cm) | Chosen Direction |
| :---: | :---: | :---: | :---: | :---: |
| **Run 1** | 72.05 | 117.61 | 165.70 | **LEFT** |
| **Run 2** | 71.86 | 117.55 | 165.58 | **LEFT** |
| **Run 3** | 72.08 | 118.52 | 166.15 | **LEFT** |
| **Run 4** | 71.14 | 117.61 | 165.65 | **LEFT** |
| **Run 5** | 72.53 | 118.06 | 165.81 | **LEFT** |
| **Run 6** | 71.40 | 118.09 | 165.74 | **LEFT** |
| **Run 7** | 71.62 | 118.06 | 165.89 | **LEFT** |
| **Run 8** | 71.62 | 118.06 | 165.75 | **LEFT** |
| **Run 9** | 71.96 | 118.06 | 165.70 | **LEFT** |
| **Run 10** | 71.98 | 68.89 | 165.84 | **LEFT** |
| **Run 11** | 71.88 | 118.30 | 165.26 | **LEFT** |
| **Run 12** | 72.41 | 118.13 | 165.77 | **LEFT** |
| **Run 13** | 72.42 | 118.16 | 165.50 | **LEFT** |
| **Run 14** | 71.62 | 118.23 | 165.39 | **LEFT** |
| **Run 15** | 72.08 | 118.06 | 166.08 | **LEFT** |
| **Run 16** | 72.53 | 117.55 | 165.55 | **LEFT** |
| **Run 17** | 72.51 | 118.06 | 166.06 | **LEFT** |
| **Run 18** | 73.28 | 117.51 | 165.53 | **LEFT** |
| **Run 19** | 72.08 | 118.46 | 165.67 | **LEFT** |
| **Run 20** | 71.12 | 70.54 | 165.43 | **LEFT** |

### Consistency Analysis

* **Decision Reliability:** **100% Consistent (20/20 runs).** `ScanDirection::Left` was correctly selected in every single iteration.
* **Measurement Stability:**
  * **Right:** High precision with minimal variance (~71.1 cm to 73.3 cm).
  * **Left:** Extremely stable with sub-centimeter variance (~165.3 cm to 166.1 cm).
  * **Center:** Baseline distance was stable (~118 cm), but occasional ultrasonic reflections caused transient dropouts (e.g., Run 10 at 68.89 cm and Run 20 at 70.54 cm).
* **Key Takeaway:** Despite intermittent ultrasonic noise on individual sensor channels, the navigation decision algorithm remained completely stable because the true max path (`Left` at ~165 cm) consistently outperformed the noisy readings.

## Problems Observed

| Issue Category | Observed Problem | Physical/Software Cause |
| :--- | :--- | :--- |
| **Transient Echo Noise** | Center distance dropped randomly from ~118 cm to ~68–70 cm in Runs 10 and 20. | Specular sound reflection (sound waves bouncing away at an angle rather than returning directly to the receiver) and acoustic noise. |
| **Mechanical Settling** | Sensor readings fluctuated if pinged immediately after turning. | Servo motor inertia and bracket vibration required a strict 750 ms settling delay to ensure static positioning before measurement. |
| **Beam Dispersion** | Narrow edge obstacles were occasionally missed or read wider than reality. | The HC-SR04 ultrasonic sensor has an ~15° sound cone, causing wider ambient coverage rather than a laser-narrow line. |

## Most Interesting Observation

* **Physical Constraints Drive Software Design:** In pure software, execution is virtually instantaneous and deterministic. In physical computing, software logic must adapt to physical hardware limitations—such as waiting for motor mass to settle (`servoSettleTimeMs`) and handling sensor timing limits (`pulseIn()` timeouts).
* **Noise Resilience over Perfect Accuracy:** Real-world sensor data is inherently imperfect. Even when individual sensor channels experience transient glitches (e.g., Center dropping by 50 cm), a well-structured decision algorithm (`findMostOpenDirection()`) maintains 100% operational reliability by filtering out invalid data and evaluating relative clearances.