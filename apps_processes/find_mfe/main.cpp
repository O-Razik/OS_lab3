#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

int findMostFrequentElement(const std::vector<std::vector<int>>& matrix) {
    std::unordered_map<int, int> elementFrequency;
    int mostFrequentElement = -1;
    int maxFrequency = 0;

    for (const auto& row : matrix) {
        for (int element : row) {
            elementFrequency[element]++;
            if (elementFrequency[element] > maxFrequency) {
                maxFrequency = elementFrequency[element];
                mostFrequentElement = element;
            }
        }
    }

    return mostFrequentElement;
}

int main(int argc, char* argv[]) {

    int n = atof(argv[1]), m = atof(argv[2]);
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }

    int result = findMostFrequentElement(matrix);
    std::cout << "Most Frequent Element: " << result << std::endl;
    getchar();
    return 0;
}
