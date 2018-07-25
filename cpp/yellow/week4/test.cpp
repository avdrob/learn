#include <iostream>
#include <string>

using namespace std;

class Base {
public:
	virtual void foo(int a)
	{
		cout << a << endl;
	}
};

class Derived : public Base {
public:
	virtual void foo(char a)
	{
		cout << a << endl;
	}
};

int main()
{
	Base base;
	Derived derived;

	Base *b = &base;
	Derived *d = &derived;

	int a[10] = {1, 2, 3, 4, 5, 6};
	for (int i : a)
		cout << i << ' ';

	return 0;
}
