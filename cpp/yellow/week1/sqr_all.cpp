#include <vector>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

template <typename T1, typename T2>
pair<T1, T2> operator*(const pair<T1, T2> &p1, const pair<T1, T2> &p2)
{
	return make_pair(p1.first * p2.first, p1.second * p2.second);
}

template <typename Key_t, typename Value_t>
map<Key_t, Value_t> operator*(const map<Key_t, Value_t> &m1,
				const map<Key_t, Value_t> &m2)
{
	map<Key_t, Value_t> res = m1;
	for (auto &it : res)
		it.second = it.second * m2.at(it.first);
	return res;
}

template <typename T> vector<T> operator*(const vector<T> &v1, const vector<T> &v2)
{
	vector<T> res(v1.size());
	for (long unsigned int i = 0; i < v1.size(); i++)
		res[i] = v1[i] * v2[i];
	return res;
}

template <typename T> auto Sqr(const T &v)
{
	return v * v;
}

/*
int main()
{
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v))
		cout << ' ' << x;
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = { {4, {2, 2}}, {7, {4, 3}} };
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs))
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;

	return 0;
}
*/
