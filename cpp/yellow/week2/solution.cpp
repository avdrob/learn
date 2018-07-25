#include <iostream>
#include <ios>
#include <cassert>
#include <string>
#include <tuple>
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

istream &operator>>(istream &is, Query &q)
{
	// Реализуйте эту функцию
	string cmd;

	is >> cmd;
	if (cmd == "NEW_BUS")
		q.type = QueryType::NewBus;
	else if (cmd == "BUSES_FOR_STOP")
		q.type = QueryType::BusesForStop;
	else if (cmd == "STOPS_FOR_BUS")
		q.type = QueryType::StopsForBus;
	else if (cmd == "ALL_BUSES")
		q.type = QueryType::AllBuses;
	else
		assert(false);

	q.bus = q.stop = "";
	q.stops = {};
	if (q.type == QueryType::NewBus) {
		int stop_count;
		string stop;
		is >> q.bus;
		is >> stop_count;
		for (auto i = 0; i < stop_count; i++) {
			is >> stop;
			q.stops.push_back(stop);
		}
	}
	else if (q.type == QueryType::BusesForStop)
		is >> q.stop;
	else if (q.type == QueryType::StopsForBus)
		is >> q.bus;
	else if (q.type == QueryType::AllBuses) {}

	return is;
}

struct BusesForStopResponse {
	// Наполните полями эту структуру
	bool exists;
	vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
	// Реализуйте эту функцию
	if (r.exists == false)
		os << "No stop";
	else
		for (const string &bus: r.buses)
			os << bus << ' ';
	return os;
}

struct StopsForBusResponse {
	// Наполните полями эту структуру
	bool exists;
	vector<tuple<string, bool, vector<string>>> route;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
	// Реализуйте эту функцию
	if (r.exists == false) {
		os << "No bus";
		return os;
	}

	bool first = true;
	for (auto const &it : r.route) {
		if (!first)
			os << endl;
		first = false;

		os << "Stop " << get<0>(it) << ": ";
		if (get<1>(it) == false)
			os << "no interchange";
		else {
			for (const string &other : get<2>(it))
				os << other << ' ';
		}
	}

	return os;
}

struct AllBusesResponse {
	// Наполните полями эту структуру
	bool empty;
	vector<tuple<string, vector<string>>> bus;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
	// Реализуйте эту функцию
	if (r.empty == true) {
		os << "No buses";
		return os;
	}

	bool first = true;
	for (const auto &it : r.bus) {
		if (!first)
			os << endl;
		first = false;

		os << "Bus " << get<0>(it) << ": ";
		for (const string &stop : get<1>(it))
			os << stop << ' ';
	}

	return os;
}

class BusManager {
public:
	void AddBus(const string &bus, const vector<string> &stops)
	{
		// Реализуйте этот метод
		bus2stops[bus] = vector<string>(stops);
		for (const string &stop : bus2stops[bus])
			stop2buses[stop].push_back(bus);
		cerr << stops.size() << endl;
	}

	BusesForStopResponse GetBusesForStop(const string &stop) const
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

	StopsForBusResponse GetStopsForBus(const string &bus) const
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

	AllBusesResponse GetAllBuses() const
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

private:
	map<string, vector<string>> bus2stops, stop2buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main()
{
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
