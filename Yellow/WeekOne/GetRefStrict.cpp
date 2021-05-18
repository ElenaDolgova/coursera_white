#include <iostream>
#include <map>

using namespace std;

template<typename Key, typename Value>
Value &GetRefStrict(map<Key, Value> &m, Key k) {
    try {
        return m.at(k);
    } catch (exception& e) {
        throw runtime_error("");
    }
}

int main() {
    map<int, string> m = {{0, "value"}};
    string &item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
}