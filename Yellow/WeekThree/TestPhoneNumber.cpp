#include "../WeekTwo/TestFramework.cpp"
#include "phone_number.cpp"


void AssertInvalidArgument(const string &phone, const std::string &hint) {
    try {
        PhoneNumber p = PhoneNumber(phone);
    } catch (std::invalid_argument &e) {
        return;
    }

    std::cerr << "Has not catch exception " << hint << endl;
}

void TestCountryCode() {
    AssertEqual(PhoneNumber("+323-22-460002").GetCountryCode(), "323", "TestCountryCode 323");
    AssertEqual(PhoneNumber("+7-495-1112233").GetCountryCode(), "7", "TestCountryCode 7");
    AssertEqual(PhoneNumber("+1-2-coursera-cpp").GetCountryCode(), "1", "TestCountryCode 1");
}

void TestHasNoPlus() {
    AssertInvalidArgument("323-22-460002", "TestHasNoPlus no");
    AssertInvalidArgument("-323-22-460002", "TestHasNoPlus -");
}

void TestCityCode() {
    AssertEqual(PhoneNumber("+323-22-460002").GetCityCode(), "22", "TestCityCode 22");
}

void TestLocalNumber() {
    AssertEqual(PhoneNumber("+7-495-111-22-33").GetLocalNumber(), "111-22-33", "TestLocalNumber 111-22-33");
    AssertEqual(PhoneNumber("+323-22-460002").GetLocalNumber(), "460002", "TestLocalNumber 460002");
    AssertEqual(PhoneNumber("+1-2-coursera-cpp").GetLocalNumber(), "coursera-cpp", "TestLocalNumber coursera-cpp");
}

void TestEmpty() {
    AssertInvalidArgument("+7-1233", "TestHasNoPlus no");
    AssertInvalidArgument("+-1233-45", "TestHasNoPlus no");
    AssertInvalidArgument("+7--45", "TestHasNoPlus no");
}

void TestInternalNumber() {
    AssertEqual(PhoneNumber("+1-2-coursera-cpp").GetInternationalNumber(), "+1-2-coursera-cpp", "TestLocalNumber coursera-cpp");
}

int main() {
    TestRunner tr;
    tr.RunTest(TestCountryCode, "TestCountryCode");
    tr.RunTest(TestHasNoPlus, "TestHasNoPlus");
    tr.RunTest(TestCityCode, "TestCityCode");
    tr.RunTest(TestLocalNumber, "TestLocalNumber");
    tr.RunTest(TestEmpty, "TestEmpty");
    tr.RunTest(TestInternalNumber, "TestInternalNumber");
}
