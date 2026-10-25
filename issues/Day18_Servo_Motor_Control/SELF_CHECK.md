# SELF_CHECK.md

1. What is a servo motor?
A servo motor is a rotary actuator that provides precise control over angular position. Unlike regular DC motors, it moves to a specified angle and actively holds that position.

2. Which KE3066 pin controls the servo?
Digital Pin 9 (`D9`).

3. What does #include <Servo.h> do?
It imports the official Arduino Servo library into the sketch, providing pre-written functions to control servo motors.

4. What is Servo scanServo;?
It declares a `Servo` object instance named `scanServo`, serving as the software representation of the physical servo motor.

5. What does scanServo.attach(servoPin) do?
It connects the software `scanServo` object to the physical pin specified by `servoPin` (`D9`), enabling signal communication.

6. What does scanServo.write(90) mean?
It commands the servo to move to the angular position corresponding to 90 degrees.

7. Does Servo.write(150) mean the same thing as analogWrite(motorPin, 150)? Explain.
No, they mean completely different things:
* `analogWrite(motorPin, 150)` controls **motor speed/power** using PWM duty cycle.
* `scanServo.write(150)` commands an **angular position** of 150 degrees.

8. What is the difference between a DC wheel motor and a positional servo?
A DC wheel motor rotates continuously to provide speed and direction. A positional servo moves to a target angle within a constrained range (usually 0°–180°) and maintains that angle.

9. Why do we use delay() after commanding a servo position in today's experiments?
Software changes state almost instantaneously, but the physical servo mechanism needs time to physically rotate to its target position.

10. Does calling write(90) prove that the real mechanism is physically at exactly 90°? Why or why not?
No. `write(90)` sends a target command, but physical alignment, mechanical tolerances, gear backlash, and mounting angles can cause the actual position to differ.

11. Why might software 90° not point perfectly forward on your robot?
Because the physical servo horn or mounting bracket may be attached at a slight angle relative to the internal gear positioning.

12. Why should you not assume 0° and 180° are mechanically safe?
The assembled robot structure, sensor bracket, or wiring may block full 0°–180° rotation, causing physical strain or mechanical binding before reaching those extremes.

13. What physical signs tell you that a servo may be reaching an unsafe limit?
* A strained buzzing or humming sound.
* The bracket pressing against another robot component.
* Visible shaking or structural bending.
* Tightly pulled wiring cables.

14. What safe left angle did you find?
160° left

15. What center angle did you find?
93°

16. What safe right angle did you find?
21° right

17. Why are named constants such as servoCenterAngle better than repeatedly writing a number like 92?
Named constants make code readable, self-documenting, and easy to maintain. If calibration changes later, you only update the value in one location.

18. What does validServoAngle() do?
It validates software input angles before sending them to `write()`, ensuring values do not fall out of bounds or cause unexpected behavior.

19. What is the difference between the Servo library's valid angle range and your robot's safe mechanical range?
* **Software Valid Range:** `0°` to `180°` (what `Servo.write()` accepts).
* **Safe Mechanical Range:** `21°` to `160°` (the physical limit where the assembled robot mechanism can safely move without obstruction).

20. Why is moveServoTo() useful?
It encapsulates input validation, position writing, and serial debugging output into a single reusable function.

21. Did your servo return to approximately the same center after moving left and right?
Yes, the servo consistently returned to the calibrated center (`93°`).

22. Did you notice shaking, buzzing, overshoot, or inconsistent movement?
The movement was generally smooth. Minor buzzing only occurred if held manually or near structural strain points.

23. Could you clearly observe a 10° position change?
Yes, a 10° shift produced a clearly visible rotation of the ultrasonic sensor bracket.

24. Could you clearly observe a 5° position change?
Yes, a 5° shift produced a subtle but observable physical change upon normal inspection.

25. What was the most surprising physical behavior you discovered?
There was a consistent ~3° offset between commanded software angles and physical output angles (e.g., commanding `90°` resulted in a physical ~`87°` direction, requiring `93°` for true center).