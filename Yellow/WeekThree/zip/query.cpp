#include "query.h"

#include <string>
#include <map>
#include <iostream>

std::istream &operator>>(std::istream &is, Query &q) {
    std::string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int count_stop;
        is >> count_stop;
        q.stops.clear();
        for (int i = 0; i < count_stop; ++i) {
            std::string stop;
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