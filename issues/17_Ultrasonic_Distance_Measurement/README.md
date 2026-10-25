# Day17 Ultrasonic Distance Measurement

## Hardware
Beetlebot 3-in-1 Smart Car (for Arduino):

+ Line following;

+ Light chasing;

+ Ultrasonic Obstacle Avoidance;

+ Infrared (Tia hong ngoai) Remote Control;

+ APP control;

+ USB charging.

## Ultrasonic Pins

TRIG: 8
ECHO: 7

## What I Learned

+ What is an Ultrasonic sensor? -> The Ultrasonic sensor measures distance using sound.

+ Trig and Echo
  + Trig (Trigger) -> The Arduino sends a short electrical pulse to the TRIG pin.
  + Echo -> Tells how long the Ultrasonic pulse took to travel to the object and return.

## How Ultrasonic Measurement Works

  sensor sends sound
          ↓
  sound travels forward
          ↓
  sound reaches object
          ↓
    sound reflects
          ↓
  echo travels back
          ↓
  sensor receives echo

## Why Distance Is Divided by Two

  Because the ECHO also count how long it tooks to return so its 2 times distance.

## Duration vs Distance

+ Duration is the time to travel and Distance is how long it takes to the obstacle.

+ Duration is type 'long' and Distance is type 'float'

+ distance = duration * 0.0343;

## Measurement Table

+ Realty: Expected Distance = 30
  Measurement: Avernge Distance = ~28.4678

+ Realty: Expected Distance = 20
  Measurement: Avernge Distance = ~19.4262

+ Realty: Expected Distance = 10
  Measurement: Avernge Distance = ~10.4022

## Object Angle Experiment
  When the object is flat (0-degree angle), readings are accurate. When angled beyond 45-degree angle, the sound bounces away from the sensor, leading to incorrect readings or timeout (duration == 0).

## Different Object Experiment
  + Real distance: 30cm
    + My pen: 31.916cm
    + My note book: ~26.8709cm

## Invalid / Missing Echo
Without a timeout, pulseIn() defaults to 1 second. Adding pulseIn(echoPin, HIGH, 30000) sets a 30 ms timeout. If no echo returns, duration becomes 0, and our function returns -1 to flag an invalid measurement.

## Known Measurement Problems
+ Small or thin objects (e.g., wires, pencils) don't reflect enough sound.

+ Angled objects reflect sound away.

+ Soft/sound-absorbing materials damp the echo.

+ Air currents or temperature shifts alter the speed of sound slightly.

## Most Interesting Observation
If i take an thin paper and put it in front of the sensor, sometimes the sensor SKIPS that paper!

//btw i calc by my bare hands so the measurement can be a little wrong