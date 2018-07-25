#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
	uint64_t N, R, W, H, D, V, M;

	cin >> N >> R;
	M = 0;
	for (uint64_t i = 0; i < N; i++) {
		cin >> W >> H >> D;
		V = W * H * D;
		M += V * R;
	}

	cout << M << endl;

	return 0;
}
