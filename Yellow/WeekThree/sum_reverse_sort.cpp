#include "sum_reverse_sort.h"

#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    std::reverse(std::begin(s), std::end(s));
    return s;
}

void Sort(vector<int> &nums) {
    std::sort(nums.begin(), nums.end());
}
