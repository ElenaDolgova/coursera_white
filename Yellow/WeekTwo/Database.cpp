#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class WrongDateFormat : public std::exception {
    std::string _msg;
public:
    explicit WrongDateFormat(std::string msg) : _msg(std::move(msg)) {}
};

class MonthValueInvalid : public std::exception {
    std::string _msg;
public:
    explicit MonthValueInvalid(std::string msg) : _msg(std::move(msg)) {}

    const char *what() {
        return _msg.c_str();
    }
};

class DayValueInvalid : public std::exception {
    std::string _msg;
public:
    explicit DayValueInvalid(std::string msg) : _msg(std::move(msg)) {}

    const char *what() {
        return _msg.c_str();
    }

};

class Date {
private:
    bool hasMinus;
    string year;
    string month;
    string day;

public:
    static bool has_only_digits(const string &s) {
        return s.find_first_not_of("0123456789") == string::npos;
    }

    Date(string year_, const string &month_, const string &day_, bool hasMinus_) {
        int intMonth = 0;
        int intDay = 0;
        try {
            intMonth = std::stoi(month_);
            intDay = std::stoi(day_);
        } catch (exception &e) {
            throw WrongDateFormat("");
        }

        if (intMonth <= 0 || intMonth > 12) {
            throw MonthValueInvalid(month_);
        }

        if (intDay <= 0 || intDay > 31) {
            throw DayValueInvalid(day_);
        }

        if (!has_only_digits(month_) || !has_only_digits(day_)) {
            throw WrongDateFormat("");
        }

        if (hasMinus_) {
            string s = year_.substr(1, year_.size());
            if (!has_only_digits(s)) {
                throw WrongDateFormat("");
            }
        } else {
            if (!has_only_digits(year_)) {
                throw WrongDateFormat("");
            }
        }


        this->year = std::move(year_);
        this->month = month_;
        this->day = day_;
        this->hasMinus = hasMinus_;

    }

public:

    [[nodiscard]] const string &getYear() const {
        return year;
    }

    [[nodiscard]] string getMonth() const {
        return month;
    }

    [[nodiscard]] string getDay() const {
        return day;
    }

    [[nodiscard]] bool isHasMinus() const {
        return hasMinus;
    }

    void print() const {
        string str;
        unsigned long yearSize = year.size();
        if (yearSize < 4) {
            str.append(std::string(4 - yearSize, '0')).append(year).append("-");
        } else {
            str.append(year).append("-");
        }

        unsigned long monthSize = month.size();
        if (monthSize < 2) {
            str.append(std::string(2 - monthSize, '0')).append(month).append("-");
        } else {
            str.append(month).append("-");
        }

        unsigned long daySize = day.size();
        if (daySize < 2) {
            str.append(std::string(2 - daySize, '0')).append(day);
        } else {
            str.append(day);
        }
        std::cout << str;
    }

    bool operator==(const Date &rhs) const {
        return hasMinus == rhs.hasMinus &&
               year == rhs.year &&
               month == rhs.month &&
               day == rhs.day;
    }

    bool operator!=(const Date &rhs) const {
        return !(rhs == *this);
    }
};

bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.isHasMinus() && !rhs.isHasMinus()) {
        return true;
    } else if (!lhs.isHasMinus() && rhs.isHasMinus()) {
        return false;
    }

    bool withOutSign;

    if (lhs.getYear() < rhs.getYear()) {
        withOutSign = true;
    } else if (lhs.getYear() > rhs.getYear()) {
        withOutSign = false;
    } else {
        if (lhs.getMonth() < rhs.getMonth()) {
            withOutSign = true;
        } else if (lhs.getMonth() > rhs.getMonth()) {
            withOutSign = false;
        } else {
            withOutSign = lhs.getDay() < rhs.getDay();
        }
    }

//    if (lhs.isHasMinus() && rhs.isHasMinus()) {
//        withOutSign = !withOutSign;
//    }

    return withOutSign;
}

class Database {
private:
    map<Date, set<string>> dBdata;

