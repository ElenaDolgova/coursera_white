#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> SplitIntoWords(const string &s) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    char delim = ' ';
    while (std::getline(ss, item, delim)) {
        elems.push_back(std::move(item));
    }
    return elems;
}
//
//int main() {
//    string s = "C Cpp Java Python";
//
//    vector<string> words = SplitIntoWords(s);
//    cout << words.size() << " ";
//    for (auto it = begin(words); it != end(words); ++it) {
//        if (it != begin(words)) {
//            cout << "/";
//        }
//        cout << *it;
//    }
//    cout << endl;
//
//    return 0;
//}

