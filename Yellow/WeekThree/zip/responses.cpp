#include "responses.h"

std::ostream &operator<<(std::ostream &os, const BusesForStopResponse &r) {
    if (!r.hasStop) {
        os << "No stop";
        return os;
    }

    bool isFirst = true;
    for (const std::string &bus: r.buses) {
        if (isFirst) {
            os << bus;
            isFirst = false;
        } else {
            os << " " << bus;
        }
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, const StopsForBusResponse &r) {
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
            os << std::endl;
        }
        ++count;
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, const AllBusesResponse &r) {
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
            os << std::endl;
        }
        ++count;
    }

    return os;
}

