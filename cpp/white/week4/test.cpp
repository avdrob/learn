#include <set>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	string buf;
	int n;

	cin >> buf;
	istringstream iss(buf);
	iss >> n;

	if (iss.eof())
		cout << "EOF";
	else {
		iss >> buf;
		cout << buf;
	}


	return 0;
}
