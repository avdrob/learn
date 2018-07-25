#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int main()
{
	vector<int64_t> v;
	int64_t sum = 0, avg = 0;
	int N, K;

	cin >> N;
	for (unsigned i = 0; i < N; i++) {
		int64_t t;
		cin >> t;
		v.push_back(t);
		sum += t;
	}
	avg = sum / N;

	K = 0;
	for (unsigned i = 0; i < N; i++)
		if (v[i] > avg)
			K++;

	cout << K << endl;
	for (unsigned i = 0; i < N; i++)
		if (v[i] > avg)
			cout << i << ' ';
	cout << endl;


	return 0;
}
