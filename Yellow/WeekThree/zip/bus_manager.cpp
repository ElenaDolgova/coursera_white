#include "bus_manager.h"

#include <string>
#include <map>
#include <vector>

void BusManager::AddBus(const std::string &bus, const std::vector<std::string> &stops) {
    buses_to_stops[bus] = stops;
    for (const std::basic_string<char> &stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string &stop) const {
    BusesForStopResponse busesForStopResponse;
    if (stops_to_buses.count(stop) == 0) {
        busesForStopResponse.hasStop = false;
        return busesForStopResponse;
    }
    busesForStopResponse.hasStop = true;
    for (const std::string &bus : stops_to_buses.at(stop)) {
        busesForStopResponse.buses.push_back(bus);
    }
    return busesForStopResponse;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string &bus) const {
    StopsForBusResponse stopsForBusResponse;
    if (buses_to_stops.count(bus) == 0) {
        stopsForBusResponse.hasBus = false;
        return stopsForBusResponse;
    }
    stopsForBusResponse.hasBus = true;
    for (const std::string &stop : buses_to_stops.at(bus)) {
        stopsForBusResponse.stops.push_back(stop);
        if (stops_to_buses.at(stop).size() != 1) {
            for (const std::string &other_bus : stops_to_buses.at(stop)) {
                if (bus != other_bus) {
                    stopsForBusResponse.stops_buses[stop].push_back(other_bus);
                }
            }
        }
    }
    return stopsForBusResponse;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse allBusesResponse;
    if (buses_to_stops.empty()) {
        allBusesResponse.hasBuses = false;
        return allBusesResponse;
    }
    allBusesResponse.hasBuses = true;
    for (const auto &bus_item : buses_to_stops) {
        allBusesResponse.buses.push_back(bus_item.first);
        for (const std::string &stop : bus_item.second) {
            allBusesResponse.bus_stops[bus_item.first].push_back(stop);
        }
    }
    return allBusesResponse;
}
