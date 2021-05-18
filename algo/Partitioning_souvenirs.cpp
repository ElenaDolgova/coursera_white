#include <iostream>
#include <vector>
#include <algorithm>

//You and two of your friends have just returned back home after visiting various countries. Now you would like to evenly split all the souvenirs that all three of you bought.
//Problem Description
//Input Format. The first line contains an integer 𝑛. The second line contains integers 𝑣1 , 𝑣2 , . . . , 𝑣𝑛 separated by spaces.
//Constraints. 1≤𝑛≤20,1≤𝑣𝑖 ≤30forall𝑖.
//Output Format. Output 1, if it possible to partition 𝑣1, 𝑣2, . . . , 𝑣𝑛 into three subsets with equal sums, and
//0 otherwise.

//Понятно, что у каждого члена группы должно быть треть веса
// Переформулировать задачу можно так: Можно ли разбить множество весов на три кучки, чтобы в каждой кучке было x
void find_out(const std::vector<int> &souvenirs, int total_in_one_weight) {

    std::vector<std::vector<bool>> P;
    std::vector<std::vector<int>> W;

    for (int i = 0; i <= total_in_one_weight; ++i) {
        std::vector<bool> p;
        std::vector<int> w;
        if (i == 0) { // первая строка
            for (int j = 0; j <= souvenirs.size(); ++j) {
                p.push_back(true);
                w.push_back(0);
            }
        } else {
            p.push_back(false);
            w.push_back(0);
        }
        W.push_back(w);
        P.push_back(p);
    }
    int count = 0;
    for (int row = 1; row <= total_in_one_weight; ++row) {
        for (int col = 1; col <= souvenirs.size(); ++col) {
            int previousRowOfSet =
                    row - souvenirs[col - 1]; // <=> row >= souvenirs[col - 1] <=> souvenirs[col - 1] <= row
            if (previousRowOfSet >= 0) {
                bool value = P[row][col - 1] || P[previousRowOfSet][col - 1];
                P[row].push_back(value);

                int newWeight = W[previousRowOfSet][col - 1] + souvenirs[col - 1];
                W[row].push_back(std::max(newWeight, W[row][col - 1]));
            } else {
                P[row].push_back(P[row][col - 1]);
                W[row].push_back(W[row][col - 1]);
            }
            if (W[row][col] == total_in_one_weight) {
                ++count;
            }
        }
    }

    if (count >= 3) {
        std::cout
//        << 1 << " "
                << P[total_in_one_weight][souvenirs.size()];
    } else {
        std::cout
//        << 0 << " "
                << P[total_in_one_weight][souvenirs.size()];
    }

//    return;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> souvenirs;
    int sum = 0;

    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        sum += k;
        souvenirs.push_back(k);
    }

    if (sum % 3 != 0 || souvenirs.size() < 3) {
        std::cout << 0;
    } else {
        find_out(souvenirs, sum / 3);
    }


    return 0;
}