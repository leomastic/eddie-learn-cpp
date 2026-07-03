#include <iostream>
#include <vector>

int main() {
    std::vector<int> scores;

    scores.push_back(10);
    scores.push_back(15);
    scores.push_back(0);
    scores.push_back(10);

    std::cout << "===== Score List =====" << std::endl;

    for (int i = 0; i < scores.size(); i++) {
        std::cout << "Round " << i + 1 << ": "
                  << scores[i] << std::endl;
    }

    int total = 0;

    for (int score : scores) {
        total += score;
    }

    double average = static_cast<double>(total) / scores.size();

    int bestScore = scores[0];
    int worstScore = scores[0];

    for (int score : scores) {
        if (score > bestScore) {
            bestScore = score;
        }

        if (score < worstScore) {
            worstScore = score;
        }
    }

    std::cout << "===== Score Report =====" << std::endl;
    std::cout << "Total: " << total << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Best score: " << bestScore << std::endl;
    std::cout << "Worst score: " << worstScore << std::endl;

    return 0;
}