#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
	map<string, vector<string>> buses, stops;
	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {
		string cmd;
		cin >> cmd;

		if (cmd == "NEW_BUS") {
			string bus, stop;
			cin >> bus;
			int cnt;
			cin >> cnt;

			for (int j = 0; j < cnt; j++) {
				cin >> stop;
				buses[bus].push_back(stop);
				stops[stop].push_back(bus);
			}

			continue;
		}

		if (cmd == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;

			if (stops.count(stop) == 0) {
				cout << "No stop" << endl;
				continue;
			}

			for (const auto& bus : stops[stop])
				cout << bus << ' ';
			cout << endl;

			continue;
		}

		if (cmd == "STOPS_FOR_BUS") {
			string bus;
			cin >> bus;

			if (buses.count(bus) == 0) {
				cout << "No bus" << endl;
				continue;
			}

			for (const auto& stop : buses[bus]) {
				cout << "Stop " << stop << ": ";
				if (stops[stop].size() == 1) {
					cout << "no interchange" << endl;
					continue;
				}
				for (const auto& b : stops[stop])
					if (b != bus)
						cout << b << ' ';
				cout << endl;
			}

			continue;
		}

		if (cmd == "ALL_BUSES") {
			if (buses.size() == 0) {
				cout << "No buses" << endl;
				continue;
			}

			for (const auto& bitem : buses) {
				cout << "Bus " << bitem.first << ": ";
				for (const auto& stop : bitem.second)
					cout << stop << ' ';
				cout << endl;
			}

			continue;
		}
	}

	return 0;
}
