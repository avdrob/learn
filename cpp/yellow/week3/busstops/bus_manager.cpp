#include <string>
#include <vector>
#include <tuple>

#include "bus_manager.h"
#include "responses.h"

using namespace std;

void BusManager::AddBus(const string &bus, const vector<string> &stops)
{
	// Реализуйте этот метод
	bus2stops[bus] = vector<string>(stops);
	for (const string &stop : bus2stops[bus])
		stop2buses[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const
{
	// Реализуйте этот метод
	BusesForStopResponse response;

	if (stop2buses.count(stop) == 0) {
		response.exists = false;
		response.buses = {};
	}
	else {
		response.exists = true;
		response.buses = vector<string>(stop2buses.at(stop));
	}

	return response;
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const
{
	// Реализуйте этот метод
	StopsForBusResponse response;
	bool interchange;
	vector<string> other_buses;

	response.route = {};

	if (bus2stops.count(bus) == 0) {
		response.exists = false;
		return response;
	}

	response.exists = true;
	for (const string &stop : bus2stops.at(bus)) {
		other_buses = {};

		if (stop2buses.at(stop).size() == 1)
			interchange = false;
		else {
			interchange = true;
			for (const string &other : stop2buses.at(stop))
				if (bus != other)
					other_buses.push_back(other);
		}

		response.route.push_back(make_tuple(stop, interchange,
						other_buses));
	}

	return response;
}

AllBusesResponse BusManager::GetAllBuses() const
{
	// Реализуйте этот метод
	AllBusesResponse response;
	string bus;
	vector<string> stops;

	response.bus = {};

	if (bus2stops.empty()) {
		response.empty = true;
		return response;
	}

	response.empty = false;
	for (const auto &bus_item : bus2stops) {
		stops = {};
		bus = bus_item.first;

		for (const string &stop : bus_item.second)
			stops.push_back(stop);

		response.bus.push_back(make_tuple(bus, stops));
	}

	return response;
}

