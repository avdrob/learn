#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v)
{
	vector<int> w = v;
	int tmp;

	for (auto i = 0; i < w.size() / 2; i++) {
		tmp = w[i];
		w[i] = w[w.size() - 1 - i];
		w[w.size() - 1 - i] = tmp;
	}

	return w;
}
