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
	size_t const third_size = elements.size() / 3;

	MergeSort(elements.begin(), elements.begin() + third_size);
	MergeSort(elements.begin() + third_size, elements.begin() + 2 * third_size);
	MergeSort(elements.begin() + 2 * third_size, elements.end());

	vector<typename RandomIt::value_type> tmp = {};
	merge(elements.begin(), elements.begin() + third_size,
		elements.begin() + third_size, elements.begin() + 2 * third_size,
		back_inserter(tmp));
	merge(tmp.begin(), tmp.end(), elements.begin() + 2 * third_size,
			elements.end(), range_begin);
}
