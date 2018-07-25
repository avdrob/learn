#include <string>
#include <vector>

using namespace std;

bool IsPalindrom(string s)
{
	bool res = true;

	for (int i = 0; i < s.size() / 2; i++)
		if (s[i] != s[s.size() - (i+1)])
			res = false;
	return res;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
	vector<string> res;

	for (auto w : words)
		if (IsPalindrom(w) && w.size() >= minLength)
			res.push_back(w);

	return res;
}
