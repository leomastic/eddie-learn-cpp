# Day16 Motor Control Fundamentals

## Hardware

This sketch controls the KE3066 motor driver and demonstrates basic movement, turning, and calibration for a differential-drive robot.

## Motor Pins

- Left direction pin: D4
- Left speed pin: D6
- Right direction pin: D2
- Right speed pin: D5

## What I Learned

The Arduino can control motor direction with digital output and motor speed with PWM.

## Left vs Right Motor Difference

The left and right motors do not produce exactly the same mechanical power for the same PWM value.

Observed stronger motor: right motor
Observed weaker motor: left motor

Why equal PWM does not produce straight motion:
Equal PWM values can still produce different wheel motion because the motors, gearbox friction, wheel contact, battery voltage, and chassis alignment are not perfectly identical. The right motor needs more PWM to match the left motor during straight driving.

## Minimum Reliable PWM

- Left: 90
- Right: 120

## Straight-Line Calibration

- Left PWM: 120
- Right PWM: 165

## Turn Calibration

| Motion | Left PWM | Right PWM | Observation |
| --- | ---: | ---: | --- |
| Forward slow | 120 | 165 | Straight motion improved |
| Forward medium | 120 | 165 | Used for standard forward movement |
| Forward fast | 200 | 255 | Intentionally clamped for validation demo |
| Backward | 120 | 110 | Backward movement tested |
| Left turn from stop | 90 | 170 | Used for a reliable left turn from rest |
| Left turn while moving | 120 | 150 | Used for a left turn while already moving |
| Right turn from stop | 170 | 90 | Used for a reliable right turn from rest |
| Right turn while moving | 150 | 120 | Used for a right turn while already moving |

## From-Stop vs While-Moving Turns

Turns started from rest and turns made while the robot is already moving need different PWM values because static friction and inertia are higher at the moment of starting motion.

## Known Issues

- Real hardware behavior can vary with battery charge and floor surface.
- The calibration values should be rechecked if the robot is tested on a different surface.

## Experiments

- Motor control fundamentals sketch
- Battery voltage experiment sketch
