#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q) {
    string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int count_stop;
        is >> count_stop;
        q.stops.clear();
        for (int i = 0; i < count_stop; ++i) {
            string stop;
            is >> stop;
            q.stops.push_back(stop);
        }
    } else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    bool hasStop;
    vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (!r.hasStop) {
        os << "No stop";
        return os;
    }

    bool isFirst = true;
    for (const string &bus: r.buses) {
        if (isFirst) {
            os << bus;
            isFirst = false;
        } else {
            os << " " << bus;
        }
    }

    return os;
}

struct StopsForBusResponse {
    bool hasBus;
    vector<string> stops;
    map<string, vector<string>> stops_buses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if (!r.hasBus) {
        os << "No bus";
        return os;
    }

    int count = 0;
    for (const auto &stop: r.stops) {
        os << "Stop " << stop << ":";

        if (r.stops_buses.count(stop) == 0) {
            os << " no interchange";
        } else {
            for (const auto &bus: r.stops_buses.at(stop)) {
                os << " " << bus;
            }
        }
        if (count != r.stops.size() - 1) {
            os << endl;
        }
        ++count;
    }

    return os;
}

struct AllBusesResponse {
    bool hasBuses;
    vector<string> buses;
    map<string, vector<string>> bus_stops;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (!r.hasBuses) {
        os << "No buses";
        return os;
    }

    int count = 0;
    for (const auto &bus: r.buses) {
        os << "Bus " << bus << ":";
        for (const auto &stop: r.bus_stops.at(bus)) {
            os << " " << stop;
        }
        if (count != r.buses.size() - 1) {
            os << endl;
        }
        ++count;
    }

    return os;
}

class BusManager {
public:
    map<string, vector<string>> buses_to_stops, stops_to_buses;

    void AddBus(const string &bus, const vector<string> &stops) {
        buses_to_stops[bus] = stops;
        for (const basic_string<char> &stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const {
        BusesForStopResponse busesForStopResponse;
        if (stops_to_buses.count(stop) == 0) {
            busesForStopResponse.hasStop = false;
            return busesForStopResponse;
        }
        busesForStopResponse.hasStop = true;
        for (const string &bus : stops_to_buses.at(stop)) {
            busesForStopResponse.buses.push_back(bus);
        }
        return busesForStopResponse;

    }

    StopsForBusResponse GetStopsForBus(const string &bus) const {
        StopsForBusResponse stopsForBusResponse;
        if (buses_to_stops.count(bus) == 0) {
            stopsForBusResponse.hasBus = false;
            return stopsForBusResponse;
        }
        stopsForBusResponse.hasBus = true;
        for (const string &stop : buses_to_stops.at(bus)) {
            stopsForBusResponse.stops.push_back(stop);
            if (stops_to_buses.at(stop).size() != 1) {
                for (const string &other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        stopsForBusResponse.stops_buses[stop].push_back(other_bus);
                    }
                }
            }
        }
        return stopsForBusResponse;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse allBusesResponse;
        if (buses_to_stops.empty()) {
            allBusesResponse.hasBuses = false;
            return allBusesResponse;
        }
        allBusesResponse.hasBuses = true;
        for (const auto &bus_item : buses_to_stops) {
            allBusesResponse.buses.push_back(bus_item.first);
            for (const string &stop : bus_item.second) {
                allBusesResponse.bus_stops[bus_item.first].push_back(stop);
            }
        }
        return allBusesResponse;
    }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
