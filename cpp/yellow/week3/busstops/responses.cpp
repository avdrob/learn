#include <ostream>
#include <vector>
#include <string>
#include <tuple>

#include "responses.h"

using namespace std;

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
