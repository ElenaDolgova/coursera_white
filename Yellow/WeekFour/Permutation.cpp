#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> &vec) {
    for (int i = 0; i < vec.size() - 1; ++i) {
        cout << vec[i] << " ";
    }
    cout << vec[vec.size() - 1] << "\n";
}

void Permutation(int count) {
    vector<int> vec;
    for (int i = 1; i <= count; ++i) {
        vec.push_back(i);
    }

    std::sort(vec.begin(), vec.end());
    std::reverse(vec.begin(), vec.end());

    do {
        print(vec);
    } while (std::prev_permutation(vec.begin(), vec.end()));

}

int main() {
    int count;
    cin >> count;
    Permutation(count);
    return 0;
}
