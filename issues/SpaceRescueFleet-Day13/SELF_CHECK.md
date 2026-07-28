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
        int Energy_;    |   variables
        int Stantity_;  |   or attributes
}

2. Why does Robot contain a Battery object instead of only storing an integer?

because its called Encapsulation. A robot class can't store all of that because we can't read all, and it takes up many lines of code. So we divide it to many classes for easier to read.

3. Who is responsible for keeping the battery level between 0 and 100?

std::clamp help keeping the battery level between 0 and 100 so it cant bo smaller or bigger.

4. Why is Battery::level_ private?

because if its public, people can change it to illegal numbers.

5. Why should Robot call battery_.consume() instead of changing the battery level directly?

makes it have more features

6. What does this initializer do?

battery_(batteryLevel)

that initializer makes that when the battery_ is created directly using the batteryLevel value.