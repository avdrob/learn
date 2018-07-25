#include <map>
#include <iostream>
#include <exception>

using namespace std;

template <typename Key_t, typename Value_t>
Value_t &GetRefStrict(map<Key_t, Value_t> &m, Key_t k)
{
	if (m.count(k))
		return m.at(k);
	else
		throw runtime_error("");
}
