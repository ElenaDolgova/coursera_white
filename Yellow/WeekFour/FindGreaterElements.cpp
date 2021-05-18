#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
    auto it = std::find_if(elements.begin(), elements.end(),
                           [&](T number) {
                               return number > border;
                           });

    vector<T> r;
    for (auto i = it; i != elements.end(); ++i) {
        r.push_back(*(i));
    }
    return r;
}


//template <typename T>
//vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
//    // Начнём итерироваться по множеству
//    auto it = begin(elements);
//    // Цель — найти первый элемент, больший border
//    // Если итератор не достиг конца и указывает не туда, двигаем
//    while (it != end(elements) && *it <= border) {
//        ++it;
//    }
//    // Возвращаем вектор, созданный из элементов множества, начиная с it
//    return {it, end(elements)};
//}
