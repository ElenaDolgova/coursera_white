#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

long findMaxCost(int W, int n, vector<int> weights) {
    vector<vector<int>> matrix;

    for (int i = 0; i < n + 1; ++i) {
        vector<int> nv;
        matrix.push_back(nv);
        matrix[i].push_back(0);
    }

    for (int i = 0; i < W; ++i) {
        matrix[0].push_back(0);
    }

    for (int row = 1; row < n + 1; ++row) {
        int currWeight = weights[row - 1];
        for (int col = 1; col < W + 1; ++col) {
            int withoutCurrentWeight = matrix[row - 1][col];
            int index = col - currWeight;
            int tryWithCurrentWeight = 0;
            if (index >= 0) {
                tryWithCurrentWeight = matrix[row - 1][index] + currWeight;
            }
            matrix[row].push_back(max(withoutCurrentWeight, tryWithCurrentWeight));
        }
    }
    return matrix[n][W];
}

int main() {
    int W;
    int n;
    cin >> W;
    cin >> n;
    vector<int> weights;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        weights.push_back(k);
    }
    cout << findMaxCost(W, n, weights);
    return 0;
}
