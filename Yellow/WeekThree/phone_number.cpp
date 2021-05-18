#include <stdexcept>
#include <string>

#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
    istringstream is(international_number);

    char sign = is.get();
    getline(is, country_code_, '-');
    getline(is, city_code_, '-');
    getline(is, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: "
        + international_number);
    }

//
//    unsigned long findFirstMinus = international_number.find('-');
//    if (international_number.find('+') == std::string::npos ||
//        findFirstMinus == std::string::npos) {
//        throw std::invalid_argument("");
//    }
//
//    this->country_code_ = international_number.substr(1, findFirstMinus - 1);
//
//    if (this->country_code_.empty()) {
//        throw std::invalid_argument("");
//    }
//
//    string strAfterFirstMinus = international_number.substr(findFirstMinus + 1, international_number.length());
//
//    unsigned long findSecondMinus = strAfterFirstMinus.find('-');
//
//    if (findSecondMinus == std::string::npos) {
//        throw std::invalid_argument("");
//    }
//
//    this->city_code_ = strAfterFirstMinus.substr(0, findSecondMinus);
//    if (this->city_code_.empty()) {
//        throw std::invalid_argument("");
//    }
//    this->local_number_ = strAfterFirstMinus.substr(findSecondMinus + 1, strAfterFirstMinus.length());
//    if (this->local_number_.empty()) {
//        throw std::invalid_argument("");
//    }
}

string PhoneNumber::GetCountryCode() const {
    return this->country_code_;
}

string PhoneNumber::GetCityCode() const {
    return this->city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return this->local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    string internalNumber;
    internalNumber.append("+")
            .append(this->country_code_)
            .append("-")
            .append(this->city_code_)
            .append("-")
            .append(this->local_number_);
    return internalNumber;
}
