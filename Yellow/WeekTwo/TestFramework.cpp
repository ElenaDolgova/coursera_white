#pragma once

#include "TestFramework.hpp"

using namespace std;

inline void AssertTrue(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

inline void AssertFalse(bool b, const string &hint) {
    AssertEqual(b, false, hint);
}

template<class TestFunc>
void TestRunner::RunTest(TestFunc func, const std::string &test_name) {
    try {
        func();
        cerr << test_name << " OK" << endl;
    } catch (runtime_error &e) {
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
    }
}

TestRunner::~TestRunner() {
    if (fail_count > 0) {
        cerr << fail_count << " unit tests failed. Terminate" << endl;
        exit(1);
    }
}

//class TestRunner {
//public:
//    template<class TestFunc>
//    void RunTest(TestFunc func, const string &test_name) {
//        try {
//            func();
//            cerr << test_name << " OK" << endl;
//        } catch (runtime_error &e) {
//            ++fail_count;
//            cerr << test_name << " fail: " << e.what() << endl;
//        }
//    }
//
//    ~TestRunner() {
//        if (fail_count > 0) {
//            cerr << fail_count << " unit tests failed. Terminate" << endl;
//            exit(1);
//        }
//    }
//
//private:
//    int fail_count = 0;
//};