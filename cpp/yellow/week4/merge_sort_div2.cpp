#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if ((range_end - range_begin) < 2)
		return;

	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	size_t const half_size = elements.size() / 2;
	MergeSort(elements.begin(), elements.begin() + half_size);
	MergeSort(elements.begin() + half_size, elements.end());
	merge(elements.begin(), elements.begin() + half_size,
		elements.begin() + half_size, elements.end(),
		range_begin);
}
