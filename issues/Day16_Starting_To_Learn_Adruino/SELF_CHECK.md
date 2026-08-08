# Self Check

## What does setup() do?
It prepares the serial connection and configures the motor control pins as outputs before the program starts moving the robot.

## What does loop() do?
It runs the movement sequence repeatedly so the robot can demonstrate stop, forward, backward, and turning behavior.

## Why are the motor pins OUTPUT?
The Arduino must send control signals to the motor driver, so the pins need to be configured as outputs.

## What does digitalWrite() control here?
It controls the motor direction pin state for the left and right motors.

## What does analogWrite() control?
It controls the PWM duty cycle that sets the motor speed.

## What is PWM?
PWM is pulse-width modulation, which changes the average power delivered to a motor by switching a signal on and off very quickly.

## What PWM range are you using?
The code uses a range from 0 to 255.

## Why might a low PWM fail to rotate a real motor?
A low PWM value may not provide enough torque to overcome static friction and start the motor moving.

## Why does the right motor require a different PWM value?
The right motor is physically weaker than the left one, so it needs a higher PWM value to produce similar motion.

## Does equal PWM guarantee equal physical wheel speed? Why?
No. Motors, friction, alignment, and battery voltage can make the wheels behave differently even when the code sends the same PWM value.

## Why does turning from rest require different motor effort?
The robot must overcome static friction and inertia when starting from rest, so turning from a stopped state needs a different amount of drive than turning while already moving.

## What is static friction, based on what you observed?
Static friction is the resistance that must be overcome to start motion from a stop. I observed that the car needs extra effort to begin turning from rest.

## Why did you originally add isStopped?
It was meant to let the turn logic use different PWM values depending on whether the robot was starting from rest or already moving.

## Why is TurnMode::FromStop clearer than true?
The enum name explains the intent directly, instead of relying on a vague boolean meaning.

## What is the difference between an arc turn and a pivot turn?
An arc turn moves the robot in a curved path while both wheels still rotate forward, while a pivot turn rotates the robot around one wheel or axle.

## Which turning method are you currently using?
The current sketch uses an arc turn with asymmetric PWM values.

## Why do you validate speed before analogWrite()?
Validation keeps the PWM values inside the safe 0 to 255 range before they are sent to the motor driver.

## Why are movement helper functions useful?
They keep the code easier to read, reduce repetition, and make it clearer which behavior is being commanded.

## Why should motor calibration be documented outside the code?
Hardware behavior changes over time and across environments, so documentation makes the tuning easier to understand and maintain.

## Describe the most surprising physical behavior you discovered.
The right motor needs more PWM than the left motor to make the car move straight, and the robot behaves differently when turning from rest versus while already moving.
