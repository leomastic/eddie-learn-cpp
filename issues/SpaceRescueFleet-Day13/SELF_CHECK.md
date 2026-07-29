1. What is composition in object-oriented programming?

Composition example:

class Human {
    public:
        Human(Energy, Stantity)         |    constructor Human() {} 
            : Energy_(Energy),          |    initialize lists
              Stantity_(Stantity) {     |
        }

        void restoreEnergy() {                                      |
            std::cout << "This person is restoring energy\n";       |
        }                                                           |   functions
                                                                    |   or methods
        void restoreStantity() {                                    |
            std::cout << "This person is restoring stantity\n";     |
        }                                                           |
                                                                    |
        void lostEnergy() {                                         |
            std::cout << "This person is loosing energy\n";         |
        }                                                           |

    private:
        Energy Energy_;      |   variables
        Stantity Stantity_;  |   or attributes
}                            |   or a class that contains an object of another class.

2. Why does Robot contain a Battery object instead of only storing an integer?

its called Composition. A robot class can't store all of that because we can't read all, and it takes up many lines of code. So we divide it to many classes for easier to read.

3. Who is responsible for keeping the battery level between 0 and 100?

The Battery class is responsible for maintaining the invariant.

4. Why is Battery::level_ private?

because if its public, people can change it to illegal numbers.

5. Why should Robot call battery_.consume() instead of changing the battery level directly?

+ Prevent the level from dropping below 0

+ Centralize rules in one place

+ Prevent the Robot from violating the Battery's encapsulation

6. What does this initializer do?
battery_(batteryLevel)

that initializer makes that when the battery_ is created directly using the batteryLevel value.

7. When is the Battery object created relative to the body of Robot::Robot()?

after Robot::Robot(...) :
before {...}

8. Why should initializer-list order match member declaration order?

You should list members in the initializer list in the same order as they are declared in the class to avoid unnecessary errors.

9. Why is Battery::level() declared const?

The `Battery::level()` function is declared as `const` because it is a read-only function. It simply returns the current battery percentage value without modifying any data or the state of the `Battery` object.

10. Why is this design better?


battery_.consume(5);

than:

batteryLevel_ -= 5;

because:

`batteryLevel_ -= 5;`: This could result in a negative battery level (e.g., 2 - 5 = -3), violating the invariant that the battery level must remain between 0% and 100%. `battery_.consume(5);`: The `consume` method automatically checks the condition; if the battery level is below 5, it prevents the operation, caps the value at 0, or raises an error to protect the system.

11. What happens if consume() receives an amount larger than the remaining battery?
the battery will stop consuming at 0

12. Which class owns the rule that battery below 15 is considered low?

class Battery.


13. Why should calculateNextState() not contain the literal number 15 anymore?

because of encapsulation


14. What advantage does BatteryStatus provide compared with returning only an integer?

It offers the benefit of distinguishing the battery's condition, rather than simply displaying the remaining battery level.

15. What was the hardest part of this refactor?

idk