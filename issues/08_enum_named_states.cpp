#include <iostream>
#include <string>

int main() {
    enum class Grade {
        A,
        B,
        C,
        D,
        F
    };

    Grade currentGrade = Grade::C;

    currentGrade = Grade::F; // This line will cause a compilation error because 'J' is not a valid Grade value.
    
    switch (currentGrade) {
        case Grade::A:
            std::cout << "The student received an A." << std::endl;
            break;
        case Grade::B:
            std::cout << "The student received a B." << std::endl;
            break;
        case Grade::C:
            std::cout << "The student received a C." << std::endl;
            break;
        case Grade::D:
            std::cout << "The student received a D." << std::endl;
            break;
        case Grade::F:
            std::cout << "The student received an F." << std::endl;
            break;
    }

    return 0;
}