#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

int inputIntVariable(std::string name) {
    int v;
    std::cout << "Enter the " + name + ": ";
    while (!(std::cin >> v)) {
        std::cout << "Invalid input for " + name + "\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return v;
}
double inputDoubleVariable(std::string name) {
    double v;
    std::cout << "Enter the " + name + ": ";
    while (!(std::cin >> v)) {
        std::cout << "Invalid input for " + name + "\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return v;
}
bool inputBoolVariable(std::string name) {
    bool v;
    std::cout << "Enter the " + name + " (1 for yes, 0 for no): ";
    while (!(std::cin >> v)) {
        std::cout << "Invalid input for " + name + " status\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return v;
}
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main() {
    std::cout << "Enter the hero name: ";
    std::string heroName;
    std::cin >> heroName;

    
    int heroHp = inputIntVariable("HP");

    int heroAtk = inputIntVariable("ATK");
    
    double heroSpeed = inputDoubleVariable("Speed");

    bool hasSword = inputBoolVariable("Has Sword");

    std::cout << "=================Hero Info=================" << std::endl;
    std::cout << "Hero Name: " << heroName << std::endl;
    std::cout << "Hero HP: " << heroHp << std::endl;
    std::cout << "Hero ATK: " << heroAtk << std::endl;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Hero Speed: " << heroSpeed << std::endl;
    std::cout << "Hero has sword: " << (hasSword ? "Yes" : "No") << std::endl;

    double x1 = inputDoubleVariable("first character x");
    double y1 = inputDoubleVariable("first character y");
    double x2 = inputDoubleVariable("second character x");
    double y2 = inputDoubleVariable("second character y");
    double d = distance(x1, y1, x2, y2);
    std::cout << "The distance between two characters is: " << d << " m\n";

    return 0;
}
