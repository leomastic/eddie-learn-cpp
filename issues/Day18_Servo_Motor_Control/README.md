# Day18 Servo Motor Control

## Hardware

## Servo Pin
Servo Pin = 9

## What I Learned
+ What is an servo: its to give detail commands
                EX: + analogWrite(leftSpeedPin, 120) does not mean rotate to 120 degrees.
                      it control power using PWM

                    + a servo is different: we normally tell it to move to this angular position.

+ Servo angles: 
    0° = right side
    90° = center
    180° = left side

    but it may not physically match these exact directions.

+ Arduino servo library:
    #include <Servo.h> --> a software

+ attach() and write()

## DC Motor vs Servo

+ DC wheel motor:

command
   ↓
speed / direction
   ↓
continuous wheel movement

+ servo:

command
   ↓
target angle
   ↓
move to position
   ↓
hold position

## Servo Library

servo library: #include <Servo.h>

## attach()

connects the software sero object to the servo pin.

## write()
Request angular position.

EX: scanServo.write(30);
requests approximately 30°.

or:
scanServo.write(150);
requests approximately 150°.

but:
write(150)

does not mean:
move at speed 150.

## Servo Calibration
Due to mechanical mounting alignment and gear tolerances, software angles did not perfectly match physical directions on the robot. A ~3° offset was observed across commands.

### Calibration Summary Table
| Position       | Commanded Angle | Observed Physical Direction | Safe? |
| :------------- | :-------------- | :-------------------------- | :---- |
| **Safe Right** | 21°             | ~22° (Right)                | Yes   |
| **Center**     | 93°             | ~90° (Straight ahead)       | Yes   |
| **Safe Left**  | 160°            | ~160° (Left)                | Yes   |

## Safe Mechanical Range
* **Range:** `21°` to `160°`
* Moving beyond these limits risks bracket collision, cable tension, or mechanical buzzing.

## Center Calibration
**Software 90° Result:** Slightly off-center (~87°).
**Calibrated Center:** `93°` produces a almost true straight-ahead physical direction

## Repeated Position Experiment
* **Observed Positions:**
  * `30°` command resulted in ~`27°` physical.
  * `90°` command resulted in ~`87°` physical.
  * `150°` command resulted in ~`147°` physical.
* **Repeatability:** The servo consistently returned to the calibrated center (`93°`) after moving left and right without significant drift.

## Small Angle Experiment
|     Commanded Angle     | Observed Direction |         Observation       |
| :---------------------- | :----------------- | :------------------------ |
| **Center - 20° (73°)**  |   Right Of Center  |       Clear movement      |
| **Center - 10° (83°)**  |    Slightly Right  | Noticeable position shift |
|    **Center (93°)**     |    Straight Ahead  |       Fully centered      |
| **Center + 10° (103°)** |    Slightly Left   | Noticeable position shift |
| **Center + 20° (113°)** |   Left Of Center   |       Clear movement      |

* **5° change:** Noticeable on normal inspection.
* **10° change:** Easily visible physical rotation.

## Known Physical Problems
* Minor mechanical backlash/slop in plastic servo gears.
* A constant ~3° software-to-physical angle shift.
* Stucked when turn < ~22° physically and turn > ~160° physically

## Most Interesting Observation
Software state changes instantly, but mechanical hardware requires physical time (`delay()`) to reach its target position. Command numbers and physical output angles are correlated but not identical.