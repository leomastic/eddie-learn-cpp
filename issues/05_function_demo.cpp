#include <iostream>
#include <string>

void printSeparator() {
    std::cout << "------------------------" << std::endl;
}

void greet(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int add(int a, int b) {
    return a + b;
}

bool isTeenager(int age) {
    return age >= 13 && age <= 19;
}

int main() {
    std::string name;
    int age;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Age: ";
    std::cin >> age;

    printSeparator();
    greet(name);

    int result = add(3, 5);
    std::cout << "3 + 5 = " << result << std::endl;

    if (isTeenager(age)) {
        std::cout << name << " is a teenager." << std::endl;
    } else {
        std::cout << name << " is not a teenager." << std::endl;
    }

    printSeparator();

    return 0;
}