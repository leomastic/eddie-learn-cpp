# Day22 Self Check — Basic Autonomous Line Following

Answer these in your own words after the practical work. Do not look for answers in code first.

1. Which pin is Eddie's left tracking sensor?
2. Which pin is Eddie's right tracking sensor?
3. What raw value did black tape produce on Eddie's robot?
4. What raw value did the white background produce?
5. What is the measured sensor-centre spacing?
6. What narrow line width was tested on Day21?
7. Why can `BothBackground` mean the robot is correctly centered on the narrow track?
8. Why can `BothBackground` also mean that the robot lost the line?
9. What information does `LineSensorState` represent?
10. What information does `LineAction` represent?
11. Why should sensor state and motor action be separate concepts?
12. What physical experiment determines which correction belongs to `LeftOnLine`?
13. What correction belongs to `RightOnLine` on Eddie's actual robot?
14. Why should you not simply guess the two correction directions?
15. What is closed-loop feedback control?
16. Why is a long `delay()` harmful in a line-following control loop?
17. Why is a gentle speed difference between the wheels more suitable here than a long obstacle-avoidance turn?
18. What can rapid switching between left and right sensor states tell you about the robot?
19. What does `BothOnLine` mean on a wide tape section or intersection, and what is the conservative Day22 action?
20. What experiment would you do before increasing the robot's speed?