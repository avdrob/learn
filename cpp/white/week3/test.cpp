#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Piu {
	public:
		Piu() {cout << "Default constructor" << endl;};
		~Piu() {cout << "Destructor" << endl;};
		int x;	
};

void print_piu(Piu p)
{
	cout << p.x << endl;
}

int main()
{
	Piu p = {};
	print_piu(p);
	return 0;
}
