#include <iostream>
#include <tuple>

using namespace std;

int main()
{
	int a, b;

	tie(a, b) = make_tuple(12, 43);
	cout << a << ' ' << b << endl;

	return 0;
}
