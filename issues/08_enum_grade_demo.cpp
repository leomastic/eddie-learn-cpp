#include <iostream>
#include <string>

enum class Grade {
    A,
    B,
    C,
    D,
    F
};

std::string gradeToString(Grade grade) {
    if (grade == Grade::A) {
        return "A";
    }

    if (grade == Grade::B) {
        return "B";
    }

    if (grade == Grade::C) {
        return "C";
    }

    if (grade == Grade::D) {
        return "D";
    }

    return "F";
}

Grade calculateGradeByAverage(double average) {
    if (average >= 90.0) {
        return Grade::A;
    }

    if (average >= 80.0) {
        return Grade::B;
    }

    if (average >= 70.0) {
        return Grade::C;
    }

    if (average >= 60.0) {
        return Grade::D;
    }

    return Grade::F;
}

int main() {
    double average;

    std::cout << "Input average score: ";
    std::cin >> average;

    Grade grade = calculateGradeByAverage(average);

    std::cout << "Grade: " << gradeToString(grade) << std::endl;

    return 0;
}