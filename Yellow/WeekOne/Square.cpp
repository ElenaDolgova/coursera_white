#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template<typename T>
T Sqr(T p);

template<typename T>
vector<T> Sqr(vector<T> &vec);

template<typename T, typename S>
map<T, S> Sqr(map<T, S> &vec);

template<typename T, typename S>
pair<T, S> Sqr(pair<T, S> p);

template<typename T, typename S>
pair<T, S> operator*(pair<T, S> first, pair<T, S> second);

template<typename T, typename S>
map<T, S> operator*(map<T, S> first, map<T, S> second);

template<typename T>
vector<T> operator*(vector<T> first, vector<T> second);



template<typename T, typename S>
pair<T, S> operator*(pair<T, S> first, pair<T, S> second) {
    pair<T, S> newPair = {first.first * second.first, first.second * second.second};
    return newPair;
}

template<typename T, typename S>
map<T, S> operator*(map<T, S> first, map<T, S> second) {
    map<T, S> newMap;
    for (const auto &p: first) {
        newMap[p.first] = p.second * p.second;
    }
    return newMap;
}

template<typename T>
vector<T> operator*(vector<T> first, vector<T> second) {
    vector<T> newVector;
    newVector.reserve(first.size());
    for (const auto &p: first) {
        newVector.push_back(p * p);
    }
    return newVector;
}

template<typename T>
vector<T> Sqr(vector<T> &vec) {
    vector<T> newVector;
    newVector.reserve(vec.size());
    for (const auto &p : vec) {
        newVector.push_back(Sqr(p));
    }
    return newVector;
}

template<typename T, typename S>
map<T, S> Sqr(map<T, S> &vec) {
    map<T, S> newMap;

    for (const auto &p:vec) {
        newMap[p.first] = Sqr(p.second);
    }

    return newMap;
}

template<typename T, typename S>
pair<T, S> Sqr(pair<T, S> p) {
    pair<T, S> newPair = {Sqr(p.first), Sqr(p.second)};
    return newPair;
}

template<typename T>
T Sqr(T p) {
    return p * p;
}


int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    cout << endl;

    vector<pair<int, double>> v2 = {{5, 2},
                                    {3, 4}};
    for (pair<int, double> x : Sqr(v2)) {
        cout << x.first << " " << x.second << endl;
    }
    cout << endl;

    vector<map<int, pair<int, int>>> v1 = {{
                                                   {4, {2, 2}},
                                                   {7, {4, 3}}
                                           },
                                           {
                                                   {5, {2, 2}},
                                                   {6, {4, 3}}
                                           },
                                           {
                                                   {7, {2, 2}},
                                                   {8, {4, 3}}
                                           }
    };

    for (const auto &x : Sqr(v1)) {
        for (const auto &p : x) {
            cout << p.first << ' ' << p.second.first << ' ' << p.second.second << endl;
        }
    }

    cout << endl;
    map<int, vector<int>> v3 = {
            {1, {4, 3, 5}},
            {3, {9, 3, 5}},
    };

    for (const auto &x : Sqr(v3)) {
        cout << x.first << " ";
        for (const auto &p : x.second) {
            cout << p << " ";
        }
        cout << endl;
    }
}
