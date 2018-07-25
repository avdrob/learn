#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	ifstream inp("input.txt");
	double v;

	cout << fixed << setprecision(3);
	while (inp >> v)
		cout << v << endl;

	return 0;
}
