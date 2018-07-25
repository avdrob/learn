#include <vector>
#include <string>

using namespace std;

void MoveStrings(vector<string>& src, vector<string>& dest)
{
	for (auto s : src)
		dest.push_back(s);
	src.clear();
}