    static void replaceAll(std::string &str, const std::string &from, const std::string &to) {
        if (from.empty())
            return;
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

    static string replace(const string &key) {
        if (key.empty()) {
            throw WrongDateFormat("pisos");
        }
        string s = key;
        replaceAll(s, "-+", "-");
        replaceAll(s, "--", "+-");

        bool firstIsNegative = false;
        if (s[0] == '-' && isdigit(s[1])) {
            firstIsNegative = true;
        }

        if (s.find("--") != std::string::npos) {
            throw WrongDateFormat("pisos");
        }
        replaceAll(s, "+-", "++");

        replaceAll(s, "-", " ");
        replaceAll(s, "++", " -");

        if (firstIsNegative) {
            s = '-' + s;
            replaceAll(s, "- ", "-");
        }

        return s;
    }


    static std::vector<std::string> splitByDlm(string &command, const char &dlm) {
        istringstream iss(command);
        std::string item;
        std::vector<std::string> elems;
        while (std::getline(iss, item, dlm)) {
            elems.push_back(item);
        }
        return elems;
    }

    static Date parseData(const string &key_) {
        string replaceString = replace(key_);

        if (replaceString.empty()) {
            throw WrongDateFormat("pisos");
        }

        std::vector<std::string> elems = splitByDlm(replaceString, ' ');
        if (elems.size() != 3) {
            throw WrongDateFormat("pisos");
        }

        Date date = Date(elems[0], elems[1], elems[2], elems[0][0] == '-');

        return date;
    }

    void printValues(const Date &date, bool needKey) {
        if (dBdata.count(date) <= 0) {
            cout << "\n";
            return;
        }
        if (needKey) {
            for (string const &value : dBdata[date]) {
                date.print();
                std::cout << " " << value << "\n";
            }
        } else {
            for (string const &value : dBdata[date]) {
                std::cout << value << "\n";
            }
        }
    }

    void print() {
        for (const pair<const Date, set<basic_string<char>>> &elem : dBdata) {
            Date date = elem.first;
            printValues(date, true);
        }
    }

    bool AddEvent(const Date &date, const string &value) {
        if (dBdata.count(date) > 0) {
            dBdata[date].insert(value);
        } else {
            dBdata[date] = {value};
        }
        return true;
    }

    void DeleteEvent(const Date &date, const string &value) {
        if (dBdata.count(date) > 0) {
            int before = dBdata[date].size();
            dBdata[date].erase(value);
            int after = dBdata[date].size();
            if (before == after) {
                std::cout << "Event not found\n";
                return;
            }
            if (dBdata[date].empty()) {
                dBdata.erase(date);
            }
            std::cout << "Deleted successfully\n";
        } else {
            std::cout << "Event not found\n";
            return;
        }

    }

    void DeleteDate(const Date &date) {
        if (dBdata.count(date) == 0) {
            printf("Deleted %d events\n", 0);
            return;
        }
        unsigned long i = dBdata[date].size();
        dBdata.erase(date);
        printf("Deleted %lu events\n", i);
    }

    void Find(const Date &date) {
        printValues(date, false);
    }

public:
    void doAction(const std::vector<std::string> &commands) {
        string data;
        if (commands.size() != 1) {
            data = commands[1];
        }

        if (commands[0] == "Add") {
            string event = commands[2];
            Date newDate = parseData(data);
            if (!AddEvent(newDate, event)) {
                printf("Wrong date format: %s\n", data.c_str());
                exit(0);
            }
        } else if (commands[0] == "Del") {
            Date newDate = parseData(data);
            if (commands.size() < 3) {
                DeleteDate(newDate);
            } else {
                string event = commands[2];
                DeleteEvent(newDate, event);
            }
        } else if (commands[0] == "Find") {
            Date newData = parseData(data);
            Find(newData);
        } else if (commands[0] == "Print") {
            print();
        } else {
            printf("Unknown command: %s", commands[0].c_str());
            exit(0);
        }
    }

    void parseCommand(string &str) {
        std::vector<std::string> commands;
        commands = splitByDlm(str, ' ');
        try {
            doAction(commands);
        } catch (WrongDateFormat &e) {
            printf("Wrong date format: %s\n", commands[1].c_str()); // ?
            exit(0);
        } catch (MonthValueInvalid &e) {
            printf("Month value is invalid: %s\n", e.what());
            exit(0);
        } catch (DayValueInvalid &e) {
            printf("Day value is invalid: %s\n", e.what());
            exit(0);
        }
    }
};


int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
//        try {
        if (!command.empty()) {
            db.parseCommand(command);
        }
//        } catch (exception &e) {
//        }
    }

    return 0;
}
