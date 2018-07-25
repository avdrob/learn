#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <tuple>

struct BusesForStopResponse {
	// Наполните полями эту структуру
	bool exists;
	std::vector<std::string> buses;
};

struct StopsForBusResponse {
	// Наполните полями эту структуру
	bool exists;
	std::vector<std::tuple<std::string, bool, std::vector<std::string>>> route;
};

struct AllBusesResponse {
	// Наполните полями эту структуру
	bool empty;
	std::vector<std::tuple<std::string, std::vector<std::string>>> bus;
};

std::ostream &operator<<(std::ostream &os, const BusesForStopResponse &r);
std::ostream &operator<<(std::ostream &os, const StopsForBusResponse &r);
std::ostream &operator<<(std::ostream &os, const AllBusesResponse &r);
