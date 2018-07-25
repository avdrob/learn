#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
		const string& hint)
{
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u
			 << " hint: " << hint;
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint)
{
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name)
	{
		try {
		func();
		cerr << test_name << " OK" << endl;
		}
		catch (runtime_error& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
	}

	~TestRunner()
	{
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate"
				<< endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

extern int GetDistinctRealRootCount(double a, double b, double c);

void TestFull()
{
	AssertEqual(GetDistinctRealRootCount(2, 5, -3), 2, "Full square eq");
}

void TestNegD()
{
	AssertEqual(GetDistinctRealRootCount(2, 1, 2), 0, "Negative discriminant");
}

void TestSqr()
{
	AssertEqual(GetDistinctRealRootCount(4, 16, 16), 1, "Square trinomial");
}

void TestIncomplete()
{
	AssertEqual(GetDistinctRealRootCount(3, -12, 0), 2, "Incomplete square eq");
}

void TestLin()
{
	AssertEqual(GetDistinctRealRootCount(0, -2, 1), 1, "Linear eq");
}

void TestLinNoroots()
{
	AssertEqual(GetDistinctRealRootCount(0, 0, 12), 0, "No x in eq");
}

void TestAll(void)
{
	TestRunner tr;
	tr.RunTest(TestFull, "TestFull");
	tr.RunTest(TestNegD, "TestNegD");
	tr.RunTest(TestSqr, "TestSqr");
	tr.RunTest(TestIncomplete, "TestIncomplete");
	tr.RunTest(TestLin, "TestLin");
	tr.RunTest(TestLinNoroots, "TestLinNoroots");

}

int main()
{
	TestAll();

	return 0;
}
