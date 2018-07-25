#include <istream>
#include <string>
#include <vector>
#include <cassert>

#include "query.h"

using namespace std;

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
