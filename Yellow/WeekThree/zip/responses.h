#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

struct BusesForStopResponse {
    bool hasStop;
    std::vector<std::string> buses;
};

std::ostream &operator<<(std::ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse {
    bool hasBus;
    std::vector<std::string> stops;
    std::map<std::string, std::vector<std::string>> stops_buses;
};

std::ostream &operator<<(std::ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse {
    bool hasBuses;
    std::vector<std::string> buses;
    std::map<std::string, std::vector<std::string>> bus_stops;
};

std::ostream &operator<<(std::ostream &os, const AllBusesResponse &r);
