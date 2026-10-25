# Self Check

## 1. Which module should own the robot status rules?
Robot should own its own status rules because the status depends on its battery level, operating hours, error state, and maintenance state.

## 2. Which module should own technician assignment state?
Technician should own assignment state because assignment and completion are technician-specific behaviors.

## 3. Which module should coordinate the full center workflow?
MaintenanceCenter should coordinate the center workflow because it manages both robot and technician collections and the cross-object operations.

## 4. Why should main.cpp stay simple?
main.cpp should focus on user interaction and menu flow, while business rules remain in the model classes.

## 5. Why are the robot and technician IDs checked before insertion?
They are checked before insertion to prevent duplicate entries and keep the center data consistent.

## 6. Why is the battery stored as a dedicated class?
Battery is a dedicated class because battery behavior such as clamping, charging, and consumption should be encapsulated and reused by robots.

## 7. What problem did the original duplicate-add path cause?
The original menu flow used temporary local data instead of the center’s stored data, so duplicate checks did not work correctly.

## 8. How was the bug fixed?
The menu flow now uses MaintenanceCenter directly for duplicate checks and insertion, so the real collection is enforced.

## 9. What issue did the console input handling have?
The console input helpers could mishandle line-based names after numeric prompts because the newline buffer was not always consumed correctly.

## 10. How was the input issue fixed?
The input helpers were adjusted to handle line-based names reliably and to read full lines for names with spaces.

## 11. Which status transitions were corrected?
The charging stop flow and maintenance transitions were corrected so the robot status changes to the right state after charging or completion.

## 12. Why does the robot constructor clamp or normalize operating hours?
Negative operating hours should not be accepted, so the constructor normalizes them to zero to keep the object valid.

## 13. What does a robot need to be considered ready?
A robot is ready when it has no active error, is not under maintenance, is not charging, and is not out of service.

## 14. When should a robot be marked for maintenance?
A robot should be marked for maintenance when it has an error or has accumulated enough operating hours.

## 15. When should a robot be marked out of service?
A robot is out of service when its battery is empty.

## 16. What happens when a robot is charging?
A robot enters charging mode and should not accept battery consumption until charging is stopped.

## 17. Why should maintenance assignment be rejected for a ready robot?
A ready robot should not be assigned for maintenance because it is not currently in a maintenance-needed state.

## 18. Why should a technician be unavailable while assigned?
A technician should be unavailable while assigned so the center does not double-book the same technician.

## 19. Why should maintenance completion clear the assignment?
Completion should clear the assignment because the technician is no longer busy with that robot.

## 20. What does the summary output report?
The summary reports total robots, total technicians, availability counts, average battery, and the most experienced technician.

## 21. What was the main testing strategy used?
The project used regression tests that exercise normal, invalid, and edge-case flows across the full center behavior.

## 22. Which test scenario was most important for the duplicate-add bug?
The duplicate robot and technician ID tests were crucial because they validate the core insertion rules.

## 23. Which test scenario validates maintenance assignment rules?
The test covering assignment to a busy technician and assignment of a ready robot validates those rules.

## 24. Which test scenario validates charging behavior?
The tests for starting charging, charging to the cap, and stopping charging validate charging behavior.

## 25. Which test scenario validates battery consumption rules?
The tests for consuming battery and rejecting consumption while charging validate those rules.

## 26. Which test scenario validates the center summary logic?
The larger mixed-state test validates the robot counts, technician availability counts, and summary-related metrics.

## 27. What did the regression test output show?
The regression suite completed successfully and printed: All RobotMaintenanceCenter-Day14 regression tests passed.

## 28. What change improved the menu wording?
The menu text was updated to use clearer phrases that match the assignment-style wording more closely.

## 29. What change improved the name entry experience?
Robot and technician names can now be entered as full lines with spaces, which is more user-friendly.

## 30. What was the main lesson from this exercise?
The main lesson is that validation and state transitions should be enforced in the domain classes, and the menu should delegate to those classes rather than handling rules locally.
