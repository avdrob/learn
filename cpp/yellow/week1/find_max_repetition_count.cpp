#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

/*
enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};
*/

bool operator<(const Region &lhs, const Region &rhs)
{
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
		tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
	map<Region, int> reg_counts;

	for (auto const &r : regions)
		reg_counts[r]++;

	int max = 0;
	for (auto const &c : reg_counts)
		if (c.second > max)
			max = c.second;

	return max;
}

/*
int main() {

	vector<Region> db1 = {
		{
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
		}, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
		}, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
		}, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
		}, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
		}
	};

	vector<Region> db2 = {
		{
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
		}, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
		}, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
		  89
		}, {
		  "Moscow",
		  "Toulouse",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
		}, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  31
		}
	};

	cout << FindMaxRepetitionCount(db1) << FindMaxRepetitionCount(db2)
		<< endl;

	return 0;
}
*/
