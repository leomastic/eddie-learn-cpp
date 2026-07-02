#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int mathScore;
    int scienceScore;
    int codingScore;
};

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue << std::endl;
            continue;
        }

        return value;
    }
}

Student readStudent(int studentNumber) {
    Student student;

    std::cout << std::endl;
    std::cout << "Student " << studentNumber << std::endl;

    std::cout << "Student name (no space): ";
    std::cin >> student.name;

    student.mathScore = readIntInRange("Math score (0-100): ", 0, 100);
    student.scienceScore = readIntInRange("Science score (0-100): ", 0, 100);
    student.codingScore = readIntInRange("Coding score (0-100): ", 0, 100);

    return student;
}

double calculateAverage(const Student& student) {
    return (student.mathScore + student.scienceScore + student.codingScore) / 3.0;
}

bool hasVeryLowSubject(const Student& student) {
    return student.mathScore < 40 || student.scienceScore < 40 || student.codingScore < 40;
}

bool isPassed(const Student& student) {
    return calculateAverage(student) >= 60.0 &&
           !hasVeryLowSubject(student);
}

char calculateGrade(const Student& student) {
    if (!isPassed(student)) {
        return 'F';
    }

    double average = calculateAverage(student);

    if (average >= 90.0) {
        return 'A';
    }

    if (average >= 80.0) {
        return 'B';
    }

    if (average >= 70.0) {
        return 'C';
    }

    if (average >= 60.0) {
        return 'D';
    }

    return 'F';
}

bool isExcellent(const Student& student) {
    return calculateAverage(student) >= 90.0
           && student.mathScore >= 85
           && student.scienceScore >= 85
           && student.codingScore >= 85
           && !hasVeryLowSubject(student);
}

double calculateClassAverage(const std::vector<Student>& students) {
    if (students.size() == 0) {
        return 0.0;
    }

    double total = 0.0;

    for (const Student& student : students) {
        total += calculateAverage(student);
    }

    return total / students.size();
}

int countPassedStudents(const std::vector<Student>& students) {
    std::size_t count = 0;

    for (const Student& student : students) {
        if (isPassed(student)) {
            count++;
        }
    }

    return count;
}

int countFailedStudents(const std::vector<Student>& students) {
    std::size_t count = 0;

    for (const Student& student : students) {
        if (!isPassed(student)) {
            count++;
        }
    }

    return count;
}

int countExcellentStudents(const std::vector<Student>& students) {
    std::size_t count = 0;

    for (const Student& student : students) {
        if (isExcellent(student)) {
            count++;
        }
    }

    return count;
}

int findBestStudentIndex(const std::vector<Student>& students) {
    if (students.size() == 0) {
        return -1;
    }

    std::size_t bestIndex = 0;
    double bestAverage = calculateAverage(students[0]);

    for (std::size_t i = 1; i < students.size(); i++) {
        double average = calculateAverage(students[i]);

        if (average > bestAverage) {
            bestAverage = average;
            bestIndex = i;
        }
    }

    return bestIndex;
}

int findWeakestStudentIndex(const std::vector<Student>& students) {
    if (students.size() == 0) {
        return -1;
    }

    std::size_t weakestIndex = 0;
    double weakestAverage = calculateAverage(students[0]);

    for (std::size_t i = 1; i < students.size(); i++) {
        double average = calculateAverage(students[i]);

        if (average < weakestAverage) {
            weakestAverage = average;
            weakestIndex = i;
        }
    }

    return weakestIndex;
}

void printStudentReport(const std::vector<Student>& students) {
    std::cout << std::endl;
    std::cout << "===== Student Report =====" << std::endl;

    for (std::size_t i = 0; i < students.size(); i++) {
        const Student& student = students[i];

        std::cout << "Student " << i + 1
                  << " | Name: " << student.name
                  << " | Math: " << student.mathScore
                  << " | Science: " << student.scienceScore
                  << " | Coding: " << student.codingScore
                  << " | Average: " << calculateAverage(student)
                  << " | Grade: " << calculateGrade(student)
                  << " | Status: " << (isPassed(student) ? "PASS" : "FAIL")
                  << std::endl;
    }
}

int main() {
    std::cout << "===== Space Student Grade Manager =====" << std::endl;

    std::cout << "Teacher name: ";
    std::string teacherName;
    std::cin >> teacherName;

    int studentCount = readIntInRange("Number of students (1-10): ", 1, 10);

    std::vector<Student> students;

    for (std::size_t i = 1; i <= studentCount; i++) {
        Student student = readStudent(i);
        students.push_back(student);

        std::cout << "Average: " << calculateAverage(student) << std::endl;
        std::cout << "Grade: " << calculateGrade(student) << std::endl;

        if (isPassed(student)) {
            std::cout << "Status: PASS" << std::endl;
        } else {
            std::cout << "Status: FAIL" << std::endl;
        }

        if (isExcellent(student)) {
            std::cout << "Excellent student!" << std::endl;
        }
    }

    double classAverage = calculateClassAverage(students);
    int passedCount = countPassedStudents(students);
    int failedCount = countFailedStudents(students);
    int excellentCount = countExcellentStudents(students);
    int bestIndex = findBestStudentIndex(students);
    int weakestIndex = findWeakestStudentIndex(students);

    std::cout << std::endl;
    std::cout << "===== Class Summary =====" << std::endl;
    std::cout << "Teacher: " << teacherName << std::endl;
    std::cout << "Total students: " << studentCount << std::endl;
    std::cout << "Class average: " << classAverage << std::endl;
    std::cout << "Passed students: " << passedCount << std::endl;
    std::cout << "Failed students: " << failedCount << std::endl;
    std::cout << "Excellent students: " << excellentCount << std::endl;

    if (bestIndex >= 0) {
        std::cout << "Best student: "
                  << students[bestIndex].name
                  << " with average "
                  << calculateAverage(students[bestIndex])
                  << std::endl;
    }

    if (weakestIndex >= 0) {
        std::cout << "Weakest student: "
                  << students[weakestIndex].name
                  << " with average "
                  << calculateAverage(students[weakestIndex])
                  << std::endl;
    }

    printStudentReport(students);

    return 0;
}