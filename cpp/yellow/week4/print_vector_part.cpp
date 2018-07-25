#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
	auto it = find_if(numbers.begin(), numbers.end(),
			[] (int i) {return i < 0;});
	while (it > numbers.begin()) {
		it--;
		cout << *it << ' ';
	}
	cout << endl;
}
