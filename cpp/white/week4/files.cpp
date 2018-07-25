#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream inp("input.txt");
	string s;

	while (getline(inp, s))
		cout << s << endl;

	return 0;
}
