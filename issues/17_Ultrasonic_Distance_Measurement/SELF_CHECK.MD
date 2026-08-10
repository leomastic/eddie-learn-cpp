# 28. SELF_CHECK.md

1. **What does an ultrasonic sensor measure?**  
   It measures the time it takes for sound waves to travel to an object and bounce back, which is then used to calculate the physical distance to that object.

2. **Which KE3066 pin is TRIG?**  
   Pin **8**.

3. **Which KE3066 pin is ECHO?**  
   Pin **7**.

4. **Why is TRIG configured as OUTPUT?**  
   Because the Arduino sends digital signals out through the TRIG pin to command the sensor to emit sound bursts.

5. **Why is ECHO configured as INPUT?**  
   Because the ECHO pin sends signals into the Arduino to tell it when the returning sound wave has been received.

6. **What does the Arduino send through TRIG?**  
   A short 10-microsecond HIGH pulse signal.

7. **Why do we first set TRIG LOW?**  
   To ensure the pin is at a clean, stable 0V base voltage before sending the HIGH trigger pulse.

8. **What does `delayMicroseconds()` do?**  
   It pauses program execution for a specified number of microseconds.

9. **How many microseconds are in one second?**  
   1,000,000 (1 million) microseconds.

10. **What does `pulseIn(echoPin, HIGH)` measure?**  
    It measures how long (in time) the ECHO pin stays in a HIGH state.

11. **What unit does `pulseIn()` return?**  
    Microseconds (µs).

12. **Why do we store duration in a `long`?**  
    Because duration values in microseconds can easily exceed 32,767 (the maximum limit of a standard 16-bit `int`), which would cause an integer overflow.

13. **Why is distance stored in a `float`?**  
    Because distance calculations involve decimal values, requiring floating-point numbers for precision.

14. **Approximately how fast does sound travel in air?**  
    Approximately 343 m/s (or 0.0343 cm/µs).

15. **Why do we divide the calculated distance by 2?**  
    Because the measured time accounts for the round trip—the sound wave traveling out to the object and coming back. Dividing by 2 gives the one-way distance to the object.

16. **What happens physically between sending TRIG and receiving ECHO?**  
    After receiving the TRIG pulse, the sensor emits 8 ultrasonic sound bursts at 40 kHz, sets the ECHO pin HIGH, waits for the sound waves to bounce off an obstacle and return to the receiver, and then sets the ECHO pin LOW.

17. **Why can two measurements of the same object be slightly different?**  
    Minor fluctuations in room temperature, airflow, noise, sensor precision limits, or slight physical vibrations can cause tiny variations in sound speed and signal timing.

18. **Why can an angled object produce a bad measurement?**  
    If an object is tilted at an angle, the reflected sound wave bounces off to the side instead of returning directly back to the sensor receiver.

19. **What does a `pulseIn()` timeout protect the program from?**  
    It prevents the Arduino from freezing or hanging indefinitely if no obstacle is detected or if an echo is never received.

20. **What does `duration == 0` mean in our Day17 program?**  
    It means the sensor timed out without receiving a returning echo (no object was detected within range).

21. **Why does `measureDistanceCm()` return `-1` for an invalid measurement?**  
    It serves as an error code indicating that the reading failed, allowing `loop()` to easily check if the reading was valid before displaying or processing it.

22. **Why is putting the measurement logic in a function better than writing everything directly in `loop()`?**  
    It keeps the code clean, modular, easier to read, and reusable anywhere else in the program without duplicating code.

---

### **Personal Observations**

23. **Which object produced your most stable measurement?**  
    A flat, hard, smooth surface like a cardboard box or a thick book facing directly toward the sensor.

24. **At which tested distance was your sensor most accurate?**  
    Between 10 cm and 30 cm.

25. **What was the most surprising thing you discovered about the ultrasonic sensor?**  
    Soft materials (like fabric or sponge) absorb the sound waves and fail to reflect an echo, making them invisible or inaccurate to the sensor.