#include <vector>
#include <algorithm>
#include <iostream>

bool isNegative(int num) {
    return num < 0;
}

void PrintVectorPart(const std::vector<int> &numbers) {
    auto it = std::find_if(numbers.begin(), numbers.end(), isNegative);

    for (auto i = it; i != numbers.begin();) {
        --i;
        std::cout << *(i) << " ";
    }
}
