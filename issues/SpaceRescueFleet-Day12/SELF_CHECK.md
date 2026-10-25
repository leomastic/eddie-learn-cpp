1. Why is a class better than a struct here?

A class is better because it can group both data and behavior together. That makes the robot easier to manage, reuse, and protect from invalid state changes.

2. Which functions became member functions?

The functions that operate on the robot’s own state became member functions, such as `print()`, `reset()`, `stateToString()`, and `actionToString()`.

3. Why is battery private?

Battery should be private so the class can control how it is changed and keep its state valid.

4. Why can't outside code modify battery directly?

Outside code should not modify it directly because that could break rules or leave the robot in an inconsistent state. Access should go through methods that validate the value.

5. Why is print() const?

`print()` is `const` because it only reads the object and does not change its state.

6. What does this point to?

`this` points to the current object instance that is calling the member function.

7. Why is Robot now responsible for its own behavior?

Because the robot knows its own state and should manage its own actions, instead of letting other code manipulate it directly.

8. Which data members should remain private?

Data that should be protected by rules, such as `batteryLevel`, `distanceToObstacle`, and other state fields that must stay valid, should remain private.

9. When would you still choose a struct instead of a class?

A struct is still a good choice for simple data containers where there is no behavior and no need for encapsulation, such as a point, a config record, or a small bundle of values.

10. What advantages did the refactoring bring?

The refactoring made the design cleaner, improved encapsulation, reduced the chance of bugs, and made the robot easier to extend and maintain.
