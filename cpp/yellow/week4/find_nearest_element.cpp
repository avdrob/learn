#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border)
{
	auto it = numbers.lower_bound(border);

	if (numbers.size() == 0)
		return numbers.end();

	if (it == numbers.end())
		return prev(it);

	if (it == numbers.begin())
		return it;

	if ((border - *prev(it)) <= (*it - border))
		return prev(it);
	else
		return it;
}
