#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements)
{
	sort(elements.begin(), elements.end());
	elements.erase(unique(elements.begin(), elements.end()), elements.end());
}
