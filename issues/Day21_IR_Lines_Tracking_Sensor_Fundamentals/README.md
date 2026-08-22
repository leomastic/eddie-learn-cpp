# Day21 Line-Tracking Sensor Fundamentals

## Goal
Observe and calibrate the two downward-facing infrared (IR) line-tracking sensors on the KE3066 robot in isolation (wheels stationary). The objective is to determine real-world logic polarities (`HIGH`/`LOW` vs. Black/White), structure state abstractions using `LineSensorState`, and understand physical environmental constraints (mounting height, surface reflectivity, boundary sensitivity, and line geometry) before implementing autonomous line following.

## Hardware
* **Microcontroller:** Arduino Uno (KE3066 Mainboard)
* **Sensors:** 2x Downward-facing IR Line-Tracking Sensor Modules (IR Emitter/Receiver pair with onboard LM393 comparator)

## Pin Mapping
* **Left Tracking Sensor:** Digital Pin `11` (`D11`)
* **Right Tracking Sensor:** Digital Pin `10` (`D10`)

## How the IR Tracking Sensors Work
1. **Emitter Phase:** The onboard IR LED emits invisible infrared light downward toward the floor.
2. **Surface Reflection Phase:** Light-colored surfaces reflect a significant portion of IR light, while dark or non-reflective surfaces absorb it.
3. **Receiver Phase:** The IR phototransistor detects the reflected IR intensity.
4. **Digitization Phase:** An onboard comparator circuit converts the continuous analog light level into a discrete digital logic level (`HIGH` or `LOW`) based on an adjustable potentiometer threshold.

## digitalRead()
The `digitalRead(pin)` function queries the logic state of an Arduino digital pin:
* Returns `0` (`LOW`) when voltage is near 0V.
* Returns `1` (`HIGH`) when voltage is near 5V.

## White Surface Experiment
| Reading # | Left Sensor (D11) | Right Sensor (D10) |
| :---: | :---: | :---: |
| 1 | 0 | 0 |
| 2 | 0 | 0 |
| 3 | 0 | 0 |
| 4 | 0 | 0 |
| 5 | 0 | 0 |
| 6 | 0 | 0 |
| 7 | 0 | 0 |
| 8 | 0 | 0 |
| 9 | 0 | 0 |
| 10 | 0 | 0 |

## Black Surface Experiment
| Reading # | Left Sensor (D11) | Right Sensor (D10) |
| :---: | :---: | :---: |
| 1 | 1 | 1 |
| 2 | 1 | 1 |
| 3 | 1 | 1 |
| 4 | 1 | 1 |
| 5 | 1 | 1 |
| 6 | 1 | 1 |
| 7 | 1 | 1 |
| 8 | 1 | 1 |
| 9 | 1 | 1 |
| 10 | 1 | 1 |

## My Actual HIGH/LOW Calibration
White: 0 (LOW)
Black: 1 (HIGH)
BTW if the sensor is too high from ground, it will return 1.

## Four Sensor States
Case A
LEFT  = BACKGROUND
RIGHT = BACKGROUND

Case B
LEFT  = LINE
RIGHT = BACKGROUND

Case C
LEFT  = BACKGROUND
RIGHT = LINE

Case D
LEFT  = LINE
RIGHT = LINE

## Sensor Height Experiment
0mm: White stable
2mm: White stable
5mm: White stable
10mm: ONLY LEFT: White stable
12mm: Black stable
> 12mm: Black stable

## Surface Material Experiment
White paper: 0 (BOTH BACKGROUND)
My black mouse pad: 0 (BOTH BACKGROUND)
Wood table: 0 (BOTH BACKGROUND)
Cardboard: 0 (BOTH BACKGROUND)
My red cardboard: 0 (BOTH BACKGROUND)

I dont have any stuff tho

## Boundary Experiment
The sensor is highly sensitive, it can yield a result from a distance of just 0.1mm or less

## Line Width Experiment
| Line width | Typical centered sensor state | Observation |
| :--- | :--- | :--- |
| **Narrow** | BOTH BACKGROUND | Can't see line |
| **Wide** | BOTH ON LINE | Can see line |

## Stability Experiment

### 30 Consecutive Stationary Samples
| Sample # | State |
| :---: | :--- |
| **1 – 30** | BOTH BACKGROUND |

*(All 30 readings consistently outputted `BOTH BACKGROUND` with 0 state fluctuations.)*

## Problems Observed
When the robot's sensor encounters my black mousepad, it treats the pad as the background; however, if the robot is lifted too high, it mistakes the floor—even where there is no line—for a line.

## Most Interesting Observation
When the robot's sensor encounters my black mousepad, it treats the pad as the background