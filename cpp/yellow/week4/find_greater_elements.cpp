#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
	vector<T> res = {};
	auto border_it = find_if(elements.begin(), elements.end(),
			[border] (const T &it) {return it > border;});
	for (auto it = border_it; it != elements.end(); it++)
		res.push_back(*it);

	return res;
}
