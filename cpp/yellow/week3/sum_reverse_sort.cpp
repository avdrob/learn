#include <string>
#include <vector>
#include <algorithm>

#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y)
{
	return x + y;
}

string Reverse(string s)
{
	int len = s.size();
	string res = s;

	if (len <= 1)
		return res;

	for (auto i = 0; i < len / 2; i++) {
		char tmp = res[i];
		res[i] = res[len - i - 1];
		res[len - i - 1] = tmp;
	}

	return res;

}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}
