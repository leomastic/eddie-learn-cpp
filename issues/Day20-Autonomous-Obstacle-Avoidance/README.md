# Day 20: Autonomous Obstacle Avoidance

## Goal
Connect motor control, ultrasonic distance measurement, and servo directional scanning into an autonomous control loop (Sense → Decide → Act).

## Hardware and Pin Mapping
* **Left Motor Direction:** Pin 4
* **Left Motor Speed:** Pin 6 (PWM)
* **Right Motor Direction:** Pin 2
* **Right Motor Speed:** Pin 5 (PWM)
* **Ultrasonic Trig:** Pin 8
* **Ultrasonic Echo:** Pin 7
* **Servo Signal:** Pin 9

## Reused Calibration

### Motor Calibration
* `forwardLeftPwm` = 120, `forwardRightPwm` = 145
* `turnFromStopLeftPwm` = 90, `turnFromStopRightPwm` = 170
* `turnWhileMovingLeftPwm` = 120, `turnWhileMovingRightPwm` = 150

### Servo Calibration
* Right = 33°
* Center = 93°
* Left = 153°

### Ultrasonic Calibration
* Sound speed ratio = 0.0343 cm/µs
* Timeout = 30,000 µs (~-1 return value on failure)

## Obstacle Distance Experiment
*Test setup: Run robot toward a cardboard box at moderate speed and stop at varying distance thresholds.*

| Threshold | Actual Stopping Distance | Collision? | Observation |
| :---: | :---: | :---: | :--- |
| **40 cm** | No | No | Normal |
| **35 cm** | No | No | Normal |
| **30 cm** | Yes | No | Stopped |
| **25 cm** | Yes | No | Stopped |
| **20 cm** | Yes | Almost | Stopped |

## Chosen Obstacle Threshold
`const float obstacleDistanceCm = 30.0;`

## Turn Duration Experiment
*Test setup: Measure rotation angle on floor surface using TurnMode::FromStop.*

| Turn Duration | Approx. Rotation | Observation |
| :---: | :---: | :--- |
| **150 ms** | *~20°* | *Small twitch* |
| **250 ms** | *~30°* | *Shallow turn* |
| **350 ms** | *~40°* | *Not good turn but can see by bare eyes* |
| **450 ms** | *~50°* | *Still not good turn but can see by bare eyes* |
| **550 ms** | *~90* | *Just Slightly Over-rotated* |

## Chosen Turn Duration
`const int turnDurationMs = 450;`

## Autonomous Control Loop
The main loop continuously measures front distance, evaluates threshold checks, triggers stationary scanning when blocked, selects wider clearance, turns, and resumes driving.

## Perception Layer
Contains `measureDistanceCm()`, `isValidDistance()`, and `measureDirection()`. Responsible purely for environmental observation.

## Decision Layer
Contains `isObstacleAhead()` and `chooseAvoidanceAction()`. Evaluates data and outputs abstract behaviors without altering motor outputs.

## Action Layer
Contains `moveForward()`, `turnLeft()`, `turnRight()`, and `stopMotors()`. Executes physical maneuvers.

## Invalid Sensor Handling
* Invalid front distance (`-1.0`) evaluates to `isObstacleAhead() = true` to force an immediate stop.
* Invalid side measurements (`-1.0`) are bypassed in favor of valid side readings. If both sides return `-1.0`, `chooseAvoidanceAction()` outputs `RobotAction::Stop`.

## Test Scenarios

| Test | Front | Right | Left | Decision | Actual Behavior | Success? |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **A** | < 30 cm | ~80 cm | ~35 cm | Turn Right | Normal | *Pass* |
| **B** | < 30 cm | ~30 cm | ~75 cm | Turn Left | Normal | *Pass* |
| **C** | < 30 cm | ~55 cm | ~55 cm | Turn Right | *Normal* | Pass |
| **D** | < 30 cm | -1.0 | ~60 cm | Turn Left | Normal | Pass |
| **E** | Multi-obstacle course | Navigated course | Sometimes stuck (went back and forth about 5 times but still can get out) | Pass |

## Two-Minute Autonomous Test
* **Number of obstacles encountered:** *[Fill in]*
* **Number of right turns:** *[Fill in]*
* **Number of left turns:** *[Fill in]*
* **Number of emergency stops:** *[Fill in]*
* **Number of collisions:** *[Fill in]*

## Problems Observed
*[Fill in physical observations, e.g., tile floor friction variances, wheel slip]*

## Improvements I Would Make Later
* Add multi-sample filtering for ultrasonic distance reads.

## Most Interesting Observation
*[Fill in your observation during testing]*