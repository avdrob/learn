#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream inp("input.txt");
	ofstream out("output.txt");
	string s;

	while (getline(inp, s))
		out << s << endl;

	return 0;
}
