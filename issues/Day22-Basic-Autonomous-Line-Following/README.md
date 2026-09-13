# Day22 Basic Autonomous Line Following

## Goal

Build an autonomous line-following robot using two tracking sensors.

```text
Sense line → Decide action → Drive motors → Robot position changes → Sense again
```

## Day21 Calibration

| Item | Value |
| --- | --- |
| Left tracking sensor | D11 |
| Right tracking sensor | D10 |
| Black tape | `HIGH` |
| White background | `LOW` |
| Sensor-centre spacing | 20 mm |
| Narrow line width | 10 mm |

## Track Geometry

The 10 mm line can sit between sensors that are 20 mm apart.

```text
Left sensor       Right sensor
     ●      █      ●
            █
```

When this happens:

```text
BothBackground
```

can mean that the robot is correctly centered.

## State-to-Action Table

| Sensor State | Physical Meaning | Required Correction |
| :--- | :--- | :--- |
| **BothBackground** | Line is centered between the sensors | **`moveForward()`** |
| **LeftOnLine** | Robot drifted right; line is under the left sensor | **`steerLeft()`** |
| **RightOnLine** | Robot drifted left; line is under the right sensor | **`steerRight()`** |
| **BothOnLine** | Wide line, crossroad, or intersection | **`moveForward()`** |

## Sense-Decide-Act Architecture

```text
readLineSensorState()
        ↓
LineSensorState
        ↓
chooseLineAction()
        ↓
LineAction
        ↓
executeLineAction()
        ↓
Motors
```

## Centered-Only Motor Test

For this experiment:

```text
BothBackground → moveForward()

LeftOnLine / RightOnLine / BothOnLine → stopMotors()
```

The robot starts centered and moves forward. It stops as soon as either sensor detects the line.

The battery percentage shown in Serial Monitor was not used because it was incorrectly calibrated.

## Forward PWM Experiment

| Left PWM | Right PWM | Drift direction | Min distance | Max distance | Average distance |
| ---: | ---: | --- | --- | --- | --- |
| 120 | 120 | Left | ~230 mm | ~240 mm | ~235 mm |
| 120 | 125 | Left | ~230 mm | ~245 mm | ~237 mm |
| 120 | 130 | Left | ~245 mm | ~440 mm | ~323 mm |
| 120 | 135 | Right | ~110 mm | ~250 mm | ~189 mm |

## Observations

- The robot drifted left at `120 / 120`.
- The robot drifted left at `125 / 120`.
- The robot drifted left at `130 / 120`.
- The robot drifted right at `135 / 120`.
- The battery percentage shown in Serial Monitor was unreliable.

## Correction PWM Experiment

| Test | Slow PWM | Normal PWM | Fast PWM | Result |
| --- | ---: | ---: | --- |
| 1 | Left: 80  Right: 80 | Left: 120  Right: 120 | Left: 150  Right: 150 | It is skewed quite a bit to the left and only moves a short distance. |
| 2 | Left: 80  Right: 85 | Left: 120  Right: 125 | Left: 150  Right: 155 |  |
| 3 | Left: 80  Right: 90 | Left: 120  Right: 130 | Left: 150  Right: 160 |  |
| 4 | Left: 80  Right: 95 | Left: 120  Right: 135 | Left: 150  Right: 165 |  |

## Straight-Line Tests

| Run | Track Length | Reached End? | Left Corrections | Right Corrections | Lost Line? |
| --- | --- | --- | --- | --- | --- |
| 1 |  |  |  |  |  |
| 2 |  |  |  |  |  |
| 3 |  |  |  |  |  |
| 4 |  |  |  |  |  |
| 5 |  |  |  |  |  |

## Curve Tests

| Attempt | Completed Curve? | Observation |
| --- | --- | --- |
| 1 |  |  |
| 2 |  |  |
| 3 |  |  |
| 4 |  |  |
| 5 |  |  |

## Start-Offset Experiment

| Start Position | Initial State | Recovered? | Time or Distance to Recover |
| --- | --- | --- | --- |
| Centered |  |  |  |
| Slightly left |  |  |  |
| Slightly right |  |  |  |

## Ambiguous BothBackground State

`BothBackground` can mean either:

1. The narrow line is correctly centered between the sensors.
2. The robot is outside the line and neither sensor sees it.

## Problems Observed

- _______________________________________________
- _______________________________________________
- _______________________________________________

## What I Would Improve Next

- _______________________________________________
- _______________________________________________
- _______________________________________________

## Most Interesting Observation

_______________________________________________