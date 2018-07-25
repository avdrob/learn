#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	ifstream inp("input.txt");
	int n, m, v;

	inp >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m-1; j++) {
			inp >> v;
			inp.ignore(1);
			cout << setw(10) << v << ' ';
		}
		inp >> v;
		cout << setw(10) << v << endl;
	}

	return 0;
}
